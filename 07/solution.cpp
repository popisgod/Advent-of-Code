// Advent of Code solution day 07
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string>
#include <unordered_map>
#include <algorithm>
#include <map> 

class Hand{ 
public: 

    class iterator {
    public:
        iterator(const std::string& str, size_t pos, const std::unordered_map<char, int>& map)
            : data(str), index(pos), charToValue(map) {}

        // Dereference operator to get the current value
        int operator*() const {
            return charToValue.at(data[index]); // Convert char to value
        }

        // Increment operator to move to the next element
        iterator& operator++() {
            ++index;
            return *this;
        }

        // Comparison operator to check for equality
        bool operator!=(const iterator& other) const {
            return index != other.index;
        }

    private:
        const std::string& data;
        size_t index;
        const std::unordered_map<char, int>& charToValue;
    };


    static const std::unordered_map<char, int> charToValue;

    Hand(std::string handValue) : hand(handValue) {}
    
    int operator[](int index){
        return charToValue.find(hand[index])->second;
    }

    int operator[](int index) const{
        return charToValue.find(hand[index])->second;
    }

    void SetCard(std::string hand){
        this->hand = hand;
    }

    std::string getHand() const{ 
        return hand; 
    }

    friend std::istringstream& operator>>(std::istringstream& iss, Hand& c) {
        std::string value;
        iss >> value;
        c.SetCard(value);
        return iss;
    }   

    iterator begin() const{
        return iterator(hand, 0, charToValue);
    }

    iterator end() const{
        return iterator(hand, hand.size(), charToValue);
    }

private:
    std::string hand; 

};

const std::unordered_map<char, int> Hand::charToValue = {
    {'J', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6},
    {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 12}, {'K', 13}, 
    {'A', 14}
};

struct game {
    Hand hand; 
    long long bid;

    game() : hand(""), bid(0) {}

    bool operator<(const game &other) const{         
        std::map<int,int> countCards[2];
        int maxCount[2] = {0, 0};
        int wildCardCount[2] = {0, 0}; 
        int mostCommon[2]; 
        int countCardsSize[2]; 

        for(auto const &card : hand){
            countCards[0][card]++; 
        }

        for(auto const &card : other.hand){
            countCards[1][card]++;
        }

        for (int i = 0; i < 2; ++i) {
            for (const auto &pair : countCards[i]) {
                if (pair.first == 1 && pair.second != 5) {
                    wildCardCount[i] += pair.second;
                    continue;
                }
                maxCount[i] = std::max(maxCount[i], pair.second);
            }

                maxCount[i] += wildCardCount[i];
                if (wildCardCount[i] > 0){
                    countCardsSize[i] = countCards[i].size() - 1; 
                } 
                else {
                    countCardsSize[i] = countCards[i].size();
                }
        }

        if (maxCount[0] == maxCount[1]){

            // FULL HOUSE 
            if (countCardsSize[0] == 2 && maxCount[0] == 3){
                if (!(countCardsSize[1] == 2))
                    return false;
            }
            if (countCardsSize[1] == 2 && maxCount[1] == 3){
                if (!(countCardsSize[0] == 2))
                    return true;
            }

            //  TWO PAIR
            if (countCardsSize[0] == 3 && maxCount[0] == 2){
                if (!(countCardsSize[1] == 3))
                    return false;
            }
            if (countCardsSize[1]== 3 && maxCount[1] == 2){
                if (!(countCardsSize[0] == 3))
                    return true;
            }            


            for (int i = 0; i < 5; i++){
                if (hand[i] < other.hand[i]) return true;
                else if (hand[i] > other.hand[i]) return false; 
                else continue; 
            }
        }
        else if (maxCount[0] > maxCount[1]) {
            return false;
        }
        return true; 
    }


}; 


int main() {
    std::string line; 
    std::vector<game> games;
    std::ifstream input("07\\input.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }


    while(getline(input, line) && !line.empty()) {
        game gm;
        std::istringstream lineStream(line);
        lineStream >> gm.hand >> gm.bid; 
        games.push_back(gm);
    }

    long long sum = 0; 
    std::sort(games.begin(), games.end());
    for(long long i = 0; i < games.size(); ++i) { 
        sum += games[i].bid * (i + 1);
    }

    std::cout << "the sum of all of the bids by their ranking is " << sum << std::endl; 
    return 0; 
}