#ifndef HITMON_MAINWINDOWDATA
#define HITMON_MAINWINDOWDATA

#include <Windows.h>
#include <string>
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

    LPCTSTR GetClassName() const;

private:
    PopupMenu* menu;
    const static std::string mClassName;

    void HandleMenuSelection(PopupMenu::MenuItem item, HWND window);
};

} // namespace UI

#endif