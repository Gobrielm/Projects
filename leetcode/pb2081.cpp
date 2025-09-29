#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

class Solution {
    void increment_number(ll& n, bool& isOddLen) {
        // Given front-half
        string number = to_string(n);
        for (int i = number.length() - 1; i >= 0; i--) {
            int num = number[i] - '0';
            if (num != 9) {
                number[i] += 1;
                for (int j = (i + 1); j < number.length(); j++) {
                    number[j] = '0';
                }
                n = stoll(number);
                return;
            }
        }
        // Atp number must be all 9's
        int digits = number.length() + (isOddLen ? -1: 0);
        isOddLen = !isOddLen;
        n = pow(10, digits);
    }

    ll get_whole_number(const ll& frontside, const bool& isOddLen) {
        string front = to_string(frontside);
        string back = front;
        std::reverse(back.begin(), back.end());
        
        if (isOddLen) {
            front.pop_back();
        }
        return stoll(front + back);
    }

    bool is_palidrone(ll number, const int& base) {

        std::string baseString = "";
        while (number > 0) {
            int remainder = number % base;
            baseString += std::to_string(remainder);
            number /= base;
        }

        for (int i = 0; i < baseString.size() / 2; i++) {
            if (baseString[i] != baseString[baseString.size() - 1 - i]) {
                return false;
            }
        }
        return true;
    }

public:
    long long kMirror(int k, int n) {
        bool isOddLen = true;
        ll total = 0, tracker = 1;
        int counted = 0;
        while (counted < n) {
            ll temp = get_whole_number(tracker, isOddLen);
            if (is_palidrone(temp, k)) {
                counted++;
                total += temp;
            }
            increment_number(tracker, isOddLen);
        }
        return total;
    }
};