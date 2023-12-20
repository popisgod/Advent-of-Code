// Advent of Code solution day 15
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


int hash(std::string string){
    int currentValue = 0;

    for(auto &ch : string){
        currentValue += (int)ch;
        currentValue *= 17;
        currentValue %= 256;
    }

    return currentValue;
}

struct lens {
    std::string label;
    int focalLength;
};

lens createLens(std::string label, int focalLength){
    lens ln;
    ln.label = label;
    ln.focalLength = focalLength;
    return ln;
}

int main(){
    int sumHashes = 0;
    std::string string;
    std::vector<std::string> stringVector;
    std::ifstream input(".\\15\\input.txt");
    std::map<int, std::vector<lens>> HASHMAP;

    while(std::getline(input, string, ',')){
        stringVector.push_back(string);
    }

    for (auto &str: stringVector) {

        if (str.find('=') != std::string::npos) {
            int boxNumber = hash(str.substr(0,str.find('=')));
            lens newLens = createLens(str.substr(0,str.find('=')), (int)(str.back() - '0'));

            // label exists
            if (HASHMAP.find(boxNumber) != HASHMAP.end()) {
                std::vector<lens> &boxLens = HASHMAP[boxNumber];
                auto it = std::find_if(boxLens.begin(), boxLens.end(),
                                       [&newLens](const lens &ln) { return ln.label == newLens.label; });
                if (it != boxLens.end()) {
                    it->focalLength = newLens.focalLength;
                } else {
                    boxLens.push_back(newLens);
                }
            }
                // label doesn't exist
            else {
                HASHMAP[boxNumber] = std::vector<lens>({newLens});
            }
        }
        else {
            int boxNumber = hash(str.substr(0,str.find('-')));
            lens newLens = createLens(str.substr(0,str.find('-')), (int)(str.back() - '0'));

            if (HASHMAP.find(boxNumber) != HASHMAP.end()) {
                std::vector<lens> &boxLens = HASHMAP[boxNumber];
                auto it = std::find_if(boxLens.begin(), boxLens.end(),
                                       [&newLens](const lens &ln) { return ln.label == newLens.label; });
                if (it != boxLens.end()) {
                    boxLens.erase(it);
                    boxLens.shrink_to_fit();
                }
            }
        }
    }

    int totalFocusingPower = 0;
    for (const auto& pair :  HASHMAP){
        for (int i = 0; i < pair.second.size(); ++i)
            totalFocusingPower += (pair.first + 1) * (i + 1) * (pair.second[i].focalLength);
    }


    std::cout << "the total focusing power of the lens configuration is " << totalFocusingPower << std::endl;
    std::cout << "the sum of all of the hashes is " << sumHashes << std::endl;
    return 0;
}