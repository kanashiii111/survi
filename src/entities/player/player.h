#ifndef PLAYER_H
#define PLAYER_H

#include "managers/world_manager/world_manager.h"
#include "raylib.h"
#include "../systems/animation/animation.h"
#include "../../managers/game_context/game_context.h"

typedef struct Entity Entity;

#define PLAYER_SPEED 2

typedef enum State {
    IDLE,
    RUN
} State;

typedef struct Player {
    Vector2 velocity;
    Vector2 position;
    State state;

    Entity *interacted_entity;
    Chunk *interacted_entity_chunk;

    Camera2D *camera;
    bool is_flipped;
    Animation animations[2];
    Animation flipped_animations[2];

    //Inventory *inventory; // overall inventory
    //Hand *hand; // what's equipped
} Player;

void init_player(GameContext *gc, Player *player);

void process_player(Player *player, WorldManager *wm);
void process_interaction(Player *player, WorldManager *wm);
void process_states(Player *player);
void process_input(Player *player);

void render_player(Player *player);

void dispose_player(Player *player);

// util

bool can_interact(Player *player, Entity *entity);
Entity *get_interacted_entity(Player *player, WorldManager *wm);

// debug

void draw_interact_debug(Player *player, WorldManager *wm);
void draw_player_pos_debug(Player *player);
void draw_mouse_pos_debug(Player *player);

#endif
