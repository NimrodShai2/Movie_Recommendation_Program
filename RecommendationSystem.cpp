#include "RecommendationSystem.h"
#include <iostream>


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
