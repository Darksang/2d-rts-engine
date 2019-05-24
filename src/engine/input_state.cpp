#include "engine/input_state.h"

#include <iostream>

const Key InputState::AllKeys[] = { KEY_SPACE, KEY_APOSTROPHE, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, 
KEY_SEMICOLON, KEY_EQUAL, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, 
KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE_ACCENT, KEY_ESCAPE, KEY_ENTER, KEY_TAB, KEY_BACKSPACE, KEY_INSERT, KEY_DELETE,
KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME, KEY_END, KEY_CAPS_LOCK, KEY_SCROLL_LOCK, KEY_NUM_LOCK, KEY_PRINT_SCREEN, KEY_PAUSE, KEY_F1, 
KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_LEFT_SHIFT, KEY_LEFT_CONTROL, KEY_LEFT_ALT, KEY_LEFT_SUPER, KEY_RIGHT_SHIFT,
KEY_RIGHT_CONTROL, KEY_RIGHT_ALT, KEY_RIGHT_SUPER, KEY_MENU };

const MouseButton InputState::AllMouseButtons[] = { MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT, MOUSE_BUTTON_MIDDLE, MOUSE_BUTTON_4,
MOUSE_BUTTON_5, MOUSE_BUTTON_6, MOUSE_BUTTON_7, MOUSE_BUTTON_8 };

InputState::InputState(GLFWwindow * Window) : Window(Window) {
    memset(KeyboardStates, KeyState::RELEASED, sizeof(KeyboardStates));
    memset(MouseStates, KeyState::RELEASED, sizeof(MouseStates));
}

void InputState::Update() {
    // Reset needed stuff
    MouseWheelDelta = 0.0f;

    // Process Keyboard
    for (const auto Key : AllKeys) {
        bool IsKeyDown = glfwGetKey(Window, Key) == GLFW_PRESS;

        KeyState LastState = KeyboardStates[Key];

        if (IsKeyDown && LastState == KeyState::JUST_DOWN)
            KeyboardStates[Key] = KeyState::DOWN;
        else if (IsKeyDown && (LastState == KeyState::RELEASED || LastState == KeyState::JUST_RELEASED))
            KeyboardStates[Key] = KeyState::JUST_DOWN;
        else if (!IsKeyDown && (LastState == KeyState::DOWN || LastState == KeyState::JUST_DOWN))
            KeyboardStates[Key] = KeyState::JUST_RELEASED;
        else if (!IsKeyDown && LastState == KeyState::JUST_RELEASED)
            KeyboardStates[Key] = KeyState::RELEASED;
    }

    // Process Mouse Buttons
    for (const auto Button : AllMouseButtons) {
        bool IsButtonDown = glfwGetMouseButton(Window, Button) == GLFW_PRESS;

        KeyState LastState = MouseStates[Button];

        if (IsButtonDown && LastState == KeyState::JUST_DOWN)
            MouseStates[Button] = KeyState::DOWN;
        else if (IsButtonDown && (LastState == KeyState::RELEASED || LastState == KeyState::JUST_RELEASED))
            MouseStates[Button] = KeyState::JUST_DOWN;
        else if (!IsButtonDown && (LastState == KeyState::DOWN || LastState == KeyState::JUST_DOWN))
            MouseStates[Button] = KeyState::JUST_RELEASED;
        else if (!IsButtonDown && LastState == KeyState::JUST_RELEASED)
            MouseStates[Button] = KeyState::RELEASED;
    }
}

bool InputState::IsKeyDown(Key K) {
    return (KeyboardStates[K] == KeyState::DOWN || KeyboardStates[K] == KeyState::JUST_DOWN);
}

bool InputState::IsKeyJustDown(Key K) {
    return KeyboardStates[K] == KeyState::JUST_DOWN;
}

bool InputState::IsMouseButtonDown(MouseButton M) {
    return (MouseStates[M] == KeyState::DOWN || MouseStates[M] == KeyState::JUST_DOWN);
}

bool InputState::IsMouseButtonJustDown(MouseButton M) {
    return MouseStates[M] == KeyState::JUST_DOWN;
}