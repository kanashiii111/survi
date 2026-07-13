#ifndef CAT_H
#define CAT_H

#include "../systems/animation/animation.h"
#include "../../managers/game_context/game_context.h"

typedef struct Cat {
    Animation animation;
} Cat;

void init_cat(GameContext *gc, Cat *cat);

void render_cat(Cat *cat);

#endif
