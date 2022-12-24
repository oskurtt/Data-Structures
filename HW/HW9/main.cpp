 #include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <fstream>
#include <utility>
#include "Movie.h"
#include "Query.h"
int table_size = 50;

class HASH {
  public:
  HASH(int size_){
    change_size(size_);
  }

  void change_size(int size_){
    size = size_;
    if (hash_table.size() == 0){
      hash_table.resize(size);
    }
    else{
      std::vector <std::pair<QUERY, std::list<MOVIE_DATA>>> tmp = hash_table;
      hash_table.clear();
      hash_table.resize(size);
      for (int i = 0; i < tmp.size(); i++){
        int new_hash;
        int new_index;
        if (tmp[i].second.size() > 0){
          new_hash = tmp[i].first.ret_hash_value();
          new_index = ret_index(new_hash);
          hash_table[new_index] = tmp[i];
        }
      }
      tmp.clear();
    }
  }
  void change_occupancy(float o){
    occupancy = o;
  }
  int ret_index (int key) {
    return abs(key % size);
  }   

  std::vector <std::pair<QUERY, std::list<MOVIE_DATA>>> get_table (){
    return hash_table;
  }
  
  void insert_pair(QUERY query, MOVIE_DATA movie, int index){
    if (hash_table[index].second.size() > 0){
      if (query == hash_table[index].first){
        hash_table[index].second.push_back(movie);
      }
      else{
        for (int i = index+1; i < hash_table.size(); i++){
          if (i = hash_table.size()-1){
            int i = 0;
          }
          if (hash_table[i].second.size() == 0){
            unique_keys++;
            if ((unique_keys/size) >= occupancy) change_size(size*2);
            table_size *= 2;
            std::pair<QUERY, std::list<MOVIE_DATA>> p;
            std::list<MOVIE_DATA> ls;
            ls.push_back(movie); 
            p = std::make_pair(query, ls);
            hash_table[i] = p;
          }
        }
      }
      
    }
    else{
      unique_keys++;
      if ((unique_keys/size) >= occupancy) change_size(size*2);
      table_size *= 2;
      std::pair<QUERY, std::list<MOVIE_DATA>> p;
      std::list<MOVIE_DATA> ls;
      ls.push_back(movie); 
      p = std::make_pair(query, ls);
      hash_table[index] = p;
    }
  }

  void compare(QUERY query, int index, std::map<std::string, std::string>& actors){
    std::vector<MOVIE_DATA> results;
    std::list<MOVIE_DATA>::iterator itr = hash_table[index].second.begin();
    for (itr; itr != hash_table[index].second.end(); itr++){
      bool match = true;
      
      if ((query.getTitle() != "?") && ((*itr).getTitle() != query.getTitle())){
        match = false;
      } 
      if ((query.getYear() != "?") && ((*itr).getYear() != query.getYear())){
        match = false;
      } 
      if ((query.getTime() != "?") && ((*itr).getTitle() != query.getTitle())){
        match = false;
      } 

      std::vector <std::string> g = query.getGenres();
      if (g.size() != 0){
        if (g.size() == (*itr).getGenres().size()){
          for (int i = 0; i < g.size(); i++){
            if (g[i] != (*itr).getGenres()[i]) match = false;
          }
        }
        else{
          match = false;
        } 
      }
      
      std::vector <std::string> a = query.getActors();
      std::vector <std::string> b = (*itr).getActors();
      if (a.size() != 0){
        if (a.size() == b.size()){
          for (int i = 0; i<a.size(); i++){
            if (a[i]!=b[i]) match = false;
          }
        }
        else {
          match = false;
        }
      }

      std::vector<std::string> r = query.getRoles();
      if (r.size() != 0){
        if (r.size() == (*itr).getRoles().size()){
          for (int i = 0; i < r.size(); i++){
            if (r[i] != (*itr).getRoles()[i]) match = false;
          }
        }
        else{
          match = false;
        } 
      }
      
      if (match){
        results.push_back(*itr);
      }
    }
    if (results.size() == 0){
      std::cout<<"No results for query."<<std::endl;
    }
    else{
      std::cout<<"Printing "<<results.size()<<" result(s):"<<std::endl;
      for (int i = 0; i < results.size(); i++){
        std::vector<std::string> info;
        std::vector<std::string> roles;
        std::cout<<results[i].getTitle()<<std::endl;
        std::cout<<results[i].getYear()<<std::endl;
        std::cout<<results[i].getTime()<<std::endl;

        info = results[i].getGenres();
        std::cout<<info.size()<<" ";
        for (int i = 0; i<info.size(); i++){
          if (i == info.size()-1){
            std::cout<<info[i];
          }
          else std::cout<<info[i]<<" ";
        }
        std::cout<<std::endl;

        info = results[i].getActors();
        roles = results[i].getRoles();
        std::cout<<info.size()<<" ";
        for (int i = 0; i<info.size(); i++){
          if (i == info.size()-1){
            std::cout<<actors[info[i]]<<" ("<<roles[i]<<")";
          }
          else std::cout<<actors[info[i]]<<" ("<<roles[i]<<") ";
        }
        std::cout<<std::endl;
      }
    }
  }


  private:
  std::vector <std::pair<QUERY, std::list<MOVIE_DATA>>> hash_table;
  int size;
  int unique_keys = 0;
  float occupancy = 0;
  
};

void permute_filters(int pos, std::vector<int> filter, MOVIE_DATA& movie, HASH& hash_table){
	if(pos == 6){
    QUERY data;

		if (filter[0] == 1) data.change_title(movie.getTitle());
    else data.change_title("?");
    if (filter[1] == 1) data.change_year(movie.getYear());
    else data.change_year("?");
    if (filter[2] == 1) data.change_time(movie.getTime());
    else data.change_time("?");

    if (filter[3] == 1){
      std::vector <std::string> g = movie.getGenres();
      for (int i = 0; i < g.size(); i++){
          data.add_genre(g[i]);
      }
    }

    if (filter[4] == 1){
      std::vector <std::string> a = movie.getActors();
      for (int i = 0; i<a.size(); i++){
          data.add_actor(a[i]);
      }
    }
    
    if (filter[5] == 1){
      std::vector<std::string> r = movie.getRoles();
      for (int i = 0; i < r.size(); i++){
          data.add_role(r[i]);
      }
    }
    int index;
    index = hash_table.ret_index(data.ret_hash_value());
    hash_table.insert_pair(data, movie, index);
		return;
	}

	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new, movie, hash_table);
	permute_filters(pos+1, filter, movie, hash_table);
}

int main () {
  std::string command; 
  float occup = 0.5; 
  int index = 0;
  HASH hash_table(table_size);
  hash_table.change_occupancy(occup);
  std::map<std::string, std::string> actors;
  while (std::cin >> command) {
    if (command == "movies"){
      std::string txt;
      std::string info;
      int x;
      std::cin>>txt;
      std::ifstream infile (txt);

      while (infile>>info){
        MOVIE_DATA movie;
        //set the title
        movie.change_title(info);

        //set the year
        infile>>info;
        movie.change_year (info);

        //set time
        infile>>info;
        movie.change_time(info);

        //set genre
        infile>>x;
        for (int i = 0; i<x; i++){
          infile>>info;
          movie.add_genre(info);
  
        }
        //set actor
        infile>>x;
        for (int i = 0; i<x; i++){
          infile>>info;
          movie.add_actor(info);
        }
        //set role
        infile>>x;
        for (int i = 0; i<x; i++){
          infile>>info;
          movie.add_role(info);
        }
        permute_filters(0, std::vector<int>(), movie, hash_table);
      }

    }
    else if (command == "actors"){
      std::string txt;
      std::string ID;
      std::string name;
      std::cin>>txt;
      std::ifstream infile (txt);
      while (infile){
        infile>>ID;
        infile>>name;
        actors[ID] = name;
      }
      
    }
    else if (command == "table_size"){
      std::cin>>table_size;
      hash_table.change_size(table_size);
    }
    else if (command == "occupancy"){
      std::cin>>occup;
      hash_table.change_occupancy(occup);
    }
    else if (command == "query"){
      QUERY query;
      std::string info;
      int x;
      //set the title
      std::cin>>info;
      query.change_title(info);
      //set the year
      std::cin>>info;
      query.change_year (info);
      //set time
      std::cin>>info;
      query.change_time(info);
      //set genre
      std::cin>>x;
      if (x != 0){
        for (int i = 0; i<x; i++){
          std::cin>>info;
          query.add_genre(info);
        }
      }
      
      //set actor
      std::cin>>x;
      if (x != 0){
        for (int i = 0; i<x; i++){
          std::cin>>info;
          query.add_actor(info);
        }
      }
      
      //set role
      std::cin>>x;
      if ( x!= 0){
        for (int i = 0; i<x; i++){
          std::cin>>info;
          query.add_role(info);
        }
      }
      
      //find the query in hash_table

      int index;
      index = hash_table.ret_index(query.ret_hash_value());
      hash_table.compare(query, index, actors);
    }
    else if (command == "quit"){
      return 0;
    }


  }
}
