#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<queue>
#include<unordered_set>
#include <iomanip>
#include"Nodo.cpp"

using namespace std;

long int nos_expandidos = 0;
int comprimento_solução = 0;
double media_heuristica = 0;
int heuristica_inicial = 0;

void delete_nodos(vector<Nodo*> &nos_alocados)
{
    for(int i = 0 ; i < nos_alocados.size(); i++){
        delete nos_alocados[i];
    }
}

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

void bfs(vector<int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    unordered_set<string> explorados;
    queue<Nodo*> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;
    int comprimento = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    nos_alocados.push_back(init);
    heuristica_inicial = init->distanceManhatan();

    if(init->e_Solucao()){
        delete init;
        return ;
    }

    fronteira.push(init);
    explorados.insert(init->convert());
    while (!fronteira.empty()){
        Nodo *atual = fronteira.front();
        fronteira.pop();
        nos_expandidos++;
        atual->expande(sucessores,atual);
        for(int i = 0; i<sucessores.size();i++){
            
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                comprimento_solução = caminho.size();
                delete_nodos(nos_alocados);
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                nos_alocados.push_back(sucessores.front());
                explorados.insert(sucessores.front()->convert());
                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
        }
    }
    return ;
}

int main(int argc, char *argv[])
{
    int stop;
    vector<vector<int>> inputs;
    string algorithm = argv[1];
    time_t start, end;
    double time_taken ;

    readInputs(inputs,argc,argv);
    vector<Nodo> sucessores;

    if(!(algorithm.compare("-bfs"))){
        for(int i = 0;i<inputs.size();i++){

            time(&start); 
            ios_base::sync_with_stdio(false); 
            bfs(inputs[i]);
            time(&end); 
            time_taken = double(end - start);
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << fixed << time_taken <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }


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