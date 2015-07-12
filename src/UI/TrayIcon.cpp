#include "TrayIcon.hpp"
#include "Config.hpp"
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
        mIconData.hIcon = (HICON)LoadImage(
            instance,
            "res/hitmon.ico",
            IMAGE_ICON,
            LR_DEFAULTSIZE,
            LR_DEFAULTSIZE,
            LR_LOADFROMFILE);

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
        //                                      --> Show current hits today <--
        if(item.id == mTaskbarIconMenu->GetIdByTitle(mMenuItemsStrings[0]))
        {
            std::string msg = "Current hits: ";
            msg += std::to_string(mKbdHook.GetHitCount());

            MessageBox(
                window,
                msg.c_str(),
                "Current hits",
                MB_ICONINFORMATION);
        }
        //                                                   --> exit <--
        else if(item.id == mTaskbarIconMenu->GetIdByTitle(mMenuItemsStrings[1]))
        {
            SendMessage(window, WM_CLOSE, 0, 0);
        }
    }
}