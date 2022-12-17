#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <fstream>
#include <random>
//#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <time.h>
#define MaxSize 100000
using namespace std;
//#include <unistd.h>
struct Eqminer
{   
    std::string homedirectory;
    std::string file1;
    std::string file2;
    int result;
};

std::vector<std::string> equalpairs;
std::vector<std::string> inequalpairs;

int GetAbsoluteFiles(const std::string& mdirectory);//main

void readinput(std::string& filename, std::string& homedirectory);               //create random input
void dealwithinput(std::vector<std::string>& input, std::string& homedirectory);


void execute(std::vector<std::string>& subfiles, std::string& homedirectory);//run oj pairs
void dealwithpairs(Eqminer *onepair);


void compare(Eqminer *onepair);                 //compare results and record
void writeinchart(Eqminer *onepair, int i);
