#ifndef MRUBY_SDL_GL_CONTEXT_H
#define MRUBY_SDL_GL_CONTEXT_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include <SDL2/SDL.h>

struct mrb_sdl_gl_context
{
  SDL_GLContext context;
};

void mrb_sdl_gl_context_free(mrb_state *mrb, void *p);

void init_mrb_sdl_gl_context(mrb_state* mrb, struct RClass* mrb_sdl_class);
mrb_value mrb_sdl_gl_context_wrap(mrb_state *mrb, SDL_GLContext context);
struct mrb_sdl_gl_context* mrb_sdl_gl_context_get_ptr(mrb_state* mrb, mrb_value value);

#endif