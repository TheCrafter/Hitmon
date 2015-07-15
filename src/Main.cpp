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

#include <windows.h>
#include "Config.hpp"
#include "PopupMenu.hpp"
#include "UI/Window.hpp"
#include "UI/MainWindowData.hpp"
#include "UI/TrayIcon.hpp"

int CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR     cmdArgs,
    int       cmdShow)
{
    // Avoid "unused formal variable" warnings
    (void)prevInstance;
    (void)cmdArgs;
    (void)cmdShow;

    // Create the window data
    UI::MainWindowData data(instance);

    // Create the window
    UI::Window<UI::MainWindowData> window(data);
    if(!window.Init(instance))
        return -1;

    // Message loop
    MSG msg;
    int getMsgRVal;
    while((getMsgRVal = GetMessage(&msg, 0, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}