// Advent of Code solution day 15
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int hash(std::string &string){
    int currentValue = 0;

    for(auto &ch : string){
        currentValue += (int)ch;
        currentValue *= 17;
        currentValue %= 256;
    }

    return currentValue;
}

int main(){
    int sumHashes = 0;
    std::string string;
    std::vector<std::string> stringVector;
    std::ifstream input(".\\15\\input.txt");


    while(std::getline(input, string, ',')){
        stringVector.push_back(string);
    }

    for (auto &str: stringVector) {
        sumHashes += hash(str);
    }

    std::cout << "the sum of all of the hashes is " << sumHashes << std::endl;
    return 0;
}