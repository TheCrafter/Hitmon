#ifndef HITMON_POPUPMENU
#define HITMON_POPUPMENU

#include <windows.h>
#include <string>
#include <functional>
#include <map>

//==================================================
/// \brief A simple class that encapsulates the basic
///        logic for a PopupMenu.
///
/// The class currently contains only basic management
/// of the PopupMenu. See it's public member functions
/// for more information.
//==================================================
class PopupMenu
{
public:
    //==================================================
    /// \brief Plain data class to group an item's attributes.
    //==================================================
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

    //==================================================
    /// Constructor
    //==================================================
    PopupMenu(HWND ownerWindow, std::function<void(MenuItem, HWND)> selectionHandlerCallback);
    
    //==================================================
    /// Destructor
    //==================================================
    ~PopupMenu();

    //==================================================
    /// \brief Adds a new item on menu.
    ///
    /// \param pos The position of the item.
    /// \param title The title of the item.
    //==================================================
    void AddItem(int pos, const std::string& title);

    //==================================================
    /// \brief Shows the menu in the current cursor position.
    //==================================================
    void Show();

    //==================================================
    /// \brief Gets the id of a menu item by each title.
    ///
    /// \param title The title to search.
    ///
    /// \return The id of the item or 0 if the id does not exist.
    //==================================================
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