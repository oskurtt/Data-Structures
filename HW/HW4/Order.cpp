#include <iostream>
#include <string>
#include "Order.h"
//constructor to old id, promised cooking time, and list of ordered items
Order::Order(const int id_, int promised_time_, const std::list<std::string> order_items_){
    id = id_;
    promised_time = promised_time_;
    order_items = order_items_;
}
//returns id
int Order::getId() const {
    return id;
}
//returns promised time
int Order::getPromised_time(){
    return promised_time;
}
//returns list of ordered items
std::list<std::string> Order::getItems() const {
    return order_items;
}
//changes the time accordingly
void Order::change_promised_time(int t){
  promised_time -= t;
}
//sorts the order by its time and ID if necessary
bool sort_by_time (Order &order1, Order &order2){
  if (order1.getPromised_time() < order2.getPromised_time()){
    return true;
  }
  else if (order1.getPromised_time() > order2.getPromised_time()){
    return false;
  }
  else{
      if (order1.getId() < order2.getId()){
          return true;
      }
      else{
          return false;
      }
  }
}
//sorts order only by its ID
bool sort_by_id (Order &order1, Order &order2){
  if (order1.getId() < order2.getId()){
    return true;
  }
  else{
      return false;
  }
}
