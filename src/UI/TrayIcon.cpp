#include "TrayIcon.hpp"
#include "Config.hpp"

namespace UI
{
    //==================================================
    //= Public functions
    //==================================================

    TrayIcon::TrayIcon(HWND window, const std::string& hoverMsg)
    {
        mIconData.cbSize = sizeof(mIconData);
        mIconData.hWnd = window;
        mIconData.uID = TRAY_ID;
        mIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        mIconData.uCallbackMessage = TRAY_MSG;
        mIconData.hIcon = LoadIcon(0, IDI_SHIELD);
        strncpy(mIconData.szTip, hoverMsg.c_str(), 128);
    }

    TrayIcon::~TrayIcon()
    {
        // TODO: Make destructor use only what's necessary from
        // mIconData. Not everything

        // Hide tray icon
        Shell_NotifyIcon(NIM_DELETE, &mIconData);
    }

    void TrayIcon::Show()
    {
        Shell_NotifyIcon(NIM_ADD, &mIconData);
    }
}