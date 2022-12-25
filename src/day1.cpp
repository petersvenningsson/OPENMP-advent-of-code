#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <omp.h>

#define SCISSOR
#define EVER (;;)

std::vector<std::string> read_file(std::string filename)
{ 
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::vector<std::string> data;
    while (std::getline(file,line)) {
        if (line.length())
            data.push_back(line);
    }

    return data;
}

int calculate_score(std::string line)
{
    int opponent_move = line.at(0) - 'A';
    int player_move = line.at(2) - 'X';

    int score = player_move + 1;
    if (opponent_move == player_move)
        score += 3;
    else if ((player_move - opponent_move + 3) % 3 == 1)
        score += 6;

    return score;
}

int main(int argc, char **argv)
{
    std::vector<std::string> args(argv, argv+argc);
    for(auto& arg: args) {
        if(arg == "--help" || arg == "-h" || argc == 1) {
            std::cout << "Usage: day [PUZZLE INPUT FILE]" << std::endl;
            return -1;
        }
    }

    std::vector<std::string> data = read_file(args[1]);

    double score = 0;
    int num_threads;
    #pragma omp parallel shared(num_threads)
    {
        int ID = omp_get_thread_num();

        if (ID == 0) {
            num_threads = omp_get_num_threads();
        }

        #pragma omp barrier
        int partial_score = 0;
        for (int i=ID; i < data.size(); i+=num_threads) {
            std::string line = data[i];
            partial_score += calculate_score(line);
        }

        #pragma omp critical
        score += partial_score;
    }
    std::cout << "Score is: " << score << std::endl;

}

