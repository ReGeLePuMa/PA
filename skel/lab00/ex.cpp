#include <bits/stdc++.h>

using namespace std;

#define N 100000000

static inline pair<int,int> maxim(pair<int,int> primu,pair<int,int> doi)
{
    return ((primu.first>doi.first) ? (primu) :(doi));
}

pair<int,int> prob(vector<pair<int,int>>& vect,int i,int j)
{
    if(i==j)
    {
        return vect[i];
    }
    int m=(i+j)/2;
    return maxim(prob(vect,i,m),prob(vect,m+1,j));
}

int main()
{
    srand(time(NULL));
    auto vect =new vector<pair<int,int>>(N);
    int x,n;
    for(int i=0;i<N;i++)
    {
        x=rand();
        vect->push_back(make_pair(x,i));
    }
    cout<<prob(*vect,0,N).second<<endl;
    delete vect;
    return 0;
}