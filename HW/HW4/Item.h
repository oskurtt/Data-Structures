#include <iostream>
#include <string>

class Item{
    //public functions
    public:
        Item (const std::string itemName_, int cooking_time_);
        std::string getName() const;
        int getCooking_time();
        void change_cooking_time(int t);
    //private functions
    private:
        std::string itemName;
        int cooking_time;
};
//sort functions
bool sort_by_cooking_time (Item &item1, Item &item2);

