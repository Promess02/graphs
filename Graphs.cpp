#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct edge {
    int s;
    int t;
};

class Graph {

private:

    int** adjMatrix;
    int n;                              // the amount of nodes
    bool directed;              //true - directed graph, false - undirected graph

    int step = 1;
    //printing the graph using depth first search algorithm
    void dfs(int s, bool* visited, int* d, int* f) {
        visited[s] = true;
        d[s] = step;
        step++;
        for (int j = 0; j < n; j++)// potential neighbours
            if (adjMatrix[s][j] == 1) {
                if (visited[j] == false) {
                    dfs(j, visited, d, f);
                    cout << " " << j;
                }
            }
        f[s] = step;
        step++;
    }

public:
    //constructor where n-amount of nodes, m-amount of edges, edges[]- array of edges, directed - true if directed else undirected
    Graph(int n, int m, edge edges[], bool directed) {
        //creating an adjency matrix
        this->n = n;
        adjMatrix = new int* [n];
        for (int i = 0; i < n; i++)
            adjMatrix[i] = new int[n];

        //initializing the matrix with zeros
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;

        this->directed = directed;
        //filling the adjency matrix using the edges array
        for (int i = 0; i < m; i++)
            adjMatrix[edges[i].s][edges[i].t] = 1;
        //if the graph is undirected the order of the vertices is not important
        if (!directed) {
            for (int i = 0; i < m; i++)
                adjMatrix[edges[i].t][edges[i].s] = 1;
        }
    }

    //checks if the graph is connected in bfs and dfs
    bool is_connected(bool* visited, int n) {
        for (int i = 0; i < n; i++)
            if (visited[i] == false) return false;
        return true;
    }
    // navigates through all nodes of a graph and prints them using breadth first search
    //returns true if the graph is connected else false
    bool bfs(int s) {
        bool* visited = new bool[n];
        for (int i = 0; i < n; i++)
            visited[i] = false;

        queue<int> FIFO;
        visited[s] = true;
        FIFO.push(s);

        while (!FIFO.empty()) {
            int u = FIFO.front();
            FIFO.pop();

            for (int j = 0; j < n; j++)//potencial neighbours
                if (adjMatrix[u][j] == 1) {
                    if (visited[j] == false) {
                        visited[j] = true;
                        FIFO.push(j);
                        cout << " " << j;
                    }
                }
        }
        cout << endl;
        return is_connected(visited, n);
    }

    // navigates through all nodes of a graph and prints them using depth first search
    //returns true if the graph is connected else false
    bool dfs(int s) {

        bool* visited = new bool[n];
        for (int i = 0; i < n; i++)
            visited[i] = false;

        int* d = new int[n];
        int* f = new int[n];

        // using the private dfs with the arrays initialized here
        dfs(s, visited, d, f);
        step = 1;
        cout << endl;
        return is_connected(visited, n);

    }


    //operator << overloading for printing a graph object
    friend ostream& operator<<(ostream& out, Graph& g) {
        g.bfs(0);
    }

    ~Graph() {};

};

struct weightedEdge {
    int s;
    int t;
    double w;        //the edge weight

};

class WeightedGraph {

private:

    double** adjWeightMatrix;
    int n;                //the amount of nodes
    bool directed;

public:

    //creates a weighted graph from the weighted edges array
    WeightedGraph(int n, int m, weightedEdge edges[], bool directed) {

        this->n = n;
        adjWeightMatrix = new double* [n];
        for (int i = 0; i < n; i++)
            adjWeightMatrix[i] = new double[n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjWeightMatrix[i][j] = DBL_MAX;

        this->directed = directed;
        for (int i = 0; i < m; i++)
            adjWeightMatrix[edges[i].s][edges[i].t] = edges[i].w;
        if (!directed) {
            for (int i = 0; i < m; i++)
                adjWeightMatrix[edges[i].t][edges[i].s] = edges[i].w;
        }
    }

    //finding the shortest paths from a given node to all other nodes in a weighted graph
    void Dijkstra(int s) {
        double* d = new double[n];
        int* S = new int[n];
        int* parent = new int[n];

        //initializing tables
        for (int i = 0; i < n; i++) {
            d[i] = DBL_MAX;
            S[i] = false;
            parent[i] = -1;
        }

        d[s] = 0;
        for (int i = 0; i < n; i++) {
            double min_weight = DBL_MAX;
            int index_min = 0;

            for (int j = 0; j < n; j++) {
                if (d[j] < min_weight && S[j] == false) {
                    min_weight = d[j];
                    index_min = j;
                }
            } //find()
            int u = index_min;
            S[u] = true;
            for (int j = 0; j < n; j++)//potential neighbours
            {
                if (adjWeightMatrix[u][j] != DBL_MAX)
                    if (d[j] > d[u] + adjWeightMatrix[u][j]) {
                        d[j] = d[u] + adjWeightMatrix[u][j];
                        parent[j] = u;
                    }
            }
        }
        cout << "Dijsktra algorithm arrays: " << endl;
        cout << "d[] = ";

        for (int i = 0; i < n; i++)
            cout << d[i] << " ";

        cout << endl;
        cout << "S[] = ";

        for (int i = 0; i < n; i++)
            cout << S[i] << " ";

        cout << endl;
        cout << "parent[] = ";

        for (int i = 0; i < n; i++)
            cout << parent[i] << " ";
        cout << endl;
    }

    //finds and prints the shortest parth from s node to t node using Dijkstras algorithm
    void DijkstraPath(int s, int t) {
        double* d = new double[n];

        int* S = new int[n];

        int* parent = new int[n];

        //initializing arrays
        for (int i = 0; i < n; i++) {

            d[i] = DBL_MAX;

            S[i] = false;

            parent[i] = -1;

        }

        d[s] = 0;

        for (int i = 0; i < n; i++) {

            double min_weight = DBL_MAX;

            int index_min = 0;

            for (int j = 0; j < n; j++) {
                if (d[j] < min_weight && S[j] == false) {

                    min_weight = d[j];
                    index_min = j;
                }
            } //find()

            int u = index_min;

            S[u] = true;

            for (int j = 0; j < n; j++)//potential neighbours
            {

                if (adjWeightMatrix[u][j] != DBL_MAX)
                    if (d[j] > d[u] + adjWeightMatrix[u][j]) {
                        d[j] = d[u] + adjWeightMatrix[u][j];
                        parent[j] = u;
                    }
            }
        }
        cout << "Shortest path from " << s << " to " << t << " has the weight sum = " << d[t] << endl;
        vector<int> list;
        while (t != s) {
            list.push_back(t);
            t = parent[t];
        }
        list.push_back(s);
        cout << "Shortest Path: ";
        for (int i = list.size() - 1; i >= 0; i--) {
            cout << list.at(i) << " ";
        }
        cout << endl;

    }

    //Floyd Warshall algorithm used to find the shortest path from each node to any other node in a graph
    //Stores the result in a matrix
    void FloydWarshall() {
        double** d = new double* [n];
        for (int i = 0; i < n; i++)
            d[i] = new double[n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = DBL_MAX;


        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][j] = adjWeightMatrix[i][j];

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                d[i][i] = 0;

        cout << "Matrix of FLoyd-Warshall shortest paths" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (d[i][j] != DBL_MAX)
                    cout << i << " " << j << ": " << d[i][j] << ", ";
            cout << endl;
        }
    }

    //overloaded operator << for weighted graph
    friend ostream& operator<<(ostream& out, WeightedGraph& g);

    ~WeightedGraph() {};

};


int main() {

    int n = 10, m = 17;

    edge directedGraph[] = { {0,1},{1,2},{1,7},{2,8},{2,3},{3,2},{3,9},{9,8},{8,5},{5,8},{8,7},{7,1},{7,4},{4,0},{7,6}, {6,7},{6,0} };  //example graph

    Graph g(n, m, directedGraph, true);
    cout << "directed graph: " << endl;
    cout << "bfs: " << endl;
    if (g.bfs(0)) cout << "graph connected according to bfs()" << endl;
    else cout << "graph not connected according to bfs()" << endl;

    cout << "dfs: " << endl;
    if (g.dfs(0)) cout << "graph connected according to dfs()" << endl;
    else cout << "graph not connected according to dfs()" << endl;

    n = 10; m = 19;

    weightedEdge directedWeightedGraph[] = { {0,1,5},{1,2,2},{1,7,3},{2,8,6},{2,3,7},{3,2,7},{3,9,5},{9,8,4},{8,5,5},{5,8,5},{5,3,2}, {8,7,1},{7,8,1}, {7,1,3},{7,4,1},{4,0,2},{7,6,5}, {6,7,5},{6,0,5} };
    weightedEdge graph2[] = { {0,1,3},{1,2,2},{0,4,1}, {2,4,4},{2,3,2},{3,4,1},{4,1,1},{4,5,4},{5,0,3} };
    WeightedGraph h(n, m, directedWeightedGraph, true);
    WeightedGraph f(6, 9, graph2, true);

    cout << "Directed weighted graph: " << endl;
    h.Dijkstra(0);
    h.DijkstraPath(3, 5); //finding shortest path from node 3 to 5 in a weighted graph
    f.FloydWarshall();

}
