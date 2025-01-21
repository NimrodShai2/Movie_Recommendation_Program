
#ifndef RECOMMENDATIONSYSTEMLOADER_H
#define RECOMMENDATIONSYSTEMLOADER_H

#include "RecommendationSystem.h"

class RecommendationSystemLoader {
private:
    RecommendationSystemLoader() = default;

public:
    static std::unique_ptr<RecommendationSystem> create_rs_from_movies(const std::string &movies_file);

    RecommendationSystemLoader(const RecommendationSystemLoader &) = delete;

    RecommendationSystemLoader &operator=(const RecommendationSystemLoader &) = delete;

    ~RecommendationSystemLoader() = delete;

};

#endif // RECOMMENDATIONSYSTEMLOADER_H
