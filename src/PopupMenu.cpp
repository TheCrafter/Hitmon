#include "PopupMenu.hpp"

PopupMenu::PopupMenu(HWND ownerWindow, std::function<void(MenuItem, HWND)> selectionHandlerCallback)
    : mOwnerWindow(ownerWindow),
    mSelectionHandlerCallback(selectionHandlerCallback),
    mNextItemId(1)
{
    mMenu = CreatePopupMenu();
}

PopupMenu::~PopupMenu()
{
    DestroyMenu(mMenu);
}

void PopupMenu::AddItem(int pos, const std::string& title)
{
    // Create mew menu item
    MenuItem newItem;
    newItem.id = mNextItemId++;
    newItem.pos = pos;
    newItem.title = title;

    // Now actually insert it in menu
    InsertMenu(
        mMenu,
        pos,
        MF_BYPOSITION |
        MF_ENABLED |
        MF_STRING,
        newItem.id,
        title.c_str());

    // Insert the new item on map
    mMenuItems[newItem.id] = newItem;
}

void PopupMenu::Show()
{
    // Retrieve current cursor position
    POINT curPos;
    GetCursorPos(&curPos);

    unsigned int trackResult = TrackPopupMenuEx(
        mMenu,
        TPM_RETURNCMD,
        curPos.x,
        curPos.y,
        mOwnerWindow,
        0);

    // Handle the selection
    mSelectionHandlerCallback(mMenuItems[trackResult], mOwnerWindow);
}

unsigned int PopupMenu::GetIdByTitle(const std::string& title)
{
    for(std::map<unsigned int, MenuItem>::iterator it = mMenuItems.begin();
        it != mMenuItems.end();
        ++it)
    {
        if(it->second.title.compare(title) == 0)
            return it->first;
    }

    return 0;
}