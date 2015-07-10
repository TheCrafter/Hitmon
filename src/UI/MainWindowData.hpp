#ifndef HITMON_MAINWINDOWDATA
#define HITMON_MAINWINDOWDATA

#include <Windows.h>
#include "Window.hpp"
#include "PopupMenu.hpp"

namespace UI
{

class MainWindowData
{
public:
    // TODO: make those stuff private somehow
    LPCTSTR wndClassName;
    Window<MainWindowData>* thisWindow;

    MainWindowData(LPCTSTR className);

    LRESULT CALLBACK wndProcCallback(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam);

private:
    PopupMenu* menu;

    void HandleMenuSelection(PopupMenu::MenuItem item, HWND window);
};

} // namespace UI

#endif