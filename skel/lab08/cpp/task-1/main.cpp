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
            fin >> x >> y;
            adj[x].push_back(y);  // arc (x, y)
        }
        fin.close();
    }

    vector<vector<int>> get_result()
    {
        //
        // TODO: Găsiți componentele tare conexe  (CTC / SCC) ale grafului
        // orientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind
        // un SCC (adică tot un vector).
        // * nodurile dintr-un SCC pot fi găsite în orice ordine
        // * SCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.
        //
        int timp = 0;
        vector<vector<int>> all_sccs;
        vector<int> visited(n + 1, 0);
        vector<int> parent(n + 1, 0);
        vector<int> low_link(n + 1, 0);
        vector<int> stiva;
        for (int i = 1; i <= n; i++)
        {
            if (parent[i] == 0)
            {
                parent[i] = i;
                dfs(i, visited, parent, low_link, stiva, timp, all_sccs);
            }
        }

        return all_sccs;
    }
    void dfs(int source, vector<int>& visited, vector<int>& parent,
             vector<int>& low_link, vector<int>& stiva, int& timp,
             vector<vector<int>>& sec)
    {
        visited[source] = ++timp;
        low_link[source] = visited[source];
        stiva.insert(stiva.begin(), source);

        for (const auto& i : adj[source])
        {
            if (parent[i] != 0)
            {
                if (count(stiva.begin(), stiva.end(), i) > 0)
                {
                    low_link[source] = min(low_link[source], visited[i]);
                }

                continue;
            }
            parent[i] = source;

            dfs(i, visited, parent, low_link, stiva, timp, sec);
            low_link[source] = min(low_link[source], low_link[i]);
        }

        if (low_link[source] == visited[source])
        {
            vector<int> new_stiva;
            int x;
            do
            {
                x = stiva.front();
                new_stiva.insert(new_stiva.begin(), x);
                stiva.erase(stiva.begin());
            } while (x != source);
            sec.push_back(new_stiva);
        }
    }
    void print_output(const vector<vector<int>>& all_sccs)
    {
        ofstream fout("out");
        fout << all_sccs.size() << '\n';
        for (const auto& scc : all_sccs)
        {
            for (auto node : scc)
            {
                fout << node << ' ';
            }
            fout << '\n';
        }
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
