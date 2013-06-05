#include "mrb_sdl.h"

#include <mruby/array.h>

#include <SDL2/SDL_opengl.h>

static struct RClass* mrb_sdl_gl_class = NULL;

mrb_value 
mrb_sdl_gl_clear_color(mrb_state* mrb, mrb_value self)
{
  mrb_float r, g, b, a;
  mrb_get_args(mrb, "ffff", &r, &g, &b, &a);

  glClearColor(r, g, b, a);

  return self;
}

void
init_mrb_sdl_gl(mrb_state* mrb) {
  mrb_sdl_gl_class = mrb_define_module(mrb, "GL");
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "clear_color", mrb_sdl_gl_clear_color, MRB_ARGS_REQ(4));
  // mrb_define_module_function(mrb, mrb_sdl_class, "clear", mrb_sdl_gl_clear, MRB_ARGS_REQ(1));
}