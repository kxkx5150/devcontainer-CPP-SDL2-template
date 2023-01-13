#ifndef MODE_GLFW

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>
#include <cstdio>
#include <iostream>
#include <ostream>
#include "sdl2.h"
#include "../def.h"


#define USE_OPENGL false


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_GLContext glContext;


void sdl_run_glframe() {
  // OPENGL
  glClearColor(0, 0, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}
void sdl_run_frame() {
  // Dots
  int pitch;
  int row, col;
  uint32_t *dst;
  void *pixels;

  SDL_LockTexture(texture, NULL, &pixels, &pitch);
  dst = (uint32_t *)pixels;

  int height = HEIGHT * ZOOM;
  int width = WIDTH * ZOOM;

  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      // RGB8888
      *dst++ = 0xff005599;
    }
  }

  SDL_UnlockTexture(texture);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}
void sdl_start() {
  bool running = true;
  SDL_Event event;

  int start_time = 0;
  int duration = 0;
  const int frame_duration = 1 + 1000 / FPS;

  while (running) {
    start_time = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_RETURN:
              //
              break;
          }
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym) {
            case SDLK_RETURN:
              //
              break;
          }
          break;
      }
    }

    if (USE_OPENGL) {
      sdl_run_glframe();
    } else {
      sdl_run_frame();
    }

    duration = SDL_GetTicks() - start_time;
    if (duration < frame_duration) {
      SDL_Delay(frame_duration - duration);
    }
  }
}
bool sdl_init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  window =
      SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH * ZOOM, HEIGHT * ZOOM, SDL_WINDOW_OPENGL);

  if (!window) {
    printf("Failed to create SDL Window\n");
    return false;
  }
  if (USE_OPENGL) {
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
      printf("Failed to create OpenGL context\n");
      return false;
    }
  } else {
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetScale(renderer, 1, 1);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING, WIDTH * ZOOM,
                                HEIGHT * ZOOM);
  }
  return true;
}
void sdl_uninit() {
  if (USE_OPENGL) {
    SDL_GL_DeleteContext(glContext);
  } else {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
  }
  SDL_DestroyWindow(window);
  SDL_CloseAudio();
  SDL_Quit();
}
#endif
