#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 Marduk_F
 Collector.c — REAL-TIME DATA INGESTION LAYER

 Fetches live weather data and converts it into field telemetry
*/

#define API_URL "https://wttr.in/Singapore?format=j1"
#define OUTPUT_FILE "../telemetry/telemetry.json"

/* helper: write raw JSON into file */
void write_file(const char *data) {
    FILE *f = fopen(OUTPUT_FILE, "w");
    if (!f) {
        printf("ERROR: cannot open telemetry.json\n");
        return;
    }

    fprintf(f, "%s", data);
    fclose(f);
}

/* fetch API using system curl */
void fetch_data(char *buffer, size_t size) {
    FILE *fp;
    char cmd[] = "curl -s https://wttr.in/Singapore?format=j1";

    fp = popen(cmd, "r");
    if (!fp) {
        strcpy(buffer, "{\"error\":\"curl failed\"}");
        return;
    }

    fread(buffer, 1, size - 1, fp);
    pclose(fp);
}

/* minimal transform: wrap raw API into field format */
void transform_to_field(const char *input, char *output) {
    snprintf(output, 8192,
        "{\n"
        "  \"source\": \"wttr.in\",\n"
        "  \"raw\": %s\n"
        "}\n",
        input
    );
}

int main() {
    char raw[8192];
    char transformed[16384];

    printf("Marduk_F Collector started (REAL-TIME MODE)\n");

    while (1) {
        memset(raw, 0, sizeof(raw));
        memset(transformed, 0, sizeof(transformed));

        fetch_data(raw, sizeof(raw));
        transform_to_field(raw, transformed);
        write_file(transformed);

        printf("Telemetry updated.\n");

        sleep(5); // 5-second real-time tick
    }

    return 0;
}
