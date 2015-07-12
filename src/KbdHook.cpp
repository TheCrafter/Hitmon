#include "KbdHook.hpp"

KbdHook* kbdObjPtr = nullptr;
unsigned int count = 0;

//==================================================
//= Static functions
//==================================================

LRESULT CALLBACK KbdHook::LowLevelKeyboardProc(
    int    nCode,
    WPARAM wParam,
    LPARAM lParam)
{
    if(nCode < 0 || kbdObjPtr == nullptr)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        kbdObjPtr->SetHitCount(kbdObjPtr->GetHitCount() + 1);

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//==================================================
//= Public functions
//==================================================

KbdHook::~KbdHook()
{
    UnhookWindowsHookEx(mHook);
}

void KbdHook::Init(HINSTANCE instance)
{
    kbdObjPtr = this;

    // Set kbd hook
    mHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, instance, 0);
}

unsigned int KbdHook::GetHitCount() const
{
    return mHitCount;
}

void KbdHook::SetHitCount(unsigned int newCount)
{
    mHitCount = newCount;
}