#include <bits/stdc++.h>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    string expr;

    void read_input() {
        ifstream fin("in");
        fin >> n >> expr;
        expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
        fin.close();
    }

    int get_result() {
        // Calculati numarul de parantezari ale expresiei date astfel incat
        // rezultatul sa dea true si returnati restul impartirii numarului
        // la 10^9 + 7 (vezi macro-ul MOD).
    int F[n][n], T[n][n];
    string oper = "|&^";
 
    // Fill diagonal entries first
    // All diagonal entries in
    // T[i][i] are 1 if exprol[i]
    // is T (true).  Similarly,
    // all F[i][i] entries are 1 if
    // symbol[i] is F (False)
    for (int i = 0; i < n; i++) {
        F[i][i] = (expr[i] == 'F') ? 1 : 0;
        T[i][i] = (expr[i] == 'T') ? 1 : 0;
    }
 
    // Now fill T[i][i+1],
    // T[i][i+2], T[i][i+3]... in order
    // And F[i][i+1], F[i][i+2],
    // F[i][i+3]... in order
    for (int gap = 1; gap < n; ++gap)
    {
        for (int i = 0, j = gap;
             j < n; ++i, ++j)
        {
            T[i][j] = F[i][j] = 0;
            for (int g = 0;
                 g < gap; g++)
            {
                // Find place of parenthesization using
                // current value of gap
                int k = i + g;
 
                // Store Total[i][k]
                // and Total[k+1][j]
                int tik = T[i][k] + F[i][k];
                int tkj = T[k + 1][j]
                  + F[k + 1][j];
 
                // Follow the recursive formulas
                // according
                // to the current operator
                if (oper[k] == '&') {
                    T[i][j] += T[i][k]
                            * T[k + 1][j];
                    F[i][j] += (tik * tkj
                                - T[i][k]
                                * T[k + 1][j]);
                }
                if (oper[k] == '|') {
                    F[i][j] += F[i][k]
                      * F[k + 1][j];
                    T[i][j] += (tik * tkj
                                - F[i][k]
                                * F[k + 1][j]);
                }
                if (oper[k] == '^') {
                    T[i][j] += F[i][k]
                      * T[k + 1][j]
                      + T[i][k]
                      * F[k + 1][j];
                    F[i][j] += T[i][k]
                            * T[k + 1][j]
                            + F[i][k] * F[k + 1][j];
                }
            }
        }
    }
    return T[0][n - 1];
    
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
