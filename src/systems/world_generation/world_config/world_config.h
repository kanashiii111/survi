#ifndef WORLD_CONFIG_H
#define WORLD_CONFIG_H

#include "FastNoiseLite.h"

typedef struct WorldConfig {
    int seed;
    fnl_state *noise;
} WorldConfig;

#endif
