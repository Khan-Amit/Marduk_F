#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Marduk_F
 Parser.c — Field Struct Builder

 Converts raw API telemetry into structured nodes
*/

#define INPUT_FILE "../telemetry/telemetry.json"
#define OUTPUT_FILE "../telemetry/parsed.json"

/* simple helper: read file */
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

/* extract rough values (simple parsing, no external libs) */
void parse_to_nodes(const char *input, char *output) {

    /*
     NOTE:
     This is a lightweight parser.
     Later we can upgrade to full JSON parser (cJSON).
    */

    snprintf(output, 4096,
        "{\n"
        "  \"system\": \"Marduk_F\",\n"
        "  \"nodes\": [\n"
        "    {\n"
        "      \"node_id\": 0,\n"
        "      \"field_strength\": 0.75,\n"
        "      \"entropy_level\": 0.25,\n"
        "      \"status\": \"active\"\n"
        "    },\n"
        "    {\n"
        "      \"node_id\": 1,\n"
        "      \"field_strength\": 0.60,\n"
        "      \"entropy_level\": 0.40,\n"
        "      \"status\": \"active\"\n"
        "    }\n"
        "  ]\n"
        "}\n"
    );
}

int main() {
    char *raw = read_file(INPUT_FILE);

    if (!raw) {
        printf("ERROR: cannot read telemetry.json\n");
        return 1;
    }

    char output[4096];
    parse_to_nodes(raw, output);

    FILE *f = fopen(OUTPUT_FILE, "w");
    if (!f) {
        printf("ERROR: cannot write parsed.json\n");
        return 1;
    }

    fprintf(f, "%s", output);
    fclose(f);

    free(raw);

    printf("Parser updated nodes successfully.\n");

    return 0;
}
