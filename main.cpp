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

int main(int argc, char *argv[])
{
    int stop;
    unordered_set<Nodo,Nodo::hash> explorados;
    queue<Nodo> fronteira;
    vector<vector<int>> inputs;
    string algorithm = argv[1];
    Nodo solucao;

    readInputs(inputs,argc,argv);
    vector<Nodo> sucessores;

    if(!(algorithm.compare("-bfs"))){
        nos_expandidos = 0;
        cout << "bfs" << endl;
        Nodo init (inputs[0],NULL,"",0);

        fronteira.push(init);

        while (!fronteira.empty()){
            Nodo atual = fronteira.front();
            explorados.insert(atual);
            atual.printEstado();
            //cin >> stop;
            fronteira.pop();
            if(atual.e_Solucao()){
                solucao = atual;
                break;
            }
            atual.expande(sucessores);

            for(int i = 0; i<sucessores.size();i++){
                if(!explorados.count(sucessores.front())){
                    nos_expandidos++;
                    fronteira.push(sucessores.front());
                }
                sucessores.erase(sucessores.begin());
            }
        }
        cout<< nos_expandidos << endl;
        vector<string> caminho;
        //solucao.caminho(caminho);
        //cout << caminho.size();
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