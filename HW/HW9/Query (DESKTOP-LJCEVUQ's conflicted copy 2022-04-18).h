#include <iostream>
#include <map>
#include <vector>
class QUERY {
    public:
    QUERY();
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

    bool operator==(const QUERY& other){
        if (title != other.getTitle()){
            return false;
        }
        else if (year != other.getYear()){
            return false;
        }
        else if (time != other.getTime()){
            return false;
        }
        else if (genres_list != other.getGenres()){
            return false;
        }
        else if (actors_list != other.getActors()){
            return false;
        }
        else if (roles_list != other.getRoles()){
            return false;
        }
        else return true;
    }
    unsigned int ret_hash_value ();
    private:
    std::string title;
    std::string year;
    std::string time;
    std::vector <std::string> genres_list;
    std::vector <std::string> actors_list;
    std::vector <std::string> roles_list;
};