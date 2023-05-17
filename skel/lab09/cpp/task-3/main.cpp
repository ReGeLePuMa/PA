#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 50005

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// structura folosita pentru a stoca distanta, vectorul de parinti
// si daca s-a intalnit un ciclu de cost negativ folosind algoritmul
// Bellman-Ford
struct BellmanFordResult
{
    bool has_cycle;
    vector<int> d;
    vector<int> p;

    BellmanFordResult(bool has_cycle, const vector<int>& d,
                      const vector<int>& p)
        : has_cycle(has_cycle), d(d), p(p)
    {
    }
};

struct Edge
{
    int node;
    int neigh;
    int w;

    Edge() {}
    Edge(int node, int neigh, int w) : node(node), neigh(neigh), w(w) {}
};

class Task
{
 public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

 private:
    // n = numar de noduri, m = numar de muchii
    int n, m;
    // adj[node] = lista de adiacenta a nodului node
    // perechea (neigh, w) semnifica arc de la node la neigh de cost w
    vector<pair<int, int>> adj[NMAX];
    // nodul sursa
    int source;

    void read_input()
    {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++)
        {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
        }
        fin.close();
    }

    BellmanFordResult get_result()
    {
        //
        // TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        // folosind Bellman-Ford pe graful orientat cu n noduri, m arce stocat
        // in adj.
        //     d[node] = costul minim / lungimea minima a unui drum de la source
        //     la nodul
        // node;
        //     d[source] = 0;
        //     d[node] = -1, daca nu se poate ajunge de la source la node.
        //
        // Atentie:
        // O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
        //     adj[node][i] == (neigh, w) - unde neigh este al i-lea vecin al
        //     lui node, iar (node, neigh) are cost w.
        //
        // In cazul in care exista ciclu de cost negativ, returnati un obiect de
        // tipul
        //  BellmanFordResult cu campul has_cycle setat pe true si doi vectori
        //  fara elemente;
        //
        struct compare
        {
            bool operator()(const pair<int, int>& lhs,
                            const pair<int, int>& rhs)
            {
                return lhs.first > rhs.first;
            }
        };
        vector<int> d(n + 1, INF);
        vector<bool> visited(n + 1, false);
        vector<int> actualizari(n + 1, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare>
            coada_calului;
        coada_calului.emplace(d[source], source);
        visited[source] = true;
        d[source] = 0;
        actualizari[source]++;
        while (!coada_calului.empty())
        {
            const auto [dist, node] = coada_calului.top();
            visited[node] = false;
            coada_calului.pop();
            for (const auto& [capat, cost] : adj[node])
            {
                if (d[node] + cost < d[capat])
                {
                    d[capat] = d[node] + cost;
                    actualizari[capat]++;
                    if (actualizari[capat] >= n * m)
                    {
                        return {true, {}, {}};
                    }
                    if (visited[capat] == false)
                    {
                        visited[capat] = true;
                        coada_calului.emplace(d[capat], capat);
                    }
                }
            }
        }
        for_each(d.begin() + 1, d.end(), [](int& x) {
            if (x == INF)
            {
                x = -1;
            }
        });
        return {false, d, {}};
    }

    void print_output(const BellmanFordResult& result)
    {
        ofstream fout("out");
        const auto& has_cycle = result.has_cycle;
        const auto& d = result.d;
        if (has_cycle)
        {
            fout << "Ciclu negativ!\n";
        }
        else
        {
            for (int node = 1; node <= n; node++)
            {
                fout << d[node] << ' ';
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
