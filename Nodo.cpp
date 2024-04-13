#include<vector>
#include<string>
#include<iostream>


class Nodo
{
    public:
    std::vector<int> estado;
    Nodo* pai;
    std::string acao;
    int custo;

    Nodo(const std::vector<int>& estado, Nodo* pai, const std::string& acao, int custo)
        : estado(estado), pai(pai), acao(acao), custo(custo) {}

    int distanceManhatan(){
        return 0;
    }

    std::vector<int> swap(std::vector<int> estado , int index_alvo, int index_vazio)
    {
        std::vector<int> new_estado = estado;
        new_estado[index_vazio] = new_estado[index_alvo];
        new_estado[index_alvo] = 0;
        return new_estado;
    }

    void expande(std::vector<Nodo>& sucessores)
    {
        int i = 0;
        while (this->estado[i] != 0)
            i ++;
        if(i != 0 && i != 1 && i != 2){
            sucessores.push_back(Nodo(swap(this->estado,i-3,i),this,"cima",0));
        }
        if(i != 0 && i != 3 && i != 6){
            sucessores.push_back(Nodo(swap(this->estado,i-1,i),this,"esquerda",0));
        }
        if(i != 2 && i != 5 && i != 8){
            sucessores.push_back(Nodo(swap(this->estado,i+1,i),this,"direita",0));
        }
        if(i != 6 && i != 7 && i != 8){
            sucessores.push_back(Nodo(swap(this->estado,i+3,i),this,"baixo",0));
        }
    }

    void printEstado()
    {
        int sizeP = this->estado.size();
        if(sizeP == 9){
            for(int i = 0; i < 9; i++){
                    std::cout << this->estado[i] << " ";
                if(!((i+1)%3))
                    std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

};



// def distancia_manhattan(estado: str):
//     string = '12345678'
//     objetivo = {
//         "1": (0, 0),
//         "2": (0, 1),
//         "3": (0, 2),
//         "4": (1, 0),
//         "5": (1, 1),
//         "6": (1, 2),
//         "7": (2, 0),
//         "8": (2, 1)
//     }
//     soma = 0
//     i = 0
//     while i < len(string):
//         indice_estado = estado.find(string[i])
//         pos = objetivo[string[i]]
//         soma += abs(pos[0] - indice_estado//3) + abs(pos[1] - indice_estado % 3)
//         i += 1
    
//     return soma
