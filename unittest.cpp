#include "testhead.h"
#include "gtest/gtest.h"

int GetAbsoluteFiles(std::string mdirectory) 
{
    DIR* dir = opendir(mdirectory.c_str()); //打开目录 

    struct dirent* d_ent = NULL;       

    std::vector<std::string> filesAbsolutePath;
    std::string newDirectory =std::string("./input/") + mdirectory; 
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
        }
    }

    return filesAbsolutePath.size();
}

TEST(AdditionTest,test1){
    EXPECT_EQ(8, GetAbsoluteFiles("4A"));
}

TEST(AdditionTest,test2){
    EXPECT_EQ(12, GetAbsoluteFiles("50A"));
}

TEST(AdditionTest,emptytest){
    EXPECT_EQ(0, GetAbsoluteFiles("empty"));
}

TEST(AdditionTest,inexisttest){
    EXPECT_EQ(-1, GetAbsoluteFiles("inexist"));
}

int str_to_num(std::string str)
{
    int num = 0;
    for (int i = 0; i < str.size(); i++)
    {
        num = num * 10 + str[i] - '0';
    }
    return num;
}

std::vector<std::string> dealwithinput(std::string filename, std::string homedirectory){
srand((unsigned int)time(NULL));
    fstream fp2;
    ifstream fp1;
    std::string str;
    fp1.open(filename.c_str());
    int i = 0, j = 0, flag1 = 0;
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
            }else if (flag1 == 0){//meet ' ''('')'for the first time
                flag1 = 1;
                input.push_back(s);//push into vector
                s = "";//clean the string
            }else{
                s = "";
            }
        }
        else{
            flag1 = 0;
            s += buff[j];
        }
        j++;
    }
    //dealwithinput(input, homedirectory);
    std::string newfilename = homedirectory + std::string("/randominput.txt");
    int flag = 0;
    std::string inputstr;
    std::vector<std::string> resstring;
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
            resstring.push_back(to_string(randnum));
        }else if(strcmp(input[i].c_str(), "char") == 0)                                      
        {
            std::string temp1 = input[++i];
            std::string temp2 = input[++i];
            char a, b;
            a = temp1[0];
            b = temp2[0];
            char randchar = a + rand() % (b - a);
	    resstring.push_back(string(1,randchar));
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
            resstring.push_back(randchar);
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
    return resstring;
}


TEST(AdditionTest,twoValues){
for (int index = 0; index < 10; index++){
    std::vector<std::string> randinput = dealwithinput("./input/50A/stdin_format.txt", "./input/50A");
    for (int i = 0; i < randinput.size(); i++)
    {
        cout << randinput[i] << " ";
    }
    cout << endl;
    vector<int> arr;
    char arr1[10];

    arr.push_back(str_to_num(randinput[0]));
    arr.push_back(str_to_num(randinput[1]));
    arr.push_back(randinput[2][0] + 97 - 'a');
    EXPECT_EQ(1, randinput[2].size());
    ASSERT_GE(arr[0], 0);
    ASSERT_LE(arr[0], 16);
    ASSERT_GE(arr[1], 100);
    ASSERT_LE(arr[1], 2147483647);
    ASSERT_GE(arr[2], 102);
    ASSERT_LE(arr[2], 109);
    ASSERT_GE(randinput[3].size(), 2);
    ASSERT_LE(randinput[3].size(), 10);
}
}



int dealwithpairs(std::string file1, std::string file2)  //run oj by system("g++ file.cpp -o a.out")
{
    ifstream op1, op2;
    op1.open(file1);
    if(!op1){
        cout << "have no access to " << file1;
        return -1;
    }
    op1.close();
    op2.open(file2);
    if(!op2){
        cout << "have no access to " << file2;
        return -1;
    }
    op2.close();
    std::string directory =std::string("randominput.txt");
    std::string cmd1 = std::string("g++ ") + file1 + std::string(" -o a.out");
    std::string cmd2 = std::string("g++ ") + file2 + std::string(" -o b.out");
    std::string cmd3 = std::string("./a.out <") + directory + std::string("> res1.txt");
    std::string cmd4 = std::string("./b.out <") + directory + std::string("> res2.txt");
    system(cmd1.c_str());
    system(cmd2.c_str());                                                         
    system(cmd3.c_str());
    system(cmd4.c_str()); 
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
        return 1;
    }
    else{
        return 0;
    }
}
TEST(AdditionTest,exec){
    int exec_res[10] = {0};
    exec_res[0] = dealwithpairs("test_1.cpp", "test_2.cpp");
    exec_res[1] = dealwithpairs("test_1.cpp", "test_3.cpp");
    exec_res[2] = dealwithpairs("test_2.cpp", "test_4.cpp");
    exec_res[3] = dealwithpairs("test_5.cpp", "test_7.cpp");
    EXPECT_EQ(1, exec_res[0]); //equal   (int
    EXPECT_EQ(2, exec_res[1]); //inequal
    EXPECT_EQ(-1, exec_res[2]);//cannot open file
    EXPECT_EQ(1, exec_res[3]);//equal   (char,string
}

for (int index = 0; index < 10; index++){
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
