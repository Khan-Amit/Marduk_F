#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

/*
 Marduk_F
 Sluice-Bench™ Processor (REAL JSON MODE)

 Fully JSON-driven computation engine
*/

#define INPUT_FILE "../telemetry/parsed.json"
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

/* compute coherence from JSON */
float compute_coherence(cJSON *nodes) {
    int count = cJSON_GetArraySize(nodes);
    float sum = 0.0f;

    for (int i = 0; i < count; i++) {
        cJSON *node = cJSON_GetArrayItem(nodes, i);

        cJSON *field = cJSON_GetObjectItem(node, "field_strength");
        cJSON *entropy = cJSON_GetObjectItem(node, "entropy_level");

        if (field && entropy) {
            sum += (field->valuedouble - entropy->valuedouble);
        }
    }

    if (count == 0) return 0.0f;

    return sum / count;
}

int main() {

    char *data = read_file(INPUT_FILE);

    if (!data) {
        printf("ERROR: cannot read parsed.json\n");
        return 1;
    }

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        printf("ERROR: invalid JSON\n");
        free(data);
        return 1;
    }

    cJSON *nodes = cJSON_GetObjectItem(json, "nodes");

    float coherence = compute_coherence(nodes);

    FILE *f = fopen(OUTPUT_FILE, "w");
    if (!f) {
        printf("ERROR: cannot write system_state.json\n");
        return 1;
    }

    fprintf(f,
        "{\n"
        "  \"system\": \"Marduk_F\",\n"
        "  \"coherence\": %.4f,\n"
        "  \"mode\": \"real-json\",\n"
        "  \"status\": \"active\"\n"
        "}\n",
        coherence
    );

    fclose(f);

    cJSON_Delete(json);
    free(data);

    printf("REAL ENGINE ACTIVE | Coherence: %.4f\n", coherence);

    return 0;
}
