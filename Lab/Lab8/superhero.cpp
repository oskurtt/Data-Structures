#include <iostream>
#include <string>
#include "superhero.h"
Superhero::Superhero(std::string n, std::string i, std::string p){
    name = n;
    identity = i;
    power = p;
    
}

std::ostream& operator<< (std::ostream& os, Superhero& s){
        return os<<"Superhero "<<s.getName()<<" has power "<<s.getPower()<<std::endl;
    }

bool Superhero::operator==(std::string s){
    if (this->getName() == s){
        return true;
    }
    else if (this->getTrueIdentity() ==s){
        return true;
    }
    else if (this->getPower() == s){
        return true;
    }
    else{
        return false;
    }
}

bool Superhero::operator!=(std::string s){
    if (this->getName() == s){
        return false;
    }
    else if (this->getTrueIdentity() ==s){
        return false;
    }
    else if (this->getPower() == s){
        return false;
    }
    else{
        return true;
    }
}

Superhero& Superhero::operator-(){
    this->changeHero();
    return *this;
}

bool Superhero::operator>(const Superhero& s){
    if ((this->getPower() == "Fire") && (s.getPower() == "Wood")){
        return true;
    }
    else if ((this->getPower() == "Wood") && (s.getPower() == "Water")){  
        return true;
    }
    else if ((this->getPower() == "Water") && (s.getPower() == "Fire")){
        return true;
    }
    else{
        return false;
    }
}