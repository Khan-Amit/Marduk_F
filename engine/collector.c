#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 Marduk_F
 ENKOMOS Renewable Telemetry System™

 Designed and Developed by:
 Seliim Ahmed

 Experimental Collector Engine
*/

void initializeCollector() {

    printf("=====================================\n");
    printf(" Marduk_F TELEMETRY COLLECTOR\n");
    printf(" ENKOMOS Renewable System\n");
    printf("=====================================\n");

}

void weatherCollector() {

    printf("[COLLECTOR] Weather API Connected\n");

}

void telemetryCollector() {

    int piu = rand() % 20 + 75;

    int solar = rand() % 25 + 70;

    int battery = rand() % 15 + 80;

    printf("[PIU] %d%%\n", piu);

    printf("[SOLAR] %d%%\n", solar);

    printf("[BATTERY] %d%%\n", battery);

}

int main() {

    srand(time(NULL));

    initializeCollector();

    weatherCollector();

    telemetryCollector();

    printf("[STATUS] Collector Engine Active\n");

    return 0;
}
