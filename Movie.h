
#ifndef EX5_MOVIE_H
#define EX5_MOVIE_H

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

#define HASH_START 17


class Movie;

typedef std::shared_ptr<Movie> sp_movie;

/**
 * those declartions and typedefs are given to you and should be used in the ex
 */
typedef std::size_t (*hash_func)(const sp_movie &movie);

typedef bool (*equal_func)(const sp_movie &m1, const sp_movie &m2);

std::size_t sp_movie_hash(const sp_movie &movie);

bool sp_movie_equal(const sp_movie &m1, const sp_movie &m2);

class Movie {
private:
    /// name of the movie
    std::string name_;
    int year_;
public:
    Movie(std::string name, int year);

    [[nodiscard]] std::string get_name() const;

    [[nodiscard]] int get_year() const;

    bool operator<(const Movie &other) const;

    std::ostream &operator<<(std::ostream &os) const;

};


#endif //EX5_MOVIE_H
