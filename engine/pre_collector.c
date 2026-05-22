#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 Marduk_F
 Pre-Collector.c — Semantic Security Gate

 Filters incoming data streams before Collector
*/

/* classify input type (your metaphor system) */
char* classify_input(const char *input) {

    if (strstr(input, "error") || strstr(input, "null")) {
        return "BLOCKED";
    }

    if (strstr(input, "temperature") || strstr(input, "weather")) {
        return "CAT";   // trusted structured data
    }

    if (strstr(input, "api") || strstr(input, "json")) {
        return "DOG";   // valid but needs sanitization
    }

    if (strlen(input) < 20) {
        return "BIRD";  // lightweight signal
    }

    return "UNKNOWN";
}

/* basic noise detection */
int is_noise(const char *input) {
    int bad_chars = 0;

    for (int i = 0; input[i]; i++) {
        if (!isprint(input[i])) {
            bad_chars++;
        }
    }

    return (bad_chars > 5);
}

/* write safe output for next stage */
void forward_data(const char *input, const char *tag) {
    FILE *f = fopen("../telemetry/pre_filtered.json", "w");

    if (!f) {
        printf("ERROR: cannot write pre_filtered.json\n");
        return;
    }

    fprintf(f,
        "{\n"
        "  \"tag\": \"%s\",\n"
        "  \"data\": \"%s\"\n"
        "}\n",
        tag,
        input
    );

    fclose(f);
}

int main() {

    /* simulate incoming stream (later replaced by real API input) */
    const char *incoming_data =
        "weather api temperature humidity json stream";

    printf("Pre-Collector started...\n");

    if (is_noise(incoming_data)) {
        printf("BLOCKED: noise detected\n");
        return 1;
    }

    char *tag = classify_input(incoming_data);

    printf("Classified as: %s\n", tag);

    if (strcmp(tag, "BLOCKED") == 0) {
        printf("Rejected unsafe input\n");
        return 1;
    }

    forward_data(incoming_data, tag);

    printf("Data forwarded safely\n");

    return 0;
}
