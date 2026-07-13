#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "../../../third_party/include/raylib.h"

typedef struct GameContext {
    Texture2D *tile_atlas;
    Texture2D *player_atlas;
    Texture2D *cat_atlas;
} GameContext;

#endif
