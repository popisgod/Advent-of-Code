// Advent of Code solution day 08
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string>
#include <unordered_map> 
#include <array>
#include <numeric>

int main(){ 
    std::string line;
    char direction; 
    std::vector<char> directions; 
    std::unordered_map<std::string, std::array<std::string, 2>> paths;
    std::ifstream input("08\\input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    std::getline(input, line);
    std::istringstream lineStream(line);
    while(lineStream >> direction) {
        directions.push_back(direction); 
    }

    std::getline(input, line); 
    while(std::getline(input, line) && !line.empty()){
        
        paths[line.substr(0,3)] = {line.substr(line.find('(') + 1, 3), 
                                    line.substr(line.find(',') + 2, 3)};

    }  

    std::vector<std::string> heads;
    for (auto &pair : paths){
        if(pair.first[2] == 'A'){
            heads.push_back(pair.first); 
        }
    }

    std::vector<int> steps; 
    for (int i = 0; i < heads.size(); ++i){
        steps.push_back(0); 
        while (heads[i][2] != 'Z') {
            if (directions[steps[i] % directions.size()] == 'R') {
            heads[i] = paths[heads[i]][1];
        } else {
            heads[i] = paths[heads[i]][0];
        }
        steps[i]++;
        }
    }

    long long stepsMinimum; 
    stepsMinimum = std::accumulate(steps.begin(), steps.end(), 1LL, [](long long x, long long y){return std::lcm(x, y);});
    std::cout << "number of steps: " << stepsMinimum << std::endl;
    return 0; 
}