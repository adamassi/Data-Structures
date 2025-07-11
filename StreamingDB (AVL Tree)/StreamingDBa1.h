// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "AVLTree.h"
#include "movie.h"
#include "user.h"
#include "group.h"

class streaming_database {
private:
	//
	// Here you may add anything you want
	//

    AVLtree<Movie*,CompMoviesByID,EqualMovies>* movies;
    AVLtree<User*,CompUsersByID,EqualUsers> *users;
    AVLtree<Group*,CompGroupsByID,EqualGroup> *groups;
	AVLtree<Movie*,CompMoviesForRating,EqualMovies>* comedy_movies;
	AVLtree<Movie*,CompMoviesForRating,EqualMovies>* drama_movies;
	AVLtree<Movie*,CompMoviesForRating,EqualMovies>* action_movies;
	AVLtree<Movie*,CompMoviesForRating,EqualMovies>* fantasy_movies;
	AVLtree<Movie*,CompMoviesForRating,EqualMovies>* all_genre_movies;






public:
	// <DO-NOT-MODIFY> {
	
	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);

    AVLtree<Movie*,CompMoviesForRating,EqualMovies>* get_genre_tree(Genre genre);

    Genre get_max(int comedy,int drama,int action,int fantasy) ;


        // } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
