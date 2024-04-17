#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<queue>
#include<unordered_set>
#include"Nodo.cpp"

using namespace std;

double nos_expandidos = 0;

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

int bfs(vector<int> init_estate,Nodo *solucao)
{
    nos_expandidos = 0;
    unordered_set<string> explorados;
    queue<Nodo> fronteira;
    Nodo* sucessores[4];
    vector<string> caminho;

    Nodo init (init_estate,NULL,"",0);

    if(init.e_Solucao()){
        init.printEstado();
        return 1;
    }

    fronteira.push(init);
    init.printEstado();
    explorados.insert(init.convert());
    while (!fronteira.empty()){
        Nodo atual = fronteira.front();
        fronteira.pop();
        nos_expandidos++;
        atual.expande(sucessores);
        for(int i = 0; i<4;i++){
            
            if(sucessores[i]){

                if(sucessores[i]->e_Solucao()){
                    solucao = sucessores[i];
                    solucao->printEstado();
                    solucao->caminho(caminho);
                    return 1;
                }

                if(!explorados.count(sucessores[i]->convert())){
                    explorados.insert(sucessores[i]->convert());
                    fronteira.push(sucessores.front());
                }
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int stop;
    vector<vector<int>> inputs;
    string algorithm = argv[1];
    Nodo *solucao;

    readInputs(inputs,argc,argv);
    vector<Nodo> sucessores;

    if(!(algorithm.compare("-bfs"))){
        cout << "bfs" << endl;
        Nodo init (inputs[0],NULL,"",0);

        vector<string> caminho;
        cout<< bfs(inputs[0],solucao) << endl;
        cout << nos_expandidos<< endl;
        cout << caminho.size();

        // for (int i = 0 ; i<caminho.size();i++){
        //     cout << caminho[i] << " ";
        // }
        // cout << endl;



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
 

}