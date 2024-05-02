/*
    Arquivo principal que contém as implementações dos algoritmos solicitados
*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<queue>
#include<unordered_set>
#include<iomanip>
#include"Nodo.cpp"
#include<chrono>
#include<cmath>

using namespace std;

int comprimento_solução = 0;
int heuristica_inicial = 0;
auto inicio = std::chrono::high_resolution_clock::now();
auto resultado = std::chrono::high_resolution_clock::now() - inicio;

void print_fornteira(priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> fronteira){
    priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> copia = fronteira;
    Nodo* atual;
    vector<Nodo*> buffer;
    cout << "f = ";
    int tamanho = copia.size();
    for(int i = 0 ; i < tamanho; i++){
        atual = copia.top();
        copia.pop();
        cout << "(h:" << atual->h << " + g:" << atual->custo << " = f:" << atual->h+atual->custo <<")" <<" ";
    }
    cout << endl << endl;
}

void print_fornteira(priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> fronteira){
    priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> copia = fronteira;
    Nodo16* atual;
    vector<Nodo16*> buffer;
    cout << "f = ";
    int tamanho = copia.size();
    for(int i = 0 ; i < tamanho; i++){
        atual = copia.top();
        copia.pop();
        cout << "(" << atual->h << "," << atual->g << ":" << atual->h+atual->g <<")" <<" ";
    }
    cout << endl << endl;
}

void delete_nodos(vector<Nodo*> &nos_alocados)
{
    nos_alocados[0]->clear_id();
    for(int i = 0 ; i < nos_alocados.size(); i++){
        delete nos_alocados[i];
    }
}

void delete_nodos(vector<Nodo16*> &nos_alocados)
{
    nos_alocados[0]->clear_id();
    for(int i = 0 ; i < nos_alocados.size(); i++){
        delete nos_alocados[i];
    }
}

void readInputs(vector<vector<short int>>& inputs ,int argc ,char* argv[])
{
    vector<short int> input;
    for(int i = 2;i < argc; i++){
        if((strlen(argv[i]) == 2 && argv[i][1] == ',')||(strlen(argv[i]) == 3 )){
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

void bfs(vector<short int> init_estate)
{
    media_count = 0;
    media_heuristica = 0;
    nos_expandidos = 0;
    comprimento_solução = 0;

    unordered_set<string> explorados;
    queue<Nodo*> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;

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
        atual->expande(sucessores,atual,nos_alocados);
        while(!sucessores.empty()){ 
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                comprimento_solução = caminho.size();
                media_heuristica = 0;
                delete_nodos(nos_alocados);
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                explorados.insert(sucessores.front()->convert());
                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
        }
    }
    return ;
}

void gbfs(vector<short int> init_estate)
{
    media_heuristica = 0;
    media_count = 0;
    nos_expandidos = 0;
    comprimento_solução = 0;

    unordered_set<string> explorados;
    priority_queue<Nodo*,vector<Nodo*>, CompareGBFS> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;

    int stop = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    nos_alocados.push_back(init);
    init->distanceManhatan();
    heuristica_inicial = init->h;
    if(init->e_Solucao()){
        delete init;
        return ;
    }
    
    fronteira.push(init);
    while(!fronteira.empty()){

        Nodo *atual = fronteira.top();
        fronteira.pop();

        if(!explorados.count(atual->convert())){
            explorados.insert(atual->convert());
            if(atual->e_Solucao()){
                atual->caminho(caminho);
                comprimento_solução = (caminho.size());
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/media_count;
                return ;
            }
            atual->expande(sucessores,atual,nos_alocados);
            while(!sucessores.empty()){
                fronteira.push(sucessores.front());
                sucessores.erase(sucessores.begin());
            }
        }
    }
    return ;
}

void astar(vector<short int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    media_count = 0;

    unordered_set<string> explorados;
    priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;

    int stop = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    nos_alocados.push_back(init);
    init->distanceManhatan();
    heuristica_inicial = init->h;
    if(init->e_Solucao()){
        delete init;
        return ;
    }
    
    fronteira.push(init);
    while(!fronteira.empty()){

        Nodo *atual = fronteira.top();
        fronteira.pop();

        if(!explorados.count(atual->convert())){
            explorados.insert(atual->convert());
            if(atual->e_Solucao()){
                atual->caminho(caminho);
                comprimento_solução = (caminho.size());
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/media_count;
                return ;
            }
            atual->expande(sucessores,atual,nos_alocados);
            while(!sucessores.empty()){
                fronteira.push(sucessores.front());
                sucessores.erase(sucessores.begin());
            }
        }
    }
    return ;
}


void astar16(vector<char> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    media_count = 0;

    unordered_set<string> explorados;
    priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> fronteira;
    vector<Nodo16*> sucessores;
    vector<Nodo16*> nos_alocados;
    string caminho;

    int stop = 0;

    Nodo16 *init = new Nodo16 (init_estate,NULL,' ',0);
    nos_alocados.push_back(init);
    init->distanceManhatan();
    heuristica_inicial = init->h;
    if(init->e_Solucao()){
        delete init;
        return ;
    }
    
    fronteira.push(init);
    while(!fronteira.empty()){
        
        resultado = std::chrono::high_resolution_clock::now() - inicio;
        if(((std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9)) > 30.00 ){
            nos_expandidos = 0;
            comprimento_solução = 0;
            media_heuristica = 0;
            media_count = 0;
            delete_nodos(nos_alocados);
            return;
        }

        Nodo16 *atual = fronteira.top();
        fronteira.pop();

        if(!explorados.count(atual->convert())){
            explorados.insert(atual->convert());
            if(atual->e_Solucao()){
                atual->caminho(caminho);
                comprimento_solução = caminho.length();
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/media_count;
                return ;
            }
            atual->expande(sucessores,atual,nos_alocados);
            while(!sucessores.empty()){
                fronteira.push(sucessores.front());
                sucessores.erase(sucessores.begin());
            }
        }
    }
    return ;
}

Nodo* dls(vector<Nodo*> &nos_alocados,Nodo* atual, int depth_Limit)
{
    vector<Nodo*> sucessores;
    Nodo *solucao = NULL;

    if(atual->e_Solucao()){
        return atual;
    }
    if(depth_Limit > 0){
        atual->expande(sucessores,atual,nos_alocados);
        for(int i = 0;i<sucessores.size();i++){
            solucao = dls(nos_alocados,sucessores[i],depth_Limit-1);
            if(solucao != NULL){
                return solucao;
            }
        }
    }
    return NULL;
}

void idfs(vector<short int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    media_count = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    init->distanceManhatan();
    heuristica_inicial = init->h;

    Nodo *solucao = NULL;
    vector<Nodo*> nos_alocados;
    nos_alocados.push_back(init);
    vector<string> caminho;
    int i = 0;
    while(true){
        solucao = dls(nos_alocados,init,i);
        if(solucao != NULL){
            solucao->caminho(caminho);
            comprimento_solução = caminho.size();
            media_heuristica = 0;
            delete_nodos(nos_alocados);
            return;
        }
        i++;
    }
}

Nodo* idastar_aux(vector<Nodo*> &nos_alocados,Nodo* atual, int f_limit, int& retorno_limit)
{
    vector<Nodo*> sucessores;
    Nodo *solucao = NULL;

    if((atual->custo + atual->h) > f_limit){
    	retorno_limit = atual->custo + atual->h;
    	return NULL;
    } 
    
    if(atual->e_Solucao()){
        retorno_limit = numeric_limits<int>::max();
        return atual;
    }
    
    int next_limit = numeric_limits<int>::max();
    int rec_limit = numeric_limits<int>::max();
    atual->expande(sucessores,atual,nos_alocados);
    comprimento_solução += sucessores.size();
    for(int i = 0; i < sucessores.size();i++){
            Nodo *new_nodo = sucessores[i];
            if(new_nodo->h < numeric_limits<int>::max()){
            	solucao = idastar_aux(nos_alocados, new_nodo, f_limit, rec_limit);
            	if(solucao != NULL){
            	    retorno_limit = numeric_limits<int>::max();
		            return solucao;
	    	    }
	    	next_limit = min(next_limit, rec_limit);
        }
    }
    retorno_limit = next_limit;
    return NULL;
}

void idastar(vector<short int> init_estate)	{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    media_count = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    init->distanceManhatan();
    heuristica_inicial = init->h;
	
    Nodo *solucao = NULL;
    vector<Nodo*> nos_alocados;
    nos_alocados.push_back(init);
    vector<string> caminho;
    
    int f_limit = heuristica_inicial;
    
    while (f_limit != numeric_limits<int>::max()){
    	solucao = idastar_aux(nos_alocados, init, f_limit, f_limit);
        if(solucao != NULL){
            solucao->caminho(caminho);
            comprimento_solução = caminho.size();
            media_heuristica = media_heuristica/media_count;
            delete_nodos(nos_alocados);
            return;
    	}
    }
}	


int main(int argc, char *argv[])
{
    int stop;
    vector<vector<short int>> inputs;
    string algorithm = argv[1];
    time_t start, end;
    double time_taken ;

    readInputs(inputs,argc,argv);

    if(!(algorithm.compare("-bfs"))){
        for(int i = 0;i<inputs.size();i++){

            inicio = std::chrono::high_resolution_clock::now();
            bfs(inputs[i]);
            resultado = std::chrono::high_resolution_clock::now() - inicio;
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }


    }
    else if(!(algorithm.compare("-astar"))){
        for(int i = 0;i<inputs.size();i++){

            if(inputs[0].size() == 9){
                inicio = std::chrono::high_resolution_clock::now();
                astar(inputs[i]);
                resultado = std::chrono::high_resolution_clock::now() - inicio;
                cout << nos_expandidos << ',';
                cout << comprimento_solução << ',';
                cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
                cout << media_heuristica << ',';
                cout << heuristica_inicial << endl;
            }
            else{

                vector<char> ini_state;
                for(int j = 0; j<16;j++){
                    ini_state.push_back(char(inputs[i][j]));
                }
                inicio = std::chrono::high_resolution_clock::now();
                astar16(ini_state);
                resultado = std::chrono::high_resolution_clock::now() - inicio;
                cout << nos_expandidos << ',';
                cout << comprimento_solução << ',';
                cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
                cout << media_heuristica << ',';
                cout << heuristica_inicial << endl;
            }
        }

    }
    else if(!(algorithm.compare("-idastar"))){
          for(int i = 0;i<inputs.size();i++){
            inicio = std::chrono::high_resolution_clock::now();
        	idastar(inputs[i]);
            resultado = std::chrono::high_resolution_clock::now() - inicio;
         	cout << nos_expandidos << ',';
         	cout << comprimento_solução << ',';
            cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
         	cout << media_heuristica << ',';
         	cout << heuristica_inicial << endl;
           }
    }
    else if(!(algorithm.compare("-idfs"))){
         for(int i = 0;i<inputs.size();i++){

            inicio = std::chrono::high_resolution_clock::now();
            idfs(inputs[i]);
            resultado = std::chrono::high_resolution_clock::now() - inicio;
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }

    }
    else if(!(algorithm.compare("-gbfs"))){
        for(int i = 0;i<inputs.size();i++){

            inicio = std::chrono::high_resolution_clock::now();
            gbfs(inputs[i]);
            resultado = std::chrono::high_resolution_clock::now() - inicio;
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }
    }
    else{

        cout << "algoritmo errado" << endl;
        Nodo* novo = new Nodo(inputs[0],NULL,"",0);
        novo->printEstado();
        cout << novo->distanceManhatan();

    }
}
