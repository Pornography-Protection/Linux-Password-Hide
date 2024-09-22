#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */ // https://www.cplusplus.com/reference/cstdlib/rand/
#include <time.h>       /* time */

#include <unistd.h>     /* getuid */
#include <pwd.h>        /* getpwuid */

#include "utils.hpp"

// TODO: put -h information below in a file in /etc/__ print it on calling help

int main(int argc, char* argv[])
{
    int normal_wait_duration_minutes = 360;
    std::string filename_normal_sleep_duration_minutes = "/etc/password_sleep_duration";

    const char* home_dir = getpwuid(getuid())->pw_dir;
    std::string outputFile = std::string(home_dir) + "/Documents/password.txt";

    if (argc >= 2)
    {
        for (int i = 0; i < argc; ++i)
        {
            if (stelijah::clean_string(argv[i]) == "-h" ||
                stelijah::clean_string(argv[i]) == "--help")
            {
                std::cout << "\n=== About program ===" << std::endl
                          << "     Wait for x minutes and then print password\n" << std::endl

                          << "=== Explanation ===" << std::endl
                          << "     1. If [" << filename_normal_sleep_duration_minutes << "] exists, first non-comment line is" << std::endl
                          << "         read and its value (must be int) is used as waiting time." << std::endl
                          << "     2. Otherwise, it will sleep for [" << normal_wait_duration_minutes
                          << "] minutes by default (" << normal_wait_duration_minutes/60 << " hours)." << std::endl
                          << "     3. On wake up, it will save password to [" << outputFile << "] (overwrite/create)." << std::endl
                          << "     4. If machine sleeps, time will not be counted.\n" << std::endl;
                return 0;
            }
        }
    }

    // Password must be separated into unequal pieces and pasted from A-Z
    stelijah::password my_password;

    // 1. Print time
    auto timer = std::chrono::system_clock::now();
    std::time_t startTime = std::chrono::system_clock::to_time_t(timer);
    std::cout<< std::ctime(&startTime) << "\n";

    // Read file:
    std::optional<std::vector<std::string>> lines = stelijah::read_file(filename_normal_sleep_duration_minutes);
    if(!lines)
    {
        std::cout << "!!! WARNING: Unable to open [" << filename_normal_sleep_duration_minutes << "]. Using default time.\n" << std::endl;
    }
    else
    {
        normal_wait_duration_minutes = std::stoi(lines.value()[0]);
    }

    // 2. Print info
    std::cout << "1. Will sleep for: [" << normal_wait_duration_minutes << "] minutes (" << normal_wait_duration_minutes/60
              << " hours). If computer sleeps, time is not counted.\n" << std::endl;

    std::cout << "2. Then overwrite/create: [" << outputFile << "]" << std::endl;

    // 3. Sleep
    std::this_thread::sleep_for(std::chrono::minutes(normal_wait_duration_minutes));

    // 4. Save password to file (create or overwrite; not append)
    std::ofstream myfile(outputFile, std::ofstream::out); // std::ofstream::app
    std::string PASSWORD = my_password.get_password();
    myfile << PASSWORD;
    myfile.close();
    std::cout<< PASSWORD << "\n";

    return 0;
}
