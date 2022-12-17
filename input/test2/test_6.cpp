#include<iostream>
#include <string>
int main(){
	char a,b;
	std::cin >> a >> b;
	std::string str = std::to_string(a) + std::to_string(b);
	std::cout<<str;
}
