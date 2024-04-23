#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<queue>
#include<unordered_set>
#include<iomanip>
#include"Nodo.cpp"
#include <chrono>

using namespace std;

long int nos_expandidos = 0;
int comprimento_solução = 0;
double media_heuristica = 0;
int heuristica_inicial = 0;

void print_fornteira(priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> fronteira){
    priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> copia = fronteira;
    Nodo* atual;
    vector<Nodo*> buffer;
    cout << "f = ";
    for(int i = 0 ; i < copia.size(); i++){
        atual = copia.top();
        copia.pop();
        cout << "(" << atual->h << "," << atual->custo << ":" << atual->h+atual->custo <<")" <<" ";
    }
    cout << endl << endl;
}

void print_fornteira(priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> fronteira){
    priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> copia = fronteira;
    Nodo16* atual;
    vector<Nodo16*> buffer;
    cout << "f = ";
    for(int i = 0 ; i < copia.size(); i++){
        atual = copia.top();
        copia.pop();
        cout << "(" << atual->h << "," << atual->g << ":" << atual->h+atual->g <<")" <<" ";
    }
    cout << endl << endl;
}

void delete_nodos(vector<Nodo*> &nos_alocados)
{
    for(int i = 0 ; i < nos_alocados.size(); i++){
        delete nos_alocados[i];
    }
}

void delete_nodos(vector<Nodo16*> &nos_alocados)
{
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
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
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
        nos_expandidos++;
        atual->expande(sucessores,atual,nos_alocados);
        for(int i = 0; i<sucessores.size();i++){ 
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                comprimento_solução = caminho.size();
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
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    unordered_set<string> explorados;
    priority_queue<Nodo*,vector<Nodo*>, CompareGBFS> fronteira , copia;
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
    explorados.insert(init->convert());
    while(!fronteira.empty()){
        Nodo *atual = fronteira.top();

        //cin >> stop;
        fronteira.pop();
        //cout << 'p' << atual->distanceManhatan() << " " << atual->custo << endl;
        //cout << endl;
        nos_expandidos ++;
        atual->expande(sucessores,atual,nos_alocados);
        for(int i = 0; i<sucessores.size();i++){ 
            sucessores.front()->distanceManhatan();
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                solucao->printEstado();
                media_heuristica += solucao->h;
                comprimento_solução = caminho.size();
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/nos_expandidos;
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                media_heuristica += sucessores.front()->h;
                explorados.insert(sucessores.front()->convert());
                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
        }
    }
    return ;
}

void astar(vector<short int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
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
    explorados.insert(init->convert());
    while(!fronteira.empty()){
        Nodo *atual = fronteira.top();
        atual->distanceManhatan();

        //cout << "atual" << endl;
        //atual->printEstado();

        fronteira.pop();

        //print_fornteira(fronteira);
        nos_expandidos ++;
        atual->expande(sucessores,atual,nos_alocados);
        for(int i = 0; i<sucessores.size();i++){ 
            sucessores.front()->distanceManhatan();
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                solucao->printEstado();
                media_heuristica += solucao->h;
                comprimento_solução = caminho.size();
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/nos_expandidos;
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                media_heuristica += sucessores.front()->h;
                explorados.insert(sucessores.front()->convert());

                //sucessores.front()->printEstado();

                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
        }
    }
    return ;
}

void astar16(vector<char> init_estate)
{
    nos_expandidos = 0;
    comprimento_solução = 0;
    media_heuristica = 0;
    unordered_set<string> explorados;
    priority_queue<Nodo16*,vector<Nodo16*>, CompareASTAR16> fronteira;
    vector<Nodo16*> sucessores;
    vector<Nodo16*> nos_alocados;
    vector<string> caminho;
    Nodo16* solucao;

    int stop = 0;

    Nodo16 *init = new Nodo16 (init_estate,NULL,' ',0);
    nos_alocados.push_back(init);
    init->distanceManhatan();
    init->printEstado();
    heuristica_inicial = init->h;
    if(init->e_Solucao()){
        delete init;
        return ;
    }
    
    fronteira.push(init);
    explorados.insert(init->convert());
    while(!fronteira.empty()){
        Nodo16 *atual = fronteira.top();
        fronteira.pop();
        nos_expandidos ++;
        atual->expande(sucessores,atual,nos_alocados);
        for(int i = 0; i<sucessores.size();i++){ 
            sucessores.front()->distanceManhatan();
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->printEstado();
                media_heuristica += solucao->h;
                comprimento_solução = solucao->g;
                delete_nodos(nos_alocados);
                media_heuristica = media_heuristica/nos_expandidos;
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                media_heuristica += sucessores.front()->h;
                explorados.insert(sucessores.front()->convert());
                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
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
        nos_expandidos ++;
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

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    init->distanceManhatan();
    heuristica_inicial = init->h;

    Nodo *solucao = NULL;
    vector<Nodo*> nos_alocados;
    nos_alocados.push_back(init);
    vector<string> caminho;
    init->printEstado();
    int i = 0;
    while(true){
        solucao = dls(nos_alocados,init,i);
        if(solucao != NULL){
            solucao->caminho(caminho);
            solucao->printEstado();
            comprimento_solução = caminho.size();
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

    if((atual->custo + atual->distanceManhatan()) > f_limit){
    	retorno_limit = atual->custo + atual->distanceManhatan();
    	return NULL;
    }
    
    
    if(atual->e_Solucao()){
        retorno_limit = numeric_limits<int>::max();
        return atual;
    }
    
    int next_limit = numeric_limits<int>::max();
    int rec_limit = numeric_limits<int>::max();
    atual->expande(sucessores,atual,nos_alocados);
    nos_expandidos ++;
    media_heuristica += atual->h;
    int tamanho = sucessores.size();
    for(int i = 0;i<tamanho;i++){
            sucessores.front()->distanceManhatan();
            Nodo *new_nodo = sucessores.front();
            sucessores.erase(sucessores.begin());
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
            //solucao->printEstado();
            comprimento_solução = caminho.size();
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

            chrono::system_clock::time_point t = chrono::system_clock::now();
            ios_base::sync_with_stdio(false); 
            bfs(inputs[i]);
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }


    }
    else if(!(algorithm.compare("-astar"))){
        for(int i = 0;i<inputs.size();i++){

            if(inputs[0].size() == 9){
                chrono::system_clock::time_point t = chrono::system_clock::now(); 
                ios_base::sync_with_stdio(false); 
                astar(inputs[i]);
                cout << nos_expandidos << ',';
                cout << comprimento_solução << ',';
                cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
                cout << media_heuristica << ',';
                cout << heuristica_inicial << endl;
            }
            else{

                vector<char> ini_state;
                for(int j = 0; j<16;j++){
                    ini_state.push_back(char(inputs[i][j]));
                }
                cout << inputs.size() << endl;
                chrono::system_clock::time_point t = chrono::system_clock::now();
                ios_base::sync_with_stdio(false); 
                astar16(ini_state);
                cout << nos_expandidos << ',';
                cout << comprimento_solução << ',';
                cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
                cout << media_heuristica << ',';
                cout << heuristica_inicial << endl;
            }
        }

    }
    else if(!(algorithm.compare("-idastar"))){
          for(int i = 0;i<inputs.size();i++){
        	chrono::system_clock::time_point t = chrono::system_clock::now();
        	ios_base::sync_with_stdio(false); 
        	idastar(inputs[i]);
         	cout << nos_expandidos << ',';
         	cout << comprimento_solução << ',';
         	cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
         	cout << media_heuristica / nos_expandidos << ',';
         	cout << heuristica_inicial << endl;
           }
    }
    else if(!(algorithm.compare("-idfs"))){
         for(int i = 0;i<inputs.size();i++){

            chrono::system_clock::time_point t = chrono::system_clock::now();
            ios_base::sync_with_stdio(false); 
            idfs(inputs[i]);
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }

    }
    else if(!(algorithm.compare("-gbfs"))){
        for(int i = 0;i<inputs.size();i++){

	    chrono::system_clock::time_point t = chrono::system_clock::now();
            ios_base::sync_with_stdio(false); 
            gbfs(inputs[i]);
            cout << nos_expandidos << ',';
            cout << comprimento_solução << ',';
            cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-t).count() <<',' ;
            cout << media_heuristica << ',';
            cout << heuristica_inicial << endl;
        }
    }
    else{
        cout << "algoritmo errado" << endl;
    }
}
