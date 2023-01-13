#include "gui/sdl2.h"
#include "gui/glfw.h"
#include "def.h"


int main(int argc, char *argv[]) {
#ifdef MODE_GLFW
  if (!glfw_init()) return 1;
  glfw_start();
  glfw_uninit();
#else
  if (!sdl_init()) return 1;
  sdl_start();
  sdl_uninit();
#endif
  return 0;
}
