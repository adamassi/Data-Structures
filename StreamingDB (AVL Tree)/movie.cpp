#include "movie.h"

Movie::Movie(int movieId,Genre genre,int views,bool vipOnly)
        :movieId(movieId), genre(genre) , views(views), vipOnly(vipOnly), rating_total(0), num_of_ratings(0) ,rating(0){}


int Movie::getMovieId() const {
    return this->movieId;
}

Movie::Movie(int movieId):movieId(movieId) {}

bool Movie::isMovieVIP() {
    return this->vipOnly;
}

void Movie::update_movie_rating(int user_rating) {
     rating_total+=user_rating;
     num_of_ratings++;
     rating=(double)(rating_total/num_of_ratings);
}

Genre Movie::get_movie_genre() {
    return this->genre;
}

