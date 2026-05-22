#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 Marduk_F
 Collector.c — Real Ingestion Layer (Linked with Pre-Collector)
*/

#define INPUT_FILE "../telemetry/pre_filtered.json"
#define OUTPUT_FILE "../telemetry/telemetry.json"

/* read file */
char* read_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

/* wrap into telemetry format */
void wrap_telemetry(const char *input, char *output) {
    snprintf(output, 4096,
        "{\n"
        "  \"source\": \"pre_collector\",\n"
        "  \"payload\": %s\n"
        "}\n",
        input
    );
}

int main() {

    printf("Collector running...\n");

    while (1) {

        char *data = read_file(INPUT_FILE);

        if (!data) {
            printf("waiting for pre_collector...\n");
            sleep(2);
            continue;
        }

        char output[4096];
        wrap_telemetry(data, output);

        FILE *f = fopen(OUTPUT_FILE, "w");
        if (f) {
            fprintf(f, "%s", output);
            fclose(f);
        }

        free(data);

        printf("Telemetry updated\n");
        sleep(2);
    }

    return 0;
}
