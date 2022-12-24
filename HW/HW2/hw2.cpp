#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Course.h" 

int main(int argc, char* argv[]){
    //intialize variables
    std::string crn, dCode, cCode, title, day, start, end, room;
    std::ifstream infile (argv[1]); 
    std::ofstream outfile (argv[2]);
    std::string func (argv[3]);
    std::vector<Course> courses;
    //if input is empty, end function
    if (std::string(argv[1]) == "empty.txt"){
        outfile<<"No data available."<<std::endl;
        return 1;
    }
    //parse data and if course has multiple days, split them
    while (infile >> crn >> dCode >> cCode >> title >> day >> start >> end >> room) {
        for (int i = 0; i < day.size(); i++){
            if (day[i] == 'M'){
                courses.push_back(Course (crn, dCode, cCode, title, "Monday", start, end, room));
            }
            if (day[i] == 'T'){
                courses.push_back(Course (crn, dCode, cCode, title, "Tuesday", start, end, room));
            }
            if (day[i] == 'W'){
                courses.push_back(Course (crn, dCode, cCode, title, "Wednesday", start, end, room));
            }
            if (day[i] == 'R'){
                courses.push_back(Course (crn, dCode, cCode, title, "Thursday", start, end, room));
            }
            if (day[i] == 'F'){
                courses.push_back(Course (crn, dCode, cCode, title, "Friday", start, end, room));
            }
        }

  }
  //if room is called with an additional argument
    if (func == "room"){
        sort(courses.begin(), courses.end(), sortRoom);
        if (argc == 5){
            int entries = 0; 
            int spaceT = 0;
            int spaceD = 0;
            //create width of space variables and number of entries
            //loops through code and update the space
            std::string rname = argv[4];
            for (int i = 0; i<courses.size(); i++){
                if (courses[i].getRoom() == rname){
                    entries += 1;
                    if (courses[i].getTitle().size() > spaceT){
                        int x = courses[i].getTitle().size();
                        spaceT = (std::max(x, 11));
                    }
                    if (courses[i].getDay().size() > spaceD){
                        spaceD = courses[i].getDay().size();
                    }
                }
            }
            //if there are zero number of entries, that means it's empty, thus 
            //no data available
        if (entries == 0){
        outfile<<"No data available."<<std::endl;
        return 1;}
        entries = 0;
        //prints out the header and the data accordingly
            outfile<<"Room "<<rname<<std::endl;
            outfile<<std::left<<std::setw(6)<<"Dept"<<std::left<<std::setw(11)<<"Coursenum"<<std::left<<std::setw(spaceT+2)<<"Class Title"<<\
            std::left<<std::setw(spaceD+2)<<"Day"<<std::left<<std::setw(12)<<"Start Time"<<std::left<<std::setw(8)<<"End Time"<<std::endl;
            outfile<<"----  "<<"---------  "<<std::string (spaceT,'-')<<"  "<<std::string (spaceD,'-')<<"  "<<"----------  "<<"--------"<<std::endl;
            for (int j = 0; j<courses.size(); j++){
                if (courses[j].getRoom() == rname){
                    courses[j].printClasses(outfile, spaceT, spaceD);
                    entries += 1;
                }
            }
            outfile<<entries<<" entries"<<"\n"<<std::endl;
        }
        //prints out data if there isn't extra argument
        //created a currentRoom variable to group each course in their correct rooms
        else{
            std::sort(courses.begin(), courses.end(), sortRoom);
            std::string currentRoom = courses[0].getRoom();
            int entries = 0; 
            int spaceT = 0;
            int spaceD = 0;
            //same concept as previously stated: update width, if entry =0, no data avaialbe
            for (int j = 0; j<courses.size(); j++){
                if (courses[j].getRoom() == currentRoom){
                    if (courses[j].getTitle().size() > spaceT){
                        int x = courses[j].getTitle().size();
                        spaceT = (std::max(x, 11));
                    }
                    if (courses[j].getDay().size() > spaceD){
                        spaceD = courses[j].getDay().size();
                    }
                }
            }
            //print out headers
            outfile<<"Room "<<currentRoom<<std::endl;
            outfile<<std::left<<std::setw(6)<<"Dept"<<std::left<<std::setw(11)<<"Coursenum"<<std::left<<std::setw(spaceT+2)<<"Class Title"<<\
            std::left<<std::setw(spaceD+2)<<"Day"<<std::left<<std::setw(12)<<"Start Time"<<std::left<<std::setw(8)<<"End Time"<<std::endl;
            outfile<<"----  "<<"---------  "<<std::string (spaceT,'-')<<"  "<<std::string (spaceD,'-')<<"  "<<"----------  "<<"--------"<<std::endl;
            //print out data using for loop 
            for (int i = 0; i<courses.size(); i++){
                if (currentRoom != courses[i].getRoom()){
                    outfile<<entries<<" entries"<<"\n"<<std::endl;
                    currentRoom = courses[i].getRoom();
                    entries = 0; 
                    spaceT = 0;
                    spaceD = 0;
                    for (int j = 0; j<courses.size(); j++){
                        if (courses[j].getRoom() == currentRoom){
                            if (courses[j].getTitle().size() > spaceT){
                                int x = courses[j].getTitle().size();
                                spaceT = (std::max(x, 11));
                            }
                            if (courses[j].getDay().size() > spaceD){
                                spaceD = courses[j].getDay().size();
                            }
                        }
                    }
                        outfile<<"Room "<<currentRoom<<std::endl;
                        outfile<<std::left<<std::setw(6)<<"Dept"<<std::left<<std::setw(11)<<"Coursenum"<<std::left<<std::setw(spaceT+2)<<"Class Title"<<\
                        std::left<<std::setw(spaceD+2)<<"Day"<<std::left<<std::setw(12)<<"Start Time"<<std::left<<std::setw(8)<<"End Time"<<std::endl;
                        outfile<<"----  "<<"---------  "<<std::string (spaceT,'-')<<"  "<<std::string (spaceD,'-')<<"  "<<"----------  "<<"--------"<<std::endl;
                        courses[i].printClasses(outfile, spaceT, spaceD);
                        entries += 1;
                }
                else if (currentRoom == courses[i].getRoom()){
                    courses[i].printClasses(outfile, spaceT, spaceD);
                    entries += 1;
                }
            }
            outfile<<entries<<" entries"<<"\n"<<std::endl;
        }
    }
//run if dept function is called
    if (func == "dept"){
        sort(courses.begin(), courses.end(), sortDept);
        int entries = 0; 
        int spaceT = 0;
        int spaceD = 0;
        std::string dname = argv[4];
        //create space widths and number of entries
        //if number of entries is zero, output no data available
         for (int j = 0; j<courses.size(); j++){
            if (courses[j].getdCode() == dname){
                entries += 1;
            }
        }
        if (entries == 0){
        outfile<<"No data available."<<std::endl;
        return 1;}
        entries = 0;
        for (int i = 0; i<courses.size(); i++){
                if (courses[i].getdCode() == dname){
                    if (courses[i].getTitle().size() > spaceT){
                        spaceT = courses[i].getTitle().size();
                    }
                    if (courses[i].getDay().size() > spaceD){
                        spaceD = courses[i].getDay().size();
                    }
                }
            }
            //print out header and courses
        outfile<<"Dept "<<dname<<std::endl;
        outfile<<std::left<<std::setw(11)<<"Coursenum"<<std::left<<std::setw(spaceT+2)<<"Class Title"<<\
        std::left<<std::setw(spaceD+2)<<"Day"<<std::left<<std::setw(12)<<"Start Time"<<std::left<<std::setw(8)<<"End Time"<<std::endl;
        outfile<<"---------  "<<std::string (spaceT,'-')<<"  "<<std::string (spaceD,'-')<<"  "<<"----------  "<<"--------"<<std::endl;
        for (int j = 0; j<courses.size(); j++){
            if (courses[j].getdCode() == dname){
                courses[j].printDept(outfile, spaceT, spaceD);
                entries += 1;
            }
        }
        outfile<<entries<<" entries"<<"\n"<<std::endl;
    }
//custom function
//prints out all classes that is in "INTRODUCTION_TO_ELECTRONICS"
    if (func == "custom"){
        sort(courses.begin(), courses.end(), sortRoom);
            int entries = 0; 
            int spaceT = 0;
            int spaceD = 0;
            std::string rname = "INTRODUCTION_TO_ELECTRONICS";
            for (int i = 0; i<courses.size(); i++){
                if (courses[i].getTitle() == rname){
                    entries += 1;
                    if (courses[i].getTitle().size() > spaceT){
                        int x = courses[i].getTitle().size();
                        spaceT = (std::max(x, 11));
                    }
                    if (courses[i].getDay().size() > spaceD){
                        spaceD = courses[i].getDay().size();
                    }
                }
            }
            //if entries is zero, output no data available
        if (entries == 0){
        outfile<<"No data available."<<std::endl;
        return 1;}
        entries = 0;
        //print out courses
            outfile<<"Class "<<rname<<std::endl;
            outfile<<std::left<<std::setw(6)<<"Dept"<<std::left<<std::setw(11)<<"Coursenum"<<\
            std::left<<std::setw(spaceD+2)<<"Day"<<std::left<<std::setw(12)<<"Start Time"<<std::left<<std::setw(8)<<"End Time"<<std::endl;
            outfile<<"----  "<<"---------  "<<std::string (spaceT,'-')<<"  "<<std::string (spaceD,'-')<<"  "<<"----------  "<<"--------"<<std::endl;
            for (int j = 0; j<courses.size(); j++){
                if (courses[j].getTitle() == rname){
                    courses[j].printClasses(outfile, spaceT, spaceD);
                    entries += 1;
                }
            }
            outfile<<entries<<" entries"<<"\n"<<std::endl;
        
    
    }

}

