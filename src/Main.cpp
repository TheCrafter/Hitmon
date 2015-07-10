#include <windows.h>
#include "PopupMenu.hpp"
#include "UI/Window.hpp"

#define TRAY_ID WM_USER + 1
#define TRAY_MSG WM_USER + 2

class WindowData
{
public:
    LPCTSTR wndClassName;
    UI::Window<WindowData>* thisWindow;
    PopupMenu* menu;

    WNDPROC wndProcCallback;

    WindowData(LPCTSTR className)
        : wndClassName(className),
        wndProcCallback(DefWindowProc),
        menu(0)
    {
    }
};

void HandleMenuSelection(PopupMenu::MenuItem item, HWND window)
{
    // Retrieve user data
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
            WindowData* data = (WindowData*)GetWindowLongPtr(window, GWLP_USERDATA);
            data->menu = new PopupMenu(window, HandleMenuSelection);
            data->menu->AddItem(1, "Do something");
            data->menu->AddItem(2, "Do something else");
            data->menu->AddItem(3, "exit");
        }break;

        case WM_DESTROY:
        {
            WindowData* data = (WindowData*)GetWindowLongPtr(window, GWLP_USERDATA);
            delete data->menu;
            PostQuitMessage(0);
        }break;

        default:
        {
            return DefWindowProc(window, msg, wParam, lParam);
        }
    }

    return 0;
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

    WindowData data("mainWindowClass");
    data.wndProcCallback = HitmonWindowProc;

    UI::Window<WindowData> window(data);

    WindowData* wndData = window.GetDataPtr();
    wndData->thisWindow = &window;

    window.Init(instance);

    // Show tray icon
    NOTIFYICONDATA trayData = ShowTrayIcon(window.GetWindow());

    MSG msg;
    int getMsgRVal;
    while((getMsgRVal = GetMessage(&msg, 0, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // Hide tray icon
    Shell_NotifyIcon(NIM_DELETE, &trayData);
    return 0;
}