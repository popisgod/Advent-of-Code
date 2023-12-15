// Advent of Code solution day 08
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string>
#include <unordered_map> 
#include <array>

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
    
    // Extract right-left directions from input 
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
    
    int steps = 0; 
    std::string head = "AAA"; 
    while (head != "ZZZ"){
        if (directions[steps % directions.size()] == 'R'){
            head = paths[head][1];
        }
        else { 
            head = paths[head][0];
        }
        steps++; 
    }

    std::cout << "number of steps: " << steps << std::endl;


    return 0; 
}