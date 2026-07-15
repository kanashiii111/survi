#include "player.h"
#include <stdlib.h>
#include "../../systems/world_generation/chunk/entity/entity.h"
#include "raylib.h"
#include "systems/world_generation/chunk/chunk.h"
#include <stdlib.h>

bool can_draw = false;

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

void process_player(Player *player, WorldManager *wm) {
    process_input(player);
    process_interaction(player, wm);
    process_states(player);
    player->position = (Vector2){player->position.x += player->velocity.x, player->position.y += player->velocity.y};
    player->camera->target = (Vector2){player->position.x, player->position.y - 14};
}

void process_input(Player *player) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
        player->velocity.x = (IsKeyDown(KEY_A)) ? -PLAYER_SPEED : PLAYER_SPEED;
        player->is_flipped = (IsKeyDown(KEY_A)) ? true : false;
    } else {
        player->velocity.x = 0;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_W)) {
        player->velocity.y = (IsKeyDown(KEY_W)) ? -PLAYER_SPEED : PLAYER_SPEED;
    } else {
        player->velocity.y = 0;
    }
}

void process_interaction(Player *player, WorldManager *wm) {
    player->interacted_entity = get_interacted_entity(player, wm);
    if (player->interacted_entity != NULL) {
        if (!(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) return;
        delete_entity(player->interacted_entity_chunk, player->interacted_entity->entity_coords);
        player->interacted_entity_chunk = NULL;
        player->interacted_entity = NULL;
    }
}

void process_states(Player *player) {
    player->state = ((int)player->velocity.x != 0 || (int)player->velocity.y != 0) ? RUN : IDLE;
}

void render_player(Player *player) {
    float spriteW = 14;
    float spriteH = 22;
    Rectangle dest = {
        player->position.x - spriteW / 2.0f,
        player->position.y - spriteH,
        spriteW,
        spriteH
    };

    Vector2 origin = {0};
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

// <----------------UTIL----------------->

bool can_interact(Player *player, Entity *entity) {
    Vector2 mouse_pos = GetScreenToWorld2D((Vector2){GetMouseX(), GetMouseY()}, *player->camera);
    Rectangle rec_mouse_pos = (Rectangle){mouse_pos.x, mouse_pos.y, 1, 1};
    Vector2 coll_box_draw_pos = grid_to_draw_pos((Vector2){entity->interact_box.x, entity->interact_box.y}, entity->interact_box.width, entity->interact_box.height);
    Rectangle entity_rec = (Rectangle){coll_box_draw_pos.x, coll_box_draw_pos.y, entity->interact_box.width, entity->interact_box.height};
    bool is_mouse_over_entity = CheckCollisionRecs(rec_mouse_pos, entity_rec);
    return is_mouse_over_entity;
}

Entity *get_interacted_entity(Player *player, WorldManager *wm) {
    for (int i = 0; i < wm->rendered_chunks_count; i++) {
        for (int j = 0; j < wm->rendered_chunks[i].entity_count; j++) {
            if (can_interact(player, &wm->rendered_chunks[i].entities[j])) {
                player->interacted_entity_chunk = &wm->rendered_chunks[i];
                return &wm->rendered_chunks[i].entities[j];
            }
        }
    }
    return NULL;
}

// <----------------DEBUG---------------->

void draw_interact_debug(Player *player, WorldManager *wm) {
    if (player->interacted_entity == NULL) return;
    draw_debug_shapes(player->interacted_entity, BLACK, RED);
}

void draw_player_pos_debug(Player *player) {
    float spriteW = 14;
    float spriteH = 22;
    Vector2 footPos = {player->position.x, player->position.y};
    DrawCircleV(footPos, 1.0f, BLUE);
    DrawText(TextFormat("X: %d, Y: %d", (int)player->position.x, (int)player->position.y), footPos.x, footPos.y - spriteH - 10, 10, BLACK);
}

void draw_mouse_pos_debug(Player *player) {
    Vector2 mouse_pos = GetScreenToWorld2D((Vector2){GetMouseX(), GetMouseY()}, *player->camera);
    DrawText(TextFormat("X: %d, Y: %d", (int)mouse_pos.x, (int)mouse_pos.y), 50, 50, 10, BLACK);
}
