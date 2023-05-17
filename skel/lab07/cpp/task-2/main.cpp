#include <bits/stdc++.h>
using namespace std;

class Task
{
 public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

 private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5;  // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    void read_input()
    {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++)
        {
            fin >> x >> y;  // arc (x, y)
            adj[x].push_back(y);
        }
        fin.close();
    }

    deque<int> get_result()
    {
        // TODO: Faceti sortarea topologica a grafului stocat cu liste de
        // adiacenta din adj.
        // *******
        // ATENTIE: nodurile sunt indexate de la 1 la n.
        // *******
        deque<int> topsort;
        vector<bool> visited(n + 1, false);
        while (isfalse(visited))
        {
            int source = 0;
            for (int i = 1; i <= n; i++)
            {
                if (!visited[i])
                {
                    source = i;
                    break;
                }
            }
            if (source != 0)
            {
                dfs(source, visited, topsort);
            }
            else
                break;
        }
        return topsort;
    }

    void dfs(int source, vector<bool>& visited, deque<int>& topsort,
             int time = 0)
    {
        visited[source] = true;
        for (const auto& i : adj[source])
        {
            if (!visited[i])
            {
                dfs(i, visited, topsort, ++time);
            }
        }
        topsort.push_front(source);
    }
    bool isfalse(const vector<bool>& v)
    {
        for (const auto& i : v)
        {
            if (!i)
            {
                return true;
            }
        }
        return false;
    }

    void print_output(const deque<int>& topsort)
    {
        ofstream fout("out");
        for (auto node : topsort)
        {
            fout << node << ' ';
        }
        fout << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main()
{
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task();  // hint: cppreference/nothrow
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
