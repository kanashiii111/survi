#ifndef GENERATION_PASS_H
#define GENERATION_PASS_H

#include "../chunk/chunk.h"
#include "../../../../third_party/include/FastNoiseLite.h"
#include "../world_config/world_config.h"

static const float WATER_THRESHOLD = -0.1;
static const float DIRT_THRESHOLD = 0.0;

void generate_terrain(Chunk *chunk, WorldConfig *config);
void generate_entities(Chunk *chunk, WorldConfig *config);

#endif
