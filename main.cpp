#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int createShaderProgram();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}
)";

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "Modelagem Hierarquica - Codigo Base",
        NULL,
        NULL
    );

    if (window == NULL)
    {
        std::cout << "Erro ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Erro ao inicializar GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned int shaderProgram = createShaderProgram();

    float vertices[] = {
        // posições             // cores

        // face traseira
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

        // face frontal
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,

        // face esquerda
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

        // face direita
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,

        // face inferior
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,

         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

        // face superior
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f
    };

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 2.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f,
            100.0f
        );

        glUniformMatrix4fv(
            viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::rotate(
            model,
            glm::radians(25.0f),
            glm::vec3(1.0f, 0.0f, 0.0f)
        );

        model = glm::rotate(
            model,
            glm::radians(-35.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glBindVertexArray(VAO);

        glUniformMatrix4fv(
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}

unsigned int createShaderProgram()
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );

    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        NULL
    );

    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(0, 0, width, height);
}