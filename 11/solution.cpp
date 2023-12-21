// Advent of Code solution day 11
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>



int main(){
    std::string line;
    std::ifstream  input(".\\11\\input.txt");
    std::vector<std::vector<char>> universe;


    while(std::getline(input, line)){
        char imageLocation;
        std::istringstream lineStream(line);

        universe.push_back(std::vector<char> ());
        while (lineStream >> imageLocation) {
        universe.back().push_back(imageLocation);
    }
}

    for (int i = 0; i < universe.size(); ++i)
        if (std::all_of(universe[i].begin(), universe[i].end(), [](int i) { return i == '.'; })){
            // insert new row
            universe.insert(universe.begin() + i + 1, std::vector<char>());
            for (int j = 0; j < universe[i].size(); ++j)
                universe[i + 1].push_back('.');
        }

    for (int i = 0; i < universe[1].size(); ++i) {
        for (int j = 0; j < universe.size(); ++j) {
            if (universe[i][j] == '.'){
                if (j == universe.size() - 1)
                    // insert new colum
                    for (int k = 0; k < universe.size(); ++k)
                        universe[i].insert(universe[i].begin() + i + 1, '.');
                continue;
            }
            else {break;}
        }
    }

    std::cout << "orad is a google fanboy" << std::endl;
    return 0;
}
