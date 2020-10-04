#include <GLFW/glfw3.h>

#include "Editor/Editor.h"

int main()
{
    glfwInit();

    Finally::Editor::Editor{}.Start();

    glfwTerminate();

    return 0;
}
