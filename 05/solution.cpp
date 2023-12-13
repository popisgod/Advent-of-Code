// Advent of Code solution day 05
#include <iostream> 
#include <vector> 
#include <fstream>
#include <sstream> 
#include <map>
#include <climits>

struct Entry { 
    long long source; 
    long long destination; 
    long long range; 
};



int main(){
    long long number; 
    long long lowestLocation = LLONG_MAX; 
    std::string line;
    std::string firstLine;
    std::vector<long long> seeds; 
    Entry entry; 
    std::vector<Entry> EntryVector; 
    std::vector<std::vector<Entry>> conversionVector; 
    std::ifstream input("Z:\\Ron\\Cyber\\Advent-Of-Code\\Advent-of-Code\\05\\input.txt");

    // extract the seed string 
    std::getline(input, line, ':');
    std::getline(input, firstLine);
    std::istringstream firstLineStream(firstLine);
       
    // extract seed values 
    while (firstLineStream >> number){
        seeds.push_back(number); 
    }
 
    while(!input.eof()) {  

        std::getline(input, line); // Read and ignore lines
        std::vector<Entry> EntryVector; 

        while (std::getline(input, line) && !line.empty()){
            std::istringstream lineStream(line);
            
            lineStream >> entry.destination; // destination 
            lineStream >> entry.source; // source 
            lineStream >> entry.range; // range
            EntryVector.push_back(entry); // create entry 
        }   
        conversionVector.push_back(EntryVector); // create conversion table 
    } 

    for(auto &seed : seeds){
        long long temp = seed; 
        for (auto &table : conversionVector) { 
            for (auto &entry: table) {
                long long maxSource = entry.source + entry.range - 1; 
                if (temp >= entry.source &&  temp <= maxSource){ 
                     temp = entry.destination + (temp - entry.source);
                    break;
                }
                
            }
        }
        
        if (temp < lowestLocation){
            lowestLocation = temp; 
        }
    }
    std::cout << lowestLocation << std::endl; 
    return 0; 
}