#include <iostream>
#include <string>
#ifndef _SUPER_
#define _SUPER_
class Superhero{
    public:
    Superhero(std::string n, std::string i, std::string p);
    const std::string& getTrueIdentity() const {return identity;}
    const std::string& getName() const {return name;}
    const std::string& getPower() const {return power;}
    friend std::ostream& operator<< (std::ostream& os, Superhero& s);

    bool isGood() {return hero;}
    void changeHero(){hero = (!hero);}

    bool operator==(std::string s);
    bool operator!=(std::string s);
    bool operator>(const Superhero& s);
    Superhero& operator-();

    private:
    bool hero = true;
    std::string name;
    std::string power;   
    std::string identity;

};
#endif
