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
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n";

        // Creare vertex shader
        unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Creare fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Creare shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // ?terge shader-ele individuale, nu mai sunt necesare dup? ce sunt link-uite
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
