#include "mrb_sdl.h"

#include <mruby/array.h>

#include "mrb_sdl_event.h"
#include "mrb_sdl_window.h"

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

mrb_value
mrb_sdl_poll_event(mrb_state* mrb, mrb_value self)
{
  SDL_Event event;
  if(SDL_PollEvent(&event)){
    return mrb_sdl_event_wrap(mrb, event);
  }

  return mrb_nil_value();
}

void
mrb_mruby_sdl_gem_init(mrb_state* mrb) {
  struct RClass *sdl_class = mrb_define_module(mrb, "SDL");
  mrb_define_class_method(mrb, sdl_class, "init", mrb_sdl_init, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, sdl_class, "quit", mrb_sdl_quit, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, sdl_class, "poll_event", mrb_sdl_poll_event, MRB_ARGS_NONE());

  init_mrb_sdl_window(mrb);
  init_mrb_sdl_event(mrb);
}

void
mrb_mruby_sdl_gem_final(mrb_state* mrb) {
  // finalizer
}
