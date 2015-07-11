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
#include "PopupMenu.hpp"

namespace UI
{

/// Data wrapper for the Main windoow
class MainWindowData
{
public:
    // TODO: Try to make thisWindow private
    Window<MainWindowData>* thisWindow;

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
    /// The taskbar's icon menu
    PopupMenu* mTaskbarIconMenu;

    /// Class name to use with RegisterClass[Ex]()
    const static std::string mClassName;

    /// Function to handle selections from taskbar icon's menu
    void HandleMenuSelection(PopupMenu::MenuItem item, HWND window);
};

} // namespace UI

#endif