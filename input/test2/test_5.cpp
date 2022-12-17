#include<iostream>
int main(){
	char a,b;
	std::string instr;
	std::cin >> a >> b >> instr;
	std::string str = "";
	str += a;
	str += b;
	str += instr;
	std::cout<<str;
}
