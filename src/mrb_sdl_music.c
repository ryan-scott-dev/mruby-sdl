#include "mrb_sdl_music.h"

#include <mrbconf.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/value.h>

static struct RClass* mrb_sdl_music_class = NULL;

struct mrb_data_type mrb_sdl_music_get_ptr_type = { "Music", mrb_sdl_music_free };

void
mrb_sdl_music_free(mrb_state *mrb, void *ptr)
{
  struct mrb_sdl_music* tm = (struct mrb_sdl_music*)ptr;

  if(tm->music) {
    Mix_FreeMusic(tm->music);
    tm->music = NULL;
  }

  mrb_free(mrb, ptr);
}

mrb_value
mrb_sdl_music_wrap(mrb_state *mrb, Mix_Music *music)
{
  struct mrb_sdl_music* tm = (struct mrb_sdl_music*)mrb_malloc(mrb, sizeof(struct mrb_sdl_music));
  tm->music = music;
  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_sdl_music_class, &mrb_sdl_music_get_ptr_type, tm));
}

struct mrb_sdl_music*
mrb_sdl_music_get_ptr(mrb_state* mrb, mrb_value value)
{
  return DATA_CHECK_GET_PTR(mrb, value, &mrb_sdl_music_get_ptr_type, struct mrb_sdl_music);
}

mrb_value
mrb_sdl_music_loop(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_music* mrb_music;
  mrb_music = mrb_sdl_music_get_ptr(mrb, self);

  Mix_PlayMusic(mrb_music->music, -1);

  return self;
}

mrb_value
mrb_sdl_music_play(mrb_state *mrb, mrb_value self)
{
  struct mrb_sdl_music* mrb_music;
  mrb_music = mrb_sdl_music_get_ptr(mrb, self);

  Mix_PlayMusic(mrb_music->music, 0);

  return self;
}

void
init_mrb_sdl_music(mrb_state* mrb, struct RClass* mrb_sdl_class)
{
  mrb_sdl_music_class = mrb_define_class_under(mrb, mrb_sdl_class, "Music", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_sdl_music_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_sdl_music_class, "loop", mrb_sdl_music_loop, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb_sdl_music_class, "play", mrb_sdl_music_play, MRB_ARGS_NONE());
}