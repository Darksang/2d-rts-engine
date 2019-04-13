#include "engine/window.h"

Window::Window(int Width, int Height, const char * Name) {
    this->Name = Name;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    WindowPointer = glfwCreateWindow(Width, Height, Name, 0, 0);
    
    if (!WindowPointer) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetWindowUserPointer(WindowPointer, this);

    glfwMakeContextCurrent(WindowPointer);

    glfwSetFramebufferSizeCallback(WindowPointer, FramebufferSizeCallback);
    glfwSetKeyCallback(WindowPointer, KeyCallback);
}

Window::~Window() {
    glfwDestroyWindow(WindowPointer);
    glfwTerminate();
}

GLFWwindow * Window::GetWindowPointer() {
    return WindowPointer;
}

void Window::GetWindowSize(int * Width, int * Height) {
    glfwGetWindowSize(WindowPointer, Width, Height);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(WindowPointer);
    glfwPollEvents();
}

void Window::SetCursorMode(int Value) {
    glfwSetInputMode(WindowPointer, GLFW_CURSOR, Value);
}

void Window::GetCursorPosition(double * X, double * Y) {
    glfwGetCursorPos(WindowPointer, X, Y);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(WindowPointer);
}

void Window::Close() {
    glfwSetWindowShouldClose(WindowPointer, true);
}

void Window::OSXFix() {
    int x, y;
    glfwGetWindowPos(WindowPointer, &x, &y);
    glfwSetWindowPos(WindowPointer, ++x, y);
}