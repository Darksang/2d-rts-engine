#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

class Window {
    public:
        Window(int Width, int Height, const char * Name);
        ~Window();

        GLFWwindow * GetWindow();
        int GetWidth();
        void SetWidth(int W);
        int GetHeight();
        void SetHeight(int H);
        const char * GetName();

        void SwapBuffers();

        void SetCursorMode(int Value);
        void GetCursorPosition(double * X, double * Y);

        bool ShouldClose();
        void Close();

        void OSXFix();
    
    private:
        GLFWwindow * MainWindow;

        int Width;
        int Height;

        const char * Name;

        // GLFW Callbacks
        inline static void FramebufferSizeCallback(GLFWwindow * Win, int Width, int Height) {
            // Update our Window object Width and Height using the pointer stored
            Window * WindowPtr = static_cast<Window *>(glfwGetWindowUserPointer(Win));
            WindowPtr->SetWidth(Width);
            WindowPtr->SetHeight(Height);
            glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
        }

        inline static void KeyCallback(GLFWwindow * Win, int Key, int Scancode, int Action, int Mods) {
            if (Key == GLFW_KEY_H)
                if (Action == GLFW_PRESS)
                    std::cout << "H pressed" << std::endl; 
                else if (Action == GLFW_RELEASE)
                    std::cout << "H released" << std::endl;
        }
};

#endif