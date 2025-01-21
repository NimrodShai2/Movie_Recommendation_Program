#ifndef USERFACTORY_H
#define USERFACTORY_H

#include <vector>
#include <string>
#include "User.h"

class UsersLoader {
private:
    UsersLoader() = default;

public:
    static std::vector<User> load_users(const std::string &users_file_path, std::unique_ptr<RecommendationSystem> rs);


};

#endif //USERFACTORY_H
