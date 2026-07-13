#ifndef PLAYER_H
#define PLAYER_H

#include "../../../third_party/include/raylib.h"
#include "../systems/animation/animation.h"
#include "../../managers/game_context/game_context.h"
#include <stdlib.h>

#define PLAYER_SPEED 2

typedef enum State {
    IDLE,
    RUN
} State;

typedef struct Player {
    Vector2 velocity;
    Vector2 position;
    State state;

    Camera2D *camera;
    bool is_flipped;
    Animation animations[2];
    Animation flipped_animations[2];

    //Inventory *inventory; // overall inventory
    //Hand *hand; // what's equipped
} Player;

void init_player(GameContext *gc, Player *player);

void process_player(Player *player);
void process_states(Player *player);
void process_input(Player *player);

void render_player(Player *player);

void dispose_player(Player *player);

#endif
