#include <GLFW/glfw3.h>

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
    if (!window) return -1;

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-1.0f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(1.0f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}