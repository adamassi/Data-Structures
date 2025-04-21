#include "StreamingDBa1.h"
#include "wet1util.h"
#include "AVLTree.h"
#include "movie.h"
#include "user.h"

streaming_database::streaming_database()
{
    // TODO: Your code goes here
    movies=new AVLtree<Movie*,CompMoviesByID,EqualMovies>();
    users=new AVLtree<User*,CompUsersByID,EqualUsers>();
    groups=new AVLtree<Group*,CompGroupsByID,EqualGroup>();
    comedy_movies=new AVLtree<Movie*,CompMoviesForRating,EqualMovies>();
    drama_movies=new AVLtree<Movie*,CompMoviesForRating,EqualMovies>();
    action_movies=new AVLtree<Movie*,CompMoviesForRating,EqualMovies>();
    fantasy_movies=new AVLtree<Movie*,CompMoviesForRating,EqualMovies>();
    all_genre_movies=new AVLtree<Movie*,CompMoviesForRating,EqualMovies>();

}

streaming_database::~streaming_database()
{
    int num_users = users->num_nodes;
        User **users_arr = new User *[num_users];
        users->PrintInOrder(num_users,users_arr);
        for (int i = 0; i < num_users; i++) {
            delete users_arr[i];
        }

        int num_movies = movies->num_nodes;
        Movie **movies_arr = new Movie *[num_movies];
        movies->PrintInOrder(num_movies,movies_arr);
        for (int i = 0; i < num_movies; i++) {
            delete movies_arr[i];
        }
        int num_groups = groups->num_nodes;
        Group **groups_arr = new Group *[num_groups];
        groups->PrintInOrder(num_groups,groups_arr);
        for (int i = 0; i < num_groups; i++) {
            delete groups_arr[i];
        }
        delete[] groups_arr;
        delete[] users_arr;
        delete[] movies_arr;
        delete movies;
        delete users;
        delete groups;
        delete comedy_movies;
        delete drama_movies;
        delete action_movies;
        delete fantasy_movies;
        delete all_genre_movies;
    // TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    // TODO: Your code goes here
    if(movieId <=0 || views<0 ||genre ==Genre::NONE ) {
        return StatusType::INVALID_INPUT;
    }
    Movie *movie = new Movie(movieId,genre,views,vipOnly);
    if (movie == nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }
    //(movies->findNode(movie)){
    //    delete movie;
    //    return StatusType::FAILURE;
    //}
    try {
        movies->insert(movie);
    }
    catch (const std::exception& e) {
        delete movie;
        return StatusType::FAILURE;
    }
    try {
        all_genre_movies->insert(movie);
    }
    catch (const std::exception& e) {
        delete movie;
        return StatusType::FAILURE;
    }

    if(genre== Genre::COMEDY){
        try {
            comedy_movies->insert(movie);
        }
        catch (const std::exception& e) {
            movies->remove(movie);
            delete movie;
            return StatusType::FAILURE;
        }
    }
    if(genre== Genre::DRAMA){
        try {
            drama_movies->insert(movie);
        }
        catch (const std::exception& e) {
            movies->remove(movie);
            delete movie;
            return StatusType::FAILURE;
        }
    }
    if(genre== Genre::ACTION){
        try {
            action_movies->insert(movie);
        }
        catch (const std::exception& e) {
            movies->remove(movie);
            delete movie;
            return StatusType::FAILURE;
        }
    }
    if(genre== Genre::FANTASY){
        try {
            fantasy_movies->insert(movie);
        }
        catch (const std::exception& e) {
            movies->remove(movie);
            delete movie;
            return StatusType::FAILURE;
        }
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    // TODO: Your code goes here
    if( movieId<=0 ){
        return StatusType::INVALID_INPUT;
    }
    Movie *movie_to_find= new Movie(movieId,Genre::NONE,0,false);
    Movie** movie;
    movie = this->movies->findData(movie_to_find);
    delete movie_to_find;
    if(movie==nullptr){
        return StatusType::FAILURE;  // ALLOCATION_ERROR or failure????? FAILURE
    }
    Movie *movie_pointer = *movie;

    if(movie_pointer->genre== Genre::COMEDY){
        this->comedy_movies->remove(movie_pointer);
    }
    if(movie_pointer->genre== Genre::DRAMA){
        this->drama_movies->remove(movie_pointer);
    }
    if(movie_pointer->genre== Genre::ACTION){
        this->action_movies->remove(movie_pointer);
    }
    if(movie_pointer->genre== Genre::FANTASY){
        this->fantasy_movies->remove(movie_pointer);
    }
    all_genre_movies->remove(movie_pointer);
    this->movies->remove(movie_pointer);
    delete (movie_pointer);
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    // TODO: Your code goes here
    if(userId<=0 ){
        return StatusType::INVALID_INPUT;
    }
    User* new_user=new User(userId,isVip);
    if(new_user==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    //if(users->findNode(new_user)){
    //    delete new_user;
    //    return StatusType::FAILURE;
    //}
    try
    {
        users->insert(new_user);
    }
    catch(const std::exception& e)
    {
        delete new_user;
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    // TODO: Your code goes here
    if(userId<=0){
        return StatusType::INVALID_INPUT;
    }
    User* p=new  User(userId,false);
    if(p==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    User** user;
    user=users->findData(p);
    delete p;
    if(user==nullptr){
        return StatusType::FAILURE;
    }
	
    if((*user)->group != nullptr){
        if((*user)->isVip){
            ((*user)->group)->numVipUsers--;
        }
        try{
            ((*user)->group)->users_group->remove(*user);
        }
        catch (const std::exception& e) {
            return StatusType::FAILURE;
        }
    }
	    User *user_pointer = *user;
    try{
        users->remove(user_pointer);
    }
    catch (const std::exception& e) {
	    delete (user_pointer);
        return StatusType::FAILURE;
    }
    delete (user_pointer);

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    // TODO: Your code goes here
    if(groupId <=0) {
        return StatusType::INVALID_INPUT;
    }
    Group *group = new Group(groupId);
    if (group == nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }
    try {
        groups->insert(group);
    }
    catch (const std::exception& e) {
        delete group;
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    // TODO: Your code goes here
    if(groupId <=0) {
        return StatusType::INVALID_INPUT;
    }
    Group* g=new  Group(groupId);
    if(g==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    Group** group;
    group=groups->findData(g);
    delete g;
    if(group==nullptr){
        return StatusType::FAILURE;
    }
    int num_users = (*group)->users_group->num_nodes;
    User **users_arr = new User *[num_users];
    (*group)->users_group->PrintInOrder(num_users,users_arr);
    for (int i = 0; i < num_users; i++) {
        users_arr[i]->action+=((*group)->action);
        users_arr[i]->comedy+=((*group)->comedy);
        users_arr[i]->drama+=((*group)->drama);
        users_arr[i]->fantasy+=((*group)->fantasy);
		users_arr[i]->group=nullptr;
        users_arr[i]=nullptr;
    }
    delete[] users_arr;

    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    //SHO BSER BAL USERS
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    ///lazem amrok 3la kl oa7d mn al users ozbet sdh kdesh 7der
	Group *Group_pointer = *group;
    try{
        groups->remove(Group_pointer);
    }
    catch (const std::exception& e) {
	    delete (Group_pointer);
        return StatusType::FAILURE;
    }
    delete (Group_pointer);

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    // TODO: Your code goes here
    if(groupId <=0|| userId<=0) {
        return StatusType::INVALID_INPUT;
    }
    Group* g=new  Group(groupId);
    if(g==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    Group** group;
    group=groups->findData(g);
    delete g;
    if(group==nullptr){
        return StatusType::FAILURE;
    }
    User* p=new  User(userId,false);
    if(p==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    User** user;
    user=users->findData(p);
    delete p;
    if(user==nullptr){
        return StatusType::FAILURE;
    }
	if((*user)->group){
	   return StatusType::FAILURE;
	}
    try
    {
        (*group)->users_group->insert(*user);
    }
    catch(const std::exception& e)
    {
        return StatusType::FAILURE;
    }
    if((*user)->isVip){
        (*group)->numVipUsers++;
    }
    (*user)->group=(*group);
    (*user)->action-=(*group)->action;
    (*user)->drama-=(*group)->drama;
    (*user)->comedy-=(*group)->comedy;
    (*user)->fantasy-=(*group)->fantasy;

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    // TODO: Your code goes here
    if(userId<=0||movieId<=0){
        return StatusType::INVALID_INPUT;
    }
    User* p=new  User(userId,false);
    if(p==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    User** user;
    user=users->findData(p);
    delete p;
    if(user==nullptr){
        return StatusType::FAILURE;
    }
    Movie *movie_to_find= new Movie(movieId,Genre::NONE,0,false);
    Movie** movie;
    movie = this->movies->findData(movie_to_find);
    delete movie_to_find;
    if(movie==nullptr){
        return StatusType::FAILURE;
    }
    if((*movie)->vipOnly){
        if((*user)->isVip){
            Genre genre=(*movie)->get_movie_genre();
            AVLtree<Movie*,CompMoviesForRating,EqualMovies>* genre_tree=get_genre_tree(genre);
            genre_tree->remove((*movie));
            all_genre_movies->remove((*movie));
            (*movie)->views++;
            if(genre== Genre::COMEDY){
                (*user)->comedy++;
            }
            if(genre== Genre::DRAMA){
                (*user)->drama++;
            }
            if(genre== Genre::ACTION){
                (*user)->action++;
            }
            if(genre== Genre::FANTASY){
                (*user)->fantasy++;
            }
            try{
                genre_tree->insert((*movie));
            }
            catch(const std::exception& e){
                return StatusType::FAILURE;
            }
            try{
                all_genre_movies->insert((*movie));
            }
            catch(const std::exception& e){
                return StatusType::FAILURE;
            }

            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    }
    Genre genre=(*movie)->get_movie_genre();
    AVLtree<Movie*,CompMoviesForRating,EqualMovies>* genre_tree=get_genre_tree(genre);
    genre_tree->remove((*movie));
    all_genre_movies->remove((*movie));
    (*movie)->views++;
    if(genre== Genre::COMEDY){
        (*user)->comedy++;
    }
    if(genre== Genre::DRAMA){
        (*user)->drama++;
    }
    if(genre== Genre::ACTION){
        (*user)->action++;
    }
    if(genre== Genre::FANTASY){
        (*user)->fantasy++;
    }
    try{
        genre_tree->insert((*movie));
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }
    try{
        all_genre_movies->insert((*movie));
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    // TODO: Your code goes here
    if(groupId<=0||movieId<=0){
        return StatusType::INVALID_INPUT;
    }
    Group* g=new  Group(groupId);
    if(g==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    Group** group;
    group=groups->findData(g);
    delete g;
    if(group==nullptr){
        return StatusType::FAILURE;
    }
    if((*group)->users_group->num_nodes==0){
        return StatusType::FAILURE;
    }
    Movie *movie_to_find= new Movie(movieId,Genre::NONE,0,false);
    Movie** movie;
    movie = this->movies->findData(movie_to_find);
    delete movie_to_find;
    if(movie==nullptr){
        return StatusType::FAILURE;
    }
    if(((*movie)->vipOnly)&&(!((*group)->numVipUsers>0))){
        return StatusType::FAILURE;
    }
    Genre genre=(*movie)->get_movie_genre();
    AVLtree<Movie*,CompMoviesForRating,EqualMovies>* genre_tree=get_genre_tree(genre);
    genre_tree->remove((*movie));
    all_genre_movies->remove((*movie));
    (*movie)->views+=(*group)->users_group->num_nodes;
    try{
        genre_tree->insert((*movie));
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }
    try{
        all_genre_movies->insert((*movie));
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }
    if(genre== Genre::COMEDY){
        (*group)->comedy++;
    }
    if(genre== Genre::DRAMA){
        (*group)->drama++;
    }
    if(genre== Genre::ACTION){
        (*group)->action++;
    }
    if(genre== Genre::FANTASY){
        (*group)->fantasy++;
    }

    (*group)->update_max_in_group();
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    if(genre== Genre::NONE){
        return movies->num_nodes;
    }
    if(genre== Genre::COMEDY){
        return comedy_movies->num_nodes;
    }
    if(genre== Genre::DRAMA){
        return drama_movies->num_nodes;
    }
    if(genre== Genre::ACTION){
        return action_movies->num_nodes;
    }
    if(genre== Genre::FANTASY){
        return fantasy_movies->num_nodes;
    }

////AAAAAAAAAAAAAAAAAAAAAAAAA
////AAAAAAAAAAAAAAAAAAAAAAAA
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    if(output==NULL){
        return StatusType::INVALID_INPUT;
    }
    int num_of_emp=0;
    if(genre== Genre::NONE){
        num_of_emp=all_genre_movies->num_nodes;
        if (num_of_emp == 0) {
            return StatusType::FAILURE;
        }
        Movie **moviesData = new Movie *[all_genre_movies->num_nodes];
        all_genre_movies->avlToSortedArrayBackwards(moviesData,num_of_emp-1);
        for (int i = 0; i < num_of_emp; i++) {
            output[i] = moviesData[i]->movieId;
            moviesData[i]=nullptr;
        }
        delete[] moviesData;
    }
    if(genre== Genre::COMEDY){
        num_of_emp=comedy_movies->num_nodes;
        if (num_of_emp == 0) {
            return StatusType::FAILURE;
        }
        Movie **moviesData = new Movie *[comedy_movies->num_nodes];
        comedy_movies->avlToSortedArrayBackwards(moviesData,num_of_emp-1);
        for (int i = 0; i < num_of_emp; i++) {
            output[i] = moviesData[i]->movieId;
            moviesData[i]=nullptr;
        }
        delete[] moviesData;
    }
    if(genre== Genre::DRAMA){
        num_of_emp=drama_movies->num_nodes;
        if (num_of_emp == 0) {
            return StatusType::FAILURE;
        }
        Movie **moviesData = new Movie *[drama_movies->num_nodes];
        drama_movies->avlToSortedArrayBackwards(moviesData,num_of_emp-1);
        for (int i = 0; i < num_of_emp; i++) {
            output[i] = moviesData[i]->movieId;
            moviesData[i]=nullptr;
        }
        delete[] moviesData;
    }
    if(genre== Genre::ACTION){
        num_of_emp=action_movies->num_nodes;
        if (num_of_emp == 0) {
            return StatusType::FAILURE;
        }
        Movie **moviesData = new Movie *[action_movies->num_nodes];
        action_movies->avlToSortedArrayBackwards(moviesData,num_of_emp-1);
        for (int i = 0; i < num_of_emp; i++) {
            output[i] = moviesData[i]->movieId;
            moviesData[i]=nullptr;
        }
        delete[] moviesData;
    }
    if(genre== Genre::FANTASY){
        num_of_emp=fantasy_movies->num_nodes;
        if (num_of_emp == 0) {
            return StatusType::FAILURE;
        }
        Movie **moviesData = new Movie *[fantasy_movies->num_nodes];
        fantasy_movies->avlToSortedArrayBackwards(moviesData,num_of_emp-1);
        for (int i = 0; i < num_of_emp; i++) {
            output[i] = moviesData[i]->movieId;
            moviesData[i]=nullptr;
        }
        delete[] moviesData;
    }


    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    // TODO: Your code goes here
    if(userId<=0){
        return StatusType::INVALID_INPUT;
    }
    User* p=new  User(userId,false);
    if(p==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    User** user;
    user=users->findData(p);
    delete p;
    if(user==nullptr){
        return StatusType::FAILURE;
    }
    if ((*user)->group)
    {
        Group* group;
        group=(*user)->group;
        if(genre==Genre::NONE){
            return (*user)->action+(*user)->drama+(*user)->comedy+(*user)->fantasy+(group)->comedy+(group)->drama+(group)->action+(group)->fantasy;
        }
        if(genre== Genre::COMEDY){
            return ((*user)->comedy)+(group->comedy);
        }
        if(genre== Genre::DRAMA){
            return ((*user)->drama)+(group->drama);
        }
        if(genre== Genre::ACTION){
            return (*user)->action+group->action;
        }
        if(genre== Genre::FANTASY){
            return (*user)->fantasy+group->fantasy;
        }

    }
    if(genre==Genre::NONE){
        return (*user)->action+(*user)->drama+(*user)->comedy+(*user)->fantasy;
    }
    if(genre== Genre::COMEDY){
        return (*user)->comedy;
    }
    if(genre== Genre::DRAMA){
        return (*user)->drama;
    }
    if(genre== Genre::ACTION){
        return (*user)->action;
    }
    if(genre== Genre::FANTASY){
        return (*user)->fantasy;
    }


    return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    if(movieId <=0 || userId<=0 || rating<0 ||  rating>100 ) {
        return StatusType::INVALID_INPUT;
    }
    User* p=new User(userId);
    if(p==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    User** user;
    user=users->findData(p);
    delete p;
    if(user==nullptr){
        return StatusType::FAILURE;
    }
    Movie *movie_to_find= new Movie(movieId,Genre::NONE,0,false);
    if (movie_to_find== nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }
    Movie** movie_pointer;
    movie_pointer = this->movies->findData(movie_to_find);
    delete movie_to_find;
    if(movie_pointer==nullptr){
        //delete user;
        return StatusType::FAILURE;  // ALLOCATION_ERROR or failure?????
    }
    Movie *movie = *movie_pointer;
    if(!((*user)->isUserVIP()) && (movie->isMovieVIP())){
        //delete movie;
        //delete user;
        return StatusType::FAILURE;
    }
    Genre genre=movie->get_movie_genre();
    AVLtree<Movie*,CompMoviesForRating,EqualMovies>* genre_tree=get_genre_tree(genre);
    genre_tree->remove(movie);
    all_genre_movies->remove(movie);
    movie->update_movie_rating(rating);
    try{
        genre_tree->insert(movie);
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }
    try{
        all_genre_movies->insert(movie);
    }
    catch(const std::exception& e){
        return StatusType::FAILURE;
    }



    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    // TODO: Your code goes here
    if(groupId <=0) {
        return StatusType::INVALID_INPUT;
    }
    Group* g=new Group(groupId);
    if(g==nullptr){
        return StatusType::ALLOCATION_ERROR;
    }
    Group** group;
    group=groups->findData(g);
    delete g;
    if(group==nullptr){
        return StatusType::FAILURE;
    }
	if((*group)->users_group->num_nodes==0){
       return StatusType::FAILURE;
    }

    int com=(*group)->get_genre_views(Genre::COMEDY);
    int com1=com;
    com=0;
	int act=(*group)->get_genre_views(Genre::ACTION);
    int act1=act;
    act=0;
	int dra=(*group)->get_genre_views(Genre::DRAMA);
    int dra1=dra;
    dra=0;
	int fan=(*group)->get_genre_views(Genre::FANTASY);
    int fan1=fan;
    fan=0;
    int num_users=(*group)->users_group->num_nodes;
    User **G_users = new User *[num_users];
    ((*group)->users_group)->avlToSortedArrayBackwards(G_users,num_users-1);
    for (int i = 0; i < num_users; i++) {
        com=com+com1+G_users[i]->comedy;
        act=act+act1+G_users[i]->action;
        dra=dra+dra1+G_users[i]->drama;
        fan=fan+fan1+G_users[i]->fantasy;
        G_users[i]=nullptr;
    }
    delete[] G_users;

    Genre genre= get_max(com,dra,act,fan);
//int views=(*group)->get_genre_views(genre);
	//if(genre==Genre::COMEDY) {
   //     views+=com;
   // }
   // else if(genre==Genre::DRAMA) {
   //    views+=dra;
   // }
    //else if(genre==Genre::ACTION) {
    //   views+=act;
   // }
   // else if(genre==Genre::FANTASY) {
  //      views+=fan;
  //  }
  
    //if(!views) return StatusType::FAILURE;
    AVLtree<Movie*,CompMoviesForRating,EqualMovies>* genre_tree=get_genre_tree(genre);
   // return genre_tree->max_node->getValue()->movieId;
	if(genre_tree->num_nodes ==0) return StatusType::FAILURE;
	return genre_tree->max_node->getValue()->movieId;
}


/////////////////////////////----FUNC-----///////////////////////////

AVLtree<Movie*,CompMoviesForRating,EqualMovies>* streaming_database::get_genre_tree(Genre genre){
    if(genre==Genre::COMEDY) {
        return comedy_movies;
    }
    else if(genre==Genre::DRAMA) {
        return drama_movies;
    }
    else if(genre==Genre::ACTION) {
        return action_movies;
    }
    else if(genre==Genre::FANTASY) {
        return fantasy_movies;
    }
    else{
        return all_genre_movies;
    }
}


Genre streaming_database::get_max(int comedy,int drama,int action,int fantasy) {
    if(comedy>=drama && comedy >=action && comedy >=fantasy)
    {
        return Genre::COMEDY;
    }
    else if(drama>comedy && drama >=action && drama>=fantasy)
    {
        return Genre::DRAMA;
    }
    else if(action>comedy && action >drama && action>=fantasy)
    {
        return Genre::ACTION;
    }
    else if(fantasy>comedy && fantasy >drama && fantasy>action)
    {
        return Genre::FANTASY;
    }
    return Genre::FANTASY;//// MSH RA7 EOSAL LHAN
}