#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "entity_definition/entity_definition.h"

typedef struct Entity {
    Rectangle interact_box;
    Vector2 entity_coords;
    EntityDefinition entity_definition;
} Entity;

void render_entity(Texture2D *atlas, Entity *entity);

// <----------------DEBUG---------------->

void draw_debug_shapes(Entity *entity, Color circle_color, Color interact_box_color);

#endif
