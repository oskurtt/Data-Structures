#include <iostream>
#include <map>
#include <vector>
class MOVIE_DATA {
    public:
    MOVIE_DATA();
    std::string getTitle() const;
    std::string getYear() const;
    std::string getTime() const;
    std::vector <std::string> getGenres() const;
    std::vector <std::string> getActors() const;
    std::vector <std::string> getRoles() const;

    void change_title (const std::string s);
    void change_time (const std::string s);
    void change_year (const std::string s);
    void add_genre (const std::string s);
    void add_actor (const std::string ID);
    void add_role (const std::string s);

    unsigned int ret_hash_value ();

    private:
    std::string title;
    std::string year;
    std::string time;
    std::vector <std::string> genres_list;
    std::vector <std::string> actors_list;
    std::vector <std::string> roles_list;
};