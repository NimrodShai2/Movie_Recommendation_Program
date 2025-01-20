#include "RecommendationSystem.h"
#include <iostream>
#include <cmath>


double cosine_similarity(const std::vector<double> &v1, const std::vector<double> &v2) {
    return dot_product(v1, v2) / (norm(v1) * norm(v2));
}

double dot_product(const std::vector<double> &v1, const std::vector<double> &v2) {
    double res = 0;
    for (int i = 0; i < v1.size(); i++) {
        res += v1[i] * v2[i];
    }
    return res;
}

double norm(const std::vector<double> &v) {
    double res = 0;
    for (double d: v) {
        res += d * d;
    }
    return sqrt(res);
}


sp_movie RecommendationSystem::get_movie(const std::string &name, int year) {
    sp_movie movie = std::make_shared<Movie>(name, year);
    auto it = movies_.find(movie);
    if (it == movies_.end()) {
        return nullptr;
    }
    return *it;
}


sp_movie RecommendationSystem::add_movie_to_rs(const std::string &name, int year, const std::vector<double> &features) {
    sp_movie movie = std::make_shared<Movie>(name, year);
    movies_.insert(movie);
    movie_features_[movie] = features;
    return movie;
}

std::ostream &RecommendationSystem::operator<<(std::ostream &os) {
    for (const auto &movie: movies_) {
        os << *movie;
    }
    return os;
}


sp_movie RecommendationSystem::recommend_by_content(const User &user_rankings) {
    double avg_rank = 0;
    int num_of_movies = (int) user_rankings.get_ranks().size();
    // create a vector of the user's rankings
    std::vector<double> user_rankings_vector = std::vector<double>(num_of_movies);
    for (const auto &rank: user_rankings.get_ranks()) {
        user_rankings_vector.push_back(rank.second);
    }
    // calculate the average rank
    for (const auto &rank: user_rankings.get_ranks()) {
        avg_rank += rank.second;
    }
    avg_rank /= num_of_movies;
    for (auto &rank: user_rankings_vector) {
        rank -= avg_rank;
    }
    // Create a vector (the size of a features vector) of the user's preferences
    std::vector<double> user_preferences = std::vector<double>(movie_features_.begin()->second.size());
    for (int i = 0; i < user_rankings_vector.size(); i++) {
        auto movie = user_rankings.get_ranks().begin();
        std::advance(movie, i);
        for (int j = 0; j < user_preferences.size(); j++) {
            user_preferences[j] += user_rankings_vector[i] * movie_features_[movie->first][j];
        }
    }
    // find the movie with the highest cosine similarity
    sp_movie best_movie;
    double best_similarity = -1;
    for (const auto &movie: movies_) {
        double similarity = cosine_similarity(user_preferences, movie_features_[movie]);
        if (similarity > best_similarity) {
            best_similarity = similarity;
            best_movie = movie;
        }
    }
    return best_movie;
}
