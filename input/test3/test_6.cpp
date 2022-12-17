#include<iostream>
#include <string>
int main(){
	char a,b;
	std::string str;
	std::cin >> str >> a >> b;
	str += std::to_string(a) + std::to_string(b);
	std::cout<<str;
}
