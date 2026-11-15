#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MIN -10
#define MAX 35
#define INTERVAL 2

int main(void) {

    srand(time(NULL));

    while (1) {

        double T = MIN + (MAX - MIN) *
                   ((double)rand() / RAND_MAX);

        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        char date[100];

        strftime(date, sizeof(date),
                 "%a %b %e %H:%M:%S %Z %Y", local);

        printf("Temperature = %1.2f @%s\n", T, date);

        fflush(stdout);

        sleep(INTERVAL);
    }

    return 0;
}