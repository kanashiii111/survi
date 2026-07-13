#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../../../third_party/include/raylib.h"
#include <stdlib.h>

typedef struct Animation {
    Texture2D atlas;
    int fps;

    Rectangle *rectangles;
    int rectangles_length;
} Animation;

Animation create_animation(Texture2D atlas, int fps, Rectangle rectangles[], int length);
void dispose_animation(Animation animation);
void draw_animation(Animation animation, Rectangle dest, Vector2 origin, float rotation, Color tint);

#endif
