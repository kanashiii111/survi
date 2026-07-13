#include "animation.h"
#include <stdlib.h>

void draw_animation(Animation animation, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    int index = (int)(GetTime() * animation.fps) % animation.rectangles_length;

    Rectangle source = animation.rectangles[index];
    DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}

Animation create_animation(Texture2D atlas, int fps, Rectangle *rectangles, int length) {
    Animation animation = {
        .atlas = atlas,
        .fps = fps,
        .rectangles_length = length,
        .rectangles = NULL
    };

    Rectangle *rects_memory = (Rectangle*)(malloc(sizeof(Rectangle) * length));
    if (rects_memory == NULL) {
        TraceLog(LOG_FATAL, "animation.c : falied allocation of memory for rectangles");
        animation.rectangles_length = 0;
        return animation;
    }

    animation.rectangles = rects_memory;

    for (int i = 0; i < length; i++) {
        animation.rectangles[i] = rectangles[i];
    }

    return animation;
}

void dispose_animation(Animation animation) {
    free(animation.rectangles);
}
