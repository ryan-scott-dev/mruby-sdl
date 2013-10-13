#include "mrb_sdl.h"

#include <mruby/array.h>

static struct RClass* mrb_sdl_gl_class = NULL;
unsigned int mrb_sdl_gl_clear_flags = 0;
mrb_float mrb_sdl_gl_clear_r, mrb_sdl_gl_clear_g, mrb_sdl_gl_clear_b;

mrb_value 
mrb_sdl_gl_set_clear_color(mrb_state* mrb, mrb_value self)
{
  mrb_get_args(mrb, "fff", &mrb_sdl_gl_clear_r, &mrb_sdl_gl_clear_g, &mrb_sdl_gl_clear_b);

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
mrb_sdl_gl_set_clear_flags(mrb_state* mrb, mrb_value self)
{
  unsigned int flags = 0;
  mrb_value flags_array;
  mrb_get_args(mrb, "A", &flags_array);

  mrb_sdl_gl_clear_flags = gl_clear_flags_array_to_flags(mrb, flags_array);
  
  return self;
}

mrb_value 
mrb_sdl_gl_clear(mrb_state* mrb, mrb_value self)
{
  glClear(mrb_sdl_gl_clear_flags);
  glClearColor(mrb_sdl_gl_clear_r, mrb_sdl_gl_clear_g, mrb_sdl_gl_clear_b, 1.0f);

  return self;
}

mrb_value 
mrb_sdl_gl_error(mrb_state* mrb, mrb_value self)
{
  GLenum error = glGetError();
  if (error == GL_NO_ERROR) {
    return mrb_nil_value();
  }

  return mrb_str_new_cstr(mrb, gluErrorString(error));
}

mrb_value 
mrb_sdl_gl_viewport(mrb_state* mrb, mrb_value self)
{
  mrb_int x, y, w, h;
  mrb_get_args(mrb, "iiii", &x, &y, &w, &h);
  glViewport(x, y, w, h);

  return self;
}

mrb_value 
mrb_sdl_gl_blend_alpha_transparency(mrb_state* mrb, mrb_value self)
{
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  return self;
}

mrb_value 
mrb_sdl_gl_blend_alpha_transparency_without_depth(mrb_state* mrb, mrb_value self)
{
  glDisable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  return self;
}

mrb_value 
mrb_sdl_gl_blend_opaque (mrb_state* mrb, mrb_value self)
{
  glEnable(GL_DEPTH_TEST);

  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
  
  return self;
}

void
init_mrb_sdl_gl(mrb_state* mrb) {
  mrb_sdl_gl_class = mrb_define_module(mrb, "GL");
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "clear", mrb_sdl_gl_clear, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "set_clear_color", mrb_sdl_gl_set_clear_color, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "set_clear_flags", mrb_sdl_gl_set_clear_flags, MRB_ARGS_REQ(1));
  
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "error", mrb_sdl_gl_error, MRB_ARGS_NONE());

  
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "blend_alpha_transparency_without_depth", mrb_sdl_gl_blend_alpha_transparency_without_depth, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "blend_alpha_transparency", mrb_sdl_gl_blend_alpha_transparency, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "blend_opaque", mrb_sdl_gl_blend_opaque, MRB_ARGS_NONE());
  
  mrb_define_module_function(mrb, mrb_sdl_gl_class, "viewport", mrb_sdl_gl_viewport, MRB_ARGS_REQ(4));
}