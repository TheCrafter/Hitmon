#include "PopupMenu.hpp"
#include <algorithm>

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

    // Insert the new item in menu items map
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
    auto iterator = std::find_if(
        std::begin(mMenuItems),
        std::end(mMenuItems),
        [&title](std::pair<unsigned int, MenuItem> pair) -> bool
        {
            return pair.second.title.compare(title) == 0;
        });

    return (iterator != std::end(mMenuItems)) ? iterator->first : 0;
}