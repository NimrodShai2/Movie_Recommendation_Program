#include "User.h"
#include <iostream>
#include <utility>

User::User(std::string name, rank_map ranks,
           std::unique_ptr<RecommendationSystem> rs) : name_(std::move(name)),
                                                       ranks_(std::move(ranks)),
                                                       rs_(std::move(rs)) {}


const std::string &User::get_name() const {
    return name_;
}

const rank_map &User::get_ranks() const {
    return ranks_;
}

void User::add_movie_to_user(const std::string &name, int year,
                             const std::vector<double> &features,
                             double rate) {
    sp_movie movie = std::make_shared<Movie>(name, year);
    // add the movie to the recommendation system
    rs_->add_movie_to_rs(name, year, features);
    // add the movie to the user's ranks
    ranks_[movie] = rate;
}

sp_movie User::get_rs_recommendation_by_content() {
    return rs_->recommend_by_content(*this);
}

sp_movie User::get_rs_recommendation_by_cf(int k) {
    return rs_->recommend_by_cf(*this, k);
}

double User::get_rs_prediction_score_for_movie(const std::string &name, int year, int k) {
    return rs_->predict_movie_score(name, year, *this);
}

std::ostream &User::operator<<(std::ostream &os) const {
    os << "name: " << name_ << std::endl;
    os << rs_ << std::endl;
}