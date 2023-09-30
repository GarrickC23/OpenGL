#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cstdlib>
#include "Particle/Particle.h"

using namespace std; 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

ParticleSystem particleSystem;

void initializeGL() {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit(-1); // Failed to initialize GLAD
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_POINT_SMOOTH); // Makes points circular.
}

int main()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    double lastTime = glfwGetTime();

    while(!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Update
        particleSystem.update(static_cast<float>(deltaTime));

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10.0f); // Makes the particle's point size bigger, adjust as necessary
        glBegin(GL_POINTS);
        glPointSize(5.0f);
        for (int i = 0; i < 1000; i++) {
            Particle* particles = particleSystem.getParticles();
            glVertex3f(particles[i].position[0], particles[i].position[1], particles[i].position[2]);
        }
        glEnd();

        // glBegin(GL_QUADS);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f( 0.5f, -0.5f);
        // glVertex2f( 0.5f,  0.5f);
        // glVertex2f(-0.5f,  0.5f);
        // glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}