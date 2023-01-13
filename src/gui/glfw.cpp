#ifdef MODE_GLFW

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glfw.h"
#include "../def.h"


void glfw_run_frame() {}
void glfw_start() {
  GLFWwindow* window =
      glfwCreateWindow(WIDTH * ZOOM, HEIGHT * ZOOM, "GLFW", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    return;
  }

  while (glfwWindowShouldClose(window) == GL_FALSE) {
    glClearColor(0.1f, 0.8f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return;
}
bool glfw_init() {
  if (glfwInit() == GL_FALSE) {
    return -1;
  }
  return true;
}
void glfw_uninit() {}
#endif
