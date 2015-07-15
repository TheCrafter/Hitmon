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

#ifndef HITMON_WINDOW
#define HITMON_WINDOW

#include <Windows.h>
#include <memory>

namespace UI
{

//==================================================
/// Wrapper class for creating windows using the WINAPI.
///
/// \tparam WindowData This template parameter should be a struct or a
///         class with at least 3 public members (LPCTSTR GetClassName(), 
///         WNDPROC).
//==================================================
template<typename WindowData>
class Window
{
public:
    /// Constructor
    Window(std::unique_ptr<WindowData>&& data);

    /// Register class and create window
    bool Init(HINSTANCE instance);
    
    /// Retrieves the handle of the window
    HWND GetWindow() const;

private:
    /// Window's data
    std::unique_ptr<WindowData> mData;

    /// Handle to the window
    HWND mWindow;

    /// Registers the window class
    bool RegisterWindowClass(HINSTANCE instance);

    /// The default window proc of the window.
    static LRESULT CALLBACK WindowProc(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam);
};

// Include the ipp file that contains the implementations of the above functions.
#include "Window.ipp"

} // namespace UI

#endif