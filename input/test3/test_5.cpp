#include<iostream>
int main(){
	char a,b;
	std::string instr;
	std::cin >> instr >> a >> b;
	std::string str = "";
	str += a;
	str += b;
	str += instr;
	std::cout<<str;
}
