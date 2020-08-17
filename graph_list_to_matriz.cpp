#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int size = 10;

//cria uma matriz de adjacência
int matrix[size][size] = {};

//cria a estrututa de uma aresta com vertice origem e destino
struct edge {
	int src, dst;
};

//cria a estrutura do grafo 
class Graph {
public:
    //cria uma lista de adjacências
	vector<vector<int>> list_adj;

    //construtor do grafo
	Graph(vector<edge> const &edges, int size){
        
        //define tamanho da lista
		list_adj.resize(size);

        //para cada aresta, preenche a lista de adjacências com vertices origem e destino
		for (auto &edge: edges){
			list_adj[edge.src].push_back(edge.dst);
			list_adj[edge.dst].push_back(edge.src);
		}
	}
};

void BFS(Graph const &graph, int v, int size){
    //cria um vetor auxiliar para guardar se cada vertice foi visitado
	vector<bool> visited(size);
    //cria uma pilha auxiliar para armazenar os vertices visitados
	queue<int> q;

    //preenche o primeiro vertice como visitado
	visited[v] = true, 
    //adiciona o primeiro vertice na pilha
	q.push(v);

    //enquanto a pilha não estiver vazia
	while (!q.empty()){
        //armazena o primeiro da pilha em "v"
		v = q.front();
        //retira o primeiro vertice da pilha
		q.pop();

        //para cada vertice da lista de adjacência de "v"
		for (int u : graph.list_adj[v]){
            //se o vertice nao foi visitado ainda
			if (!visited[u]){
                //visita "u"
				visited[u] = true;
                //coloca "u" na pilha
				q.push(u);
                //marca a adjacência na matriz
                matrix[u][v] = matrix[v][u] = 1;
            }      
        }
	}
}

int main(){
	vector<edge> edges = {
		{1, 2}, {2, 3}, {2, 8}, {3, 4}, {4, 6}, {5, 7},
		{5, 9}, {8, 9}, {8, 4}, {2,4}
	};

	Graph graph(edges, size);

    BFS(graph, 1, size);

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++){
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    } 

	return 0;
}