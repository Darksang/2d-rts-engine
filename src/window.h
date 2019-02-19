#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

class Window {
    public:
        GLFWwindow * MainWindow;

        int Width;
        int Height;

        const char * Name;

        Window(int Width, int Height, const char * Name);
        ~Window();

        void SwapBuffers();

        void GetCursorPosition(double * X, double * Y);

        bool ShouldClose();
        void Close();

        void OSXFix();
    
    private:
        static void FramebufferSizeCallback(GLFWwindow * Window, int Width, int Height);
};

#endif