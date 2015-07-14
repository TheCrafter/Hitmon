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