#include "libs.h"

#include <glfw3.h>
#include <iostream>

int main() {
    // Ini?ializeaz? GLFW
    if (!glfwInit()) {
        std::cerr << "Eroare la ini?ializarea GLFW" << std::endl;
        return -1;
    }

    // Creeaz? o fereastr?
    GLFWwindow* window = glfwCreateWindow(800, 600, "Acvariu OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Eroare la crearea ferestrei" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Seteaz? contextul curent
    glfwMakeContextCurrent(window);

    // Bucla principal?
    while (!glfwWindowShouldClose(window)) {
        // Cur??? buffer-ul
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        // Aici vei ad?uga codul pentru a desena

        // Schimb? buffer-ele
        glfwSwapBuffers(window);

        // Proceseaz? evenimentele de intrare
        glfwPollEvents();
    }

    // Cur??? ?i închide
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
