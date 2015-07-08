#include "windows.h"

LRESULT CALLBACK hitmonWindowProc(
    HWND   window,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }break;

        default:
        {
            return DefWindowProc(window, msg, wParam, lParam);
        }
    }

    return 0;
}

WNDCLASSEX createWindowClass(HINSTANCE instance)
{
    WNDCLASSEX mainWClass;
    mainWClass.cbSize = sizeof(WNDCLASSEX);
    mainWClass.style = CS_HREDRAW | CS_VREDRAW;
    mainWClass.lpfnWndProc = hitmonWindowProc;
    mainWClass.cbClsExtra = 0;
    mainWClass.cbWndExtra = 0;
    mainWClass.hInstance = instance;
    mainWClass.hIcon = LoadIcon(0, IDI_SHIELD);
    mainWClass.hCursor = LoadCursor(0, IDC_CROSS);
    mainWClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    mainWClass.lpszMenuName = 0;
    mainWClass.lpszClassName = "MainWClass";
    mainWClass.hIconSm = 0;

    return mainWClass;
}

int CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR     cmdArgs,
    int       cmdShow)
{
    // Create window class
    WNDCLASSEX mainWClass = createWindowClass(instance);
    
    // Register window class
    if(RegisterClassEx(&mainWClass) == 0)
        return -1;

    // Create window
    HWND window = CreateWindowEx(
        0,                              // Extended window style of the window created
        "MainWClass",                   // Class name from previous call to RegisterClass[Ex]
        "Hitmon",                       // Window Name
        WS_OVERLAPPEDWINDOW |
        WS_MAXIMIZEBOX      |
        WS_MINIMIZEBOX      |
        WS_VISIBLE,                     // Window style
        64,                             // Initial x position for window
        64,                             // Initial y position for window
        640,                            // Window width
        480,                            // Window height
        0,                              // Handle to parent window
        0,                              // Handle to menu
        instance,                       // A handle to the instance of the module to be associated with the window.
        0);                             // Pointer to params for the window

    if(window == 0)
        return -1;

    MSG msg;
    int getMsgRVal;
    while((getMsgRVal = GetMessage(&msg, 0, 0, 0)) != 0)
    {
        if(getMsgRVal == -1)
            return -1;

        // TODO: Read WHY I need TranslateMessage
        //TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}