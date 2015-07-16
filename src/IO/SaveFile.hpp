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

#ifndef HITMON_SAVEFILE
#define HITMON_SAVEFILE

#include <string>

namespace IO
{
    
class SaveFile
{
public:
    /// Constructor
    SaveFile(const std::string& date, long long count);

    /// Parsing-file constructor
    SaveFile(const std::string& fileString);

    /// Gets a string as input and sets mDate and mCount after parsing it
    void Parse(const std::string& str);

    /// Retrieves a string with this save file's date
    const std::string& GetDate() const;

    /// Retrieves this save file's hit count
    long long GetCount() const;

    /// True if this save file's date is today
    bool IsToday() const;

    /// Compares two save files based on their dates
    bool operator==(const SaveFile& rhs) const;
    bool operator!=(const SaveFile& rhs) const;

private:
    /// String with the date in format: Fri Jul 15
    std::string mDate;

    /// Current hit count
    long long mCount;

    /// Is the date same as today
    bool mIsToday;

    /// Updates the mIsToday variable after checking if mDate is today
    bool CheckIfDateIsToday();
};

} // namespace IO

#endif