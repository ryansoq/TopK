#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>

class Tool
{
    public:
        template<typename T, int SIZE>
        std::vector< std::tuple<int, std::string, T> > decode_predictions(T * data, const char* path)
        {
            // Get labels
            std::vector<std::string> label;
            std::string line;
            std::ifstream load_label(path);

            if (!load_label.good())
            {
                std::cout << "Not found label ..." << std::endl;
                assert(0);
            }
            while (std::getline(load_label, line))
            {
                label.push_back(line);
            }

            // Get values
            std::vector<T> value(data, data + SIZE);
            std::vector< std::tuple<int, std::string, T> > ILV; // original index, label name, prediction value

            // Integration
            for (auto i = 0 ; i < value.size(); i++)
            {
                ILV.push_back(std::make_tuple(i, label[i], value[i]));
            }

            // Sort
            std::sort(ILV.begin(), ILV.end(), [](std::tuple<int, std::string, T> a, std::tuple<int, std::string, T> b) { return std::get<2>(a) > std::get<2>(b); });

            return ILV;
        }
};
