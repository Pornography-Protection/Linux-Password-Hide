#include "utils.hpp"

namespace stelijah
{
    std::string clean_string(std::string str)
    {
        std::string copy = str;

        // This removes spaces even from middle of string:
        /*
        *      std::string::iterator end_pos = std::remove(copy.begin(), copy.end(), ' ');
        *      copy.erase(end_pos, copy.end());
        */

        // Instead do:
        copy = std::regex_replace(copy, std::regex(" +$"), "");
        copy = std::regex_replace(copy, std::regex("^ +"), "");
        // removes any extra spaces inside string (replaces all double spaces with a single one)
        copy = std::regex_replace(copy, std::regex(" +"), " ");

        return copy;
    }

    std::optional<std::vector<std::string>> split(std::string input_string, std::string delimiter)
    {
        std::string input = stelijah::clean_string(input_string);
        if (input == "")
        {
            return std::nullopt;
        }
        size_t pos_start = 0;
        size_t pos_end;
        size_t delim_len = delimiter.length();

        std::string token;
        std::string input_str = stelijah::clean_string(input);
        std::vector<std::string> res;
        while ((pos_end = input_str.find(delimiter, pos_start)) != std::string::npos)
        {
            token = input_str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
            //std::cout << "1: " << token << "\n";
        }
        std::string output = input_str.substr(pos_start);
        //std::cout << "2: " << output << "\n";

        res.push_back(stelijah::clean_string(output));
        return std::make_optional<std::vector<std::string>>(res);
    }

    std::optional<std::vector<std::string>> read_file(std::string path_file)
    {
        std::vector<std::string> output_lines;

        std::ifstream file(path_file);
        std::string line;
        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                std::string new_line = stelijah::clean_string(line);

                // Remove everything after '#':
                std::string new_line2 = new_line.substr(0, new_line.find("#", 0));
                new_line = stelijah::clean_string(new_line2);

                if (new_line != "")
                {
                    output_lines.push_back(new_line);
                }
            }

            if (output_lines.size() == 0)
            {
                std::cout << "< Warning: Empty file [" << path_file << "]." << std::endl;
                return std::nullopt;
            }

            file.close();
            return std::make_optional<std::vector<std::string>>(output_lines);
        }
        else
        {
            std::cout << "< ERROR: Unable to open file [" << path_file << "]." << std::endl;
            return std::nullopt;
        }
    }

    std::string password::get_password()
    {
        return this->A +
               this->B +
               this->C +
               this->D +
               this->E +
               this->F +
               this->G +
               this->H +
               this->I +
               this->J +
               this->K +
               this->L +
               this->M +
               this->N +
               this->O +
               this->P +
               this->Q +
               this->R +
               this->S +
               this->T +
               this->U +
               this->V +
               this->W +
               this->X +
               this->Y +
               this->Z;
    }

} /* namespace stelijah */
