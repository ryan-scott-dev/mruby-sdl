#include <mruby.h>
#include <mruby/array.h>
#include <stdio.h>
#include <SDL.h>

#include "mrb_sdl_surface.h"
#include "mrb_sdl_event.h"

mrb_value
mrb_sdl_init(mrb_state* mrb, mrb_value self)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  return self;
}

mrb_value
mrb_sdl_quit(mrb_state* mrb, mrb_value self)
{
  SDL_Quit();
  return self;
}

unsigned int
video_mode_symbol_to_flag(mrb_state* mrb, mrb_value sym)
{
  mrb_sym flag = mrb_obj_to_sym(mrb, sym);

  if (flag == mrb_intern_cstr(mrb, "sw_surface"))
    return SDL_SWSURFACE;
  if (flag == mrb_intern_cstr(mrb, "hw_surface"))
    return SDL_HWSURFACE;
  if (flag == mrb_intern_cstr(mrb, "async_blit"))
    return SDL_ASYNCBLIT;
  if (flag == mrb_intern_cstr(mrb, "any_format"))
    return SDL_ANYFORMAT;
  if (flag == mrb_intern_cstr(mrb, "hw_palette"))
    return SDL_HWPALETTE;
  if (flag == mrb_intern_cstr(mrb, "double_buffer"))
    return SDL_DOUBLEBUF;
  if (flag == mrb_intern_cstr(mrb, "fullscreen"))
    return SDL_FULLSCREEN;
  if (flag == mrb_intern_cstr(mrb, "opengl"))
    return SDL_OPENGL;
  if (flag == mrb_intern_cstr(mrb, "opengl_blit"))
    return SDL_OPENGLBLIT;
  if (flag == mrb_intern_cstr(mrb, "resizable"))
    return SDL_RESIZABLE;
  if (flag == mrb_intern_cstr(mrb, "noframe"))
    return SDL_NOFRAME;

  return 0;
}

unsigned int
video_mode_symbols_to_flags(mrb_state* mrb, mrb_value array)
{
  struct RArray *a = mrb_ary_ptr(array);
  unsigned int flags = 0;
  int i;

  for(i = 0; i < a->len; i++)
  {
    flags = flags | video_mode_symbol_to_flag(mrb, a->ptr[i]);
  }

  return flags;
}

mrb_value
mrb_sdl_poll_event(mrb_state* mrb, mrb_value self)
{
  SDL_Event event;
  if(SDL_PollEvent(&event)){
    return mrb_sdl_event_wrap(mrb, event);
  }

  return mrb_nil_value();
}

mrb_value
mrb_sdl_set_video_mode(mrb_state* mrb, mrb_value self)
{
  mrb_int width, height, dpi;
  mrb_value flags_array;
  SDL_Surface* surface;
  unsigned int flags;

  mrb_get_args(mrb, "iiiA", &width, &height, &dpi, &flags_array);
  flags = video_mode_symbols_to_flags(mrb, flags_array);

  surface = SDL_SetVideoMode(width, height, dpi, flags);
  return mrb_sdl_surface_wrap(mrb, surface);
}

mrb_value
mrb_sdl_gl_swap_buffers(mrb_state* mrb, mrb_value self)
{
  SDL_GL_SwapBuffers();
  return self;
}

void
mrb_mruby_sdl_gem_init(mrb_state* mrb) {
  struct RClass *sdl_class = mrb_define_module(mrb, "SDL");
  mrb_define_class_method(mrb, sdl_class, "init", mrb_sdl_init, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, sdl_class, "quit", mrb_sdl_quit, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, sdl_class, "set_video_mode", mrb_sdl_set_video_mode, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, sdl_class, "poll_event", mrb_sdl_poll_event, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, sdl_class, "swap_buffers", mrb_sdl_gl_swap_buffers, MRB_ARGS_NONE());

  init_mrb_sdl_surface(mrb);
  init_mrb_sdl_event(mrb);
}

void
mrb_mruby_sdl_gem_final(mrb_state* mrb) {
  // finalizer
}
