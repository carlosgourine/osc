#include "datamgr.h"
#include <stdio.h>
#include "lib/dplist.h"
#include <stdlib.h>


typedef struct{
    sensor_id_t sensor_id;
    uint16_t room_id;
    sensor_value_t temperatures[RUN_AVG_LENGTH];
    int count;
    int next_index;
    sensor_value_t sum;
    sensor_ts_t last_modified;
} element_t;
static dplist_t *sensor_list = NULL;
static void *sensor_copy(void *source){
    element_t *copy=malloc(sizeof(element_t));
    ERROR_HANDLER(copy==NULL,"Memory allocation failed");
    *copy=*(element_t *)source;
    return copy;
}

static void sensor_free(void **element){
    free(*element);
    *element=NULL;
}

static int sensor_compare(void *a,void *b){
    element_t *sensor_a=(element_t *)a;
    element_t *sensor_b=(element_t *)b;
    if(sensor_a->sensor_id<sensor_b->sensor_id)
        return -1;
    if(sensor_a->sensor_id>sensor_b->sensor_id)
        return 1;
    return 0;
}

static element_t *find_sensor(sensor_id_t id){
    ERROR_HANDLER(sensor_list==NULL,"Sensor list not initialized");

    element_t search={0};
    search.sensor_id=id;

    int index=dpl_get_index_of_element(sensor_list,&search);

    ERROR_HANDLER(index==-1,"Invalid sensor ID");

    return (element_t *)dpl_get_element_at_index(sensor_list,index);
}

void datamgr_parse_sensor_files(FILE *map,FILE *data){

    sensor_list=dpl_create(sensor_copy,sensor_free,sensor_compare);

    uint16_t room_id;
    uint16_t sensor_id;
    unsigned int temp_room_id;
    unsigned int temp_sensor_id;
    int temp_count=0;

    while(fscanf(map,"%u %u",&temp_room_id,&temp_sensor_id)==2){
    temp_count=temp_count+1;
if (temp_room_id == 0 || temp_room_id > UINT16_MAX ||
    temp_sensor_id == 0 || temp_sensor_id > UINT16_MAX){
        fprintf(stderr, "Invalid ID at row %d\n" ,temp_count);
        continue;
    }
   

    
room_id=(uint16_t)temp_room_id;
sensor_id=(uint16_t)temp_sensor_id;

element_t sensor={0};
sensor.room_id=room_id;
sensor.sensor_id=sensor_id;

sensor_list=dpl_insert_at_index(sensor_list,&sensor,dpl_size(sensor_list),true);

}
sensor_id_t measurement_id;
sensor_value_t measurement_temp;
sensor_ts_t measurement_time;
while(fread(&measurement_id,sizeof(measurement_id),1,data)==1){
if(fread(&measurement_temp,sizeof(measurement_temp),1,data)!=1){
    fprintf(stderr,"Error reading temperature\n");
    break;
}

if(fread(&measurement_time,sizeof(measurement_time),1,data)!=1){
    fprintf(stderr,"Error reading timestamp\n");
    break;
}
element_t zoek={0};
zoek.sensor_id=measurement_id;

int index=dpl_get_index_of_element(sensor_list,&zoek);

if(index==-1){
    fprintf(stderr,"Unknown sensor ID: %u\n",(unsigned int)measurement_id);
    continue;
}

element_t *sensor=(element_t *)dpl_get_element_at_index(sensor_list,index);

if(sensor->count==RUN_AVG_LENGTH){
    sensor->sum-=sensor->temperatures[sensor->next_index];
}
else{
    sensor->count++;
}

sensor->temperatures[sensor->next_index]=measurement_temp;
sensor->sum+=measurement_temp;

sensor->next_index=(sensor->next_index+1)%RUN_AVG_LENGTH;
sensor->last_modified=measurement_time;
if(sensor->count==RUN_AVG_LENGTH){
    sensor_value_t avg=sensor->sum/RUN_AVG_LENGTH;

    if(avg<SET_MIN_TEMP){
        fprintf(stderr,"Room %u is too cold: %.2f C\n",
                (unsigned int)sensor->room_id,avg);
    }

    if(avg>SET_MAX_TEMP){
        fprintf(stderr,"Room %u is too hot: %.2f C\n",
                (unsigned int)sensor->room_id,avg);
    }
}

}
}
void datamgr_free(){

        dpl_free( &sensor_list, true);}

uint16_t datamgr_get_room_id(sensor_id_t sensor_id){
    element_t *sensor=find_sensor(sensor_id);
    return sensor->room_id;
}

sensor_value_t datamgr_get_avg(sensor_id_t sensor_id){
    element_t *sensor=find_sensor(sensor_id);

    if(sensor->count<RUN_AVG_LENGTH){
        return 0;
    }

    return sensor->sum/RUN_AVG_LENGTH;
}

time_t datamgr_get_last_modified(sensor_id_t sensor_id){
    element_t *sensor=find_sensor(sensor_id);
    return sensor->last_modified;
}

int datamgr_get_total_sensors(){
    if(sensor_list==NULL){
        return 0;
    }

    return dpl_size(sensor_list);
}

