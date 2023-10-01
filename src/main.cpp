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
        particleSystem.update(static_cast<float>(deltaTime), currentTime);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        for (int i = 0; i < 50; i++) {
            Particle* particles = particleSystem.getParticles();
            glColor3f(0.6f, 0.7f, 0.8f);
            float x = particles[i].position[0];
            float y = particles[i].position[1];

            // Specify the four vertices for the rectangle
            glVertex3f(x - particles[i].width/2, y - particles[i].height/2, 0.0f);  // bottom-left corner
            glVertex3f(x + particles[i].width/2, y - particles[i].height/2, 0.0f);  // bottom-right corner
            glVertex3f(x + particles[i].width/2, y + particles[i].height/2, 0.0f);  // top-right corner
            glVertex3f(x - particles[i].width/2, y + particles[i].height/2, 0.0f);  // top-left corner

            // glVertex3f(particles[i].position[0], particles[i].position[1], particles[i].position[2]);
        }
        glEnd();

        if ( glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS )
        {
            float windValue = 0.1f;
            particleSystem.setWind(windValue);
        }
        if ( glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS )
        {
            float windValue = -0.1f;
            particleSystem.setWind(windValue);
        }

        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(-1.0f, -1.0f); // bottom-left
        glVertex2f( 1.0f, -1.0f); // bottom-right
        glVertex2f( 1.0f, -0.8f); // top-right
        glVertex2f(-1.0f, -0.8f); // top-left
        for ( auto &landing : particleSystem.landings )
        {
            float elapsedTime = currentTime - landing.second;

            if ( elapsedTime < 1.0 )
            {
                glColor3f(0.5f, 0.5f, 0.5f);
            }
            else
            {
                float darkenFactor = 1.0f - 0.5f * (elapsedTime / 2.0f);
                glColor3f(0.5f * darkenFactor, 0.5f * darkenFactor, 0.5f * darkenFactor);
            }
            float landing_x = landing.first;
            float landing_size = 0.008f;
            glVertex2f(landing_x - landing_size, -0.808f - landing_size);
            glVertex2f(landing_x + landing_size, -0.808f - landing_size);
            glVertex2f(landing_x + landing_size, -0.808f + landing_size);
            glVertex2f(landing_x - landing_size, -0.808f + landing_size);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}