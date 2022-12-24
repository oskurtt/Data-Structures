#include <iostream>
#include "Movie.h"
//constructor
MOVIE_DATA::MOVIE_DATA(){
    title = "";
    year = "";
    time = "";
    genres_list;
    actors_list;
    roles_list;
}
//getters
std::string MOVIE_DATA::getTitle() const {return title;}
std::string MOVIE_DATA::getYear() const {return year;}
std::string MOVIE_DATA::getTime() const {return time;}
std::vector <std::string> MOVIE_DATA::getGenres() const {return genres_list;}
 std::vector <std::string> MOVIE_DATA::getActors() const {return actors_list;}
std::vector<std::string> MOVIE_DATA::getRoles() const {return roles_list;}
//changing data
void MOVIE_DATA::change_title (const std::string s){
    title = s;
}
void MOVIE_DATA::change_time (const std::string s){
    time = s;
}
void MOVIE_DATA::change_year (const std::string s){
    year = s;
}
void MOVIE_DATA::add_genre (const std::string s){
    genres_list.push_back(s);
}
void MOVIE_DATA::add_actor (const std::string ID){
    actors_list.push_back(ID);
}
void MOVIE_DATA::add_role (const std::string s){
    roles_list.push_back(s);
}
//function to return hash value
//add all info into a string and hash using function from lab
unsigned int MOVIE_DATA::ret_hash_value(){
    //hash taken from lab
    std::string s = "";
    if (getTitle() != "?") s+= getTitle();
    if (getTime() != "?") s+= getTime();
    if (getYear() != "?") s+= getYear();
    std::vector <std::string> g = getGenres();
    if (g.size() != 0){
        for (int i = 0; i < g.size(); i++){
            s += g[i];
        }
    }
    

    std::vector <std::string> a = getActors();
    if (a.size()!= 0){
        for (int i = 0; i < a.size(); i++){
            s += a[i];
        }
    }
    

    std::vector<std::string> r = getRoles();
    if (r.size() != 0){
        for (int i = 0; i < r.size(); i++){
            s += r[i];
        }
    }
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < s.length(); i++){
       hash ^= ((hash << 5) + s[i] + (hash >> 2)); 
    }
    return hash;
} 