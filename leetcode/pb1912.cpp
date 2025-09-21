#include <vector>
#include <unordered_map>
#include <set>

using namespace std;


class MovieRentingSystem {
    struct Movie {
        int shop;
        int movie;
        int price;
        Movie(int p_shop, int p_movie, int p_price): shop(p_shop), movie(p_movie), price(p_price) {};
    };

    struct MovieComp {
        bool operator()(const Movie& m1, const Movie& m2) const {
            if (m1.price == m2.price) {
                if (m1.shop == m2.shop) return m1.movie < m2.movie;
                return m1.shop < m2.shop;
            }
            return m1.price < m2.price;
        }
    };
    unordered_map<int, set<Movie, MovieComp>> movie_searcher; // movie -> movie
    unordered_map<int, unordered_map<int, int>> price_tracker; // shop -> movie -> price

    set<Movie, MovieComp> rented_movie_set;
    

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (const auto& entry: entries) {
            auto mov = Movie(entry[0], entry[1], entry[2]);
            movie_searcher[mov.movie].insert(mov);
            price_tracker[entry[0]][entry[1]] = entry[2];
        }
    }
    
    vector<int> search(int movie) {
        vector<int> v;
        auto& movies = movie_searcher[movie];
        auto it = movies.begin();
        for (int i = 0; i < min(5, (int)movies.size()); i++) {
            v.push_back(it->shop);
            it++;
        }

        return v;
    }
    
    void rent(int shop, int movie) {
        int prev_price = price_tracker[shop][movie];
        auto mov = Movie(shop, movie, prev_price);
        movie_searcher[movie].erase(mov);

        rented_movie_set.insert(mov);
    }
    
    void drop(int shop, int movie) {
        int price = price_tracker[shop][movie];

        auto mov = Movie(shop, movie, price);
        movie_searcher[movie].insert(mov);
        rented_movie_set.erase(mov);

        price_tracker[shop][movie] = price;
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> r;
        auto it = rented_movie_set.begin();
        for (int i = 0; i < min(5, (int)rented_movie_set.size()); i++) {
            r.push_back(vector<int>{it->shop, it->movie});
            it++;
        }

        return r;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */