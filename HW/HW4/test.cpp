#include <iostream>
#include <vector>


int main(){
   int elem[4] = {1,2,3,4};
   for (int i = 0; i<(sizeof(elem)/sizeof(elem[0])); i++){
      std::cout<<elem[3]<<std::endl;
   }

}