#include <iostream>
#include <string>
#include <regex>

#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

// Sleeping
#include <chrono>
#include <thread>

#include "utils.hpp"

// https://www.cplusplus.com/reference/cstdlib/rand/

std::vector<std::vector<int>> read_day_times(std::string filename_allow_day_times)
{
    std::vector<std::vector<int>> day_times;
    std::optional<std::vector<std::string>> lines = stelijah::read_file(filename_allow_day_times);
    if(!lines)
    {
        std::cout << "\n<< Warning: Times file [" << filename_allow_day_times << "] not found. Password can be acquired any time of the day.\n" << std::endl;
    }
    else
    {
        for (int i = 0; i < lines.value().size(); i++)
        {
            std::vector<int> day_times_current;
            std::string line = lines.value()[i];

            std::optional<std::vector<std::string>> splitted_day_times = stelijah::split(line, " ");
            day_times_current.push_back(std::stoi(splitted_day_times.value()[1]));
            day_times_current.push_back(std::stoi(splitted_day_times.value()[2]));

            day_times.push_back(day_times_current);
        }
    }

//     for (int i = 0; i < day_times.size(); i++)
//     {
//         std::cout << day_times[i][0] << ", " << day_times[i][1] << "\n";
//     }

    return day_times;
}

/* If date alone exists in file; push zero with it */
std::vector<std::vector<std::string>> read_banned_days(std::string filename_allow_days)
{
    std::vector<std::vector<std::string>> banned_days;
    std::optional<std::vector<std::string>> lines2 = stelijah::read_file(filename_allow_days);
    if(!lines2)
    {
        std::cout << "\n<< Warning: Dates file [" << filename_allow_days << "] not found. No banned days.\n" << std::endl;
    }
    else
    {
        for (int i = 0; i < lines2.value().size(); i++)
        {
            std::string line = lines2.value()[i];
            std::optional<std::vector<std::string>> splitted_ban = stelijah::split(line, " ");
            if(splitted_ban)
            {
                if (splitted_ban.value().size() == 1)
                {
                    splitted_ban.value().push_back("0");
                }
                banned_days.push_back(splitted_ban.value());
            }
        }
    }

//     std::cout << std::endl;
//     for (int i = 0; i < banned_days.size(); i++)
//     {
//         std::cout << banned_days[i][0] << ", " << banned_days[i][1] << "\n";
//     }

    return banned_days;
}

int main(int argc, char* argv[])
{
    std::string filename_allow_days       = "/etc/password_allowance_dates";
    std::string filename_allow_day_times = "/etc/password_allowance_time_of_day";
    int default_sleep_time_minutes = 30;
    int day_begin = 0;
    int day_end = 0;

    // 0. Print help menu:
    if (argc >= 2)
    {
        for (int i = 0; i < argc; ++i)
        {
            if (stelijah::clean_string(argv[i]) == "-h" ||
                stelijah::clean_string(argv[i]) == "--help")
            {
                std::cout << "\n=== About program ===" << std::endl
                          << "     Print sudo password to screen if:" << std::endl
                          << "     1. Time is within [" << filename_allow_day_times << "]" << std::endl
                          << "     2. Date is within [" << filename_allow_days << "]. Min wait time of [" << default_sleep_time_minutes << "] min." << std::endl;
                return 0;
            }
        }
    }

    // 1. Read first file
    std::vector<std::vector<int>> day_times = read_day_times(filename_allow_day_times);

    // 2. Read second file
    std::vector<std::vector<std::string>> banned_days = read_banned_days(filename_allow_days);

    // 3. Calculate current time:
    std::time_t tnow = std::time(0);
    std::tm* date = std::localtime(&tnow);
    //int minute_current = date->tm_min;
    int hour_current   = date->tm_hour;
    int day_current    = date->tm_wday; // 0 is Sunday, 6 is Saturday
    int year_current   = date->tm_year + 1900;
    int month_current  = date->tm_mon + 1;
    int mday_current   = date->tm_mday; // e.g. 31
//     std::cout << "\n- current year = " << year_current << "\n";
//     std::cout << "- current mon  = " << month_current << "\n";
//     std::cout << "- current mday = " << mday_current << "\n";
//     std::cout << "- current hour_current = " << hour_current << "\n";
//     std::cout << "- current day_current  = " << day_current << "\n\n";

    // 4. First check time of day:
    bool is_pass_time_of_day = true;

    int minimum_time = day_times[day_current][0];
    int maximum_time = day_times[day_current][1];
//     std::cout << "minimum_time = " << minimum_time << "\n";
//     std::cout << "maximum_time = " << maximum_time << "\n\n";

    if ((minimum_time == 0 && maximum_time == 0) ||
        (hour_current < minimum_time || hour_current > maximum_time))
    {
        is_pass_time_of_day = false;
    }

    // 5. Then check the day:
    bool day_filter = false;
    stelijah::password my_password;
    if (is_pass_time_of_day)
    {
        for (int i = 0; i < banned_days.size(); i++)
        {
            std::vector<std::string> parts = banned_days[i];
            int num_year = std::stoi(parts[0].substr(0, 4));
            int num_mon = std::stoi(parts[0].substr(4, 2));
            int num_day = std::stoi(parts[0].substr(6, 2));
            int waiting_minutes = std::stoi(parts[1]);

            // std::cout << "year = " << num_year << '\n';
            // std::cout << "mon  = " << num_mon << '\n';
            // std::cout << "day  = " << num_day << '\n\n';

            if (year_current == num_year)
            {
                if (month_current == num_mon)
                {
                    if (mday_current == num_day)
                    {
                        if (waiting_minutes == 0)
                        {
                            default_sleep_time_minutes = 360;
                        }
                        else if (waiting_minutes >= default_sleep_time_minutes)
                        {
                            default_sleep_time_minutes = waiting_minutes;
                        }

                        day_filter = true;
                        //break;
                    }
                }
            }
        }
    }

    if(is_pass_time_of_day)
    {
        //std::cout << "<< Time covered by the file [" << filename_allow_day_times << "]." << std::endl;

        if (day_filter)
        {
            //std::cout << "<< Today is listed in [" << filename_allow_days << "]\n";
            //std::cout << "<< You will need to wait for [" << default_sleep_time_minutes << "] minutes (" << default_sleep_time_minutes/60 << " hours).\n";

            std::this_thread::sleep_for(std::chrono::minutes(default_sleep_time_minutes));
        }
        // else
        // {
        //     std::cout << "<< Today not listed in [" << filename_allow_days << "]." << std::endl << std::endl;
        // }
        std::string PASSWORD = my_password.get_password();
        std::cout << PASSWORD << std::endl;
        return 1;
    }

    // std::cout << "<< Time not covered by the file [" << filename_allow_day_times << "].\n" << std::endl << std::endl;
    return 0;

} /* main() */
