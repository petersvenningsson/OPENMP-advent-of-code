#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>

int main(int argc, char **argv)
{
    std::vector<std::string> args(argv, argv+argc);
    for(auto& arg: args) {
        if(arg == "--help" || arg == "-h" || argc == 1) {
            std::cout << "Usage: day [PUZZLE INPUT FILE]" << std::endl;
            return -1;
        }
    }

    if (std::getenv("MP_SINGLE_THREAD")) {
        int omp_set_num_threads(1);
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Invalid filepath" << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> food_sacks;
    std::vector<int> sack;
    std::string line;

    while (std::getline(file,line)) {
        if (line.length() == 0) {
            food_sacks.push_back(sack);
            sack.clear();
        } else {
            sack.push_back(std::stoi(line));
        }
    }
    
    std::vector<int> calories;
#pragma omp parallel for
    for (auto sack : food_sacks) {
        int sum = std::accumulate(sack.begin(), sack.end(), 0);
#pragma omp critical
        calories.push_back(sum);
    }
    auto max = std::max_element(calories.begin(), calories.end());

    std::cout << "The maximum amount of calories is: " << *max << std::endl;
    return 0;
}
