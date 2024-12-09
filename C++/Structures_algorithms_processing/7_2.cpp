#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 

//using namespace std;

struct Edge {//структура для хранения ребра
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

bool compare_edges(const Edge& a, const Edge& b) {//функция для сравнения ребер для сортировки по весу
    return a.weight < b.weight;
}

class UnionFind {//система непересек множеств
private:
    std::vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);//массив для род узлов
        rank.resize(n, 0);//массив рангов с нулями
        for (int i = 0; i < n; ++i) {
            parent[i] = i;//каждый узел - себе сам родитель
        }
    }

    int find(int x) {
        if (parent[x] != x) {//рекурсия
            parent[x] = find(parent[x]);
        }
        return parent[x];//корень множества
    }

    void Union(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x != root_y) {//обьединяем множества
            if (rank[root_x] > rank[root_y]) {
                parent[root_y] = root_x;
            }
            else if (rank[root_x] < rank[root_y]) {
                parent[root_x] = root_y;
            }
            else {
                parent[root_y] = root_x;//увелич его ранг
                rank[root_x]++;
            }
        }
    }
};

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    std::cout << "original graph:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(3) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void kruskal(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();//колво узлов в графе
    std::vector<Edge> edges;//вектор для хранения ребер

    for (int i = 0; i < n; ++i) {// извлечение ребер из матрицы смежности
        for (int j = i + 1; j < n; ++j) {//ток верхний треуг матрицы
            if (matrix[i][j] != 0) {
                edges.emplace_back(i, j, matrix[i][j]);
            }
        }
    }

    sort(edges.begin(), edges.end(), compare_edges);//сортировка по веса

    UnionFind uf(n);
    std::vector<Edge> minimum_ostovnoe_tree;
    int minimum_ostovnoe_tree_weight = 0;
    std::vector<Edge> edges_not_included;

    for (const auto& edge : edges) {//по cорт ребрам
        if (uf.find(edge.u) != uf.find(edge.v)) {//если не цикл
            minimum_ostovnoe_tree.push_back(edge);//добав ребро в мод
            minimum_ostovnoe_tree_weight += edge.weight;
            uf.Union(edge.u, edge.v);//обьединяем два множества

            if (minimum_ostovnoe_tree.size() == n - 1) {
                break;
            }
        }
        else {
            edges_not_included.push_back(edge);//не вход в мод
        }
    }

    print_matrix(matrix);

    std::cout << "\n\nedges minimum ostovnoe tree:\n";
    for (const auto& edge : minimum_ostovnoe_tree) {
        std::cout << edge.u + 1 << " - " << edge.v + 1 << " : " << edge.weight << std::endl;
    }
    std::cout << "\ntotal all weight: " << minimum_ostovnoe_tree_weight << std::endl;

    std::cout << "\nnumber of edges in the minimum ostovnoe tree: " << minimum_ostovnoe_tree.size() << std::endl;

    std::cout << "\nedges are not included in minimum ostovnoe tree:\n";
    for (const auto& edge : edges_not_included) {
        std::cout << edge.u + 1 << " - " << edge.v + 1 << " : " << edge.weight << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 20, 0, 0, 0, 23, 1},
        {20, 0, 15, 0, 0, 0, 4},
        {0, 15, 0, 3, 0, 0, 9},
        {0, 4, 3, 0, 17, 0, 16},
        {0, 0, 0, 17, 0, 28, 25},
        {23, 0, 0, 0, 28, 0, 36},
        {1, 4, 9, 16, 25, 36, 0}
    };

    kruskal(matrix);

    return 0;
}
