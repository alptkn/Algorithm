#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include <sstream>
#include <queue>
#include <tuple>
#include <bits/stdc++.h>

using namespace std;

bool sortinrev(const pair<int, int> &a, const pair<int, int> &b) {
    return (a.first > b.first);
}


struct testSuite{
    string name;
    int number_of_bugs;
    int exec_time;
    vector<vector<int>> test_cases;
    vector<int> statement_coverage;
};

class optimalTestCases{
    vector<testSuite> test_suites;
    vector<int> answers;
    vector<int> number_of_test_case;
    int distance;
    int number_of_test_suites;
    int max_exec_time;
    int temp_coverage;
    int orderOptimalTestSuitesRecursion(vector<testSuite> test_suites, int index, int max_exec_time, vector<vector<int>> dp);
    int orderOptimalTestSuites(vector<testSuite> test_suites, int index, int max_exec_time );
    int min_2(int x, int y, int z);
    void copyVector(vector<int> &src, vector<int> &dst, int index);
    int editDist(vector<int> num1, vector<int> num2);
    int max_coverage_index(int index);
public:
    void number(string name);
    void readFromFile(string name);
    void orderTestSuites();
};
//It returens the test cases that has mazimum coverage 
//statement_coverage holds the number of zeros in each test cases, for that reason, it finds the minimum 
int optimalTestCases::max_coverage_index(int index) {
    int min = 999999999, min_index;
    for(int i = 0; i < test_suites[index].statement_coverage.size(); i++ ){
        if(test_suites[index].statement_coverage[i] < min){
            min = test_suites[index].statement_coverage[i];
            min_index = i;
        }
    }
    temp_coverage = min;
    return min_index;
}
void optimalTestCases::copyVector(vector<int> &src, vector<int> &dst, int index) {
    for(int i = 0; i < src.size(); i++)
        dst[i] = src[i];
}
int optimalTestCases::min_2(int x, int y, int z) {
    if(x <= y && x <= z)
        return x;
    if(y <= x && y <= z)
        return y;
    if(z <= y && z <= x)
        return z;
}
int optimalTestCases::orderOptimalTestSuitesRecursion(vector<testSuite> test_suites, int index, int max_exec_time, vector<vector<int>> dp) {
    int take = 0, not_take = 0;
    if(index < 0 )
        return 0;
    if(dp[index][max_exec_time] != -1)
        return dp[index][max_exec_time];
    if(test_suites[index].exec_time > max_exec_time){
        dp[index][max_exec_time] = orderOptimalTestSuitesRecursion(test_suites, index - 1, max_exec_time, dp);
        return dp[index][max_exec_time];
    }
    else{
        take = test_suites[index].number_of_bugs + orderOptimalTestSuitesRecursion(test_suites, index - 1, max_exec_time - test_suites[index].exec_time, dp);
        vector<int> temp(number_of_test_suites);
        copyVector(answers, temp, index);
        not_take = orderOptimalTestSuitesRecursion(test_suites, index - 1, max_exec_time, dp);
        if(take > not_take){
            dp[index][max_exec_time] = take;
            copyVector(temp, answers, index);
            answers[index] = 1;                //if the test suites n in the optimal subset, answer[n-1] = 1
            return dp[index][max_exec_time];
        }
        else{
            dp[index][max_exec_time] = not_take;
            answers[index] = 0;
            return dp[index][max_exec_time];
        }
    }
}
int optimalTestCases::orderOptimalTestSuites(vector<testSuite> test_suites, int index, int max_exec_time) {
    vector<vector<int>> dp;
    dp.resize(number_of_test_suites);
    for(int i = 0; i < index; i++)
        dp[i].resize(max_exec_time + 1);
    for(int i = 0; i < index; i++)
        for(int j = 0; j < max_exec_time + 1; j++)
            dp[i][j] = -1;

    return orderOptimalTestSuitesRecursion(test_suites, index - 1, max_exec_time, dp);
}
int optimalTestCases::editDist(vector<int> num1, vector<int> num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    vector<vector<int>> DP(2, vector<int>(len1 + 1,0));
    for(int i = 0; i<= len1; i++)
        DP[0][i] = i;
    for(int i = 1; i <= len2; i++){
        for(int j = 0; j <= len1; j++){
            if(j == 0)
                DP[i % 2][j] = i;
            else if(num1[j - 1] == num2[i - 1])
                DP[i % 2][j] = DP[(i - 1) % 2][j - 1];
            else
                DP[i % 2][j] = 1 + min_2(DP[(i - 1) % 2][j],
                                         DP[i % 2][j - 1],
                                         DP[(i - 1) % 2][j - 1]);
        }
    }
    distance =  DP[len2 % 2][len1];
}
//It counts number of test suites and number of test cases in each test suite 
void optimalTestCases::number(string file_name) {
    string line;
    int count = 0, count_2 = 0;
    fstream myfile(file_name, ios::in);
    if(myfile.is_open()){
        while(!myfile.eof()){
            getline(myfile, line);
            count++;
            if(count > 3){
                for(int i = 0; i < line.length(); i++){
                    if(line[i] == ' '){
                        count_2++;
                    }

                }
                number_of_test_case.push_back(count_2 - 2);
                count_2 = 0;
            }
        }
        myfile.close();
    }
    number_of_test_suites =  count - 4;
}
//Performs reading operation from file 
void optimalTestCases::readFromFile(string file_name) {
    number(file_name);
    answers.resize(number_of_test_suites);
    test_suites.resize(number_of_test_suites);
    for(int m = 0; m < test_suites.size(); m++)
        test_suites[m].test_cases.resize(number_of_test_case[m]);
    int a, b, c, i = 0,j = 0, count = 0, order = 0;
    char d;
    string name, buf;
    vector<pair<int,int>> temp_int;

    fstream myfile(file_name, ios::in);
    myfile.seekg(26, ios::beg);
    myfile >> a;
    max_exec_time = a;
    myfile >> buf;
    myfile >> buf;
    myfile >> buf;
    myfile >> buf;
    while(myfile >> name){
        myfile >> skipws >> b;
        myfile >> skipws >> c;
        test_suites[i].name = name;
        test_suites[i].number_of_bugs = b;
        test_suites[i].exec_time = c;

        myfile >> d;
        while(d != '\n'){
            if(d != '-' && d != ' '){
                temp_int.push_back(make_pair(d - '0', j + 1));
                if(d - '0' == 0)
                    count++;
                j++;
            }
            else if(d == ' '){
                test_suites[i].statement_coverage.push_back(count);
                count = 0;
                j = 0;
                sort(temp_int.begin(), temp_int.end());
                    for(int m = 0; m < temp_int.size(); m++)
                        test_suites[i].test_cases[order].push_back(temp_int[m].second);
                temp_int.clear();
                order++;
            }
            myfile >> noskipws >> d;
        }
        test_suites[i].statement_coverage.push_back(count);
        count = 0;
        j = 0;
        sort(temp_int.begin(), temp_int.end());
        for(int m = 0; m < temp_int.size(); m++)
            test_suites[i].test_cases[order].push_back(temp_int[m].second);
        temp_int.clear();
        order = 0;
        i++;
    }
}
//It finds optimal subset of test suites and arrange the order of the test cases in each test suit in optimal subset 
void optimalTestCases::orderTestSuites() {
    int p = orderOptimalTestSuites(test_suites, test_suites.size(), max_exec_time);
    queue<int> indexes;
    vector<pair<int,int>> differences;
    vector<int> temp_1, temp_2;
    int index, first;
    for(int m = 0; m < answers.size(); m++){
        if(answers[m] == 1)
            indexes.push(m);              //pushing the optimal test suites the queue 
    }
    while(!indexes.empty()){
        index = indexes.front();
        indexes.pop();
        first = max_coverage_index(index);               //find the index of test cases that has max coverage 
        temp_1 = test_suites[index].test_cases[first];
        cout << test_suites[index].name << " " << first + 1 << " ";
        if(test_suites[index].statement_coverage.size() > 1){
            for(int i = 0; i < test_suites[index].test_cases.size(); i++){
                temp_2 = test_suites[index].test_cases[i];
                if(i != first && test_suites[index].statement_coverage[i] != temp_coverage){
                    int k = editDist(temp_1, temp_2);
                    differences.push_back(make_pair(distance , i + 1));           //stores levensthein distance and id of test cases 
                }
                else if(i != first && test_suites[index].statement_coverage[i] == temp_coverage )
                    cout << i+1 << " ";
            }
        }
        sort(differences.begin(), differences.end(), sortinrev);  //sorts differences in descending order )
        for(int m = 0; m < differences.size(); m++)
            cout <<differences[m].second << " ";
        cout << endl;
        differences.clear();
    }
}



int main(int argc, char **argv){
    optimalTestCases test;
    test.readFromFile(argv[1]);
    test.orderTestSuites();

}