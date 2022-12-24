/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/

void permute_filters(int pos, std::vector<int> filter){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors
		return;
	}

	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new);
	permute_filters(pos+1, filter);
}

//Driver function, feel free to modify to pass more arguments
void permute_filters(){
		permute_filters(0, std::vector<int>());
}
