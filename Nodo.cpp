#include<vector>
#include<string>

class Nodo{
    public:
    std::vector<int> estado;
    Nodo* pai;
    std::string acao;
    int custo;

    Nodo(std::vector<int> initEstate, Nodo *pai, std::string acao, int custo){
        estado = initEstate;
        pai = pai;
        acao = acao;
        custo = custo;
    }

    int distanceManhatan(){
        return 0;
    }
    void acoesPossiveis(){

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
