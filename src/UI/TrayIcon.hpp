/******************************************************************************/
/*                                                                            */
/*              __/^\__                                                       */
/*            ./       \.                                                     */
/*           /    ___    \    THE                                             */
/*          /   ./   \.   \    CRAFTER                                        */
/*         /  ./       \.  \                                                  */
/*        /  / ___   ___ \  \                                                 */
/*       /  / |___|-|___| \  \                                                */
/*      /  /               \  \                                               */
/*      \  \               /  /                                               */
/*       \  \/\         /\/  /                                                */
/*        \    \       /    /                                                 */
/*         `\   \     /   /`                                                  */
/*           `\  \   /  /`                                                    */
/*             `\_\ /_/`                                                      */
/*    /  /                   \  \                                             */
/*   /   \                   /    \                                           */
/*   |  _.\\                 //._  |                                          */
/*   !!!!  \|               |/  !!!!                                          */
/*   \\\\                       ////                                          */
/*   _______________________________                                          */
/*   | o o o o o ------ o o o o o o |                                         */
/*   | o ~ ~ o ~~ o o o o o o o o ~~|                                         */
/*   | o ~ ~ o o ~~ o o o o o o o ~~|                                         */
/*   | o - - - - - - - - - - - - - ~|                                         */
/*   |______________________________|                                         */
/*                                                                            */
/*                                                                            */
/* Copyright 2015 Vlachakis Dimitris                                          */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License");            */
/* you may not use this file except in compliance with the License.           */
/* You may obtain a copy of the License at                                    */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/*                                                                            */
/******************************************************************************/

#ifndef HITMON_TRAYICON
#define HITMON_TRAYICON

#include <Windows.h>
#include <vector>
#include <string>
#include "PopupMenu.hpp"
#include "KbdHook.hpp"

namespace UI
{

/// Creates and shows a tray icon in taskbar notification area
class TrayIcon
{
public:
    /// Constructor
    TrayIcon();

    /// Initialize the TrayIcon
    void Init(HWND window, HINSTANCE instance, const std::string& hoverMsg);

    /// De-initialize the TrayIcon
    void Shutdown();

    /// Show the icon
    void Show();

    /// Show popup menu
    void ShowMenu();

    /// Show a notification balloon
    void ShowBalloon(const std::string& title,
                     const std::string& msg,
                     unsigned int timeout = 5000) const;

private:
    /// Struct that holds the icon's data
    NOTIFYICONDATA mIconData;

    /// Handle to the owner window
    HWND mWindow;

    /// The taskbar's icon menu
    PopupMenu* mTaskbarIconMenu;

    /// Vector with menu items' strings
    std::vector<std::string> mMenuItemsStrings;

    /// The keyboard hook
    KbdHook mKbdHook;

    /// Function to handle selections from taskbar icon's menu
    void HandleMenuSelection(PopupMenu::MenuItem item, HWND window);
};

} // namespace UI

#endif