#include "MainWindowData.hpp"
#include <functional>
#include "Config.hpp"

namespace UI
{
    //==================================================
    //= Static members
    //==================================================

    const std::string MainWindowData::CLASS_NAME = "MainWindowClass";


    //==================================================
    //= Public functions
    //==================================================

    MainWindowData::MainWindowData(HINSTANCE instance) : mInstance(instance)
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
                    case WM_RBUTTONDOWN:
                    {
                        mTrayIcon.ShowMenu();
                    }break;
                }
            }break;

            case TRAY_HIT_MILESTONE:
            {
                int* x = (int*)wParam;
                mTrayIcon.ShowBalloon("Milestone reached",
                                      "Current hits: " + std::to_string(*x));
                delete x;
            }break;

            case WM_CREATE:
            {
                mTrayIcon.Init(window, mInstance, "Hitmon is running...");
                mTrayIcon.Show();
            }break;

            case WM_DESTROY:
            {
                mTrayIcon.Shutdown();
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
        return CLASS_NAME.c_str();
    }

} // namespace UI