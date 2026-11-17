#include "datamgr.h"
#include <stdio.h>



uint16_t room_id;
uint16_t sensor_id;

void datamgr_parse_sensor_files(FILE *p_map,FILE *p_data){
unsigned int temp_room_id;
unsigned int temp_sensor_id;
int temp_count = 0;
while(fscanf(p_map, "%u %u", &temp_room_id, &temp_sensor_id)==2){
    temp_count=temp_count+1;
if (temp_room_id == 0 || temp_room_id > UINT16_MAX ||
    temp_sensor_id == 0 || temp_sensor_id > UINT16_MAX){
        fprintf(stderr, "Invalid ID at row %d\n" ,temp_count);
        
        continue;
    }
    uint16_t room_id = (uint16_t)temp_room_id;
    uint16_t sensor_id = (uint16_t)temp_sensor_id;   
    printf("Room %u has sensor %u\n",
       (unsigned int)room_id,
       (unsigned int)sensor_id);
}


}