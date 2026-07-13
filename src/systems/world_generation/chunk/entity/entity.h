#ifndef ENTITY_H
#define ENTITY_H

#include "../../../../../third_party/include/raylib.h"
#include "entity_definition/entity_definition.h"
#include "../tile/tile.h"

typedef struct Entity {
    Rectangle collision_box;
    Vector2 entity_coords;
    EntityDefinition entity_definition;
} Entity;

void render_entity(Texture2D *atlas, Entity *entity);

#endif
