#include <iostream>
#include <vector>
#include<bits/stdc++.h> 
using namespace std;

//cria a estrututa de uma aresta com vertice origem e destino
struct edge {
	int src, dst;
};

//cria a estrutura do grafo 
class Graph {
public:
    //cria uma lista de adjacências
	list<int> *list_adj;
    vector<edge> edges;

    //construtor do grafo
	Graph(vector<edge> &e, int size){
        
        edges = e;

        //define tamanho da lista
		list_adj = new list<int>[size]; 

        //para cada aresta, preenche a lista de adjacências com vertices origem e destino
		for (auto &edge: edges)
			list_adj[edge.src].push_back(edge.dst);
	}
};

bool hasCycleUtil(Graph &graph, int v, bool visited[], bool *stack){
    if(visited[v] == false){
        visited[v] = true; 
        stack[v] = true; 

        list<int>::iterator it; 
        for(it = graph.list_adj[v].begin(); it != graph.list_adj[v].end(); ++it) { 
            if (!visited[*it] && hasCycleUtil(graph, *it, visited, stack)) 
                return true; 
            else if (stack[*it]) 
                return true; 
        } 
    }
    stack[v] = false;
    return false;
}

// retorna verdadeiro/falso para se grafo tem um ciclo
bool hasCycle(Graph &graph, int size){        
    //cria um vetor auxiliar para guardar se cada vertice foi visitado
	bool *visited = new bool[size]; 
	bool *stack = new bool[size]; 

	for(int i = 0; i < size; i++) { 
		visited[i] = false; 
		stack[i] = false; 
	} 
  
    for (int i = 0; i < size; i++)
        if (hasCycleUtil(graph, i, visited, stack))
            return true;       
    
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