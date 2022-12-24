// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <algorithm>
#include "Order.h"
#include "Item.h"

typedef std::list<Order> OrderList;
typedef std::list<Item> KitchenList;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);

int main(int argc, char* argv[]) {
  std::ifstream infile(argv[1]); //intialize arguments
  std::ofstream outfile(argv[2]);
  OrderList orders;
  KitchenList food_cooking;
  KitchenList food_completed;

  std::string token;
  while (std::cin >> token) {
    if (token == "add_order") {
      int id, promised_time, n_items = 0;
      std::string next_item;
      std::list <std::string> order_items;

      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);

      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //pushes each order class into a list of orders
      orders.push_back(Order(id, promised_time, order_items));
      //sort the orders list and then print them out
      orders.sort(sort_by_time);
      std::cout<<"Received new order #"<<id<<" due in "<<promised_time<<" minute(s):"<<std::endl;
      for (std::list<std::string>::iterator itr = order_items.begin(); itr != order_items.end(); ++itr){
          std::cout<<"  "<<*itr<<std::endl;
      }
    } else if (token == "add_item") {
      int cook_time = -1;
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //if there is no cook time, add it to list of completed foods
      if (cook_time ==0){
        food_completed.push_back(Item(name, cook_time));
      }
      //else cook it
      else{
        food_cooking.push_back(Item(name, cook_time));
      }
      //sort the food cooking list by its cooking time and print out what you're cooking
      food_cooking.sort(sort_by_cooking_time);
      std::cout<<"Cooking new "<<name<<" with "<<cook_time<<" minute(s) left."<<std::endl;
    } else if (token == "print_orders_by_time") {
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //sort orders by time first
      orders.sort(sort_by_time);
      std::cout<<"Printing "<<orders.size()<<" order(s) by promised time remaining:"<<std::endl;
      //loop through orders list and print out each order
      for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i){
        std::cout<<"  #"<<(*i).getId()<<" ("<<(*i).getPromised_time()<<" minute(s) left):"<<std::endl;
        std::list<std::string> x = (*i).getItems();
        for (std::list<std::string>::iterator j = x.begin(); j != x.end();++j){
          std::cout<<"    "<<*j<<std::endl;
        }
      }

    } else if (token == "print_orders_by_id") {
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //sort orders by ID first
      orders.sort(sort_by_id);
      std::cout<<"Printing "<<orders.size()<<" order(s) by ID:"<<std::endl;
      //loop through orders list and print out each order
      for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i){
        std::cout<<"  #"<<(*i).getId()<<" ("<<(*i).getPromised_time()<<" minute(s) left):"<<std::endl;
        std::list<std::string> x = (*i).getItems();
        for (std::list<std::string>::iterator j = x.begin(); j != x.end();j++){
          std::cout<<"    "<<*j<<std::endl;
        }
      }

    } else if (token == "print_kitchen_is_cooking") {
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //loop throught kitchen cooking and print out its contents
      std::cout<<"Printing "<<food_cooking.size()<<" items being cooked:"<<std::endl;
      for (std::list<Item>::iterator i = food_cooking.begin(); i != food_cooking.end(); ++i){
        std::cout<<"  "<<(*i).getName()<<" ("<<(*i).getCooking_time()<<" minute(s) left)"<<std::endl;
      }
    } else if (token == "print_kitchen_has_completed") {
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //loop throught kitchen completed and print out its contents
      std::cout<<"Printing "<<food_completed.size()<<" completely cooked items:"<<std::endl;
      for (std::list<Item>::iterator i = food_completed.begin(); i != food_completed.end(); ++i){
        std::cout<<"  "<<(*i).getName()<<std::endl;
      }
    } else if (token == "run_for_time") {
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //first sort orders and cooking by its time
      orders.sort(sort_by_time);
      food_cooking.sort(sort_by_cooking_time);
      std::cout<<"===Starting run of "<<run_time<<" minute(s)==="<<std::endl;
      //loop through each individual minute of the run time and determine if there're any events you can do fullfill in that time
        for (int ctime = 0; ctime <= run_time; ++ctime){
          //iterate through the food cooking list to see if any items can finish cooking
          for (std::list<Item>::iterator i = food_cooking.begin(); i != food_cooking.end(); ++i){
            if ((*i).getCooking_time() == ctime){
                std::cout<<"Finished cooking "<<(*i).getName()<<std::endl;
                food_completed.push_back(*i);
                i = food_cooking.erase(i);
                --i;
            }
          }
        //iterate through the orders and check if that order can be fullfilled in the current time
        for (std::list<Order>::iterator j = orders.begin(); j != orders.end(); ++j){
          //if the proimsed time of the order is equal to our current time, we check if it can be fullfilled
          if ((*j).getPromised_time()==ctime){
            KitchenList kitchen_completed;
            OrderFillList items_to_remove;
            if (CanFillOrder(*j, food_completed, items_to_remove)){
              std::cout<<"Filled order #"<<(*j).getId()<<std::endl;
              j = orders.erase(j);
              j--;
              //loop throught items that we need to remove and remove it from the food completed list
              for (OrderFillList::const_iterator k = items_to_remove.begin(); k != items_to_remove.end(); ++k){
                food_completed.erase(*k);
                std::cout<<"Removed a "<<(**k).getName()<<" from completed items."<<std::endl;
              }
            }
            //if not fullfilled, make it expire
            else{
              std::cout<<"Order # "<<(*j).getId()<<" expired."<<std::endl;
              j = orders.erase(j);
              j--;
            }
          }
          //if the promised time is more than the amount of time we ran, we can still check if we can fullfill that order
          //however, you don't have to remove it since there is still time remaining to fullfill that order
          else{
            KitchenList kitchen_completed;
            OrderFillList items_to_remove;
            if (CanFillOrder(*j, food_completed, items_to_remove)){
              std::cout<<"Filled order #"<<(*j).getId()<<std::endl;
              j = orders.erase(j);
              j--;
              for (OrderFillList::const_iterator k = items_to_remove.begin(); k != items_to_remove.end(); ++k){
                std::cout<<"Removed a "<<(**k).getName()<<" from completed items."<<std::endl;
                food_completed.erase(*k);
              }
            }
          }
        }
      }
      std::cout<<"===Run for specified time is complete==="<<std::endl;
      //decrement the promised cooking time and cooking time 
      for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i){
        (*i).change_promised_time(run_time);
      }
      for (std::list<Item>::iterator i = food_cooking.begin(); i != food_cooking.end(); ++i){
        (*i).change_cooking_time(run_time);
      }
    } else if (token == "run_until_next") {
      std::cout << "Running until next event." << std::endl;
      /* YOU MUST FINISH THIS IMPLEMENTATION */
      //run condition if there is no food cooking
      if (food_cooking.size() == 0){
        if (orders.size() == 0){
          std::cout<<"No events waiting to process."<<std::endl;
        }
        else if (orders.size() > 0){
          for (std::list<Order>::iterator O = orders.begin(); O != orders.end(); O++){
            std::cout<<"Order # "<<(*O).getId()<<" expired."<<std::endl;
            std::cout<<(*O).getPromised_time()<<" minute(s) have passed."<<std::endl;
            O = orders.erase(O);
          }
        }
      }
      //else run a while loop and break out of the while loop if an event has happened
      else{
        bool b = true;
        int ctime = 0;
        while (b){
          //iterate through food cooking and check if it has finished cooking
          for (std::list<Item>::iterator i = food_cooking.begin(); i != food_cooking.end(); ++i){
            if ((*i).getCooking_time() == ctime){
              std::cout<<"Finished cooking "<<(*i).getName()<<std::endl;
              food_completed.push_back(*i);
              i = food_cooking.erase(i);
              --i;
              std::cout<<ctime<<" minute(s) have passed."<<std::endl;
              b = false;
              for (std::list<Order>::iterator i = orders.begin(); i != orders.end(); ++i){
                (*i).change_promised_time(ctime);
              }
              for (std::list<Item>::iterator i = food_cooking.begin(); i != food_cooking.end(); ++i){
                (*i).change_cooking_time(ctime);
              }
              break;
            }
          }
          //if there are no foods finished cooking, check if any orders can be fullfilled
          for (std::list<Order>::iterator j = orders.begin(); j != orders.end(); ++j){
            KitchenList kitchen_completed;
            OrderFillList items_to_remove;
            if (CanFillOrder(*j, food_completed, items_to_remove)){
              for (OrderFillList::const_iterator k = items_to_remove.begin(); k != items_to_remove.end(); ++k){
                std::cout<<"Filled order #"<<(*j).getId()<<std::endl;
                j = orders.erase(j);
                j--;
                std::cout<<"Removed a "<<(**k).getName()<<" from completed items."<<std::endl;
                food_completed.erase(*k);
                std::cout<<ctime<<"  minute(s) have passed."<<std::endl;
                b = false;
                break;
              }
            }
          }
          ++ctime;
        }
      }
    }
  }

  return 0;
}

bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

