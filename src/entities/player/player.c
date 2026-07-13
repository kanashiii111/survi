#include "player.h"
#include "systems/animation/animation.h"

void init_player(GameContext *gc, Player *player){
    Camera2D *camera = malloc(sizeof(Camera2D));
    player->camera = camera;
    player->camera->target = (Vector2){0, 0};
    player->camera->offset = (Vector2){1280 / 2.0f, 960 / 2.0f};
    player->camera->rotation = 0.0f;
    player->camera->zoom = 2.5f;

    PlayerAnimation idle_animation = create_player_animation(*gc->player_atlas, 2,
        (Rectangle[]) {
            (Rectangle){0, 0, 12, 17},
            (Rectangle){13, 0, 12, 17}
        }, 2);

    PlayerAnimation flipped_idle_animation = create_player_animation(*gc->player_atlas, 2,
        (Rectangle[]) {
            (Rectangle){0, 0, -12, 17},
            (Rectangle){13, 0, -12, 17}
        }, 2);

    player->idle_animation = idle_animation;
    player->flipped_idle_animation = flipped_idle_animation;
}

void process_player(Player *player) {
    if (IsKeyDown(KEY_LEFT)) { player->camera->target.x -= 5.0f; player->is_flipped = true; };
    if (IsKeyDown(KEY_RIGHT)) { player->camera->target.x += 5.0f; player->is_flipped = false; };
    if (IsKeyDown(KEY_UP)) { player->camera->target.y -= 5.0f; };
    if (IsKeyDown(KEY_DOWN)) { player->camera->target.y += 5.0f; };
}

void render_player(Player *player) {
    Rectangle dest = (Rectangle){player->camera->target.x, player->camera->target.y, 12, 17};
    Vector2 origin = { 0 };
    if (player->is_flipped) { draw_player_animation(player->flipped_idle_animation, dest, origin, 0, WHITE); return; }
    draw_player_animation(player->idle_animation, dest, origin, 0, WHITE);
}

void dispose_player(Player *player) {
    free(player->camera);
    dispose_player_animation(player->idle_animation);
}
