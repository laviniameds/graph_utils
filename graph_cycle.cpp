#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//cria a estrututa de uma aresta com vertice origem e destino
struct edge {
	int src, dst;
};

//cria a estrutura do grafo 
class Graph {
public:
    //cria uma lista de adjacências
	vector<vector<int>> list_adj;
    vector<edge> edges;

    //construtor do grafo
	Graph(vector<edge> &e, int size){
        
        edges = e;

        //define tamanho da lista
		list_adj.resize(size);

        //para cada aresta, preenche a lista de adjacências com vertices origem e destino
		for (auto &edge: edges)
			list_adj[edge.src].push_back(edge.dst);
	}
};

bool hasCycleUtil(Graph &graph, int v, vector<bool> &visited, vector<bool> &stack){
    //se o vertice nao foi visitado
    if(visited[v] == false){
        visited[v] = true;  //marca como visitado
        stack[v] = true;  //coloca na pilha

        //para cada vertice adjacente a v
        for(int u : graph.list_adj[v]) { 
            //verifica se os vertices adjacentes foram visitados
            if (!visited[u] && hasCycleUtil(graph, u, visited, stack)) 
                return true; 
            //verifica se o vertice atual esta na pilha
            else if (stack[u]) 
                return true; 
        } 
    }
    //tira o vertice atual da pilha
    stack[v] = false;
    //nao contem um ciclo
    return false;
}

// retorna verdadeiro/falso para se grafo tem um ciclo
bool hasCycle(Graph &graph, int size){        
    //cria um vetor auxiliar para guardar se cada vertice foi visitado
    vector<bool> visited(size);
    vector<bool> stack(size);
  
    for (int i = 0; i < size; i++)
        if (hasCycleUtil(graph, i, visited, stack))
            return true;    
    
    //nao contem um ciclo
    return false;
}

int main(){
	vector<edge> edges = {
		{1, 4}, {4,2}, {4,3}, {4, 5}, {5, 6}
	};

    int size = 7;

	Graph graph(edges, size);

	if (hasCycle(graph, size))
		cout << "Graph has Cycle\n";
	else
		cout << "Graph has not Cycle\n";

	return 0;
}