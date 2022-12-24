#include <iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iomanip>
//create class
class Course{
    public:
    Course();
    Course(std::string crn,
                std::string dCode,
                std::string cCode,
                std::string title,
                std::string day,
                std::string start,
                std::string end,
                std::string room);

//functions to return variables
    std::string getRoom() const;
    std::string getDay() const;
    std::string getStart() const;
    std::string getcCode() const;
    std::string getdCode() const;
    std::string getTitle() const;
    std::string getCrn() const;
    //functions to print
    void printClasses (std::ofstream& outfile ,int spaceT, int spaceD) const;
    void printDept(std::ofstream& outfile, int spaceT, int spaceD) const;
    
    private:
    std::string crn;
    std::string dCode;
    std::string cCode;
    std::string title;
    std::string day;
    std::string start;
    std::string end;
    std::string room;


};
//sort functions
bool sortRoom(const Course& c1, const Course& c2);
bool sortDept(const Course& c1, const Course& c2);
