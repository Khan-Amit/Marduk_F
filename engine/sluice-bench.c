#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 Marduk_F
 Sluice-Bench™ — Final Processing Engine

 Reads telemetry.json and produces system_state.json
*/

#define INPUT_FILE "../telemetry/telemetry.json"
#define OUTPUT_FILE "../telemetry/system_state.json"

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

/* extract simple numeric signal (light parser) */
float extract_signal(const char *data) {
    float value = 0.5f;

    for (int i = 0; data[i]; i++) {
        value += (data[i] % 7) * 0.001f;
    }

    if (value > 1.0f) value = 1.0f;
    if (value < 0.0f) value = 0.0f;

    return value;
}

int main() {

    printf("Sluice-Bench running...\n");

    char *data = read_file(INPUT_FILE);

    if (!data) {
        printf("waiting for telemetry...\n");
        return 1;
    }

    float coherence = extract_signal(data);

    FILE *f = fopen(OUTPUT_FILE, "w");
    if (!f) {
        printf("ERROR writing system_state.json\n");
        free(data);
        return 1;
    }

    fprintf(f,
        "{\n"
        "  \"system\": \"Marduk_F\",\n"
        "  \"coherence\": %.4f,\n"
        "  \"status\": \"active\",\n"
        "  \"mode\": \"live-pipeline\"\n"
        "}\n",
        coherence
    );

    fclose(f);
    free(data);

    printf("System state updated | Coherence: %.4f\n", coherence);

    return 0;
}
