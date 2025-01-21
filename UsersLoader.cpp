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
    // with the string "NA" means that the user didn't rate the movie in the index.
    while (std::getline(file, line)) {
        std::istringstream iss2(line);
        std::string user_name;
        iss2 >> user_name;
        rank_map ranks;
        for (auto &movie: movies) {
            std::string rate;
            iss2 >> rate;
            if (rate != "NA") {
                ranks[rs->get_movie(movie.first, movie.second)] = std::stod(rate);
            }
        }
        users.emplace_back(user_name, ranks, std::move(rs));
    }
    return users;
}
