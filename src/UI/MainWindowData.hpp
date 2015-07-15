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

#ifndef HITMON_MAINWINDOWDATA
#define HITMON_MAINWINDOWDATA

#include <Windows.h>
#include <string>
#include "Window.hpp"
#include "TrayIcon.hpp"

namespace UI
{

/// Data wrapper for the Main windoow
class MainWindowData
{
public:
    /// Constructor
    MainWindowData(HINSTANCE instance);

    /// Window procedure
    LRESULT CALLBACK wndProcCallback(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam);

    /// Retrieves a pointer to the class name
    LPCTSTR GetClassName() const;

    /// Class name to use with RegisterClass[Ex]()
    const static std::string CLASS_NAME;

private:
    /// The icon that appears in system tray
    TrayIcon mTrayIcon;

    /// Handle to the instance
    HINSTANCE mInstance;
};

} // namespace UI

#endif