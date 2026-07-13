#include "cat.h"

void init_cat(GameContext *gc, Cat *cat) {
    Animation idle_animation = create_animation(*gc->cat_atlas, 2,
        (Rectangle[]) {
            (Rectangle){80 * 0, 0, 80, 64},
            (Rectangle){80 * 1, 0, 80, 64},
            (Rectangle){80 * 2, 0, 80, 64},
            (Rectangle){80 * 3, 0, 80, 64},
            (Rectangle){80 * 4, 0, 80, 64},
            (Rectangle){80 * 5, 0, 80, 64},
            (Rectangle){80 * 6, 0, 80, 64},
            (Rectangle){80 * 7, 0, 80, 64},
        }, 8);

    cat->animation = idle_animation;
}

void render_cat(Cat *cat) {
    Rectangle dest = (Rectangle){50, 50, 80, 64};
    Vector2 origin = { 0 };
    draw_animation(cat->animation, dest, origin, 0, WHITE);
}
