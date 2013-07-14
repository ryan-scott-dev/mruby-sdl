#ifndef MRUBY_SDL_GL_HEADER_H
#define MRUBY_SDL_GL_HEADER_H

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(GRAPHICS_GLES2)
  #include <SDL2/SDL_opengles2.h>

  #define glBindVertexArray glBindVertexArrayOES
  #define glGenVertexArrays glGenVertexArraysOES
  #define glDeleteVertexArrays glDeleteVertexArraysOES
	#define GL_RED GL_RED_EXT
#else 
  #define GL_GLEXT_PROTOTYPES
  #include <SDL2/SDL_opengl.h>
#endif

#endif