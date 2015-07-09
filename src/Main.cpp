#include <windows.h>
#include "PopupMenu.hpp"

#define TRAY_ID 666
#define TRAY_MSG 666

struct WindowData
{
    PopupMenu* menu;
};

void HandleMenuSelection(PopupMenu::MenuItem item, HWND window)
{
    WindowData* data = (WindowData*)GetWindowLongPtr(window, GWLP_USERDATA);
    if(item.id == data->menu->GetIdByTitle("exit"))
        SendMessage(window, WM_CLOSE, 0, 0);
}

LRESULT CALLBACK HitmonWindowProc(
    HWND   window,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch(msg)
    {
        // Handle messages from tray icon
        case TRAY_MSG:
        {
            switch(lParam)
            {
                case WM_LBUTTONDOWN:
                {
                    WindowData* data = (WindowData*)GetWindowLongPtr(window, GWLP_USERDATA);
                    data->menu->Show();
                }break;
            }
        }break;

        case WM_CREATE:
        {
            // Configure window data
            WindowData* data = new WindowData();
            data->menu = new PopupMenu(window, HandleMenuSelection);
            data->menu->AddItem(1, "Do something");
            data->menu->AddItem(2, "Do something else");
            data->menu->AddItem(3, "exit");

            // Set userdata
            SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)data);
        }break;

        case WM_DESTROY:
        {
            WindowData* data = (WindowData*)GetWindowLongPtr(window, GWLP_USERDATA);
            delete data->menu;
            delete data;
            PostQuitMessage(0);
        }break;

        default:
        {
            return DefWindowProc(window, msg, wParam, lParam);
        }
    }

    return 0;
}

WNDCLASSEX CreateWindowClass(HINSTANCE instance)
{
    WNDCLASSEX mainWClass;
    mainWClass.cbSize = sizeof(WNDCLASSEX);
    mainWClass.style = CS_HREDRAW | CS_VREDRAW;
    mainWClass.lpfnWndProc = HitmonWindowProc;
    mainWClass.cbClsExtra = 0;
    mainWClass.cbWndExtra = 0;
    mainWClass.hInstance = instance;
    mainWClass.hIcon = LoadIcon(0, IDI_SHIELD);
    mainWClass.hCursor = LoadCursor(0, IDC_CROSS);
    mainWClass.hbrBackground = 0;
    mainWClass.lpszMenuName = 0;
    mainWClass.lpszClassName = "MainWClass";
    mainWClass.hIconSm = 0;

    return mainWClass;
}

NOTIFYICONDATA ShowTrayIcon(HWND window)
{
    NOTIFYICONDATA rVal;
    rVal.cbSize = sizeof(rVal);
    rVal.hWnd = window;
    rVal.uID = TRAY_ID;
    rVal.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    rVal.uCallbackMessage = TRAY_MSG;
    rVal.hIcon = LoadIcon(0, IDI_SHIELD);
    strncpy(rVal.szTip, "Hitmon is running...", 128);
    // Set guid later
    //rVal.guidItem = ...;

    Shell_NotifyIcon(NIM_ADD, &rVal);

    return rVal;
}

int CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR     cmdArgs,
    int       cmdShow)
{
    (void)prevInstance;
    (void)cmdArgs;
    (void)cmdShow;

    // Create window class
    WNDCLASSEX mainWClass = CreateWindowClass(instance);
    
    // Register window class
    if(RegisterClassEx(&mainWClass) == 0)
        return -1;

    // Create window
    HWND window = CreateWindowEx(
        0,                              // Extended window style of the window created
        "MainWClass",                   // Class name from previous call to RegisterClass[Ex]
        "Hitmon",                       // Window Name
        0,                              // Window style
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

    // Show tray icon
    NOTIFYICONDATA trayData = ShowTrayIcon(window);

    MSG msg;
    int getMsgRVal;
    while((getMsgRVal = GetMessage(&msg, 0, 0, 0)) != 0)
    {
        if(getMsgRVal == -1)
            return -1;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // Hide tray icon
    Shell_NotifyIcon(NIM_DELETE, &trayData);
    return 0;
}