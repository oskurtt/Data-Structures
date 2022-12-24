#include <iostream>
int recursion(int x, int y){
    if (x==0 && y==0){
        return 1;
    }
    else if (x == 0 ){
        return recursion(x, y-1);
    }
    else if (y == 0 ){
        return recursion(x-1,y);
    }
    else{
        return recursion(x-1,y)+recursion(x, y-1);
    }
}
int main(){
    std::cout<<recursion(2,2)<<std::endl;
}