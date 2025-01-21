#include "RecommendationSystemLoader.h"
#include <fstream>
#include <sstream>


std::unique_ptr<RecommendationSystem>
RecommendationSystemLoader::create_rs_from_movies(const std::string &movies_file) {
    std::ifstream file(movies_file);
    if (!file.is_open()) {
        throw std::invalid_argument("file not found");
    }
    std::unique_ptr<RecommendationSystem> rs = std::make_unique<RecommendationSystem>();
    std::string line;
    // read the file line by line
    while (std::getline(file, line)) {
        std::string name;
        int year;
        std::vector<double> features;
        std::string feature;
        // parse the line
        std::istringstream iss(line);
        // read the line up to the char '-' - the name of the movie
        std::getline(iss, name, '-');
        // read the line up to the char ' ' - the year of the movie
        iss >> year;
        // read the line up to the end, with ' ' as the delimiter - the features of the movie
        while (std::getline(iss, feature, ' ')) {
            features.push_back(std::stod(feature));
        }
        rs->add_movie_to_rs(name, year, features);
    }
    return rs;
}
