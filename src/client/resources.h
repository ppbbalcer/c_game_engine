#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdbool.h>
#include <SDL2/SDL.h>

enum gtexture {
	TEXT_TEXTURE,
	CHAR_TEXTURE,
	TILESET_TEXTURE,

	MAX_GTEXTURE
};

enum gmusic {
	MUSIC_MENU,

	MAX_GMUSIC
};

enum gsound {
	SOUND_START,
	SOUND_HELIC,

	MAX_GSOUND
};

struct position {
	int x;
	int y;
};

struct positionf {
	float x;
	float y;
};

struct size {
	int width;
	int height;
};

enum game_font {
	FONT_BASIC,

	MAX_GAME_FONTS
};

struct font {
	enum gtexture texture;
	struct size size;
};

bool resources_load(SDL_Renderer *ren);
bool resources_unload();

SDL_Texture *resources_get_texture(enum gtexture texture);
struct font *resources_get_font(enum game_font font);

void resources_pause_music();
void resources_resume_music();
void resources_halt_music();

void resources_play_music(enum gmusic music);
void resources_play_sound(enum gsound sound);

#endif /* RESOURCES_H */
