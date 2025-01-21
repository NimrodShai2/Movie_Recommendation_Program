//
// Created on 2/20/2022.
//

#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <set>
#include "User.h"
#include "Movie.h"

typedef std::unordered_map<sp_movie, std::vector<double>, hash_func, equal_func> movie_features_map;

class User;

/**
 * A comparator for movies
 */
struct MovieComparator {
    bool operator()(const sp_movie &m1, const sp_movie &m2) const {
        return *m1 < *m2; // Use Movie::operator< to compare
    }
};


class RecommendationSystem {
private:
    /// A binary search tree of movies with a vector of features
    std::set<sp_movie, MovieComparator> movies_;

    /// An unordered map of movies with a vector of features
    movie_features_map movie_features_{0, sp_movie_hash, sp_movie_equal};

public:


    /**
     * returns a movie from the recommendation system
     * @param name the name of the movie
     * @param year the year the movie was made
     * @return the movie, or nullptr if it doesn't exist
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

    friend std::ostream &operator<<(std::ostream &os, const RecommendationSystem &rs);
};


/*
 * Calculate the cosine similarity between two vectors
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the cosine similarity between the two vectors
 */
double cosine_similarity(const std::vector<double> &v1, const std::vector<double> &v2);

/**
 * Calculate the norm of a vector
 * @param v the vector
 * @return the norm of the vector
 */
double norm(const std::vector<double> &v);

/**
 * Calculate the dot product of two vectors
 * @param v1 the first vector
 * @param v2 the second vector
 * @return the dot product of the two vectors
 */
double dot_product(const std::vector<double> &v1, const std::vector<double> &v2);

#endif // RECOMMENDATIONSYSTEM_H
