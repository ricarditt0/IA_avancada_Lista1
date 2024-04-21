	#include<iostream>
	#include<string>
	#include<cstring>
	#include<vector>
	#include<cstdlib>
	//#include"Nodo.cpp"
	#include"node_math.cpp"

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
	    vector<Nodo> sucessores;

	    if(!(algorithm.compare("-bfs"))){
	        int resultado_encontrado = 0, melhor_nodo = -1, melhor_heuristica = 200;
		cout << "bfs" << endl;
		Nodo n1(inputs[0],NULL,"",0);
		n1.printEstado();
		printf("distância manhatan do estado: %d\n\n", n1.distanceManhatan());
		n1.expande(sucessores);
		while(sucessores[melhor_nodo].custo != 0){
			for (int i = 0; i < sucessores.size(); i++){
				if (sucessores[i].custo < melhor_heuristica){
					melhor_heuristica = sucessores[i].custo;
					melhor_nodo = i;
				}
			}
		}
		int tamanho = sucessores.size()+1;
		printf("nodos expandidos = %d\n", tamanho);
		
		for(int j = 0; j < sucessores.size();j++){
            		sucessores[j].printEstado();
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


	    // Nodo n1(inputs[0],NULL,"",0);
	    // for(int i = 0 ; i < size(inputs[0]);i++){
	    //     cout << inputs[0][i] << " ";
	    // }
	    // cout << endl;

	    // for(int i = 0 ; i < size(n1.estado);i++){
	    //     cout << n1.estado[i] << " ";
	    // }

	}
