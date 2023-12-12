// Advent of Code solution day 03
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include <map> 

struct pair {
    int first;
    int second;

       
    bool operator<(const pair& other) const {
        if (first != other.first) {
            return first < other.first;
        }
        return second < other.second;
    }
};

pair makePair(int first, int second) {
    pair p;
    p.first = first;
    p.second = second;
    return p;
}

std::map<pair, std::vector<int>> gearMap;


bool validNumber(std::vector<std::string> const &engineSchematic, std::string const  &number, int indexLine, int indexPart){
    int numberSize = number.size();

    for(int i = indexLine - 1; i <= indexLine + 1; i++){
        for (int j = indexPart - 1; j <= indexPart + numberSize; j++){
            if (i >= 0 && i < engineSchematic.size() && j >= 0 && j < engineSchematic[i].size()) {
                if (engineSchematic[i][j] == '*'){
                    gearMap[makePair(i, j)].push_back(stoi(number));
                }
                if(!isdigit(engineSchematic[i][j]) && engineSchematic[i][j] != '.')
                    return true;
             }
        }
    }
    return false;
}

int main(){
    std::string number;  
    int indexPart; 
    int sumOfElems = 0; 
    int sumOfGearRatios = 0;
    std::vector<int> validNumbers; 


    std::ifstream  input("03\\input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1; // Return an error code to indicate failure
    }


    std::vector<std::string> engineSchematic;
    std::string line; 

    while(std::getline(input, line)){;
        engineSchematic.push_back(line);
    }
    input.close();

 
    for(int i = 0; i < engineSchematic.size(); ++i){   
        for(int j = 0; j < engineSchematic[i].size(); ++j){
            
            if(isdigit(engineSchematic[i][j])){
                if(number == ""){
                    indexPart = j;
                }
                number += engineSchematic[i][j];
            }
            else{
                if (!number.empty() && validNumber(engineSchematic, number, i, indexPart))
                    {
                        validNumbers.push_back(stoi(number));
                    }

                number = ""; // Reset number 

            }

        }
                // Process the remaining number in the line (if any)
        if (!number.empty() && validNumber(engineSchematic, number, i, indexPart)) {
            validNumbers.push_back(stoi(number));
        }

    number = ""; // Reset number 
    }

    for (auto & n : validNumbers){
     sumOfElems += n;
    }
    std::cout << "sum of elements:" << sumOfElems << std::endl;

    for(const auto & entry : gearMap){
        if (entry.second.size() == 2){
            sumOfGearRatios += entry.second[0]*entry.second[1];
        }
    }
    
   std::cout << "sum of gear ratios:" << sumOfGearRatios << std::endl;
    return 0;
}


