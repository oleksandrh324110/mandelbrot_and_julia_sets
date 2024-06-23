#include "App.hpp"

int main(void) {
  // GLuint VAO;
  // glGenVertexArrays(1, &VAO);
  // glBindVertexArray(VAO);

  // GLuint VBO;
  // glGenBuffers(1, &VBO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // GLuint EBO;
  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(0);

  // gfx::Shader shader("../res/shaders/main.vs", "../res/shaders/main.fs");

  // int polygon_mode = GL_FILL;
  // glm::ivec2 window_size;
  // glm::vec2 offset(0, 0);
  // float zoom = 1;

  // while (!glfwWindowShouldClose(window)) {
  //   glfwPollEvents();

  //   if (glfwGetKey(window, GLFW_KEY_Q))
  //     glfwSetWindowShouldClose(window, true);

  //   {
  //     ImGui::Begin("Title");
  //     {
  //       ImGui::Text("Polygon mode:");
  //       ImGui::RadioButton("Line Mode (GL_LINE)", &polygon_mode, GL_LINE);
  //       ImGui::RadioButton("Fill Mode (GL_FILL)", &polygon_mode, GL_FILL);
  //       glPolygonMode(GL_FRONT_AND_BACK, polygon_mode == GL_LINE ? GL_LINE : GL_FILL);

  //       ImGui::Text("Adjust Offset:");
  //       ImGui::SliderFloat("x offset", &offset.x, -3, 1);
  //       ImGui::SliderFloat("y offset", &offset.y, -2, 2);

  //       ImGui::Text("Zoom:");
  //       ImGui::SliderFloat("zoom", &zoom, 0.001, 2);
  //     }
  //     ImGui::End();
  //   }
  //   {
  //     glfwGetWindowSize(window, &window_size.x, &window_size.y);
  //     shader.set_ivec2("window_size", window_size);
  //     shader.set_vec2("offset", offset);
  //     shader.set_float("zoom", zoom);

  //     shader.use();
  //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //   }
  //   {}
  //   glfwSwapBuffers(window);
  // }

  // ImGui_ImplOpenGL3_Shutdown();
  // ImGui_ImplGlfw_Shutdown();
  // ImGui::DestroyContext();

  // glfwTerminate();
}
