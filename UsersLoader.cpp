#include "UsersLoader.h"
#include "User.h"
#include <fstream>
#include <sstream>

std::vector<User>
UsersLoader::load_users(const std::string &users_file_path, std::unique_ptr<RecommendationSystem> rs) {
    std::vector<User> users;
    std::ifstream file(users_file_path);
    if (!file.is_open()) {
        throw std::invalid_argument("file not found");
    }
    std::string line;
    // Read the first line - the header (movies names and years in the format "name-year name-year ...")
    std::getline(file, line);
    std::istringstream iss(line);
    std::string name;
    std::string year;
    std::vector<std::pair<std::string, int>> movies;
    while (iss >> name >> year) {
        movies.emplace_back(name, std::stoi(year));
    }
    // Read the rest of the lines - the users. Each line is in the format "user_name rate rate rate ...". An index
    // NA means that the user didn't rate the movie in the index.
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string user_name;
        iss >> user_name;
        rank_map ranks;
        for (int i = 0; i < movies.size(); ++i) {
            double rate;
            iss >> rate;
            if (rate != -1) {
                sp_movie movie = std::make_shared<Movie>(movies[i].first, movies[i].second);
                ranks[movie] = rate;
            }
        }
        users.emplace_back(user_name, ranks, std::move(rs));
    }
    return users;
}
