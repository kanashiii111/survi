#include "player.h"
#include "../systems/animation/animation.h"

void init_player(GameContext *gc, Player *player){
    Camera2D *camera = malloc(sizeof(Camera2D));
    player->camera = camera;
    player->camera->target = (Vector2){0, 0};
    player->camera->offset = (Vector2){1280 / 2.0f, 960 / 2.0f};
    player->camera->rotation = 0.0f;
    player->camera->zoom = 4.0f;

    player->velocity = (Vector2){0, 0};
    player->position = (Vector2){0, 0};
    player->state = IDLE;

    Animation idle_animation = create_animation(*gc->player_atlas, 2,
        (Rectangle[]) {
            (Rectangle){0, 0, 14, 22},
            (Rectangle){15, 0, 14, 22}
        }, 2);

    Animation flipped_idle_animation = create_animation(*gc->player_atlas, 2,
        (Rectangle[]) {
            (Rectangle){0, 0, -14, 22},
            (Rectangle){15, 0, -14, 22}
        }, 2);

    Animation run_animation = create_animation(*gc->player_atlas, 6,
        (Rectangle[]) {
            (Rectangle){30, 0, 14, 22},
            (Rectangle){45, 0, 14, 22},
            (Rectangle){60, 0, 14, 22}
        }, 3);

    Animation flipped_run_animation = create_animation(*gc->player_atlas, 6,
        (Rectangle[]) {
            (Rectangle){30, 0, -14, 22},
            (Rectangle){45, 0, -14, 22},
            (Rectangle){60, 0, -14, 22}
        }, 3);

    player->animations[IDLE] = idle_animation;
    player->animations[RUN] = run_animation;

    player->flipped_animations[IDLE] = flipped_idle_animation;
    player->flipped_animations[RUN] = flipped_run_animation;
}

void process_player(Player *player) {
    process_input(player);
    process_states(player);
    player->position = (Vector2){player->position.x += player->velocity.x, player->position.y += player->velocity.y};
    player->camera->target = player->position;
}

void process_input(Player *player) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
        player->velocity.x = (IsKeyDown(KEY_LEFT)) ? -PLAYER_SPEED : PLAYER_SPEED;
        player->is_flipped = (IsKeyDown(KEY_LEFT)) ? true : false;
    } else {
        player->velocity.x = 0;
    }

    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP)) {
        player->velocity.y = (IsKeyDown(KEY_UP)) ? -PLAYER_SPEED : PLAYER_SPEED;
    } else {
        player->velocity.y = 0;
    }
}

void process_states(Player *player) {
    player->state = ((int)player->velocity.x != 0 || (int)player->velocity.y != 0) ? RUN : IDLE;
}

void render_player(Player *player) {
    Rectangle dest = (Rectangle){player->position.x, player->position.y, 14, 22};
    Vector2 origin = { 0 };
    if (player->is_flipped) {
        draw_animation(player->flipped_animations[player->state], dest, origin, 0, WHITE);
    } else {
        draw_animation(player->animations[player->state], dest, origin, 0, WHITE);
    }
}

void dispose_player(Player *player) {
    free(player->camera);
    dispose_animation(player->animations[IDLE]);
    dispose_animation(player->animations[RUN]);
    dispose_animation(player->flipped_animations[IDLE]);
    dispose_animation(player->flipped_animations[RUN]);
}
