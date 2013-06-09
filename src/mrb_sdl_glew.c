#include "mrb_sdl_glew.h"

#include <mruby/array.h>

static struct RClass* mrb_sdl_glew_class = NULL;

mrb_value 
mrb_sdl_glew_init(mrb_state* mrb, mrb_value self)
{
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Error initializing glew: %S", mrb_str_new_cstr(mrb, glewGetErrorString(err)));
  }
  return self;
}

void
init_mrb_sdl_glew(mrb_state* mrb) {
  mrb_sdl_glew_class = mrb_define_module(mrb, "GLEW");
  mrb_define_module_function(mrb, mrb_sdl_glew_class, "init", mrb_sdl_glew_init, MRB_ARGS_NONE());
}