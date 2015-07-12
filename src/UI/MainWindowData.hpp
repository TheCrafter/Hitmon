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
    MainWindowData();

    /// Window procedure
    LRESULT CALLBACK wndProcCallback(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam);

    /// Retrieves a pointer to the class name
    LPCTSTR GetClassName() const;

private:
    /// Class name to use with RegisterClass[Ex]()
    const static std::string mClassName;

    /// The icon that appears in system tray
    TrayIcon mTrayIcon;
};

} // namespace UI

#endif