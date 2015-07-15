#include "KbdHook.hpp"
#include "UI/MainWindowData.hpp"
#include "IO/SaveFileIO.hpp"

KbdHook* kbdObjPtr = nullptr;
long long count = 0;

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
    {
        kbdObjPtr->SetHitCount(kbdObjPtr->GetHitCount() + 1);

        if(kbdObjPtr->IsMilestone(kbdObjPtr->GetHitCount()))
        {
            long long* x = new long long(kbdObjPtr->GetHitCount());
            PostMessage(
                FindWindow(UI::MainWindowData::CLASS_NAME.c_str(), 0),
                TRAY_HIT_MILESTONE,
                (WPARAM)x,
                0);
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//==================================================
//= Public functions
//==================================================
KbdHook::KbdHook()
{
    IO::SaveFileIO io(HITMON_SAVEFILE_NAME);
    mHitCount = io.ReadTodaysHits();
}

KbdHook::~KbdHook()
{
    // Save count
    IO::SaveFileIO io(HITMON_SAVEFILE_NAME);
    io.SaveCount(mHitCount);

    UnhookWindowsHookEx(mHook);
}

void KbdHook::Init(HINSTANCE instance)
{
    kbdObjPtr = this;

    // Set kbd hook
    mHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, instance, 0);
}

long long KbdHook::GetHitCount() const
{
    return mHitCount;
}

void KbdHook::SetHitCount(long long newCount)
{
    mHitCount = newCount;
}

bool KbdHook::IsMilestone(long long val)
{
    return mMilestone.IsMilestone(val);
}