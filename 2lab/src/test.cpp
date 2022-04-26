#include <iostream>
#include <fstream>
int main(){
	std::string a = "abc";
	std::ofstream out(a, std::ofstream::binary | std::ofstream::app);
	if (!out){
		std::cout << "Not OK" << std::endl;
	} else{
		std::cout << "OK" << std::endl;
	}
	return 0;
}
