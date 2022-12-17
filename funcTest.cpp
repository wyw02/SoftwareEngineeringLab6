#include "testhead.h"
#include "gtest/gtest.h"



//std::vector<std::string> equalpairs;
//std::vector<std::string> inequalpairs;


int str_to_num(std::string str)
{
    int num = 0;
    for (int i = 0; i < str.size(); i++)
    {
        num = num * 10 + str[i] - '0';
    }
    return num;
}

int GetAbsoluteFiles(std::string& mdirectory) 
{
   
    std::string newDirectory =std::string("./input/") + mdirectory; 
    DIR* subdir = opendir(newDirectory.c_str());
    if ( subdir == NULL )
    {
        return -1;
    }
    struct dirent* subd_ent = NULL; 
    std::vector<std::string> filesAbsolutePath;
    while((subd_ent = readdir(subdir))!= NULL)
    {
        if ( subd_ent->d_type != DT_DIR ){
            std::string newsubDirectory = newDirectory + std::string("/") + std::string(subd_ent->d_name);
            if(strcmp(subd_ent->d_name, "stdin_format.txt") != 0 && strcmp(subd_ent->d_name, "randominput.txt")!= 0)
            {                            
                filesAbsolutePath.push_back(newsubDirectory);
            }
            else if(strcmp(subd_ent->d_name, "stdin_format.txt") == 0 ) // create random input and write into file
            {
                readinput(newsubDirectory, newDirectory);
            }
            
        }
    }
    execute(filesAbsolutePath, newDirectory);
    /*
    while ( (d_ent = readdir(dir)) != NULL )    //读目录
    { 
        if ( (strcmp(d_ent->d_name, dot) != 0)
              && (strcmp(d_ent->d_name, dotdot) != 0) )  {

            if ( d_ent->d_type == DT_DIR ) //是目录
            {
                std::vector<std::string> filesAbsolutePath;
                std::string newDirectory = mdirectory + std::string("/") + std::string(d_ent->d_name); 
                DIR* subdir = opendir(newDirectory.c_str());
                if ( subdir == NULL )
                {
                    return -1;
                }
                struct dirent* subd_ent = NULL; 
                while((subd_ent = readdir(subdir))!= NULL)
                {
                    if ( subd_ent->d_type != DT_DIR ){
                        std::string newsubDirectory = newDirectory + std::string("/") + std::string(subd_ent->d_name);
                        if(strcmp(subd_ent->d_name, "stdin_format.txt") != 0 && strcmp(subd_ent->d_name, "randominput.txt")!= 0)
                        {                            
                            filesAbsolutePath.push_back(newsubDirectory);
                        }
                        else if(strcmp(subd_ent->d_name, "stdin_format.txt") == 0 ) // create random input and write into file
                        {
                            readinput(newsubDirectory, newDirectory);
                        }
                    
                    }
                }
                execute(filesAbsolutePath, newDirectory);
            }
        }
    }
    */
    
    return 0;
}




std::pair<std::vector<std::string>,std::vector<std::string>> searesult(std::string subdirectory)
{
    
    system("rm -f /home/njucs/Eqminer/output/*"); //clear the output files from last test
	GetAbsoluteFiles(subdirectory);
    return make_pair(equalpairs, inequalpairs);
}


void execute(std::vector<std::string>& subfiles, std::string& homedirectory)
{
    int count = 0;
    for (int i = 0; i < subfiles.size(); i++)
    {
        for (int j = i+1; j < subfiles.size(); j++)//traverse all pairs  C(n,2)
        {
            Eqminer *one = new Eqminer;
            one->file1 = subfiles[i];
            one->file2 = subfiles[j];
            one->homedirectory = homedirectory;
            dealwithpairs(one);
        }
    }
}

void dealwithpairs(Eqminer *onepair)  //run oj by system("g++ file.cpp -o a.out")
{
    std::string file1 = onepair->file1;
    std::string file2 = onepair->file2;
    std::string directory = onepair->homedirectory + std::string("/randominput.txt");
    std::string cmd1 = std::string("g++ ") + file1 + std::string(" -o a.out");
    std::string cmd2 = std::string("g++ ") + file2 + std::string(" -o b.out");
    std::string cmd3 = std::string("./a.out <") + directory + std::string("> res1.txt");
    std::string cmd4 = std::string("./b.out <") + directory + std::string("> res2.txt");
    system(cmd1.c_str());
    system(cmd2.c_str());                                                         
    system(cmd3.c_str());
    system(cmd4.c_str()); 
    compare(onepair);
}



void readinput(std::string& filename, std::string& homedirectory){
    ifstream fp1;
    std::string str;
    fp1.open(filename.c_str());
    int i = 0, j = 0, flag = 0;
    std::vector<std::string> input;
    while(!fp1.eof())
        str += fp1.get();
    const char *buff = str.c_str();
    std::string s;
    while(buff[j] != '\0')
    {
        if (j == 0 || buff[j] == ' '||buff[j] == '('||buff[j] == ')'||buff[j] == ',')//((strcmp(buff[i-1] , ' ') == 0)
        {
            if (j == 0){
                s = "";
                s += buff[j];
            }else if (flag == 0){//meet ' ''('')'for the first time
                flag = 1;
                input.push_back(s);//push into vector
                s = "";//clean the string
            }else{
                s = "";
            }
        }
        else{
            flag = 0;
            s += buff[j];
        }
        j++;
    }
    dealwithinput(input, homedirectory);
    fp1.close();
}
void dealwithinput(std::vector<std::string>& input, std::string& homedirectory){ 
    fstream fp2;
    std::string newfilename = homedirectory + std::string("/randominput.txt");
    int flag = 0;
    std::string inputstr;
    fp2.open(newfilename.c_str(), ios::out);
    srand(time(0));
    for(int i = 0; i < input.size(); i++)
    {
        if (strcmp(input[i].c_str(), "int") == 0)
        {
            std::string temp1 = input[++i];
            std::string temp2 = input[++i];
            int j = 0, left = 0, right = 0;
            while(temp1[j] != '\0'){
                left = left * 10 + temp1[j] - '0';
                j++;
            }
            j = 0;
            while(temp2[j] != '\0'){
                right = right * 10 + temp2[j] - '0';
                j++;
            }
            int randnum = left + rand() % (right - left);
            if (flag == 0){
                flag = 1;
            }
            else{
                inputstr.append(" ");
            }
            inputstr.append(to_string(randnum));
        }else if(strcmp(input[i].c_str(), "char") == 0)                                      
        {
            std::string temp1 = input[++i];
            std::string temp2 = input[++i];
            char a, b;
            a = temp1[0];
            b = temp2[0];
            char randchar = a + rand() % (b - a);
            if (flag == 0){
                flag = 1;
            }
            else
            {
                inputstr.append(" ");
            }
            inputstr.append(to_string(randchar));
        }else if(strcmp(input[i].c_str(), "string") == 0)
        {
            std::string temp1 = input[++i];
            std::string temp2 = input[++i];
            int a = 0, b = 0;
            a = str_to_num(temp1);
            b = str_to_num(temp2);
            int length = a + rand()%(b-a);

            //cout << length << endl;
            std::string randchar = "";
            for (int j = 0; j < length; j++){
	        int type = rand() % 2;
                char onechar = (char)(97 - 32 * type + rand() % 26);
                 //random charactor among A to z
                randchar += onechar;
            }
            if (flag == 0){
                flag = 1;
            }
            else
            {
                inputstr.append(" ");
            }
            inputstr.append(randchar);
            
        }
    }
    fp2 << inputstr;
    fp2.close();
}

void compare(Eqminer *onepair){
    ifstream op;
    std::string str1,str2;
    std::string path1 = std::string("./res1.txt");
    std::string path2 = std::string("./res2.txt");
    op.open(path1);
    while(!op.eof())
        str1+=op.get();
    op.close();
    op.open(path2);
    while(!op.eof())
        str2+=op.get();
    op.close();

    if(str1==str2){
        writeinchart(onepair, 1);
    }
    else{
        writeinchart(onepair, 0);
    }
    return;
}

void writeinchart(Eqminer *onepair, int i)
{
    std::string file1 = onepair->file1.substr(2, onepair->file1.size()-2);
    std::string file2 = onepair->file2.substr(2, onepair->file2.size()-2);
    std::string records = file1 + "," + file2;
    if (i == 1){
        equalpairs.push_back(records);
        ofstream outfile;
        outfile.open("./output/equal.csv",ios::app);
        outfile << file1 << "," << file2 << endl;

    }
    else
    {
        inequalpairs.push_back(records);
        ofstream outfile;
        outfile.open("./output/inequal.csv",ios::app);
        outfile << file1 << "," << file2 << endl;
    }
    return;
}
bool findinVector(std::vector<std::string> results, std::string records1, std::string records2){
	for(int i = 0; i < results.size(); i++){
		if(results[i] == records1 || results[i] == records2)
			return true;
	}
	return false;
}

TEST(IntegrationTest0, exec){
	std::pair<std::vector<std::string>,std::vector<std::string>> twovec = searesult("test5");
	EXPECT_EQ(0, twovec.first.size());

}

TEST(IntegrationTest1, exec){
    std::pair<std::vector<std::string>,std::vector<std::string>> twovec = searesult("4A");
    ASSERT_EQ(true, findinVector(twovec.first,"input/4A/84822638.cpp,input/4A/84822639.cpp","input/4A/84822639.cpp,input/4A/84822638.cpp"));
    ASSERT_EQ(true, findinVector(twovec.first,"input/4A/134841308.cpp,input/4A/127473352.cpp","input/4A/127473352.cpp,input/4A/134841308.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/4A/48762087.cpp,input/4A/84822638.cpp","input/4A/84822638.cpp,input/4A/48762087.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/4A/48762087.cpp,input/4A/84822639.cpp","input/4A/84822639.cpp,input/4A/48762087.cpp"));    
}

TEST(IntegrationTest2, exec){
    std::pair<std::vector<std::string>,std::vector<std::string>> twovec = searesult("test1");
    ASSERT_EQ(true, findinVector(twovec.first,"input/test1/test_1.cpp,input/test1/test_2.cpp","input/test1/test_2.cpp,input/test1/test_1.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test1/test_1.cpp,input/test1/test_3.cpp","input/test1/test_3.cpp,input/test1/test_1.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test1/test_2.cpp,input/test1/test_3.cpp","input/test1/test_3.cpp,input/test1/test_2.cpp"));
}

TEST(IntegrationTest3, exec){
    std::pair<std::vector<std::string>,std::vector<std::string>> twovec = searesult("test2");
    ASSERT_EQ(true, findinVector(twovec.first,"input/test2/test_5.cpp,input/test2/test_7.cpp","input/test2/test_7.cpp,input/test2/test_5.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test2/test_5.cpp,input/test2/test_6.cpp","input/test2/test_6.cpp,input/test2/test_5.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test2/test_6.cpp,input/test2/test_7.cpp","input/test2/test_7.cpp,input/test2/test_6.cpp"));
}

TEST(IntegrationTest4, exec){
    std::pair<std::vector<std::string>,std::vector<std::string>> twovec = searesult("test3");
    ASSERT_EQ(true, findinVector(twovec.first,"input/test3/test_5.cpp,input/test3/test_7.cpp","input/test3/test_7.cpp,input/test3/test_5.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test3/test_5.cpp,input/test3/test_6.cpp","input/test3/test_6.cpp,input/test3/test_5.cpp"));
    ASSERT_EQ(false, findinVector(twovec.first,"input/test3/test_6.cpp,input/test3/test_7.cpp","input/test3/test_7.cpp,input/test3/test_6.cpp"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
