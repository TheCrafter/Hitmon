/******************************************************************************/
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

#include "SaveFile.hpp"
#include <chrono>
#include <ctime>

namespace IO
{
    //==================================================
    //= Non-member function declaration
    //==================================================

    // Get iterator to the 'pos' time we find the char 'check'
    std::string::const_iterator GetIteratorToChar(
        const std::string& str,
        char check = ' ',
        unsigned int pos = 3);

    //==================================================
    //= Public functions
    //==================================================

    SaveFile::SaveFile(const std::string& date, long long count)
        : mDate(date),
        mCount(count),
        mIsToday(CheckIfDateIsToday())
    {
    }

    SaveFile::SaveFile(const std::string& fileString)
    {
        Parse(fileString);
        mIsToday = CheckIfDateIsToday();
    }

    void SaveFile::Parse(const std::string& str)
    {
        std::string::const_iterator it = std::begin(str);
        for(unsigned int i = 0; i < 3; i++)
            it = std::find(it + 1, std::end(str), ' ');

        mDate = std::string(std::begin(str), it);
        mCount = std::stoll(std::string(it, std::end(str)));
    }

    const std::string& SaveFile::GetDate() const
    {
        return mDate;
    }

    long long SaveFile::GetCount() const
    {
        return mCount;
    }

    bool SaveFile::IsToday() const
    {
        return mIsToday;
    }

    bool SaveFile::operator==(const SaveFile& rhs) const
    {
        return mDate == rhs.mDate;
    }

    bool SaveFile::operator!=(const SaveFile& rhs) const
    {
        return !operator==(rhs);
    }


    //==================================================
    //= Private functions
    //==================================================

    bool SaveFile::CheckIfDateIsToday()
    {
        // Get current time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t curTime = std::chrono::system_clock::to_time_t(now);

        std::string time(ctime(&curTime));

        std::string::const_iterator dateIt = GetIteratorToChar(time);
        std::string::const_iterator strIt = GetIteratorToChar(mDate);

        return std::string(std::begin(time), dateIt) == std::string(std::begin(mDate), strIt);
    }


    //==================================================
    //= Non-member function implementation
    //==================================================

    std::string::const_iterator GetIteratorToChar(
        const std::string& str,
        char check /* = ' ' */,
        unsigned int pos /* = 3 */)
    {
        std::string::const_iterator it = std::begin(str);
        for(unsigned int i = 0; i < pos; i++)
            it = std::find(it + 1, std::end(str), check);

        return std::move(it);
    }

} // namespace IO