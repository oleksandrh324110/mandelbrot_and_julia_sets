#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <algorithm>
#include <iostream>

#include "gfx/shader.h"

int main(void) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });

  GLfloat vertices[] = {1,  1,  0,  //
                        1,  -1, 0,  //
                        -1, -1, 0,  //
                        -1, 1,  0};
  GLuint indicies[] = {0, 1, 2,  //
                       2, 3, 0};

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  Shader shader("../res/shaders/main.vs", "../res/shaders/main.fs");

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad |
      ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsLight();
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  int polygon_mode = GL_FILL;
  glm::ivec2 window_size;
  glm::vec2 offset(0, 0);
  float zoom = 1;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_Q))
      glfwSetWindowShouldClose(window, true);

    {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      ImGui::Begin("Title");
      {
        ImGui::Text("Polygon mode:");
        ImGui::RadioButton("Line Mode (GL_LINE)", &polygon_mode, GL_LINE);
        ImGui::RadioButton("Fill Mode (GL_FILL)", &polygon_mode, GL_FILL);
        glPolygonMode(GL_FRONT_AND_BACK,
                      polygon_mode == GL_LINE ? GL_LINE : GL_FILL);

        ImGui::Text("Adjust Offset:");
        ImGui::SliderFloat("x offset", &offset.x, -3, 1);
        ImGui::SliderFloat("y offset", &offset.y, -2, 2);

        ImGui::Text("Zoom:");
        ImGui::SliderFloat("zoom", &zoom, 0.001, 2);
      }
      ImGui::End();
    }
    {
      glClearColor(0.2, 0.2, 0.2, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      glfwGetWindowSize(window, &window_size.x, &window_size.y);
      shader.set_ivec2("window_size", window_size);
      shader.set_vec2("offset", offset);
      shader.set_float("zoom", zoom);

      shader.use();
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    {
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      ImGui::EndFrame();

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
      }
    }
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}
