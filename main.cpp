#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include"Nodo.cpp"

using namespace std;

void readInputs(vector<vector<int>>& inputs ,int argc ,char* argv[])
{
    vector<int> input;
    for(int i = 2;i < argc; i++){
        if(strlen(argv[i]) == 2 && argv[i][1] == ','){
            input.push_back(atoi(argv[i]));
            inputs.push_back(input);
            input.clear();
        }
        else{
            input.push_back(atoi(argv[i]));
        }
    }   
    inputs.push_back(input);
}

int main(int argc, char *argv[])
{
    vector<vector<int>> inputs;
    string algorithm = argv[1];

    readInputs(inputs,argc,argv);

    if(!(algorithm.compare("-bfs"))){
        cout << "bfs" << endl;
    }
    else if(!(algorithm.compare("-astar"))){
        cout << "astar" << endl;
    }
    else if(!(algorithm.compare("-idastar"))){
        cout << "idastar" << endl;
    }
    else if(!(algorithm.compare("-idfs"))){
        cout << "idfs" << endl;
    }
    else if(!(algorithm.compare("-gbfs"))){
        cout << "gbfs" << endl;
    }
    else
        cout << "algoritmo errado" << endl;

    

    Nodo n1(inputs[0],NULL,"",0);
    for(int i = 0 ; i < size(n1.estado);i++){
        cout << n1.estado[i] << " ";
    }

}