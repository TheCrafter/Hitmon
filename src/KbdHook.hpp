/******************************************************************************/
/*                                                                            */
/*              __/^\__                                                       */
/*            ./       \.                                                     */
/*           /    ___    \    THE                                             */
/*          /   ./   \.   \    CRAFTER                                        */
/*         /  ./       \.  \                                                  */
/*        /  / ___   ___ \  \                                                 */
/*       /  / |___|-|___| \  \                                                */
/*      /  /               \  \                                               */
/*      \  \               /  /                                               */
/*       \  \/\         /\/  /                                                */
/*        \    \       /    /                                                 */
/*         `\   \     /   /`                                                  */
/*           `\  \   /  /`                                                    */
/*             `\_\ /_/`                                                      */
/*    /  /                   \  \                                             */
/*   /   \                   /    \                                           */
/*   |  _.\\                 //._  |                                          */
/*   !!!!  \|               |/  !!!!                                          */
/*   \\\\                       ////                                          */
/*   _______________________________                                          */
/*   | o o o o o ------ o o o o o o |                                         */
/*   | o ~ ~ o ~~ o o o o o o o o ~~|                                         */
/*   | o ~ ~ o o ~~ o o o o o o o ~~|                                         */
/*   | o - - - - - - - - - - - - - ~|                                         */
/*   |______________________________|                                         */
/*                                                                            */
/*                                                                            */
/* Copyright 2015 Vlachakis Dimitris                                          */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License");            */
/* you may not use this file except in compliance with the License.           */
/* You may obtain a copy of the License at                                    */
/*                                                                            */
/*      http://www.apache.org/licenses/LICENSE-2.0                            */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/*                                                                            */
/******************************************************************************/

#ifndef HITMON_KBDHOOK
#define HITMON_KBDHOOK

#include <Windows.h>
#include <list>

class KbdHook
{
public:
    /// Destructor
    ~KbdHook();

    /// Gets the object ready for usage
    void Init(HINSTANCE instance);

    /// Returns the current hit count
    long long GetHitCount() const;

    /// Updates the current hit count
    void SetHitCount(long long newCount);

    /// Returns true if val is a milesotne, false if not
    bool IsMilestone(long long val);

private:
    /// To low level keyboard hook, used to get keyboard hits
    HHOOK mHook;

    /// Current hit count, counting from the start of the program
    long long mHitCount;

    /// Callback function for keyboard events
    static LRESULT CALLBACK LowLevelKeyboardProc(
        int    nCode,
        WPARAM wParam,
        LPARAM lParam);

    /// Templated class to bundle milesotne logic
    template<long long CurMilestone, long long... RestMilestones>
    class Milestone
    {
    public:
        /// Constructor
        Milestone()
        {
            mNextValToCheck = CurMilestone;
            mLastValToCheck = -1;
        }

        /// Check if a value matches a milestone
        bool IsMilestone(long long val)
        {
            // Avoid unecessary checks to save time
            if(val != mNextValToCheck)
                return false;

            mLastValToCheck = mNextValToCheck;
            mNextValToCheck = GetNextMilestone(CurMilestone, RestMilestones...);

            return true;
        }

    private:
        /// The next value to be checked
        long long mNextValToCheck;

        /// The last value we checked (initial value: -1)
        long long mLastValToCheck;

        // Recursive checking for next value to check
        //----------------------------------------------
        template<typename CurMilestone, typename... rest>
        long long GetNextMilestone(CurMilestone x, rest... args)
        {
            if(mLastValToCheck == -1)
                return x;

            return (mLastValToCheck < x) ? x : GetNextMilestone(args...);
        }

        template<typename LastMilestone>
        long long GetNextMilestone(LastMilestone x)
        {
            return x;
        }
        //----------------------------------------------
    };

    Milestone<100, 1000, 5000, 7500, 10000, 50000, 100000, 300000, 1000000, 2000000, 5000000> mMilestone;
};

#endif