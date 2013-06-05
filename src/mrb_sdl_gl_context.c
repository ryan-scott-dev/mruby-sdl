#include "mrb_sdl_gl_context.h"

#include <mrbconf.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

static struct RClass* mrb_sdl_gl_context_class = NULL;

struct mrb_data_type mrb_sdl_gl_context_get_ptr_type = { "GLContext", mrb_sdl_gl_context_free };

void
mrb_sdl_gl_context_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value
mrb_sdl_gl_context_wrap(mrb_state *mrb, SDL_GLContext context)
{
  struct mrb_sdl_gl_context* tm = (struct mrb_sdl_gl_context*)mrb_malloc(mrb, sizeof(struct mrb_sdl_gl_context));
  tm->context = context;
  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_sdl_gl_context_class, &mrb_sdl_gl_context_get_ptr_type, tm));
}

struct mrb_sdl_gl_context*
mrb_sdl_gl_context_get_ptr(mrb_state* mrb, mrb_value value)
{
  return (struct mrb_sdl_gl_context*)mrb_data_get_ptr(mrb, value, &mrb_sdl_gl_context_get_ptr_type);
}

mrb_value 
mrb_sdl_gl_context_destroy(mrb_state* mrb, mrb_value self)
{
  struct mrb_sdl_gl_context* context = mrb_sdl_gl_context_get_ptr(mrb, self);
  SDL_GL_DeleteContext(context->context);
  
  return mrb_nil_value();
}

void
init_mrb_sdl_gl_context(mrb_state* mrb)
{
  mrb_sdl_gl_context_class = mrb_define_class(mrb, "GLContext", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_sdl_gl_context_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_sdl_gl_context_class, "destroy", mrb_sdl_gl_context_destroy, ARGS_NONE());
}