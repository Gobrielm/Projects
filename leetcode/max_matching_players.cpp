#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end(), std::less<int>()); // Ascending Order, reverse access
        sort(trainers.begin(), trainers.end(), std::greater<int>()); // Descending Order

        int count = 0, trainer_index = 0;
        while (trainer_index < trainers.size() && !players.empty()) {
            int trainer = trainers[trainer_index];
            int player = players.back(); // Biggest Player
            if (player <= trainer) {
                count++;
                trainer_index++;
            }
            players.pop_back();
            
        }
        return count;
    }
};