#include <iostream>
#include <string>
#include "Item.h"
//constructor to old item name and its cooking time
Item::Item (const std::string itemName_, int cooking_time_){
    itemName = itemName_;
    cooking_time = cooking_time_;
}
//returns item name
std::string Item::getName() const{
    return itemName;
}
//returns cooking time
int Item::getCooking_time(){
    return cooking_time;
}
//changes cooking time
void Item::change_cooking_time(int t){
  cooking_time -= t;
}
//sort Items by its cooking time and then its name
bool sort_by_cooking_time (Item &item1, Item &item2){
  if (item1.getCooking_time() < item2.getCooking_time()){
    return true;
  }
  else if (item1.getCooking_time() > item2.getCooking_time()){
    return false;
  }
  else{
      if (item1.getName() < item2.getName()){
          return true;
      }
      else{
          return false;
      }
  }
}