
using namespace std;

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int total = 0;
        int empty = 0;
        while (numBottles > 0) {
            total += numBottles;
            empty += numBottles;
            numBottles = 0;

            while (empty >= numExchange) {
                numBottles += 1;
                empty -= numExchange;
                numExchange++;
            }
        }
        return total;
    }
};