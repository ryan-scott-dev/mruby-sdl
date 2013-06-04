// #include "mrb_sdl_surface.h"

// #include <mruby.h>
// #include <mruby/class.h>
// #include <mruby/data.h>

// #include <SDL_Video.h>

// static struct RClass* mrb_sdl_surface_class = NULL;

// struct mrb_data_type mrb_sdl_surface_get_ptr_type = { "Surface", mrb_sdl_surface_free };

// void mrb_sdl_surface_free(mrb_state *mrb, void *ptr)
// {
//   mrb_free(mrb, ptr);
// }

// mrb_value mrb_sdl_surface_wrap(mrb_state *mrb, struct SDL_Surface *surface)
// {
//   struct mrb_sdl_surface* tm = (struct mrb_sdl_surface*)mrb_malloc(mrb, sizeof(struct mrb_sdl_surface));
//   tm->surface = surface;
//   return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_sdl_surface_class, &mrb_sdl_surface_get_ptr_type, tm));
// }

// struct mrb_sdl_surface* mrb_sdl_surface_get_ptr(mrb_state* mrb, mrb_value value)
// {
//   return (struct mrb_sdl_surface*)mrb_data_get_ptr(mrb, value, &mrb_sdl_surface_get_ptr_type);
// }

// void init_mrb_sdl_surface(mrb_state* mrb)
// {
//   mrb_sdl_surface_class = mrb_define_class(mrb, "Surface", mrb->object_class);
//   MRB_SET_INSTANCE_TT(mrb_sdl_surface_class, MRB_TT_DATA);
// }