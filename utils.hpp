#pragma once

#ifndef ELYAHW_UTILS_CPP
#define ELYAHW_UTILS_CPP

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <optional>

namespace stelijah
{

    /**
     * @param[in] str string
     * @param[out] string cleaned from spaces (beginning, end, extra ones in middle)
     */
    std::string clean_string(std::string str);

    /**
     * @param[in] s (string)
     * @param[in] delimiter (string)
     * @param[out] vector of strings of splitted items cleaned from spaces
     */
    std::optional<std::vector<std::string>> split(std::string s, std::string delimiter);

    /**
     * @param[in] path_file
     * @param[out] vector of strings containing lines inside path_file.
     *                    Lines are: - cleaned from spaces
     *                               - everything following '#' is hashes ignored
     *                               - empty lines removed
     */
    std::optional<std::vector<std::string>> read_file(std::string path_file);

    /**
     * Class to store different parts of a password (unordered).
     * Note: Making a class that contains a vector, and randomly separating the string into parts of random length
     *        and pushing them into an array will not work as the whole string should not be stored as a single entity.
     */
    class password
    {
    public:
        std::string get_password();

    private:
        // Password must be separated into unequal pieces and put from A-Z:
        // FATHER_SON_HOLY_SPIRIT_JESUS_CHRIST_SON_OF_GOD_OUR_MOTHER_MARY_SAINTS_ANGELS
        std::string A = "";
        std::string F = "";
        std::string X = "";
        std::string Z = "";
        std::string S = "";
        std::string O = "";
        std::string R = "";
        std::string T = "";
        std::string Q = "";
        std::string L = "";
        std::string I = "";
        std::string K = "";
        std::string G = "";
        std::string Y = "";
        std::string B = "";
        std::string E = "";
        std::string M = "";
        std::string U = "";
        std::string W = "";
        std::string V = "";
        std::string P = "";
        std::string N = "";
        std::string J = "";
        std::string C = "";
        std::string D = "";
        std::string H = "";
    };

} /* namespace stelijah */

#endif // ELYAHW_UTILS_CPP
