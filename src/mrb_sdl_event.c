#include "mrb_sdl_event.h"

#include <mrbconf.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

static struct RClass* mrb_sdl_event_class = NULL;

struct mrb_data_type mrb_sdl_event_get_ptr_type = { "Event", mrb_sdl_event_free };

void
mrb_sdl_event_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value
mrb_sdl_event_wrap(mrb_state *mrb, SDL_Event event)
{
  struct mrb_sdl_event* tm = (struct mrb_sdl_event*)mrb_malloc(mrb, sizeof(struct mrb_sdl_event));
  tm->event = event;
  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_sdl_event_class, &mrb_sdl_event_get_ptr_type, tm));
}

struct mrb_sdl_event*
mrb_sdl_event_get_ptr(mrb_state* mrb, mrb_value value)
{
  return (struct mrb_sdl_event*)mrb_data_get_ptr(mrb, value, &mrb_sdl_event_get_ptr_type);
}

mrb_value
mrb_sdl_window_event_type_to_sym(mrb_state *mrb, SDL_Event event)
{
  switch (event.window.event)
  {
    case (SDL_WINDOWEVENT_SHOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_shown"));
    case (SDL_WINDOWEVENT_EXPOSED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_exposed"));
    case (SDL_WINDOWEVENT_MOVED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_moved"));
    case (SDL_WINDOWEVENT_RESIZED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_resized"));
    case (SDL_WINDOWEVENT_MINIMIZED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_minimized"));
    case (SDL_WINDOWEVENT_MAXIMIZED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_maximized"));
    case (SDL_WINDOWEVENT_RESTORED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_restored"));
    case (SDL_WINDOWEVENT_ENTER):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_enter"));
    case (SDL_WINDOWEVENT_LEAVE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_leave"));
    case (SDL_WINDOWEVENT_FOCUS_GAINED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_focus_gained"));
    case (SDL_WINDOWEVENT_FOCUS_LOST):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_focus_lost"));
    case (SDL_WINDOWEVENT_CLOSE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "window_close"));
  }

  return mrb_symbol_value(mrb_intern_cstr(mrb, "window"));
}

mrb_value
mrb_sdl_event_type_to_sym(mrb_state *mrb, SDL_Event event)
{
  switch (event.type)
  {
    /* Application Events */
    case (SDL_QUIT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "quit"));

    /* Window Events */
    case (SDL_WINDOWEVENT):
      return mrb_sdl_window_event_type_to_sym(mrb, event);
    case (SDL_SYSWMEVENT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "system"));

    /* App Events */
    case (SDL_APP_TERMINATING):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "terminating"));
    case (SDL_APP_LOWMEMORY):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "low_memory"));
    case (SDL_APP_WILLENTERBACKGROUND):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "entering_background"));
    case (SDL_APP_DIDENTERBACKGROUND):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "entered_background"));
    case (SDL_APP_WILLENTERFOREGROUND):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "entering_foreground"));
    case (SDL_APP_DIDENTERFOREGROUND):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "entered_foreground"));
    
    /* Keyboard Events */
    case (SDL_KEYDOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "key_down"));
    case (SDL_KEYUP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "key_up"));
    case (SDL_TEXTEDITING):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "text_editing"));
    case (SDL_TEXTINPUT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "text_input"));

    /* Mouse Events */
    case (SDL_MOUSEMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_moved"));
    case (SDL_MOUSEBUTTONDOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_down"));
    case (SDL_MOUSEBUTTONUP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_up"));
    case (SDL_MOUSEWHEEL):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "mouse_wheel"));

    /* Joystick Events */
    case (SDL_JOYAXISMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_axis_moved"));
    case (SDL_JOYBALLMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_ball_moved"));
    case (SDL_JOYHATMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_hat_moved"));
    case (SDL_JOYBUTTONDOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_down"));
    case (SDL_JOYBUTTONUP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "joy_up"));

    /* Game Controller Events */
    case (SDL_CONTROLLERAXISMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_motion"));
    case (SDL_CONTROLLERBUTTONDOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_down"));
    case (SDL_CONTROLLERBUTTONUP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_up"));
    case (SDL_CONTROLLERDEVICEADDED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_added"));
    case (SDL_CONTROLLERDEVICEREMOVED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_removed"));
    case (SDL_CONTROLLERDEVICEREMAPPED):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "controller_remapped"));

    /* Touch Events */
    case (SDL_FINGERDOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "touch_down"));
    case (SDL_FINGERUP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "touch_up"));
    case (SDL_FINGERMOTION):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "touch_moved"));
      
    /* Gesture Events */
    case (SDL_DOLLARGESTURE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "gesture_dollar"));
    case (SDL_DOLLARRECORD):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "gesture_record"));
    case (SDL_MULTIGESTURE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "gesture_multi"));

    /* Clipboard Events */
    case (SDL_CLIPBOARDUPDATE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "clipboard_update"));

    /* Drag and Drop Events */
    case (SDL_DROPFILE):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "file_dropped"));

    /* Custom Events */
    case (SDL_USEREVENT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "user"));
  }

  return mrb_nil_value();
}

mrb_value
mrb_sdl_event_type(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_event* mrb_event;
  mrb_event = mrb_sdl_event_get_ptr(mrb, self);

  return mrb_sdl_event_type_to_sym(mrb, mrb_event->event);
}

mrb_value 
mrb_sdl_event_inspect(mrb_state* mrb, mrb_value self)
{
  char buf[256];
  int len;
  struct mrb_sdl_event* mrb_event;
  mrb_event = mrb_sdl_event_get_ptr(mrb, self);

  if (!mrb_event) return mrb_nil_value();

  len = snprintf(buf, sizeof(buf), "{type: %s}",
    mrb_sym2name(mrb, mrb_obj_to_sym(mrb, mrb_sdl_event_type_to_sym(mrb, mrb_event->event))));
  return mrb_str_new(mrb, buf, len);
}

mrb_value
mrb_sdl_event_keycode_to_sym(mrb_state *mrb, SDL_Keycode keycode)
{
  switch (keycode)
  {
    case (SDLK_LEFT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "left"));
    case (SDLK_RIGHT):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "right"));
    case (SDLK_UP):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "up"));
    case (SDLK_DOWN):
      return mrb_symbol_value(mrb_intern_cstr(mrb, "down"));
  }

  return mrb_nil_value();
}

mrb_value
mrb_sdl_event_key(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_event* mrb_event;
  mrb_event = mrb_sdl_event_get_ptr(mrb, self);

  return mrb_sdl_event_keycode_to_sym(mrb, mrb_event->event.key.keysym.sym);
}

mrb_value
mrb_sdl_event_resize_width(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_event* mrb_event;
  mrb_event = mrb_sdl_event_get_ptr(mrb, self);

  return mrb_fixnum_value(mrb_event->event.window.data1);
}

mrb_value
mrb_sdl_event_resize_height(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_event* mrb_event;
  mrb_event = mrb_sdl_event_get_ptr(mrb, self);

  return mrb_fixnum_value(mrb_event->event.window.data2);
}

void
init_mrb_sdl_event(mrb_state* mrb, struct RClass* mrb_sdl_class)
{
  mrb_sdl_event_class = mrb_define_class_under(mrb, mrb_sdl_class, "Event", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_sdl_event_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_sdl_event_class, "key", mrb_sdl_event_key, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_sdl_event_class, "resize_width", mrb_sdl_event_resize_width, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_sdl_event_class, "resize_height", mrb_sdl_event_resize_height, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb_sdl_event_class, "type", mrb_sdl_event_type, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_sdl_event_class, "inspect", mrb_sdl_event_inspect, MRB_ARGS_NONE());
}