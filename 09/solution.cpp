// Advent of Code solution day 09
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 


template<typename InputIt ,typename UnaryPredicate> 
bool all_of(InputIt first, InputIt last, UnaryPredicate pred){
    for (; first != last; ++first){
        if (!pred(*first)) return false; 
    }
    return true; 
}

int nextNumber(std::vector<int> &seq){
    std::vector<int> difSeq; 

    for (int i = 0; i < seq.size() - 1; ++i){ 
        difSeq.push_back(seq[i+1] - seq[i]);  
        
        
    }
    if (all_of(difSeq.begin(), difSeq.end(), [](int i) {return i == 0;})){
        return seq.back(); 
    }
    return nextNumber(difSeq) + seq.back() ;
}

int PervNumber(std::vector<int> &seq){
    std::vector<int> difSeq; 

    for (int i = 0; i < seq.size() - 1; ++i){ 
        difSeq.push_back(seq[i+1] - seq[i]);  
        
    }
    if (all_of(difSeq.begin(), difSeq.end(), [](int i) {return i == 0;})){
        return seq.front(); 
    }
    return seq.front() - PervNumber(difSeq) ;
}


int main(){
    std::string line; 
    std::vector<std::vector<int>> sequences; 
    std::ifstream input("09\\input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    
    while (std::getline(input, line)){ 
        int number;
        std::istringstream lineStream(line); 
        std::vector<int> seq = {};
        sequences.push_back(seq);  
        
        while(lineStream >> number){
            sequences.back().push_back(number);
        }
    }

    int sumNext = 0;
    int sumPerv = 0; 
    for (auto seq : sequences){
        sumNext += nextNumber(seq);
        sumPerv += PervNumber(seq);
    }

    std::cout << "the sum of next numbers is " << sumNext << std::endl;
    std::cout << "the sum of Perv numbers is " << sumPerv << std::endl;
    return 0; 
}

