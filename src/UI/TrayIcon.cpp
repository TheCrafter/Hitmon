#include "TrayIcon.hpp"
#include "Config.hpp"
#include "Resources.hpp"
#include <string>

namespace UI
{
    //==================================================
    //= Public functions
    //==================================================

    TrayIcon::TrayIcon()
    {
        mMenuItemsStrings.push_back("Show current hits today");
        mMenuItemsStrings.push_back("exit");
    }

    void TrayIcon::Init(HWND window, HINSTANCE instance, const std::string& hoverMsg)
    {
        mWindow = window;

        // Init hook
        mKbdHook.Init(instance);

        // Create PopupMenu
        mTaskbarIconMenu = new PopupMenu(
            window,
            std::bind(
                &TrayIcon::HandleMenuSelection,
                this,
                std::placeholders::_1,
                std::placeholders::_2));

        // Add items to PopupMenu
        {
            int pos = 1;
            for(auto v : mMenuItemsStrings)
                mTaskbarIconMenu->AddItem(pos++, v);
        }

        // Set IconData
        mIconData.cbSize = sizeof(mIconData);
        mIconData.hWnd = window;
        mIconData.uID = TRAY_ID;
        mIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        mIconData.uCallbackMessage = TRAY_MSG;
        mIconData.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_APP_ICON));

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

    void TrayIcon::ShowBalloon(
        const std::string& title,
        const std::string& msg,
        unsigned int timeout /* = 5000 */) const
    {
        NOTIFYICONDATA data;

        data.cbSize = sizeof(NOTIFYICONDATA);
        data.hWnd = mWindow;
        data.uID = TRAY_ID;
        data.uFlags = NIF_INFO;
        data.uTimeout = timeout;

        // 128 is the maximum bytes allowed in szInfo
        strncpy(data.szInfo, msg.c_str(), 128);
        // and 64 ub szInfoTitle
        strncpy(data.szInfoTitle, title.c_str(), 64);

        data.dwInfoFlags = NIIF_USER;

        Shell_NotifyIcon(NIM_MODIFY, &data);
    }

    //==================================================
    //= Private functions
    //==================================================

    void TrayIcon::HandleMenuSelection(PopupMenu::MenuItem item, HWND window)
    {   
        //                                      --> Show current hits today <--
        if(item.id == mTaskbarIconMenu->GetIdByTitle(mMenuItemsStrings[0]))
        {
            std::string msg = "Current hits: ";
            msg += std::to_string(mKbdHook.GetHitCount());

            ShowBalloon("Current hits", msg);
        }
        //                                                   --> exit <--
        else if(item.id == mTaskbarIconMenu->GetIdByTitle(mMenuItemsStrings[1]))
        {
            SendMessage(window, WM_CLOSE, 0, 0);
        }
    }
}