#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>

#define LABEL_PATH "imagenet1000_clsidx_to_labels.txt"

class Tool
{
    public:
        template<typename T, int SIZE>
        std::vector< std::tuple<int, std::string, T> > decode_predictions(T * data, int top, const char* path = "")
        {
            // Get labels
            std::string str(path);
            std::vector<std::string> label;
            std::string line;
            std::ifstream load_label;

            if (str == "")
                load_label.open(LABEL_PATH);
            else
                load_label.open(path);

            if (!load_label.good())
            {
                std::cout << "Not found label ..." << std::endl;
                assert(0);
            }

            while (std::getline(load_label, line))
            {
                label.push_back(line);
            }

            load_label.close();

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

            // Print
            int index_;
            std::string label_;
            T value_;

            std::cout << "Predicted: [" << std::endl;
            for (auto i = 0; i < top; i++)
            {
                std::tie(index_, label_, value_) = ILV[i];

                if (i!=0)
                    std::cout << ", " << std::endl;

                std::cout << "(" << index_ << ", " << label_ << ", " << (float)value_;
                std::cout << ")";
            }
            std::cout << "]" << std::endl;
            return ILV;
        }
};
