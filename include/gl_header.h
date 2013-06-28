#ifndef MRUBY_SDL_GL_HEADER_H
#define MRUBY_SDL_GL_HEADER_H

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(GRAPHICS_GLES2)
  #include <SDL2/SDL_opengles2.h>
#else 
  #define GL_GLEXT_PROTOTYPES
  #include <SDL2/SDL_opengl.h>
#endif

#endif