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

// retorna verdadeiro/falso para grafo bibartido
bool isBipartite(Graph const &graph, int v, int size){
    //cria um vetor auxiliar para guardar se cada vertice foi visitado
	vector<bool> visited(size);
    //cria um vetor auxiliar para armazenar o nível dos vertices
	vector<int> level(size);
    //cria uma pilha auxiliar para armazenar os vertices visitados
	queue<int> q;

    //preenche o primeiro vertice como visitado e nível 0
	visited[v] = true, level[v] = 0;
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
                //atribui o nivel de "u" ao nível do seu adjacente "v" + 1
				level[u] = level[v] + 1;
                //coloca "u" na pilha
				q.push(u);
            }
            // se o nível de "u" for igual ao de "v", signifca que existe uma ligação entre
            //vertices do mesmo conjunto, deixando o grafo nao-bipartido.
			else if (level[v] == level[u])
                return false;          
        }
	}
    //se a funcao nao retornou "false" ate aqui: grafo bipartido, retorna verdadeiro.
	return true;
}

int main()
{
	vector<edge> edges = {
		{1, 2}, {2, 3}, {2, 8}, {3, 4}, {4, 6}, {5, 7},
		{5, 9}, {8, 9}, {8, 4}, {2,4}
	};

	int size = 10;

	Graph graph(edges, size);

	if (isBipartite(graph, 1, size))
		cout << "Bipartite Graph\n";
	else
		cout << "Not-Bipartite Graph\n";

	return 0;
}