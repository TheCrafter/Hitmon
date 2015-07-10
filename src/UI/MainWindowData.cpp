#include "MainWindowData.hpp"
#include <functional>
#include "Config.hpp"

namespace UI
{
    const std::string MainWindowData::mClassName = "MainWindowClass";

    //==================================================
    //= Public functions
    //==================================================

    MainWindowData::MainWindowData(LPCTSTR className)
        : wndClassName(className),
        menu(0)
    {
    }

    LRESULT CALLBACK MainWindowData::wndProcCallback(
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
                        menu->Show();
                    }break;
                }
            }break;

            case WM_CREATE:
            {
                auto x = std::bind(
                    &MainWindowData::HandleMenuSelection,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2);

                menu = new PopupMenu(window, x);
                menu->AddItem(1, "Do something");
                menu->AddItem(2, "Do something else");
                menu->AddItem(3, "exit");
            }break;

            case WM_DESTROY:
            {
                delete menu;
                PostQuitMessage(0);
            }break;

            default:
            {
                return DefWindowProc(window, msg, wParam, lParam);
            }
        }

        return 0;
    }

    LPCTSTR MainWindowData::GetClassName() const
    {
        return mClassName.c_str();
    }

    //==================================================
    //= Private functions
    //==================================================

    void MainWindowData::HandleMenuSelection(PopupMenu::MenuItem item, HWND window)
    {
        if(item.id == menu->GetIdByTitle("exit"))
            SendMessage(window, WM_CLOSE, 0, 0);
    }

} // namespace UI