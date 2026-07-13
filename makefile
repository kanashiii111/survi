SHELL = cmd.exe
CC = gcc

SRCDIR  = .
BUILDDIR = build
OBJDIR  = $(BUILDDIR)/obj

CFLAGS  = -I. -Iinclude
LDFLAGS = -Lthird_party/lib -lraylib -lgdi32 -lwinmm

SOURCES = \
    src/main.c \
    src/entities/player/player.c \
    src/entities/cat/cat.c \
    src/entities/systems/animation/animation.c \
    src/managers/game_context/game_context.c \
    src/managers/world_manager/world_manager.c \
    src/systems/chunk_streamer/chunk_streamer.c \
    src/systems/world_generation/chunk/chunk.c \
    src/systems/world_generation/chunk/tile/tile.c \
    src/systems/world_generation/chunk/tile/tile_definition/tile_definition.c \
    src/systems/world_generation/generation_pass/generation_pass.c \
    src/systems/world_generation/world_config/world_config.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
TARGET  = $(BUILDDIR)/main.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-@mkdir "$(subst /,\,$(dir $@))" 2>nul
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist "$(BUILDDIR)" rmdir /s /q "$(BUILDDIR)"
