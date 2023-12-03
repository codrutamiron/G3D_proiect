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
    float vertices[] = {
    -0.5f, -0.5f, 0.0f, // stânga jos
     0.5f, -0.5f, 0.0f, // dreapta jos
     0.0f,  0.5f, 0.0f  // sus
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Legare VAO
    glBindVertexArray(VAO);

    // Legare VBO ?i copierea datelor în buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Setare pointeri pentru atributele vertex-urilor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO ?i VAO pentru a evita modific?ri accidentale
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        // Procesare input
        // ...

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Seteaz? culoarea de fundal
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenare triunghi
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // Legare VAO (nu este necesar dac? avem un singur VAO, dar folositor pentru practic?)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers ?i procesare evenimente IO
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();


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
