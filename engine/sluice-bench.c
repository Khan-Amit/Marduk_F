#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Marduk_F
 Sluice-Bench™ Telemetry Processor (Core Engine)

 Now with JSON telemetry export
 Designed by: Seliim Ahmed
*/

#define NODE_COUNT 10

typedef struct {
    int node_id;
    float field_strength;
    float entropy_level;
    char status[32];
} Node;

typedef struct {
    Node nodes[NODE_COUNT];
    int active_nodes;
    float global_coherence;
} MardukSystem;

/* ---------------- INIT SYSTEM ---------------- */
void init_system(MardukSystem *sys) {
    sys->active_nodes = 0;
    sys->global_coherence = 0.0f;

    for (int i = 0; i < NODE_COUNT; i++) {
        sys->nodes[i].node_id = i;
        sys->nodes[i].field_strength = 0.0f;
        sys->nodes[i].entropy_level = 0.0f;
        strcpy(sys->nodes[i].status, "offline");
    }
}

/* ---------------- ACTIVATE NODE ---------------- */
void activate_node(MardukSystem *sys, int id, float field, float entropy) {
    if (id < 0 || id >= NODE_COUNT) return;

    sys->nodes[id].field_strength = field;
    sys->nodes[id].entropy_level = entropy;
    strcpy(sys->nodes[id].status, "active");
}

/* ---------------- COMPUTE COHERENCE ---------------- */
void compute_coherence(MardukSystem *sys) {
    float sum = 0.0f;
    int active = 0;

    for (int i = 0; i < NODE_COUNT; i++) {
        if (strcmp(sys->nodes[i].status, "active") == 0) {
            sum += sys->nodes[i].field_strength - sys->nodes[i].entropy_level;
            active++;
        }
    }

    if (active > 0)
        sys->global_coherence = sum / NODE_COUNT;
    else
        sys->global_coherence = 0.0f;
}

/* ---------------- EXPORT TO JSON ---------------- */
void export_telemetry(MardukSystem *sys) {
    FILE *f = fopen("../telemetry/telemetry.json", "w");

    if (!f) {
        printf("ERROR: Cannot open telemetry.json\n");
        return;
    }

    fprintf(f, "{\n");
    fprintf(f, "  \"active_nodes\": %d,\n", sys->active_nodes);
    fprintf(f, "  \"global_coherence\": %.4f,\n", sys->global_coherence);
    fprintf(f, "  \"nodes\": [\n");

    for (int i = 0; i < NODE_COUNT; i++) {
        fprintf(f, "    {\n");
        fprintf(f, "      \"node_id\": %d,\n", sys->nodes[i].node_id);
        fprintf(f, "      \"field_strength\": %.4f,\n", sys->nodes[i].field_strength);
        fprintf(f, "      \"entropy_level\": %.4f,\n", sys->nodes[i].entropy_level);
        fprintf(f, "      \"status\": \"%s\"\n", sys->nodes[i].status);
        fprintf(f, "    }%s\n", (i < NODE_COUNT - 1) ? "," : "");
    }

    fprintf(f, "  ]\n");
    fprintf(f, "}\n");

    fclose(f);
}

/* ---------------- MAIN LOOP ---------------- */
int main() {
    MardukSystem system;

    init_system(&system);

    /* Example simulation tick */
    activate_node(&system, 0, 0.8f, 0.2f);
    activate_node(&system, 1, 0.6f, 0.3f);
    activate_node(&system, 2, 0.9f, 0.4f);
    activate_node(&system, 3, 0.4f, 0.1f);

    compute_coherence(&system);
    export_telemetry(&system);

    printf("Marduk_F telemetry exported successfully.\n");

    return 0;
}
