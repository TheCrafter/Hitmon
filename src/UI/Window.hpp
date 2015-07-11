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

#ifndef HITMON_WINDOW
#define HITMON_WINDOW

namespace UI
{

#include <Windows.h>

//==================================================
/// Wrapper class for creating windows using the WINAPI.
///
/// \tparam WindowData This template parameter should be a struct or a
///         class with at least 3 public members (LPCTSTR GetClassName(), 
///         Window<WindowData>*, WNDPROC).
//==================================================
template<typename WindowData>
class Window
{
public:
    /// Constructor
    Window(WindowData data);

    /// Register class and create window
    bool Init(HINSTANCE instance);
    
    /// Retrieves the handle of the window
    HWND GetWindow() const;

    /// Retrieves a pointer to this window's data
    WindowData* GetDataPtr();

private:
    /// Window's data
    WindowData mData;

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