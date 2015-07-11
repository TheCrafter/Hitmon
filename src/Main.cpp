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

    // Create the window
    UI::MainWindowData data;

    UI::Window<UI::MainWindowData> window(data);

    UI::MainWindowData* wndData = window.GetDataPtr();
    wndData->thisWindow = &window;

    if(!window.Init(instance))
        return -1;

    // Create and show the tray icon
    UI::TrayIcon trayIcon(window.GetWindow(), "Hitmon is running...");

    trayIcon.Show();

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