#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Course.h"
#include <sstream>
//default initializers
/*
Course::Course(){
    crn = "00";
    dCode = "00";
    cCode = "00";
    title = "00";
    day = "00";
    start = "00";
    end = "00";
    room = "00";
}*/
//Intializers
Course::Course(std::string crn_, std::string dCode_, std::string cCode_, std::string title_, std::string day_, std::string start_, std::string end_, std::string room_){
    crn = crn_;
    dCode = dCode_;
    cCode = cCode_;
    title = title_;
    day = day_;
    start = start_;
    end = end_;
    room = room_;
}
//return each component of the data
std::string Course::getRoom() const {return room;}
std::string Course::getDay() const {return day;}
std::string Course::getStart() const {return start;}
std::string Course::getcCode() const {return cCode;}
std::string Course::getdCode() const {return dCode;}
std::string Course::getTitle() const {return title;}
std::string Course::getCrn() const {return crn;}
//prints room function
void Course::printClasses(std::ofstream& out, int spaceT, int spaceD) const{
    out<<std::left<<std::setw(6)<<dCode<<std::left<<std::setw(11)<<cCode<<std::left<<std::setw(spaceT+2)<<title<<\
    std::left<<std::setw(spaceD+2)<<day<<std::left<<std::setw(12)<<start<<std::left<<std::setw(8)<<end<<std::endl;
}
//prints dept function
void Course::printDept(std::ofstream& out, int spaceT, int spaceD) const{
    out<<std::left<<std::setw(11)<<cCode<<std::left<<std::setw(spaceT+2)<<title<<\
    std::left<<std::setw(spaceD+2)<<day<<std::left<<std::setw(12)<<start<<std::left<<std::setw(8)<<end<<std::endl;
}
//sort by room function
bool sortRoom(const Course& c1, const Course& c2){
    //compare the room by alphabetical order
    if (c1.getRoom() < c2.getRoom()){
        return true;
    }
    else if (c1.getRoom() > c2.getRoom()){
        return false;
    }
    //compare by day of the week
    else {
        if (c1.getDay() == "Monday" && c2.getDay() != "Monday"){
            return true;
        }
        else if (c1.getDay() != "Monday" && c2.getDay() == "Monday"){
            return false;
        }
        else if (c1.getDay() == "Tuesday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday"){
            return true;
        }
        else if (c2.getDay() == "Tuesday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday"){
            return false;
        }
        else if (c1.getDay() == "Wednesday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday" && c2.getDay() != "Wednesday"){
            return true;
        }
        else if (c2.getDay() == "Wednesday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday" && c1.getDay() != "Wednesday"){
            return false;
        }
        else if (c1.getDay() == "Thursday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday" && c2.getDay() != "Wednesday" && c2.getDay() != "Thursday"){
            return true;
        }
        else if (c2.getDay() == "Thursday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday" && c1.getDay() != "Wednesday" && c1.getDay() != "Thursday"){
            return false;
        }
        else if ((c2.getDay() == "Friday")&&(c1.getDay() != "Friday")){
            return true;
        }
        else if ((c1.getDay() == "Friday")&&(c2.getDay() != "Friday")){
            return false;
        }
        /*create a string that takes in the hours as string and then convert 
        it to an integer. If it's PM, you would convert it to millitary time
        */
        else {
            std::string sHour1 = "";
            std::string sHour2 = "";
            sHour1 = sHour1 + c1.getStart()[0] + c1.getStart()[1];
            sHour2 = sHour2 + c2.getStart()[0] + c2.getStart()[1];
            int hour1 = atoi(sHour1.c_str());
            int hour2 = atoi(sHour2.c_str());
            if (c1.getStart()[5] == 'P'){
                hour1 = hour1+12;
            }
            if (c2.getStart()[5] == 'P'){
                hour2 = hour2+12;
            }
            if (hour1 == 24 && hour2 > 12){
                return true;
            }
            else if (hour1 > 12 && hour2 == 24){
                return false;
            }
            else if (hour1<hour2){
                return true;
            }
            else if (hour1 > hour2){
                return false;
            }
            else{
                //take in the course num as strings and following the same concept
                //as the previous function, you can sort it by its integer
                std::string str_cCode1 = "";
                std::string str_cCode2 = "";
                str_cCode1 += c1.getcCode()[6];
                str_cCode2 += c2.getcCode()[6];
                int int_cCode1 = atoi(str_cCode1.c_str());
                int int_cCode2 = atoi(str_cCode2.c_str());
                if (int_cCode1 < int_cCode2){
                    return true;
                }
                else if (int_cCode1 > int_cCode2){
                    return false;
                }
                else{
                    if (c1.getdCode() < c2.getdCode()){
                        return true;
                    }
                    else if (c1.getdCode() > c2.getdCode()){
                        return false;
                    }
                    return false;
                }
            }
        }
    }
}   
//sort if function is dept.
//same exact logic however i changed the order in which it is sorted
bool sortDept(const Course& c1, const Course& c2){
    std::string str_cCode1 = "";
    std::string str_cCode2 = "";
    str_cCode1 += c1.getcCode()[6];
    str_cCode2 += c2.getcCode()[6];
    if (c1.getcCode() < c2.getcCode()){
        return true;
    }
    else if (c1.getcCode() > c2.getcCode()){
        return false;
    }
    else{
        if (c1.getDay() == "Monday" && c2.getDay() != "Monday"){
            return true;
        }
        else if (c1.getDay() != "Monday" && c2.getDay() == "Monday"){
            return false;
        }
        else if (c1.getDay() == "Tuesday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday"){
            return true;
        }
        else if (c2.getDay() == "Tuesday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday"){
            return false;
        }
        else if (c1.getDay() == "Wednesday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday" && c2.getDay() != "Wednesday"){
            return true;
        }
        else if (c2.getDay() == "Wednesday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday" && c1.getDay() != "Wednesday"){
            return false;
        }
        else if (c1.getDay() == "Thursday" && c2.getDay() != "Monday" && c2.getDay() != "Tuesday" && c2.getDay() != "Wednesday" && c2.getDay() != "Thursday"){
            return true;
        }
        else if (c2.getDay() == "Thursday" && c1.getDay() != "Monday" && c1.getDay() != "Tuesday" && c1.getDay() != "Wednesday" && c1.getDay() != "Thursday"){
            return false;
        }
        else if ((c2.getDay() == "Friday")&&(c1.getDay() != "Friday")){
            return true;
        }
        else if ((c1.getDay() == "Friday")&&(c2.getDay() != "Friday")){
            return false;
        }
        else{
            std::string sHour1 = "";
            std::string sHour2 = "";
            sHour1 = sHour1 + c1.getStart()[0] + c1.getStart()[1];
            sHour2 = sHour2 + c2.getStart()[0] + c2.getStart()[1];
            int hour1 = atoi(sHour1.c_str());
            int hour2 = atoi(sHour2.c_str());
            if (c1.getStart()[5] == 'P'){
                hour1 = hour1+12;
            }
            if (c2.getStart()[5] == 'P'){
                hour2 = hour2+12;
            }
            if (hour1 == 24 && hour2 > 12){
                return false;
            }
            else if (hour1 > 12 && hour2 == 24){
                return false;
            }
            else if (hour1<hour2){
                return false;
            }
            else if (hour1 > hour2){
                return true;
            }
            return false;
        }
    }
 
}
               
        
                
                
                