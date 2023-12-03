#include "initWindow.h"
#include "shaderLoader.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>


#define SHADER_PATH "shaders/"
#define VERT_SHADER SHADER_PATH "vert.glsl"
#define FRAG_SHADER SHADER_PATH "frag.glsl"

#define WIDTH 1000
#define HEIGHT 700


void processInput(GLFWwindow* window);
void window_size_callback(GLFWwindow* window, int width, int height);

static int x = 0;
static int y = 0;


int main()
{
    glewExperimental = 1;
    GLFWwindow* window = initWindow(WIDTH, HEIGHT, "Hello World! :)");
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    printf("OpenGL: version supported by this platform (%s): \n", glGetString(GL_VERSION));

    static const GLfloat vertexData[] = {
        // x, y, z, r, g, b
        0.0f, 0.5f, 0.0f,    1.0f, 0.0f, 0.f,
        0.5f, -0.5, 0.0f,    0.0f, 1.0f, 0.f,
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.f
    };



    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // position attribute
    // position = 0
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);

    // color attribute
    // position = 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


    glBindVertexArray(0);


    GLuint programID = LoadShaders(VERT_SHADER, FRAG_SHADER);
    

    glfwSetWindowSizeCallback(window, window_size_callback);


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);


        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float aspectRatio = (float)width / (float)height;
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        glm_scale_uni(model, aspectRatio);

        GLint model_loc = glGetUniformLocation(programID, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)model);

        // Draw triangle
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glViewport(x, y, width, height);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, 1);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) x -= 10;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) x += 10;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) y += 10;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) y -= 10;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(x, y, width, height);
}
