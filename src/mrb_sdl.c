#include "mrb_sdl.h"

#include <mruby/array.h>

#include "mrb_sdl_event.h"
#include "mrb_sdl_window.h"
#include "mrb_sdl_gl_context.h"
#include "mrb_sdl_music.h"
#include "mrb_sdl_gl.h"

static struct RClass* mrb_sdl_class = NULL;

mrb_value
mrb_sdl_init(mrb_state* mrb, mrb_value self)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Error initializing sdl: %S", mrb_str_new_cstr(mrb, SDL_GetError()));
  }

  return self;
}

mrb_value
mrb_sdl_quit(mrb_state* mrb, mrb_value self)
{
  SDL_Quit();
  return self;
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
mrb_sdl_set_gl_version(mrb_state* mrb, mrb_value self)
{
  mrb_int major, minor;
  mrb_get_args(mrb, "ii", &major, &minor);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  return self;
}

mrb_value
mrb_sdl_delay(mrb_state* mrb, mrb_value self)
{
  mrb_int duration;
  mrb_get_args(mrb, "i", &duration);
  
  SDL_Delay(duration);

  return self;
}

mrb_value
mrb_sdl_error(mrb_state* mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, SDL_GetError());
}

mrb_value
mrb_sdl_platform(mrb_state* mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, SDL_GetPlatform());
}

void
mrb_mruby_sdl_gem_init(mrb_state* mrb) {
  mrb_sdl_class = mrb_define_module(mrb, "SDL");
  mrb_define_module_function(mrb, mrb_sdl_class, "init", mrb_sdl_init, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_class, "quit", mrb_sdl_quit, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_class, "poll_event", mrb_sdl_poll_event, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_class, "set_gl_version", mrb_sdl_set_gl_version, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mrb_sdl_class, "delay", mrb_sdl_delay, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_sdl_class, "error", mrb_sdl_error, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_class, "platform", mrb_sdl_platform, MRB_ARGS_NONE());
  
  init_mrb_sdl_window(mrb, mrb_sdl_class);
  init_mrb_sdl_event(mrb, mrb_sdl_class);
  init_mrb_sdl_gl_context(mrb, mrb_sdl_class);
  init_mrb_sdl_music(mrb, mrb_sdl_class);

  init_mrb_sdl_gl(mrb);
}

void
mrb_mruby_sdl_gem_final(mrb_state* mrb) {
  // finalizer
}
