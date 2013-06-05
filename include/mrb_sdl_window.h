#ifndef MRUBY_SDL_WINDOW_H
#define MRUBY_SDL_WINDOW_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <SDL2/SDL.h>

struct mrb_sdl_window
{
  SDL_Window* window;
};

void mrb_sdl_window_free(mrb_state *mrb, void *p);

void init_mrb_sdl_window(mrb_state* mrb, struct RClass* mrb_sdl_class);
mrb_value mrb_sdl_window_wrap(mrb_state *mrb, SDL_Window* window);
struct mrb_sdl_window* mrb_sdl_window_get_ptr(mrb_state* mrb, mrb_value value);

#endif