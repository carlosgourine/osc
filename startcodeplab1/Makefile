
all: main.c datamgr.c datamgr.h config.h lib/dplist.c lib/dplist.h
	gcc -g -Wall -Wextra -DSET_MIN_TEMP=15 -DSET_MAX_TEMP=25 main.c datamgr.c lib/dplist.c -o main.out

gen: config.h file_creator.c 
	gcc -g file_creator.c config.h -o gen.out

gendebug: config.h file_creator.c
	gcc -g file_creator.c config.h -o gendebug.out -DDEBUG