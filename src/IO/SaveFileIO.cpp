#include "SaveFileIO.hpp"
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>

namespace IO
{
    //==================================================
    //= Non-member functions
    //==================================================

    std::string::const_iterator GetIteratorToChar(const std::string&& str, char check, unsigned int pos)
    {
        std::string::const_iterator it = std::begin(str);
        for(unsigned int i = 0; i < pos; i++)
            it = std::find(it + 1, std::end(str), check);

        return std::move(it);
    }

    std::string RemoveTimeFromDate(const std::string&& str)
    {
        // ctime returns time at this format: Wed May 30 12:25:03 2012
        // We only need the "Wed May 30" part. That's why we return a
        // substring from the start till the 3rd space

        // Get an iterator to 3rd space character location
        std::string::const_iterator it = GetIteratorToChar(std::move(str), ' ', 3);
        
        return std::string(std::begin(str), it);
    }

    std::string FormatReadFile(const std::string& str)
    {
        // The file already contains data in this format: Thu Jul 16 500
        // We only need the "500" part. That's why we return a substring
        // from the 3rd space till the end

        // Get an iterator to 3rd space character location
        std::string::const_iterator it = GetIteratorToChar(std::move(str), ' ', 3);
        
        return std::string(it, std::end(str));
    }

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

        // Get current time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t curTime = std::chrono::system_clock::to_time_t(now);

        // Get date string and reformat it
        std::string date(
            RemoveTimeFromDate(std::string(ctime(&curTime))) +
            " " +
            std::to_string(hitCount));

        stream.write(date.c_str(), date.length());

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

        // Count characters in file
        stream.seekg(0, std::ios_base::end);
        std::streampos pos = stream.tellg();
        stream.seekg(0, std::ios_base::beg);

        // Init buffer to hold the read data
        int bufsize = static_cast<int>(pos) + 1;
        char* buf = new char[bufsize];
        memset(buf, 0, bufsize);

        // Retrieve the saved data
        stream.getline(buf, bufsize);

        // Convert char* buffer to string
        std::string bufStr(buf);

        // Free allocated space
        delete buf;

        // Check if read was successful
        if(stream.fail())
            return 0;

        // Strip down the string
        std::string hits(FormatReadFile(bufStr));

        return std::stoll(hits);
    }

}