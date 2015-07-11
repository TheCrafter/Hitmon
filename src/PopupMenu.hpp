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

#ifndef HITMON_POPUPMENU
#define HITMON_POPUPMENU

#include <windows.h>
#include <string>
#include <functional>
#include <map>

/// A simple class that encapsulates the basic logic for a PopupMenu
class PopupMenu
{
public:
    /// Plain data class to group an item's attributes
    class MenuItem
    {
    public:
        /// The position in menu.
        int pos;

        /// The id of the attribute (for the TrackPopMenu function)
        unsigned int id;

        /// Item's title
        std::string title;
    };

    /// Constructor
    PopupMenu(HWND ownerWindow, std::function<void(MenuItem, HWND)> selectionHandlerCallback);
    
    /// Destructor
    ~PopupMenu();

    /// Adds a new item on menu.
    void AddItem(int pos, const std::string& title);

    /// Shows the menu in the current cursor position
    void Show();

    /// Retrieves the id of a menu item by its title
    unsigned int GetIdByTitle(const std::string& title);

private:
    /// Handler to menu.
    HMENU mMenu;

    /// Handler to menu's owner window.
    HWND mOwnerWindow;

    /// The id of the next item to be added.
    int mNextItemId /* Initial value is 1 */ ;
    
    /// All items that are curently in menu.
    std::map<unsigned int, MenuItem> mMenuItems;

    /// A pointer to a function that takes as a parameter the
    /// it of the selected item. This function should handle the
    /// selection.
    std::function<void(MenuItem, HWND)> mSelectionHandlerCallback;
};

#endif