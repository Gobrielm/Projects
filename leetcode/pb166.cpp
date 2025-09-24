#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;
using ll = long long;

class Solution {
    const int max_length = 10000;


public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";

        std::string fraction;
        if ((numerator < 0) ^ (denominator < 0))
            fraction += "-";

        // Gets Whole part of fraction
        ll dividend = std::llabs((ll)numerator);
        ll divisor = std::llabs((ll)denominator);
        fraction += std::to_string(dividend / divisor);

        ll remainder = dividend % divisor;
        if (remainder == 0) {
            return fraction;
        }

        fraction += ".";
        std::unordered_map<ll, int> remainders;

        while (remainder != 0) {
            // IF Remainder ever repeats then pattern is found,
            if (remainders.count(remainder)) {
                fraction.insert(remainders[remainder], "(");
                fraction += ")";
                break;
            }
            remainders[remainder] = fraction.size();
            remainder *= 10;
            fraction += std::to_string(remainder / divisor);
            remainder %= divisor;
        }

        return fraction;
    }
};