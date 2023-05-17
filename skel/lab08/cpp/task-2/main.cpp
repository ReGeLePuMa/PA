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
            fin >> x >> y;  // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    vector<int> get_result()
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
        vector<int> all_cv;
        vector<int> visited(n + 1, 0);
        vector<int> parent(n + 1, 0);
        vector<int> low_link(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            if (parent[i] == 0)
            {
                parent[i] = i;
                dfs(i, visited, parent, low_link, timp, all_cv);
            }
        }

        return all_cv;
    }
    void dfs(int source, vector<int>& visited, vector<int>& parent,
             vector<int>& low_link, int& timp, vector<int>& sec)
    {
        visited[source] = ++timp;
        low_link[source] = visited[source];

        int copii = 0;
        for (const auto& i : adj[source])
        {
            if (parent[i] != 0)
            {
                if (i != parent[source])
                {
                    low_link[source] = min(low_link[source], visited[i]);
                }

                continue;
            }
            parent[i] = source;
            ++copii;
            dfs(i, visited, parent, low_link, timp, sec);
            low_link[source] = min(low_link[source], low_link[i]);
            if (parent[source] != source && low_link[i] >= visited[source])
            {
                sec.insert(sec.begin(), source);
            }
        }
        if (parent[source] == source && copii > 1)
        {
            sec.insert(sec.begin(), source);
        }
    }

    void print_output(const vector<int>& all_cvs)
    {
        ofstream fout("out");
        for (auto cv : all_cvs)
        {
            fout << cv << ' ';
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
