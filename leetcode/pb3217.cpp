#include <vector>
#include <unordered_set>

using namespace std;

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> toDelete = unordered_set<int>(nums.begin(), nums.end());
        
        ListNode* lastNode = nullptr;
        ListNode* currentNode = head;
        while (currentNode != nullptr) {
            
            if (toDelete.count(currentNode->val)) {
                ListNode* temp = currentNode;
                if (lastNode != nullptr) {
                    lastNode->next = currentNode->next;
                } else {
                    head = currentNode->next;
                }
                currentNode = currentNode->next;
                delete temp;
            } else {
                lastNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        return head;
    }
};

int main() {
    ListNode* node = new ListNode(1);
    node->next = new ListNode(2);
    node->next->next = new ListNode(3);
    node->next->next->next = new ListNode(4);
    node->next->next->next->next = new ListNode(5);
    Solution sol;
    vector<int> nums = {1, 2, 3};
    sol.modifiedList(nums, node);
}