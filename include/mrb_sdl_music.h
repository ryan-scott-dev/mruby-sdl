#ifndef MRUBY_SDL_MUSIC_H
#define MRUBY_SDL_MUSIC_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <SDL2/SDL_mixer.h>

struct mrb_sdl_music
{
  Mix_Music *music;
};

void mrb_sdl_music_free(mrb_state *mrb, void *p);

void init_mrb_sdl_music(mrb_state* mrb, struct RClass* mrb_sdl_class);
mrb_value mrb_sdl_music_wrap(mrb_state *mrb, Mix_Music *music);
struct mrb_sdl_music* mrb_sdl_music_get_ptr(mrb_state* mrb, mrb_value value);

#endif