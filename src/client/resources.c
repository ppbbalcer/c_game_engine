#include "resources.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define RESOURCE_PATH_LEN 50

struct gtexture_info {
	char path[RESOURCE_PATH_LEN];
	Uint8 color_key[3];
};

static const struct gtexture_info gtexture_infos[MAX_GTEXTURE] = {
	{"c.png", {0, 0, 136}},
	{"bard.png", {155, 188, 15}},
	{"tileset.png", {255, 255, 255}},
};

static struct font fonts[MAX_GAME_FONTS] = {
	{TEXT_TEXTURE, {8, 16}}
};

static SDL_Texture *gtextures[MAX_GTEXTURE] = {NULL, };

static const char *gmusic_infos[MAX_GMUSIC] = {
	"music.wav"
};

static const char *gsound_infos[MAX_GSOUND] = {
	"sound.wav",
	"helic.wav"
};

static Mix_Music *gmusics[MAX_GMUSIC] = {NULL, };
static Mix_Chunk *gsounds[MAX_GSOUND] = {NULL, };

void
resources_pause_music()
{
	Mix_PauseMusic();
}

void
resources_resume_music()
{
	Mix_ResumeMusic();
}

void
resources_halt_music()
{
	Mix_HaltMusic();
}

void
resources_play_music(enum gmusic music)
{
	Mix_PlayMusic(gmusics[music], -1);
}

void
resources_play_sound(enum gsound sound)
{
	Mix_PlayChannel(-1, gsounds[sound], 0);
}

static bool
resources_load_music()
{
	for (int i = 0; i < MAX_GMUSIC; ++i)
		gmusics[i] = Mix_LoadMUS(gmusic_infos[i]);

	return true;
}

static bool
resources_load_sound()
{
	for (int i = 0; i < MAX_GSOUND; ++i)
		gsounds[i] = Mix_LoadWAV(gsound_infos[i]);

	return true;
}

static bool
resources_load_texture(SDL_Renderer *ren, enum gtexture gt)
{
	struct gtexture_info info = gtexture_infos[gt];
	SDL_Surface* surface = IMG_Load(info.path);
	if (surface == NULL) {
		printf("FAILED TO LOAD SURFACE");
		return false;
	}

	SDL_SetColorKey(surface, SDL_TRUE,
		SDL_MapRGB(surface->format,
			info.color_key[0],
			info.color_key[1],
			info.color_key[2]));

	gtextures[gt] = SDL_CreateTextureFromSurface(ren, surface);

	SDL_FreeSurface(surface);

	return true;
}

static bool
resources_load_textures(SDL_Renderer *ren)
{
	for (int i = 0; i < MAX_GTEXTURE; ++i)
		resources_load_texture(ren, i);

	return true;
}

SDL_Texture *
resources_get_texture(enum gtexture texture)
{
	return gtextures[texture];
}

bool
resources_load(SDL_Renderer *ren)
{
	if (!resources_load_textures(ren))
		return false;

	if (!resources_load_music())
		return false;

	if (!resources_load_sound())
		return false;

	Mix_VolumeMusic(30);

	return true;
}

bool
resources_unload()
{
	return true;
}

struct font *resources_get_font(enum game_font font)
{
	return &fonts[font];
}
