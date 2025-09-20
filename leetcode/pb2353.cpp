#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class FoodRatings {

    struct FoodRating {
        int rating;
        string food;

        FoodRating(int _rating, string _food): rating(_rating), food(_food) {}
    };
    struct FoodRatingCmp {
        bool operator()(const FoodRating& f1, const FoodRating& f2) const {
            if (f1.rating == f2.rating) 
                for (int i = 0; i < min(f1.food.size(), f2.food.size()); i++) {
                    if (f1.food[i] != f2.food[i]) return f1.food[i] < f2.food[i];
                }
                return f1.food.size() < f2.food.size();
            return f1.rating > f2.rating; // descending order for rating
        }
    };


    unordered_map<string, set<FoodRating, FoodRatingCmp>> m;
    unordered_map<string, string> food_to_cuisine;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        const auto& n = foods.size();
        for (int i = 0; i < n; i++) {
            m[cuisines[i]].insert(FoodRating(ratings[i], foods[i]));
            food_to_cuisine[foods[i]] = cuisines[i];
        }
    }
    
    void changeRating(string food, int newRating) {
        m[food_to_cuisine[food]].insert(FoodRating(newRating, food));
    }
    
    string highestRated(string cuisine) {
        return m[cuisine].begin()->food;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */