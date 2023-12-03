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

static const int WIDTH = 800;
static const int HEIGHT = 600;

static int window_width = WIDTH;
static int window_height = HEIGHT;


void processInput(GLFWwindow* window);


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
        // x, y, z,                         r, g, b
        WIDTH*0.5f, HEIGHT*0.75f, 0.0f,     1.0f, 0.0f, 0.f,
        WIDTH*0.25f, HEIGHT*0.25f, 0.0f,    0.0f, 1.0f, 0.f,
        WIDTH*0.75f, HEIGHT*0.25f, 0.0f,    0.0f, 0.0f, 1.f
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


    mat4 projection;
    glm_ortho(0, WIDTH, 0, HEIGHT, -1.0f, 1.0f, projection);

    mat4 view = GLM_MAT4_IDENTITY_INIT;

    mat4 model = GLM_MAT4_IDENTITY_INIT;
  
    mat4 mvp;
    glm_mat4_mul(projection, view, mvp);
    glm_mat4_mul(mvp, model, mvp);

    GLuint mvpID = glGetUniformLocation(programID, "mvp");


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        glUniformMatrix4fv(mvpID, 1, GL_FALSE, (const GLfloat*)mvp);


        glfwGetWindowSize(window, &window_width, &window_height);
        glViewport(0, 0, window_width, window_height);

        // Draw triangle
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}
