#include "mrb_sdl.h"

#include <mruby/array.h>

#include <glew.h>
#include <SDL2/SDL_opengl.h>

static struct RClass* mrb_sdl_gl_class = NULL;

mrb_value 
mrb_sdl_gl_clear_color(mrb_state* mrb, mrb_value self)
{
  mrb_float r, g, b, a;
  mrb_get_args(mrb, "ffff", &r, &g, &b, &a);

  glClearColor((float)r, (float)g, (float)b, (float)a);

  return self;
}

unsigned int
gl_clear_flag_symbol_to_flag(mrb_state* mrb, mrb_value sym)
{
  mrb_sym flag = mrb_obj_to_sym(mrb, sym);

  if (flag == mrb_intern_cstr(mrb, "color"))
    return GL_COLOR_BUFFER_BIT;
  if (flag == mrb_intern_cstr(mrb, "depth"))
    return GL_DEPTH_BUFFER_BIT;
  if (flag == mrb_intern_cstr(mrb, "stencil"))
    return GL_STENCIL_BUFFER_BIT;

  return 0;
}

unsigned int
gl_clear_flags_array_to_flags(mrb_state* mrb, mrb_value array)
{
  struct RArray *a = mrb_ary_ptr(array);
  unsigned int flags = 0;
  int i;

  for(i = 0; i < a->len; i++)
  {
    flags = flags | gl_clear_flag_symbol_to_flag(mrb, a->ptr[i]);
  }

  return flags;
}

mrb_value 
mrb_sdl_gl_clear(mrb_state* mrb, mrb_value self)
{
  unsigned int flags = 0;
  mrb_value flags_array;
  mrb_get_args(mrb, "A", &flags_array);

  flags = gl_clear_flags_array_to_flags(mrb, flags_array);
  glClear(flags);

  return self;
}

mrb_value 
mrb_sdl_gl_clear(mrb_state* mrb, mrb_value self)
{
  GLenum error = glGetError();
  if (error == GL_NO_ERROR) {
    return mrb_nil_value();
  }

  return mrb_fixnum_value(error);
}

void
init_mrb_sdl_gl(mrb_state* mrb) {
  mrb_sdl_gl_class = mrb_define_module(mrb, "GL");
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "clear_color", mrb_sdl_gl_clear_color, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "clear", mrb_sdl_gl_clear, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "error", mrb_sdl_gl_error, MRB_ARGS_NONE());
}