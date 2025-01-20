//
// Created on 2/20/2022.
//

#ifndef USER_H
#define USER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Movie.h"
#include "RecommendationSystem.h"

typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;


class User {
private:
    rank_map ranks_;
    std::string name_;
    std::shared_ptr<RecommendationSystem> rs_;

public:

    /**
     * constructor for the user
     * @param name the name of the user
     * @param ranks the ranks map of the user
     * @param rs the recommendation system
     */
    User(std::string name, rank_map ranks, std::unique_ptr<RecommendationSystem> rs);


    /**
     * function for adding a movie to the DB
     * @param name name of movie
     * @param year year it was made
     * @param features a vector of the movie's features
     * @param rate the user rate for this movie
     */
    void add_movie_to_user(const std::string &name, int year,
                           const std::vector<double> &features,
                           double rate);


    /**
     * returns a recommendation according to the movie's content
     * @return recommendation
     */
    sp_movie get_rs_recommendation_by_content();

    /**
     * returns a recommendation according to the similarity recommendation method
     * @param k the number of the most similar movies to calculate by
     * @return recommendation
     */
    sp_movie get_rs_recommendation_by_cf(int k);

    /**
     * predicts the score for a given movie
     * @param name the name of the movie
     * @param year the year the movie was created
     * @param k the parameter which represents the number of the most similar movies to predict the score by
     * @return predicted score for the given movie
     */
    double get_rs_prediction_score_for_movie(const std::string &name, int year, int k);

    /**
     * returns the name of the user
     * @return the name of the user
     */
    const std::string &get_name() const;

    /**
     * returns the rank map of the user
     * @return the ranks map the user
     */
    const rank_map &get_ranks() const;

    std::ostream &operator<<(std::ostream &os) const;

};


#endif //USER_H
