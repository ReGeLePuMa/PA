#include <bits/stdc++.h>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }
    int get_value(int n, int x, int y) 
    {
       if(n==1)
       {
            if(x==1)
            {
                return (y==1) ? (1) : (2);
            }
            else return (y==1) ? (3) : (4);
       }
       int dim=(1<<n);
       int cons=(1<<(2*n-2));
       if(x<=(dim/2) && y<=(dim/2))
       {
            return get_value((--n),x,y);
       }
       else if(x<=(dim/2) && y>(dim/2))
       {
            return cons + get_value((--n),x,(y-(dim/2)));
       }
       else if(x>(dim/2) && y<=(dim/2))
       {
            return 2*cons + get_value((--n),(x-(dim/2)),y);
       }
       else if(x>(dim/2) && y>(dim/2))
       { 
            return 3*cons + get_value((--n),(x-(dim/2)),(y-(dim/2)));
       }
       else return -1;
    }

    int get_result() { return get_value(n, x, y); }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
