#include <string>
#include <vector>
#include <array>

using namespace std;


class Spreadsheet {
    vector<std::array<int, 26>> spreadsheet;

    pair<int, int> parse_cell_to_index(const string& cell) {
        int col = cell[0] - 'A';
        string row_str = cell.substr(1, cell.length() - 1);
        int row = stoi(row_str) - 1; // Is 1-indexed, 0 it
        return pair<int, int>(row, col);
    }

    inline bool checkBounds(const pair<int, int>& pair) {
        if (pair.first < 0 || pair.first >= spreadsheet.size()) return false;
        if (pair.second < 0 || pair.second > 26) return false;
        return true;
    }

    int getValueOfCell(string cell) {
        auto pair = parse_cell_to_index(cell);
        if (!checkBounds(pair)) return 0;

        return spreadsheet[pair.first][pair.second];
    }

public:
    Spreadsheet(int rows) {
        spreadsheet.resize(rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < 26; j++) {
                spreadsheet[i][j] = 0;
            }
        }
    }
    
    void setCell(string cell, int value) {
        auto pair = parse_cell_to_index(cell);
        if (!checkBounds(pair)) return;
        spreadsheet[pair.first][pair.second] = value;
    }
    
    void resetCell(string cell) {
        auto pair = parse_cell_to_index(cell);
        if (!checkBounds(pair)) return;
        spreadsheet[pair.first][pair.second] = 0;
    }
    
    int getValue(string formula) {
        auto it = formula.begin() + 1; // First char is =
        string str_val;
        bool is_all_numbers1 = true;
        while (*it != '+') {
            str_val += *it;
            int num = *it - '0';
            if (num < 0 || num > 9) is_all_numbers1 = false;
            it++;
        }
        it++; // To move from + to next char
        string str_val2;
        bool is_all_numbers2 = true;
        while (it != formula.end()) {
            str_val2 += *it;
            int num = *it - '0';
            if (num < 0 || num > 9) is_all_numbers2 = false;
            it++;
        }

        int val1 = is_all_numbers1 ? stoi(str_val): getValueOfCell(str_val);
        int val2 = is_all_numbers2 ? stoi(str_val2): getValueOfCell(str_val2);
        return val1 + val2;
    }
};
/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */