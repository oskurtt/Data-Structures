#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "time.h"

Time::Time(){
    hour = 0;
    min = 0;
    sec = 0;
}
Time::Time(int h, int m, int s){
    hour = h;
    min = m;
    sec = s;
    std::cout<<"creating new object"<<std::endl;
}

int Time::getHour() const {return hour;}
int Time::getMinute() const {return min;}
int Time::getSecond() const {return sec;}

void Time::setHour(int h){
    hour = h;
}
void Time::setMinute(int m){
    min = m;
}
void Time::setSecond(int s){
    sec = s;
}

void Time::PrintAMPM() const {
    if (hour > 12){
        std::cout<<hour-12<<":";
    }
    else{
        std::cout<<hour<<":";
    }

    if (min <10){
        std::cout<<"0"<<min<<":";
    }
    else{
        std::cout<<min<<":";
    }

    if (sec < 10){
        std::cout<<"0"<<sec<<":";
    }
    else{
        std::cout<<sec<<":";
    }

    if (hour<12){
        std::cout<<"am";
    }
    else{
        std::cout<<"pm";
    }
    std::cout<<std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2){
    if(t1.getHour() > t2.getHour()){
        return false;
    }
    else if (t1.getHour() < t2.getHour()){
        return true;
    }
    else{
        if(t1.getMinute() > t2.getMinute()){
            return false;
        }
        else if (t1.getMinute() < t2.getMinute()){
            return true;
        }
        else{
            if (t1.getSecond() > t2.getSecond()){
                return false;
            }
            else if (t1.getSecond() < t2.getSecond()){
                return true;
            }
        }

    }
}