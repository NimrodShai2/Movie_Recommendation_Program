#include "RecommendationSystem.h"
#include "Movie.h"
#include <iostream>
#include <cmath>
#include <algorithm>


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
    auto it = movies_.find(std::make_shared<Movie>(name, year));
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

std::ostream &operator<<(std::ostream &os, const RecommendationSystem &rs) {
    for (const auto &movie: rs.movies_) {
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
        // if the user has already ranked the movie, skip it
        if (user_rankings.get_ranks().find(movie) != user_rankings.get_ranks().end()) {
            continue;
        }
        double similarity = cosine_similarity(user_preferences, movie_features_[movie]);
        if (similarity > best_similarity) {
            best_similarity = similarity;
            best_movie = movie;
        }
    }
    return best_movie;
}


double RecommendationSystem::predict_movie_score(const User &user_rankings, const sp_movie &movie, int k) {
    auto features = movie_features_[movie];
    // Find top k movies
    std::vector<std::pair<sp_movie, double>> top_k;
    // calculate the similarity between the movie and the user's rankings
    for (const auto &user_movie: user_rankings.get_ranks()) {
        double similarity = cosine_similarity(features, movie_features_[user_movie.first]);
        top_k.emplace_back(user_movie.first, similarity);
    }
    // sort the vector by similarity, in descending order
    std::sort(top_k.begin(), top_k.end(),
              [](const std::pair<sp_movie, double> &a, const std::pair<sp_movie, double> &b) {
                  return a.second > b.second;
              });
    // Resize the vector to k
    if (top_k.size() > k) {
        top_k.resize(k);
    }
    // calculate the predicted score
    double predicted_score = 0;
    double sum_of_similarities = 0;
    for (const auto &m: top_k) {
        predicted_score += user_rankings.get_ranks().at(m.first) * m.second;
        sum_of_similarities += m.second;
    }
    return predicted_score / sum_of_similarities;
}

sp_movie RecommendationSystem::recommend_by_cf(const User &user_rankings, int k) {
    // Find top k movies
    std::vector<std::pair<sp_movie, double>> top_k;
    for (const auto &movie: movies_) {
        // if the user has already ranked the movie, skip it
        if (user_rankings.get_ranks().find(movie) != user_rankings.get_ranks().end()) {
            continue;
        }
        double similarity = predict_movie_score(user_rankings, movie, k);
        top_k.emplace_back(movie, similarity);
    }
    // sort the vector by similarity, in descending order
    std::sort(top_k.begin(), top_k.end(),
              [](const std::pair<sp_movie, double> &a, const std::pair<sp_movie, double> &b) {
                  return a.second > b.second;
              });
    // return the movie with the highest similarity
    return top_k[0].first;
}
