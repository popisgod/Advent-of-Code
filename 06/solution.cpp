// Advent of Code solution day 02
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <numeric> 

struct race { 
    long long time; 
    long long distance; 
}; 

void extractNumbers(const std::string& line, std::vector<race>& races, bool setTime) {
    std::istringstream lineStream(line.substr(line.find(':') + 1));

    long long number;
    while (lineStream >> number) {
        if (setTime) {
            race rc;
            rc.time = number;
            rc.distance = 0; 
            races.push_back(rc);
        } else {
            if (!races.empty()) {
                for (auto &race : races){
                    if(race.distance == 0){
                        race.distance = number;
                        break;
                    }
                }
            }
        }
    }
}

int main() {  
    std::string line;
    std::vector<int> sumRacePossibilities;
    std::vector<race> races; 
    std::ifstream input("06\\input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1; // Return an error code to indicate failure
    }
    std::getline(input, line); 
    extractNumbers(line, races, true); // Extract time values
    std::getline(input, line); 
    extractNumbers(line, races, false); // Extract distance values

    
    for(auto &race : races){ 
        std::cout << "time" << race.time << "dis" << race.distance << std::endl; 

    }

   for(auto &race : races) {
    int sum = 0; 
    for(int speed = 1; speed < race.time; ++speed)
        if (speed*(race.time - speed) > race.distance) {
            ++sum; 
        }
    sumRacePossibilities.push_back(sum);
   }

   int solution = std::accumulate(sumRacePossibilities.begin(), sumRacePossibilities.end(), 1, [](int x, int y){return x * y;});

   std::cout << solution << std::endl; 

    return 0; 
}