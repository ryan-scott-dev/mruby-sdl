#include "mrb_sdl_glew.h"

#include <mruby/array.h>

static struct RClass* mrb_sdl_glew_class = NULL;

mrb_value 
mrb_sdl_glew_init(mrb_state* mrb, mrb_value self)
{

#ifndef PLATFORM_IOS
  glewExperimental = GL_TRUE;

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Error initializing glew: %S", mrb_str_new_cstr(mrb, glewGetErrorString(err)));
  }
#endif
  
  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
  printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  
  return self;
}

void
init_mrb_sdl_glew(mrb_state* mrb) {
  mrb_sdl_glew_class = mrb_define_module(mrb, "GLEW");
  mrb_define_module_function(mrb, mrb_sdl_glew_class, "init", mrb_sdl_glew_init, MRB_ARGS_NONE());
}