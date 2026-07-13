#ifndef PLAYER_ANIMATION_H
#define PLAYER_ANIMATION_H

#include "../../../../../third_party/include/raylib.h"
#include <stdlib.h>

typedef struct PlayerAnimation {
    Texture2D atlas;
    int fps;

    Rectangle *rectangles;
    int rectangles_length;
} PlayerAnimation;

PlayerAnimation create_player_animation(Texture2D atlas, int fps, Rectangle rectangles[], int length);
void dispose_player_animation(PlayerAnimation animation);
void draw_player_animation(PlayerAnimation animation, Rectangle dest, Vector2 origin, float rotation, Color tint);

#endif
