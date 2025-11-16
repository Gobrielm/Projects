#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        std::priority_queue<Wrapper*, std::vector<Wrapper*>, Wrapper::WrapperCompare> extra_students_to_insert; // Total
        double entire_total = 0;
        for (int index = 0; index < classes.size(); index++) {
            const auto& v = classes[index];
            int to_pass = v.at(0);
            int total = v.at(1);
            entire_total += double(to_pass) / total;
            extra_students_to_insert.push(new Wrapper(index, to_pass, total));
        }

        for (int i = 0; i < extraStudents; i++) {
            Wrapper* wrapper = (extra_students_to_insert.top());
            extra_students_to_insert.pop();
            wrapper->total_size++;
            wrapper->passing++;
            entire_total += wrapper->internal_diff;
            wrapper->update_internal_diff();
            classes[wrapper->index][0]++;
            classes[wrapper->index][1]++;
            extra_students_to_insert.push(std::move(wrapper));

        }

        return entire_total / classes.size();
    }

    struct Wrapper {
        int total_size;
        int passing;
        int index;
        double internal_diff;
        Wrapper(int p_index = -1, int p_passing = 0, int p_total_size = 0) {
            index = p_index;
            passing = p_passing;
            total_size = p_total_size;

            internal_diff = ((double(passing) + 1.0) / (double(total_size) + 1.0)) - (double(passing) / total_size);
        }

        void update_internal_diff() {
            internal_diff = ((double(passing) + 1.0) / (double(total_size) + 1.0)) - (double(passing) / total_size);
        }

        struct WrapperCompare {
            bool operator()(const Wrapper* lhs, const Wrapper* rhs) const {
                return lhs->internal_diff < rhs->internal_diff; // smaller gain = lower priority
            }
        };
    };
};