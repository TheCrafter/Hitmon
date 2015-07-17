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

#include "SaveFileIO.hpp"
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>
#include <memory>
#include "SaveFile.hpp"

namespace IO
{
    //==================================================
    //= Non-member function declaration
    //==================================================

    // Remove time from date string
    std::string RemoveTimeFromDate(const std::string&& str);

    // Get a string with current date and time
    std::string GetCurrentTime();

    //==================================================
    //= Public functions
    //==================================================

    SaveFileIO::SaveFileIO(const std::string& filename) : mFilename(std::move(filename))
    {
    }

    bool SaveFileIO::SaveCount(long long hitCount) const
    {
        // Open the file
        std::ofstream stream(mFilename, std::ios_base::out);

        // Return false if failed to open the file
        if(stream.fail())
            return false;

        // Get date string and reformat it
        std::string date(RemoveTimeFromDate(GetCurrentTime()));

        // Create save file
        SaveFile saveFile(date, hitCount);

        // Create string to write
        std::string toWrite(saveFile.GetDate() + " " + std::to_string(saveFile.GetCount()));
        stream.write(toWrite.c_str(), toWrite.length());

        // Check if write was successful
        if(stream.fail())
            return false;

        // Close the stream
        stream.close();

        return true;
    }

    long long SaveFileIO::ReadTodaysHits() const
    {
        // Open the file
        std::ifstream stream(mFilename, std::ios_base::in);

        // Return false if failed to open the file
        if(stream.fail())
            return 0;

        // Read line
        std::string bufStr;
        std::getline(stream, bufStr);

        // Check if read was successful
        if(stream.fail())
            return 0;

        // Create SaveFily by parsing the string we read
        SaveFile saveFile(bufStr);

        // Check if the saved data is from today
        if(!saveFile.IsToday())
            return 0;

        return saveFile.GetCount();
    }


    //==================================================
    //= Non-member function implementation
    //==================================================}

    std::string RemoveTimeFromDate(const std::string&& str)
    {
        // ctime returns time at this format: Wed May 30 12:25:03 2012
        // We only need the "Wed May 30" part. That's why we return a
        // substring from the start till the 3rd space

        // Get an iterator to 3rd space character location
        std::string::const_iterator it = std::begin(str);
        for(unsigned int i = 0; i < 3; i++)
            it = std::find(it + 1, std::end(str), ' ');

        return std::string(std::begin(str), it);
    }

    std::string GetCurrentTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t curTime = std::chrono::system_clock::to_time_t(now);

        return std::string(ctime(&curTime));
    }
}