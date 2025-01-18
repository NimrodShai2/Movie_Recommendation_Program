//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <set>
#include "User.h"
#include "Movie.h"

class RecommendationSystem {
private:
    /// A binary search tree of movies with a vector of features
    std::set<sp_movie> movies_;

    /// An unordered map of movies with a vector of features
    std::unordered_map<sp_movie, std::vector<double>, hash_func, equal_func> movie_features_;

public:
    /**
     * returns a movie from the recommendation system
     * @param name the name of the movie
     * @param year the year the movie was made
     * @return the movie
     */
    sp_movie get_movie(const std::string &name, int year);

    /**
     * adds a movie to the recommendation system
     * @param name the name of the movie
     * @param year the year the movie was made
     * @param features the features of the movie
     * @return the movie added
     */
    sp_movie add_movie_to_rs(const
                             std::string &name, int year, const std::vector<double> &features);

    /**
     * returns a recommendation according to the movie's content
     * @param user_rankings
     * @return a recommendation according to the movie's content
     */
    sp_movie recommend_by_content(const User &user_rankings);


    double predict_movie_score(const User &user_rankings, const sp_movie &movie, int k);

    sp_movie recommend_by_cf(const User &user_rankings, int k);

    std::ostream &operator<<(std::ostream &os);

};

#endif // RECOMMENDATIONSYSTEM_H
