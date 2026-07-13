#ifndef ENTITY_DEFINITION_H
#define ENTITY_DEFINITION_H

typedef enum ENTITIES {
    NONE = -1,
    BIG_TREE,
    SMALL_TREE,
    BIG_ROCK,
    SMALL_ROCK
} ENTITY;

typedef struct EntityDefinition {
    ENTITY entity_type;
} EntityDefinition;

#endif
