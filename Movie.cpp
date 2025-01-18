#include "Movie.h"

#define HASH_START 17
#define RES_MULT 31

/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie &movie) {
    std::size_t res = HASH_START;
    res = res * RES_MULT + std::hash<std::string>()(movie->get_name());
    res = res * RES_MULT + std::hash<int>()(movie->get_year());
    return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie &m1, const sp_movie &m2) {
    return !(*m1 < *m2) && !(*m2 < *m1);
}

/**
 * Constructor
 * @param name name of the movie
 * @param year year of the movie
 */
Movie::Movie(std::string name, int year) : name_(std::move(name)), year_(year) {}

/**
 * Get the name of the movie
 * @return name of the movie
 */
std::string Movie::get_name() const {
    return name_;
}

/**
 * Get the year value of the movie
 * @return Release year of the movie
 */
int Movie::get_year() const {
    return year_;
}

/**
 * Compare two movies by their release year and then name
 * @param other movie to compare to
 * @return true if this movie was released before the other movie or if they were released in the same year
 * and the name of this movie is lexicographically smaller than the other movie
 */
bool Movie::operator<(const Movie &other) const {
    return year_ < other.year_ || (year_ == other.year_ && name_ < other.name_);
}

/**
 * Print the movie to the output stream
 * @param os output stream
 * @return output stream
 */
std::ostream &Movie::operator<<(std::ostream &os) const {
    os << name_ << " (" << year_ << ")\n";
    return os;
}

/**
 * Print the movie to the output stream
 * @param os output stream
 * @param movie movie to print
 * @return output stream
 */
std::ostream &operator<<(std::ostream &os, const Movie &movie) {
    os << movie.name_ << " (" << movie.year_ << ")\n";
    return os;
}




