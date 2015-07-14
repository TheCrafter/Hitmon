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

#ifndef HITMON_KBDHOOK
#define HITMON_KBDHOOK

#include <Windows.h>
#include <list>

class KbdHook
{
public:
    ~KbdHook();

    void Init(HINSTANCE instance);

    long long GetHitCount() const;

    void SetHitCount(long long newCount);

    bool CheckVal(long long val);

private:
    HHOOK mHook;

    long long mHitCount;

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
        bool CheckVal(long long val)
        {
            // Avoid unecessary checks to save time
            if(val != mNextValToCheck)
                return false;

            mLastValToCheck = mNextValToCheck;
            mNextValToCheck = GetNextVal(CurMilestone, RestMilestones...);

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
        long long GetNextVal(CurMilestone x, rest... args)
        {
            if(mLastValToCheck == -1)
                return x;

            return (mLastValToCheck < x) ? x : GetNextVal(args...);
        }

        template<typename LastMilestone>
        long long GetNextVal(LastMilestone x)
        {
            return x;
        }
        //----------------------------------------------
    };

    Milestone<100, 1000, 5000, 10000, 50000, 100000, 1000000, 2000000> mMilestone;
};

#endif