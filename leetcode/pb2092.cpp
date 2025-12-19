#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {

    struct SolutionCmp {
        bool operator()(const vector<int>& v1, const vector<int>& v2) const {
            return v1[2] < v2[2];
        }
    };

    public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<bool> knows(n, false); // People who know secret

        knows[firstPerson] = true;
        knows[0] = true;

        sort(meetings.begin(), meetings.end(), SolutionCmp());
        
        unordered_map<int, vector<int>> meetingsGraph;
        int time = meetings[0][2];

        auto surveyGraph = [&] () {
            int person;
            queue<int> peopleToSurvey;
            for (const auto& personPair: meetingsGraph) {
                if (knows[personPair.first]) {
                    peopleToSurvey.push(personPair.first);
                }
            }

            while (!peopleToSurvey.empty()) {
                person = peopleToSurvey.front(); peopleToSurvey.pop();

                for (const auto& otherPerson: meetingsGraph[person]) {
                    if (!knows[otherPerson]) {
                        peopleToSurvey.push(otherPerson);
                        knows[otherPerson] = true;
                    }
                }
            }
            meetingsGraph.clear();
        };

        for (const auto& meeting: meetings) {
            const int& x = meeting[0];
            const int& y = meeting[1];
            const int& t = meeting[2];

            if (t != time) {
                surveyGraph();
                time = t;
            }

            if (knows[x]) {
                meetingsGraph[x].push_back(y);
            } else if (knows[y]) {
                meetingsGraph[y].push_back(x);
            } else {
                meetingsGraph[x].push_back(y);
                meetingsGraph[y].push_back(x);
            }
        }

        surveyGraph();
        
        vector<int> result; // People who know secret
        for (int i = 0; i < n; i++) {
            if (knows[i]) result.push_back(i);
        }

        return result;
    }
};