// Advent of Code solution day 04
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

std::vector<int> split(std::string const &str){
    std::istringstream strStream(str);
    int number; 
    std::vector<int> splitNumbers; 

    while(strStream >> number){
        splitNumbers.push_back(number);
    }

    return splitNumbers; 
}

int RecursiveMatch(std::vector<int> &copies, int index){
    int sumCopies = 1; 
    
    if(index >= copies.size() || copies[index] == 0){
        return 1; 
    }
    
    for (int i = 1 + index; i <= index + copies[index] && i < copies.size(); ++i){
        sumCopies += RecursiveMatch(copies, i); 
    }

    return sumCopies; 

}


int main(){
    int totalScratchCards = 0;
    int sumPoints = 0; 
    std::string line; 
    std::ifstream input("04\\input.txt");
    std::vector<std::string> cards;
    std::vector<int> copies; 
    if (!input.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 1; // Return an error code to indicate failure
    }
    
    while(std::getline(input, line)){
        cards.push_back(line);
    }

    for(auto &line : cards){ 
        int counter = -1; 
        size_t pos = line.find(':');
        line.erase(0, pos + 1);

        pos = line.find('|');
        std::string winningNumbersString = line.substr(1, pos - 1);
        std::string scratchedNumbersString = line.substr(pos + 2, std::string::npos);

 
        std::unordered_map<int, int> intresectionMap; 
        for (int number : split(scratchedNumbersString)){
            intresectionMap[number]++;
        }
       
        for (int number : split(winningNumbersString)){
            if (intresectionMap.find(number) != intresectionMap.end()){
                counter++; 
            }
        }


        if(counter > -1){
            sumPoints += pow(2, counter); 
            
        }   
        copies.push_back(counter + 1);   
   
        // for (auto &number : copies){
        //     std::cout << number << " ";
        // }
    }


    for (int i = 0; i < copies.size(); i++){
        totalScratchCards += RecursiveMatch(copies, i);
    }
  
    std::cout << "the number of points the elf won is " << sumPoints << std::endl; 
    std::cout << "you end up with " << totalScratchCards << " cards" << std::endl;

    return 0;
}