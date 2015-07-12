#include "MainWindowData.hpp"
#include <functional>
#include "Config.hpp"

namespace UI
{
    //==================================================
    //= Static members
    //==================================================

    const std::string MainWindowData::mClassName = "MainWindowClass";


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
                    case WM_LBUTTONDOWN:
                    {
                        mTrayIcon.ShowMenu();
                    }break;
                }
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
        return mClassName.c_str();
    }

} // namespace UI