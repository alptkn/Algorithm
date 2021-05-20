#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace chrono;

struct pokemon {
    int pikachu_HP;
    int pikachu_PP;
    int blastoise_HP;
    int blastoise_PP;
    char turn;
    double prob;
    int level;
    bool isLeaf;
    string attack_type;
    bool isEffective;
    pokemon *parent;
    vector<pokemon *> child;
    bool isLive_pikachu();
    bool isLive_blastoise();

};
//pokemon that creates new pokemon
pokemon *newPokemon(int pikachu_HP, int pikachu_PP, int blastoise_HP, int blastoise_PP, char turn, double prob, int level, bool isLeaf, string attack_type, bool isEffective){
    pokemon *temp = new pokemon;
    temp->pikachu_HP = pikachu_HP;
    temp->pikachu_PP = pikachu_PP;
    temp->blastoise_HP = blastoise_HP;
    temp->blastoise_PP = blastoise_PP;
    temp->turn = turn;
    temp->prob = prob;
    temp->level = level;
    temp->isLeaf = isLeaf;
    temp->parent = NULL;
    temp->attack_type = attack_type;
    temp->isEffective = isEffective;
    return temp;
}
bool pokemon::isLive_pikachu() {
    if(pikachu_HP > 0)
        return true;
    else
        return false;
}
bool pokemon::isLive_blastoise() {
    if(blastoise_HP > 0)
        return true;
    else
        return false;
}
class Graph{
    int current_level = 1;
    void writeDetail(pokemon *root, string attack);
public:
    void constrcutGraph(pokemon *root, int level);
    void print(pokemon *root);
    void BFS(pokemon *root);
    void DFS(pokemon *root, int &node_count);
    void shorthest_path_pikachu(pokemon *root);
    void shorthest_path_blastoiese(pokemon *root);
};
void Graph::constrcutGraph(pokemon *root,int level) {
    bool leaf = false;
    if(level == 0)
        return;
    if(current_level <= level){
        if(current_level == level)
            leaf = true;
        if(root->turn =='P' && root->isLive_blastoise()){                 //pikachu turn and blastoise is live so that pikachu can attack 
            if(root->pikachu_PP >= 10)
            {
                if(current_level < 4)                                     //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 10, root->blastoise_HP - 40,root->blastoise_PP, 'B', root->prob * 0.33, root->level + 1, leaf,"Thunderstack",true));

                else
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 10, root->blastoise_HP - 40,root->blastoise_PP, 'B', root->prob * 0.25, root->level + 1, leaf,"Thunderstack",true ));
            }
            if(root->pikachu_PP >= 15){
                if(current_level < 4){                                   //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 15, root->blastoise_HP - 50,root->blastoise_PP, 'B', root->prob * 0.33* 0.7, root->level + 1, leaf,"Skull Bash",true ));
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 15, root->blastoise_HP,root->blastoise_PP, 'B', root->prob * 0.33* 0.3, root->level + 1, leaf,"Skull Bash", false ));
                }

                else{
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 15, root->blastoise_HP - 50,root->blastoise_PP, 'B', root->prob * 0.25* 0.7, root->level + 1, leaf,"Skull Bash", true ));
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 15, root->blastoise_HP,root->blastoise_PP, 'B', root->prob * 0.25* 0.3, root->level + 1, leaf,"Skull Bash", false ));
                }

            }
            if(root->pikachu_PP >= 20){
                if(current_level < 4){                                 //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 20, root->blastoise_HP - 60,root->blastoise_PP, 'B', root->prob * 0.33* 0.8, root->level + 1, leaf,"Slam",true ));
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 20, root->blastoise_HP,root->blastoise_PP, 'B', root->prob * 0.33* 0.2, root->level + 1, leaf, "Slam", false ));
                }

                else{
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 20, root->blastoise_HP - 60,root->blastoise_PP, 'B', root->prob * 0.25* 0.8, root->level + 1, leaf,"Slam", true ));
                    root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP - 20, root->blastoise_HP,root->blastoise_PP, 'B', root->prob * 0.25* 0.2, root->level + 1, leaf, "Slam",false ));
                }

            }
            if(current_level >= 4)                                    //chechk the current level after the level 3, new option skip can be used 
                root->child.push_back(newPokemon(root->pikachu_HP,root->pikachu_PP + 100,root->blastoise_HP,root->blastoise_PP,'B',root->prob * 0.25, root->level + 1, leaf,"Skip",true));
            current_level++;
        }
        else if (!root->isLive_blastoise()){                        // chechk if the balstoise is dath if its is mark the node as leaf 
            root->isLeaf = true;
        }
        if(root->turn == 'B' && root->isLive_pikachu()){            //blastoise turn and pikachu is live so that blastoise can attack 
            if(root->blastoise_PP >= 10){
                if(current_level < 4)                               //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(newPokemon(root->pikachu_HP - 30, root->pikachu_PP, root->blastoise_HP,root->blastoise_PP - 10, 'P', root->prob * 0.33, root->level + 1, leaf,"Tackle",true));
                else
                    root->child.push_back(newPokemon(root->pikachu_HP - 30, root->pikachu_PP, root->blastoise_HP,root->blastoise_PP - 10, 'P', root->prob * 0.25, root->level + 1, leaf,"Tackle",true));
            }
            if(root->blastoise_PP >= 20) {
                if(current_level < 4)                              //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(
                            newPokemon(root->pikachu_HP - 40, root->pikachu_PP, root->blastoise_HP, root->blastoise_PP - 20,
                                       'P', root->prob * 0.33, root->level + 1, leaf,"Water Gun", true));
                else
                    root->child.push_back(
                            newPokemon(root->pikachu_HP - 40, root->pikachu_PP, root->blastoise_HP, root->blastoise_PP - 20,
                                       'P', root->prob * 0.25, root->level + 1, leaf,"Water Gun", true));
            }
            if(root->blastoise_PP >= 25){
                if(current_level < 4)                              //chechk the current level after the level 3, new option skip can be used and probability will be changed
                    root->child.push_back(newPokemon(root->pikachu_HP - 60, root->pikachu_PP, root->blastoise_HP,root->blastoise_PP - 25, 'P',
                                                     root->prob * 0.33, root->level + 1, leaf,"Bite",true));
                else
                    root->child.push_back(newPokemon(root->pikachu_HP - 40, root->pikachu_PP, root->blastoise_HP,root->blastoise_PP - 20, 'P',
                                                     root->prob * 0.25, root->level + 1, leaf,"Bite", true));
            }
            if(current_level >= 4){                                //chechk the current level after the level 3, new option skip can be used 
                root->child.push_back(newPokemon(root->pikachu_HP, root->pikachu_PP, root->blastoise_HP,root->blastoise_PP + 100, 'P',
                                                 root->prob * 0.25, root->level + 1, leaf, "Skip", true));
            }
            current_level++;
        }
        else if(!root->isLive_pikachu())                        //chech the pikachu is death if it is mark the node as leaf    
            root->isLeaf = true;
    }
    else
        return;
    for(int i = 0; i < root->child.size(); i++){               // assign parent pointer of child nodes to their parent 
        root->child.at(i)->parent = new pokemon;
        root->child.at(i)->parent = root;
    }

    for(int i = 0; i < root->child.size(); i++){
        constrcutGraph(root->child.at(i),level);               //call the function for child nodes 
    }
    current_level--;
    return;
}
void Graph::writeDetail(pokemon *root, string attack) {
    if(root == nullptr)
        return;
    if(root->parent != nullptr)
        writeDetail(root->parent,root->attack_type);          //call the function until reach the root 
    if(!root->isLeaf){

        if(root->turn == 'P'){
            cout << "Pikachu used " << attack;
            if(root->isEffective)
                cout << ". It's effective" << endl;
            else
                cout << ". It's ineffective" << endl;
        }
        else{
            cout << "Blastoise used " << attack;
            if(root->isEffective)
                cout << ". It's effective" << endl;
            else
                cout << ". It's ineffective" << endl;
        }
        return;
    }
}
void Graph::BFS(pokemon *root) {     //operates BFS 
    queue<pokemon *> q;
    q.push(root);
    int count = 0;
    while(!q.empty()){
        pokemon *p = q.front();
        q.pop();
        count++;
        for(int i = 0; i < p->child.size(); i++){
            if(p->child.at(i) != nullptr)
                q.push(p->child.at(i));
        }
    }
    cout << "Number of node: " << count << endl;
}
// this function finds the first node where pikachu is death 
void Graph::shorthest_path_pikachu(pokemon *root) {        
    queue<pokemon *> q;
    pokemon *p = newPokemon(0,0,0,0,'P',0,0,false,"None",true);
    q.push(root);
    while(!q.empty()){
        p = q.front();
        if(p->pikachu_HP <= 0){
            break;
        }
        q.pop();
        for(int i = 0; i < p->child.size(); i++){
            if(p->child.at(i) != nullptr)
                q.push(p->child.at(i));
        }
    }
    cout << endl;
    writeDetail(p,p->attack_type);             //call writeDetail to show what is happend so far 
    cout << "Level count: " << p->level << endl;
    cout << "Probability: " << p->prob << endl;
}
// this function finds the first node where blastoise is death 
void Graph::shorthest_path_blastoiese(pokemon *root) {
    queue<pokemon *> q;
    pokemon *p = newPokemon(0,0,0,0,'P',0,0,false,"None",true);
    q.push(root);
    while(!q.empty()){
        p = q.front();
        if(p->blastoise_HP <= 0){
            break;
        }
        q.pop();
        for(int i = 0; i < p->child.size(); i++){
            if(p->child.at(i) != nullptr)
                q.push(p->child.at(i));
        }
    }
    cout << endl;
    writeDetail(p,p->attack_type);          //call writeDetail to show what is happend so far 
    cout << "Level count: " << p->level << endl;
    cout << "Probability: " << p->prob << endl;
}
void Graph::DFS(pokemon *root, int &node_count) {  //operates DFS
    if(root == NULL)
        return;
    node_count++;
    for(int i = 0; i < root->child.size(); i++){
        DFS(root->child.at(i),node_count);
    }
    return;
}
//this function prints the all node in level order 
void Graph::print(pokemon *root) {
    if(root == NULL)
        return;
    queue<pokemon *> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        while(n > 0){
            pokemon *p = q.front();
            q.pop();
            cout << "P_HP: " << p->pikachu_HP << "   P_PP: " << p->pikachu_PP << "   B_HP: " << p->blastoise_HP << "   B_PP: " << p->blastoise_PP << "   PROB: " << p->prob << endl;
            for(int i = 0; i < p->child.size(); i++)
                q.push(p->child.at(i));
            n--;
        }
    }
}


int main(int argc, char **argv) {
    if(argc <= 2  ){
        cout << "Invalid arguments" << endl;
        return 0;
    }
    Graph graph;
    pokemon *root = newPokemon(200,100,200,100,'P',1,0,0,"None", true);
    if( !strcmp(argv[1], "part1") && argc == 3){
        graph.constrcutGraph(root,atoi(argv[2]));
        graph.print(root);
    }
    else if( !strcmp(argv[1],"part2") && argc == 4){
        int count = 0;
        graph.constrcutGraph(root,atoi(argv[2]));
        if(!strcmp(argv[3], "bfs")){
             cout << "BFS" << endl;
            auto start_bfs = high_resolution_clock::now();
            graph.BFS(root);
            auto stop_bfs = high_resolution_clock::now();
            auto duration_bfs = duration_cast<microseconds>(stop_bfs - start_bfs);
            cout << "Time taken by BFS: "
             << duration_bfs.count() << " microseconds" << endl;
        }
       else{
        cout << "DFS" << endl;     
        auto start_dfs = high_resolution_clock::now();
        graph.DFS(root, count);
        auto stop_dfs = high_resolution_clock::now();
        auto duration_dfs = duration_cast<microseconds>(stop_dfs - start_dfs);
        cout << "Number of node: " << count << endl;
        cout << "Time taken by DFS: "
             << duration_dfs.count() << " microseconds" << endl;
       }
        
    }
    else if(!strcmp(argv[1],"part3") && argc == 3){
        graph.constrcutGraph(root, 9);
        if(!strcmp(argv[2] , "pikachu"))
            graph.shorthest_path_pikachu(root);
        else
            graph.shorthest_path_blastoiese(root);
    }
    else 
        cout << "Invalid Argument." << endl;
    return 0;
}
