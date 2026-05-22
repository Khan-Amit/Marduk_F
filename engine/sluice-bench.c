#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Marduk_F
 Sluice-Bench™ Telemetry Processor

 Designed and Developed by:
 Seliim Ahmed
*/

typedef struct {

    int piu;
    int solar;
    int battery;

} TelemetryData;

void initializeSluiceBench() {

    printf("=====================================\n");
    printf(" SLUICE-BENCH INITIALIZED\n");
    printf(" Renewable Telemetry Processor\n");
    printf("=====================================\n");

}

void processTelemetry(TelemetryData data) {

    printf("[PROCESSING] Incoming Telemetry Stream\n");

    /* PIU FILTER */

    if (data.piu > 85) {

        printf("[PIU] HIGH STABILITY\n");

    } else {

        printf("[PIU] MODERATE LOAD\n");

    }

    /* SOLAR FILTER */

    if (data.solar > 80) {

        printf("[SOLAR] OPTIMAL HARVEST\n");

    } else {

        printf("[SOLAR] LOW INPUT\n");

    }

    /* BATTERY FILTER */

    if (data.battery > 75) {

        printf("[BATTERY] STORAGE STABLE\n");

    } else {

        printf("[BATTERY] LOW STORAGE WARNING\n");

    }

}

void telemetryIndex(TelemetryData data) {

    printf("\n[INDEX REPORT]\n");

    printf("PIU INDEX: %d\n", data.piu);

    printf("SOLAR INDEX: %d\n", data.solar);

    printf("BATTERY INDEX: %d\n", data.battery);

}

int main() {

    TelemetryData currentTelemetry;

    currentTelemetry.piu = 84;

    currentTelemetry.solar = 88;

    currentTelemetry.battery = 91;

    initializeSluiceBench();

    processTelemetry(currentTelemetry);

    telemetryIndex(currentTelemetry);

    printf("\n[STATUS] Sluice-Bench Active\n");

    return 0;
}
