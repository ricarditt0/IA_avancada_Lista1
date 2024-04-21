#include<vector>
#include<string>
#include<iostream>
#include<iomanip> 

using namespace std;

class Nodo
{
    public:
    vector<int> estado;
    Nodo* pai;
    string acao;
    int custo;
    int h;

    Nodo(){}

    Nodo(const vector<int>& estado, Nodo* pai, const string& acao, int custo)
        : estado(estado), pai(pai), acao(acao), custo(custo) {}

    int distanceManhatan(){
        int distancia = 0;
        for (int i = 0; i < 9; ++i) {
            if (estado[i]) {
                int val = estado[i];
                int rowDistance = std::abs((val) % 3 - static_cast<int>(i % 3));
                int colDistance = std::abs((val) / 3 - static_cast<int>(i / 3));
                distancia += rowDistance + colDistance;
            }
        }
        this->h = distancia;
    	return distancia;
    }
    int distanceManhatan16(){
        int distancia = 0;
        for (int i = 0; i < 16; ++i) {
            if (estado[i]) {
                int val = estado[i];
                int rowDistance = std::abs((val) % 4 - static_cast<int>(i % 4));
                int colDistance = std::abs((val) / 4 - static_cast<int>(i / 4));
                distancia += rowDistance + colDistance;
            }
        }
        this->h = distancia;
    	return distancia;
    }


    string convert()
    {
        std::string s;
        for (int elem : this->estado) {
                s = s + std::to_string(elem);
            }
        return s;
    }

    bool e_Solucao()
    {
        for(int i = 0;i<this->estado.size();i++){
            if(this->estado[i] != i){
                return false;
            }
        }
        return true;
    }

    vector<int> swap(vector<int> estado , int index_alvo, int index_vazio)
    {
        std::vector<int> new_estado = estado;
        new_estado[index_vazio] = new_estado[index_alvo];
        new_estado[index_alvo] = 0;
        return new_estado;
    }

    void expande(vector<Nodo*>& sucessores,Nodo *pai,vector<Nodo*>& nos_alocados)
    {
        int i = 0;
        int custo = 0;
        while (this->estado[i] != 0)
            i ++;

        if(i != 0 && i != 1 && i != 2 && this->acao.compare("baixo")){
            sucessores.push_back(new Nodo(swap(this->estado,i-3,i),pai,"cima",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 0 && i != 3 && i != 6 && this->acao.compare("direita")){
            sucessores.push_back(new Nodo(swap(this->estado,i-1,i),pai,"esquerda",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 2 && i != 5 && i != 8 && this->acao.compare("esquerda")){
            sucessores.push_back(new Nodo(swap(this->estado,i+1,i),pai,"direita",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 6 && i != 7 && i != 8 && this->acao.compare("cima")){
            sucessores.push_back(new Nodo(swap(this->estado,i+3,i),pai,"baixo",this->custo + 1));
            nos_alocados.push_back(sucessores.back()); 
        }
    }
    void expande16(vector<Nodo*>& sucessores,Nodo *pai,vector<Nodo*>& nos_alocados)
    {
        int i = 0;
        int custo = 0;
        while (this->estado[i] != 0)
            i ++;

        if(i != 0 && i != 1 && i != 2 && i != 3 && this->acao.compare("baixo")){
            sucessores.push_back(new Nodo(swap(this->estado,i-4,i),pai,"cima",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 0 && i != 4 && i != 8 && i != 12 && this->acao.compare("direita")){
            sucessores.push_back(new Nodo(swap(this->estado,i-1,i),pai,"esquerda",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 3 && i != 7 && i != 11 && i != 15 && this->acao.compare("esquerda")){
            sucessores.push_back(new Nodo(swap(this->estado,i+1,i),pai,"direita",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
        }

        if(i != 12 && i != 13 && i != 14 && i != 15 && this->acao.compare("cima")){
            sucessores.push_back(new Nodo(swap(this->estado,i+3,i),pai,"baixo",this->custo + 1));
            nos_alocados.push_back(sucessores.back()); 
        }
    }

    void caminho(vector<string> &caminho){
        if(this->pai){
            caminho.push_back(this->acao);
            this->pai->caminho(caminho);
        }
    }

    void printEstado() const
    {
        int sizeP = this->estado.size();
        cout << this->acao << endl;
        if(sizeP == 9){
            for(int i = 0; i < 9; i++){
                    cout << this->estado[i] << " ";
                if(!((i+1)%3))
                    cout << endl;
            }
            cout << endl;
        }
        else
        {
            for(int i = 0; i < 16; i++){
                    cout << this->estado[i] << '\t';
                if(!((i+1)%4))
                    cout << endl;
            }
            cout << endl;
        }
    }
};

class CompareGBFS {
    public:
        bool operator()(Nodo *a, Nodo *b){
            if(a->h!= b->h)
                return a->h > b->h;
            if(a->custo != b->custo)
                return a->custo < b->custo;
            return true;
        }
};

class CompareASTAR{
    public:
        bool operator()(Nodo *a,Nodo *b){
            int f_a = a->custo + a->h;
            int f_b = b->custo + b->h;
            if(f_a != f_b)
                return f_a > f_b;
            if(a->h!= b->h)
                return a->h > b->h;
            return false;
        }
};

class CompareASTAR16{
    public:
        bool operator()(Nodo *a,Nodo *b){
            int f_a = a->h + a->custo;
            int f_b = b->h + b->custo; 

            if(f_a != f_b)
                return f_a > f_b;
            if(a->h!= b->h)
                return a->h > b->h;
            return false;
        }
};