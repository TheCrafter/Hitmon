#include "TrayIcon.hpp"
#include "Config.hpp"

namespace UI
{
    //==================================================
    //= Public functions
    //==================================================

    void TrayIcon::Init(HWND window, const std::string& hoverMsg)
    {
        // Setup PopupMenu
        auto x = std::bind(
            &TrayIcon::HandleMenuSelection,
            this,
            std::placeholders::_1,
            std::placeholders::_2);

        mTaskbarIconMenu = new PopupMenu(window, x);

        // Add items to PopupMenu
        mTaskbarIconMenu->AddItem(1, "Do something");
        mTaskbarIconMenu->AddItem(2, "Do something else");
        mTaskbarIconMenu->AddItem(3, "exit");

        // Set IconData
        mIconData.cbSize = sizeof(mIconData);
        mIconData.hWnd = window;
        mIconData.uID = TRAY_ID;
        mIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        mIconData.uCallbackMessage = TRAY_MSG;
        mIconData.hIcon = LoadIcon(0, IDI_SHIELD);

        // 128 is the maximum size allowed in szTip
        strncpy(mIconData.szTip, hoverMsg.c_str(), 128);
    }

    void TrayIcon::Shutdown()
    {
        // TODO: Make Shutdown() use only what's necessary from
        // mIconData. Not everything

        // Hide tray icon
        Shell_NotifyIcon(NIM_DELETE, &mIconData);
        delete mTaskbarIconMenu;
    }

    void TrayIcon::Show()
    {
        Shell_NotifyIcon(NIM_ADD, &mIconData);
    }

    void TrayIcon::ShowMenu()
    {
        mTaskbarIconMenu->Show();
    }

    //==================================================
    //= Private functions
    //==================================================

    void TrayIcon::HandleMenuSelection(PopupMenu::MenuItem item, HWND window)
    {
        if(item.id == mTaskbarIconMenu->GetIdByTitle("exit"))
            SendMessage(window, WM_CLOSE, 0, 0);
    }
}