// #include "mrb_sdl_event.h"

// #include <mrbconf.h>
// #include <mruby.h>
// #include <mruby/class.h>
// #include <mruby/data.h>
// #include <mruby/value.h>

// #include <SDL_events.h>

// static struct RClass* mrb_sdl_event_class = NULL;

// struct mrb_data_type mrb_sdl_event_get_ptr_type = { "Event", mrb_sdl_event_free };

// void
// mrb_sdl_event_free(mrb_state *mrb, void *ptr)
// {
//   mrb_free(mrb, ptr);
// }

// mrb_value
// mrb_sdl_event_wrap(mrb_state *mrb, SDL_Event event)
// {
//   struct mrb_sdl_event* tm = (struct mrb_sdl_event*)mrb_malloc(mrb, sizeof(struct mrb_sdl_event));
//   tm->event = event;
//   return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_sdl_event_class, &mrb_sdl_event_get_ptr_type, tm));
// }

// struct mrb_sdl_event*
// mrb_sdl_event_get_ptr(mrb_state* mrb, mrb_value value)
// {
//   return (struct mrb_sdl_event*)mrb_data_get_ptr(mrb, value, &mrb_sdl_event_get_ptr_type);
// }

// mrb_value
// mrb_sdl_event_type_to_sym(mrb_state *mrb, unsigned short type)
// {
//   switch (type)
//   {
//     case (SDL_NOEVENT):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "no_event"));
//     case (SDL_ACTIVEEVENT):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "active"));
//     case (SDL_KEYDOWN):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "key_down"));
//     case (SDL_KEYUP):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "key_up"));
//     case (SDL_MOUSEMOTION):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_motion"));
//     case (SDL_MOUSEBUTTONDOWN):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_button_down"));
//     case (SDL_MOUSEBUTTONUP):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_button_up"));
//     case (SDL_JOYAXISMOTION):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_axis_motion"));
//     case (SDL_JOYBALLMOTION):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_ball_motion"));
//     case (SDL_JOYHATMOTION):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_hat_motion"));
//     case (SDL_JOYBUTTONDOWN):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_button_down"));
//     case (SDL_JOYBUTTONUP):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_button_up"));
//     case (SDL_QUIT):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "quit"));
//     case (SDL_SYSWMEVENT):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "sys_event"));
//     case (SDL_VIDEORESIZE):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "video_resize"));
//     case (SDL_VIDEOEXPOSE):
//       return mrb_symbol_value(mrb_intern_cstr(mrb, "video_expose"));
//   }

//   return mrb_nil_value();
// }

// mrb_value
// mrb_sdl_event_type(mrb_state *mrb, mrb_value self)
// {
//   struct mrb_sdl_event* mrb_event;
//   mrb_event = mrb_sdl_event_get_ptr(mrb, self);

//   return mrb_sdl_event_type_to_sym(mrb, mrb_event->event.type);
// }

// mrb_value mrb_sdl_event_inspect(mrb_state* mrb, mrb_value self)
// {
//   char buf[256];
//   int len;
//   struct mrb_sdl_event* mrb_event;
//   mrb_event = mrb_sdl_event_get_ptr(mrb, self);

//   if (!mrb_event) return mrb_nil_value();

//   len = snprintf(buf, sizeof(buf), "{type: %s}",
//     mrb_sym2name(mrb, mrb_obj_to_sym(mrb, mrb_sdl_event_type_to_sym(mrb, mrb_event->event.type))));
//   return mrb_str_new(mrb, buf, len);
// }

// void
// init_mrb_sdl_event(mrb_state* mrb)
// {
//   mrb_sdl_event_class = mrb_define_class(mrb, "Event", mrb->object_class);
//   MRB_SET_INSTANCE_TT(mrb_sdl_event_class, MRB_TT_DATA);

//   mrb_define_method(mrb, mrb_sdl_event_class, "type", mrb_sdl_event_type, MRB_ARGS_NONE());
//   mrb_define_method(mrb, mrb_sdl_event_class, "inspect", mrb_sdl_event_inspect, MRB_ARGS_NONE());
// }