#include <iostream>
#include <string>
#include <list>
class Order{
    //public functions
    public:
        Order(const int id_, int promised_time_, const std::list<std::string> order_items_);
        int getId() const;
        int getPromised_time();
        void change_promised_time(int t);
        std::list<std::string> getItems() const;
    //private functions
    private:
        int id;
        int promised_time;
        std::list <std::string> order_items;
};
//sort functions
bool sort_by_time (Order &order1, Order &order2);
bool sort_by_id (Order &order1, Order &order2);