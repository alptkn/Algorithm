#include <iostream>
#include<vector>
#include <fstream>
#include<limits>
#include <climits>

using namespace std;

struct Node {
    int value;
    int dist;
};

class HW_2{
    vector<vector<int>> adjMatrix;
    vector<pair<int, int>> path_Joseph;
    vector<pair<int, int>> path_Joseph_return;
    vector<pair<int, int>> path_Lucy;
    vector<pair<int, int>> path_Lucy_return;
    int JH, JD, LH, LD, number_of_nodes, JD_duration, LD_duration;
    bool isPrint = true;
    int minDistance(vector<int> dist, vector<bool> sptSet );
    void duration();
    int count_time(int src, int dst);
    int temp;
    bool isPath;
public:
    void createAdjMatrix(string filename);
    void shortestPath(bool var, bool var2);
    void printPath(vector<int> dist, vector<int> parent, int dst, bool choose, bool var);
    void print();
    void fixIntersection(bool choose_path);
    bool getPrint();
};
bool HW_2::getPrint() {
    return isPrint;
}
// This methods perform reading operation from file and creates adjacecy matrix 
void HW_2::createAdjMatrix(string filename) {
    int src, dst, weight;
    ifstream fin;
    fin.open(filename,ios::in);
    fin >> number_of_nodes;
    vector< vector<int> > temp(number_of_nodes, vector<int> (number_of_nodes, 0));
    fin >> JH;
    fin >> JD;
    fin >> LH;
    fin >> LD;
    while(!fin.eof()){
        fin >> src;
        fin >> dst;
        fin >> weight;
        temp[src][dst] = weight;
    }
    adjMatrix = temp;
}
// Find the minimum value in the dist vector, next node in the Dijkstra
int HW_2::minDistance(vector<int> dist, vector<bool> sptSet) {
    int min = INT_MAX, min_index;
    for(int i = 0; i < number_of_nodes; i++){
        if(sptSet[i] == false && dist[i] <= min){
            min = dist[i],
            min_index = i;
        }
    }
    if(min != INT_MAX)
        return min_index;
    else
        return -1;
}
// It counts cost of the path 
int HW_2::count_time(int src, int dst) {
    vector<int> dest(number_of_nodes);
    //This vector holds the shortest distance from
    //source to destination
    vector<int> dist(number_of_nodes);
    //vector to check if vertex i is in the
    //shortest path or not
    vector<bool> sptSet(number_of_nodes);
    //vector that stores shortest path tree
    vector<int> parent(number_of_nodes);

    for(int i = 0; i < number_of_nodes; i++){
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for(int i = 0; i < number_of_nodes - 1; i++){

        //find the minimum distance vertex from the
        //vertices that are not covered yet
        int u = minDistance(dist, sptSet);
        if(u >= 0){
            sptSet[u] = true;

            for(int j = 0; j < number_of_nodes; j++){
                //Update dist[v] when it is not in the sptSet
                //there is a edge between u to v
                //src to v through u is smaller than dist[v]
                if(!sptSet[j] && adjMatrix[u][j] && dist[u] + adjMatrix[u][j] < dist[j]){
                    parent[j] = u;
                    dist[j] = dist[u] + adjMatrix[u][j];
                }
            }
        }
    }
    // If the path is not valid, makes isPath false
    if(parent[dst] == -1)
        isPath = false;
    else
        isPath = true;
    return dist[dst];
}
void HW_2::duration() {
    for(int i = 0; i < path_Joseph.size(); i++){
        if(path_Joseph[i].first == JD){
            JD_duration = path_Joseph[i].second;
        }
    }
    for(int i = 0; i < path_Lucy.size(); i++){
        if(path_Lucy[i].first == LD){
            LD_duration = path_Lucy[i].second;
        }
    }
}
// It finds the path from parent vector,
//Parent vector stores the parent of each node in the path 
void HW_2::printPath(vector<int> dist, vector<int> parent, int dst, bool choose, bool var) {
    if (parent[dst] == -1) {
        if (choose) {
            if (var)
                path_Joseph_return.push_back(make_pair(dst, dist[dst] + 30 + path_Joseph.back().second));
            else
                path_Joseph.push_back(make_pair(dst, dist[dst]));
        } else {
            if (var)
                path_Lucy_return.push_back(make_pair(dst, dist[dst] + 30 + path_Lucy.back().second));
            else
                path_Lucy.push_back(make_pair(dst, dist[dst]));
        }
        return;
    }
    printPath(dist, parent, parent[dst], choose, var);
    if (choose) {
        if (var)
            path_Joseph_return.push_back(make_pair(dst, dist[dst] + 30 + path_Joseph.back().second));
        else
            path_Joseph.push_back(make_pair(dst, dist[dst]));
    } else {
        if (var)
            path_Lucy_return.push_back(make_pair(dst, dist[dst] + 30 + path_Lucy.back().second));
        else
            path_Lucy.push_back(make_pair(dst, dist[dst]));
    }
}
//It finds to minimum cost for src to all nodes in the graph 
void HW_2::shortestPath(bool var, bool var2) {
    int src, dst;
    // Determine which type of path ==> home --> dest or dest --> home
    if(var){
        //Determine whose path Joseph or Lucy 
        if(var2){
            src = JH;
            dst = JD;
        }
        else {
            src = JD;
            dst = JH;
        }
    }
    else{
        if(var2){
            src = LH;
            dst = LD;
        }
        else{
            src = LD;
            dst = LH;
        }
    }
    //This vector holds the shortest distance from
    //source to destination
    vector<int> dist(number_of_nodes);
    //vector to check if vertex i is in the
    //shortest path or not
    vector<bool> sptSet(number_of_nodes);
    //vector that stores shortest path tree
    vector<int> parent(number_of_nodes);

    for(int i = 0; i < number_of_nodes; i++){
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for(int i = 0; i < number_of_nodes - 1; i++){

        //find the minimum distance vertex from the
        //vertices that are not covered yet
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for(int j = 0; j < number_of_nodes; j++){
            //Update dist[v] when it is not in the sptSet
            //check if there is a edge between u to v
            if(!sptSet[j] && adjMatrix[u][j] && dist[u] + adjMatrix[u][j] < dist[j]){
                parent[j] = u;
                dist[j] = dist[u] + adjMatrix[u][j];
            }
        }
    }
    printPath(dist, parent,dst, var, !var2);
}
void HW_2::print() {
    int count_J = path_Joseph_return.back().second;
    int count_L = path_Lucy_return.back().second;
    cout << "Joseph's Path, duration : " << count_J << endl;
    if(!path_Joseph.empty()){
        vector<pair<int, int>>::iterator i;
        for(i = path_Joseph.begin(); i != path_Joseph.end(); i++)
            cout << "Node : " <<  (*i).first << "  Time :  " << (*i).second << endl;

    }
    cout << "--- return ---" << endl;
    if(!path_Joseph_return.empty()){
        vector<pair<int, int>>::iterator i;
        for(i = path_Joseph_return.begin(); i != path_Joseph_return.end(); i++)
            cout << "Node : " <<  (*i).first << "  Time :  " << (*i).second << endl;

    }
    cout << endl;
    cout << "Lucy's Path, duration : " << count_L << endl;
    if(!path_Lucy.empty()){
        vector<pair<int, int>>:: iterator i;
        for(i = path_Lucy.begin(); i != path_Lucy.end(); i++)
            cout << "Node : " <<  (*i).first << "  Time :  " << (*i).second << endl;
    }
    cout << "--- return ---" << endl;
    if(!path_Lucy_return.empty()){
        vector<pair<int, int>>:: iterator i;
        for(i = path_Lucy_return.begin(); i != path_Lucy_return.end(); i++)
            cout << "Node : " <<  (*i).first << "  Time :  " << (*i).second << endl;
    }

}
void HW_2::fixIntersection(bool choose_path) {
    bool flag_1 = false, flag_2;
    bool isPath_L, isPath_J;
    bool flag_J = false,flag_L = false;
    int cost_Joseph, cost_Lucy, temp;
    int duration_J = path_Joseph.back().second, duration_L = path_Lucy.back().second;
    int prev_J, prev_L, index;
    if(choose_path){    //determine which path being investigated for intersection home --> dst or dest --> home 
        while(!flag_1){
            flag_2 = false;
            vector<pair<int, int>>::iterator i;
            for(i = path_Joseph.begin(); i != path_Joseph.end(); i++)
            {
                flag_L = false;
                flag_J = false;
                vector<pair<int,int>>::iterator j;
                for(j = path_Lucy.begin(); j != path_Lucy.end(); j++){
                    if((*i).first == (*j).first){
                        if((*i).first == JD){  // Check if the intersection points belongs to Joseph's destination 
                            if(((*j).second >= duration_J) && ((*j).second <= duration_J + 30)){
                                flag_L = true;
                                flag_2 = true;
                                prev_L = (*--j).first;
                                index = (*++j).first;
                                break;
                            }
                        }
                        else if((*j).first == LD){ // Check if the intersection point belongs to Lucy's destination 
                            if(((*i).second >= duration_L) && ((*i).second <= duration_L + 30)){
                                flag_J = true;
                                flag_2 = true;
                                prev_J = (*--i).first;
                                index = (*++i).first;
                                break;
                            }
                        }
                        else if((*i).second == (*j).second){
                            prev_J = (*--i).first;
                            prev_L = (*--j).first;
                            flag_2 = true;
                            index = (*++i).first;
                            flag_J = flag_L = true;
                            break;
                        }
                    }
                }
                if(flag_2)
                    break;
            }
           if(flag_2){
               if(flag_J && flag_L){  //Intersection point does not belongs to any person's destination points 
                   temp = adjMatrix[prev_J][index];
                   adjMatrix[prev_J][index] = 0;    //Make intersection point 0 
                   cost_Joseph = count_time(JH,JD); //Find the cost when Joseph path is changing 
                   isPath_J = isPath;               //Check if there is path or not 
                   adjMatrix[prev_J][index] = temp;
                   temp = adjMatrix[prev_L][index];
                   adjMatrix[prev_L][index] = 0;
                   cost_Lucy = count_time(LH, LD); //Find the cost when Lucy path is changing 
                   isPath_L = isPath;             //Check if there is path or not 
                   adjMatrix[prev_L][index] = temp;
                   if(isPath_L == false && isPath_J == true ){    //check there is no valid path for Lucy
                       path_Joseph.clear();
                       temp = adjMatrix[prev_J][index];
                       adjMatrix[prev_J][index] = 0;
                       shortestPath(true, true);
                       adjMatrix[prev_J][index] = temp;
                   }
                   else if(isPath_J == false && isPath_L == true){   //chechk there is no valid path Joseph
                       path_Lucy.clear();
                       temp = adjMatrix[prev_L][index];
                       adjMatrix[prev_L][index] = 0;
                       shortestPath(false, true);
                       adjMatrix[prev_L][index] = temp;
                   }
                   else if(isPath_J == true && isPath_L == true){  //Check the cost of the new paths and determine whose path should be changed 
                       if(cost_Joseph <= cost_Lucy ){             
                           path_Joseph.clear();
                           temp = adjMatrix[prev_J][index];
                           adjMatrix[prev_J][index] = 0;
                           shortestPath(true, true);
                           adjMatrix[prev_J][index] = temp;
                       }
                       else if(cost_Lucy <= cost_Joseph){
                           path_Lucy.clear();
                           temp = adjMatrix[prev_L][index];
                           adjMatrix[prev_L][index] = 0;
                           shortestPath(false, true);
                           adjMatrix[prev_L][index] = temp;
                       }
                   }
                   else{
                       isPrint = false;
                       cout << "No solution !" << endl;    //Thre is no other paths 
                       return;
                   }
               }
               else if(flag_J){              //Intersection point belongs to Lucy's destintion point
                   path_Joseph.clear();
                   temp = adjMatrix[prev_J][index];
                   adjMatrix[prev_J][index] = 0;
                   shortestPath(true, true);
                   adjMatrix[prev_J][index] = temp;
               }
               else{     //Intersection point belongs to Joseph's destintion piont
                   path_Lucy.clear();
                   temp = adjMatrix[prev_L][index];
                   adjMatrix[prev_L][index] = 0;
                   shortestPath(false, true);
                   adjMatrix[prev_L][index] = temp;
               }
           } else
               flag_1 = true;
        }
    }
    else{
        while(!flag_1){
            flag_2 = false;
            vector<pair<int, int>>::iterator i;
            for(i = path_Joseph_return.begin(); i != path_Joseph_return.end(); i++)
            {
                flag_J = false;
                flag_L = false;
                vector<pair<int,int>>::iterator j;
                for(j = path_Lucy_return.begin(); j != path_Lucy_return.end(); j++){
                    if((*i).first == (*j).first){
                        if((*i).first == JD){   // Check if the intersection points belongs to Joseph's destination 
                            if(((*j).second >= duration_J) && ((*j).second <= duration_J + 30)){
                                flag_L = true;
                                flag_2 = true;
                                prev_L = (*--j).first;
                                index = (*++j).first;
                                break;
                            }
                        }
                        else if((*j).first == LD){   // Check if the intersection point belongs to Lucy's destination 
                            if(((*i).second >= duration_L) && ((*i).second <= duration_L + 30)){
                                flag_J = true;
                                flag_2 = true;
                                prev_J = (*--i).first;
                                index = (*++i).first;
                                break;
                            }
                        }
                        else if((*i).second == (*j).second){
                            prev_J = (*--i).first;
                            prev_L = (*--j).first;
                            flag_2 = true;
                            index = (*++i).first;
                            flag_L = flag_J = true;
                            break;
                        }
                    }
                }
                if(flag_2)
                    break;
            }
            if(flag_2){ 
                if(flag_J && flag_L){     //Intersection point does not belongs to any person's destination points 
                    temp = adjMatrix[prev_J][index];
                    adjMatrix[prev_J][index] = 0;      //Make intersection point 0 
                    cost_Joseph = count_time(JD,JH);   //Find the cost when Joseph path is changing 
                    isPath_J = isPath;                  //Check if there is path or not 
                    adjMatrix[prev_J][index] = temp;
                    temp = adjMatrix[prev_L][index];
                    adjMatrix[prev_L][index] = 0;
                    cost_Lucy = count_time(LD, LH);    //Find the cost when Lucy path is changing 
                    isPath_L = isPath;                 //Check if there is path or not 
                    adjMatrix[prev_L][index] = temp;
                    if(isPath_L == false && isPath_J == true ){    //check there is no valid path for Lucy
                        path_Joseph.clear();
                        temp = adjMatrix[prev_J][index];
                        adjMatrix[prev_J][index] = 0;
                        shortestPath(true, true);
                        adjMatrix[prev_J][index] = temp;
                    }
                    else if(isPath_J == false && isPath_L == true){       //chechk there is no valid path Joseph
                        path_Lucy_return.clear();
                        temp = adjMatrix[prev_L][index];
                        adjMatrix[prev_L][index] = 0;
                        shortestPath(false, false);
                        adjMatrix[prev_L][index] = temp;
                    }
                    else if(isPath_J == true && isPath_L == true){      //compare the cost of the both of the new path and select the one that has minimum cost   
                        if(cost_Joseph <= cost_Lucy ){
                            path_Joseph_return.clear();
                            temp = adjMatrix[prev_J][index];
                            adjMatrix[prev_J][index] = 0;
                            shortestPath(true, false);
                            adjMatrix[prev_J][index] = temp;
                        }
                        else if(cost_Lucy <= cost_Joseph){
                            path_Lucy.clear();
                            temp = adjMatrix[prev_L][index];
                            adjMatrix[prev_L][index] = 0;
                            shortestPath(false, false);
                            adjMatrix[prev_L][index] = temp;
                        }
                    }
                    else{                                        //Thre is no other paths 
                        isPrint = false;
                        cout << "No solution !" << endl;
                        return;
                    }
                }
                else if(flag_J){                      //Intersection point belongs to Lucy's destintion point
                    path_Joseph_return.clear();
                    temp = adjMatrix[prev_J][index];
                    adjMatrix[prev_J][index] = 0;
                    shortestPath(true, false);
                    adjMatrix[prev_J][index] = temp;
                }
                else{                              //Intersection point belongs to Joseph's destintion piont
                    path_Lucy_return.clear();
                    temp = adjMatrix[prev_L][index];
                    adjMatrix[prev_L][index] = 0;
                    shortestPath(false, false);
                    adjMatrix[prev_L][index] = temp;
                }
            } else
                flag_1 = true;
        }
    }
}

int main(int argc, char **argv) {
    HW_2 test;
   test.createAdjMatrix(argv[1]);
   test.shortestPath(true,true);
   test.shortestPath(false,true);
   test.fixIntersection(true);
   test.shortestPath(true, false);
   test.shortestPath(false, false);
   test.fixIntersection(false);
   if(test.getPrint() == true)
       test.print();
    return 0;
}
