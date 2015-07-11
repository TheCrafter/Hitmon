/**********************************************************/
/*                                                        */
/*              __/^\__                                   */
/*            ./       \.                                 */
/*           /    ___    \    THE                         */
/*          /   ./   \.   \    CRAFTER                    */
/*         /  ./       \.  \                              */
/*        /  / ___   ___ \  \                             */
/*       /  / |___|-|___| \  \                            */
/*      /  /               \  \                           */
/*      \  \               /  /                           */
/*       \  \/\         /\/  /                            */
/*        \    \       /    /                             */
/*         `\   \     /   /`                              */
/*           `\  \   /  /`                                */
/*             `\_\ /_/`                                  */
/*    /  /                   \  \                         */
/*   /   \                   /    \                       */
/*   |  _.\\                 //._  |                      */
/*   !!!!  \|               |/  !!!!                      */
/*   \\\\                       ////                      */
/*   _______________________________                      */
/*   | o o o o o ------ o o o o o o |                     */
/*   | o ~ ~ o ~~ o o o o o o o o ~~|                     */
/*   | o ~ ~ o o ~~ o o o o o o o ~~|                     */
/*   | o - - - - - - - - - - - - - ~|                     */
/*   |______________________________|                     */
/*                                                        */
/**********************************************************/

#include <windows.h>
#include "Config.hpp"
#include "PopupMenu.hpp"
#include "UI/Window.hpp"
#include "UI/MainWindowData.hpp"

NOTIFYICONDATA ShowTrayIcon(HWND window)
{
    NOTIFYICONDATA rVal;
    rVal.cbSize = sizeof(rVal);
    rVal.hWnd = window;
    rVal.uID = TRAY_ID;
    rVal.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    rVal.uCallbackMessage = TRAY_MSG;
    rVal.hIcon = LoadIcon(0, IDI_SHIELD);
    strncpy(rVal.szTip, "Hitmon is running...", 128);
    // Set guid later
    //rVal.guidItem = ...;

    Shell_NotifyIcon(NIM_ADD, &rVal);

    return rVal;
}

int CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR     cmdArgs,
    int       cmdShow)
{
    (void)prevInstance;
    (void)cmdArgs;
    (void)cmdShow;

    UI::MainWindowData data;

    UI::Window<UI::MainWindowData> window(data);

    UI::MainWindowData* wndData = window.GetDataPtr();
    wndData->thisWindow = &window;

    if(!window.Init(instance))
        return -1;

    // Show tray icon
    NOTIFYICONDATA trayData = ShowTrayIcon(window.GetWindow());

    MSG msg;
    int getMsgRVal;
    while((getMsgRVal = GetMessage(&msg, 0, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // Hide tray icon
    Shell_NotifyIcon(NIM_DELETE, &trayData);
    return 0;
}