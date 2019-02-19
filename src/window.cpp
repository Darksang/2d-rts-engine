#include "window.h"

Window::Window(int Width, int Height, const char * Name) {
    this->Width = Width;
    this->Height = Height;
    this->Name = Name;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    MainWindow = glfwCreateWindow(this->Width, this->Height, this->Name, 0, 0);
    
    if (!MainWindow) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(MainWindow);

    glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(MainWindow, FramebufferSizeCallback);
}

Window::~Window() {
    glfwTerminate();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(MainWindow);
    glfwPollEvents();
}

void Window::GetCursorPosition(double * X, double * Y) {
    glfwGetCursorPos(MainWindow, X, Y);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(MainWindow);
}

void Window::Close() {
    glfwSetWindowShouldClose(MainWindow, true);
}

void Window::OSXFix() {
    int x, y;
    glfwGetWindowPos(MainWindow, &x, &y);
    glfwSetWindowPos(MainWindow, ++x, y);
}

// Callbacks
void Window::FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height) {
    glViewport(0, 0, Width, Height);
}