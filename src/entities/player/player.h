#ifndef PLAYER_H
#define PLAYER_H

#include "../../../third_party/include/raylib.h"
#include "systems/animation/animation.h"
#include "../../managers/game_context/game_context.h"
#include <stdlib.h>

typedef struct Player {
    Camera2D *camera;
    bool is_flipped;
    PlayerAnimation idle_animation;
    PlayerAnimation flipped_idle_animation;
    //Inventory *inventory; // overall inventory
    //Hand *hand; // what's equipped
} Player;

void init_player(GameContext *gc, Player *player);
void process_player(Player *player);
void render_player(Player *player);
void dispose_player(Player *player);

void draw_animation(Player *player, PlayerAnimation animation);

#endif
