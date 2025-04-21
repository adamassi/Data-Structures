#ifndef WET1_DS_movie
#define WET1_DS_movie
#include "wet1util.h"


class Movie{
public:    
    int movieId;
    Genre genre;
    int views;
    bool vipOnly;
    double rating_total;
    int num_of_ratings;
    double rating;

public:
    Movie(int movieId,Genre genre,int views,bool vipOnly);
    Movie(int movieId);
    Movie()=default;
    ~Movie()=default;
	//{  //to delete trees;}
    int getMovieId()const;
    bool isMovieVIP();
    void update_movie_rating(int user_rating);
    Genre get_movie_genre();

};

class CompMoviesByID {
public:
    bool operator()(Movie *t1, Movie *t2) const {
        return t1->getMovieId() < t2->getMovieId();
    }
};
class EqualMovies {
public:
    bool operator()(Movie *t1, Movie *t2) const {
        return t1->movieId == t2->movieId;
    }
};

class CompMoviesForRating {
public:
    bool operator()(Movie *t1, Movie *t2) const {
        if(t1->rating==t2->rating){
            if(t1->views==t2->views){
                return t1->getMovieId() > t2->getMovieId();
            }
            else return t1->views <t2->views;
        }
        else return t1->rating < t2->rating;
    }
};

// class EqualMoviesForRating {
// public:
//     bool operator()(Movie *t1, Movie *t2) const {
//         if(t1->rating==t2->rating){
//             if(t1->views==t2->views){
//                 return t1->getMovieId() == t2->getMovieId();
//             }
//             else return t1->views==t2->views;
//         }
//         else return t1->rating==t2->rating;
//     }
// };
#endif
