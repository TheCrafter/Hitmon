/******************************************************************************/
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