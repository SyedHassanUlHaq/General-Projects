#include<bits/stdc++.h>

using namespace std;
using namespace chrono;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

// class structure for Disjoint Set Union
class DSU{
  vector<ll> par,rank;
public:
  // Constructor call ot initialize the par (parent) and rank arrays
  DSU(ll n)
  {
    par.resize(n + 1, 0);
    rank.resize(n + 1, 1);
    for(ll i = 1; i <= n; i++) par[i] = i;
  }

  // Function call to check for the parent
  ll findPar(ll x)
  {
    if(x == par[x]) return x;
    return par[x] = findPar(par[x]);
  }\


  // Merge the parents of two given nodes w.r.t to the weight
  ll merge(ll a, ll b, ll w)
  {
    a = findPar(a);
    b = findPar(b);
    if(a == b) return 0;
    ll x = (rank[a] * rank[b] * w);
    if(rank[a] <= rank[b]) {
      par[a] = b;
      rank[b] += rank[a];
    }
    else{
      par[b] = a;
      rank[a] += rank[b];
    }
    return x;
  }
};

struct Edge{
  ll u,v,weight;
  bool operator<(Edge const& other){
    return weight > other.weight;
  }
};


void solve() {
  cout << "Enter the number of edges : ";
  ll n;
  cin >> n;
  vector<Edge> adj,res;
  ll mx = INT_MIN, mn = INT_MAX;
  for(ll i = 0; i < n; i++)
  {
    cout << "Enter the two nodes between which the edge shall be present along with the weight of the edge : ";
    ll a, b, w;
    cin>> a >> b >> w;
    Edge e;
    e.u = a;
    e.v = b;
    e.weight = w;
    mx = max(mx, max(a, b));
    mn = min(mn, min(a, b));
    adj.push_back(e);  // pushing structure of type Edge in to the adjacency list
  }

  DSU dsu = DSU(mx);   // creating the DSU
  sort(adj.begin(),adj.end());
  //for(auto&x:adj) cout<<x.u<<" "<<x.v<<" "<<x.weight<<endl;

  ll sm = 0; // sum of the minimum weight edges of the MST
  for(auto&e : adj) {
    ll s = dsu.merge(e.u, e.v, e.weight);
    sm += s;
    // cout<<s<<endl;
  }
  cout << "Weight of the minimum spanning tree is : " << sm << endl;
}

int main() {
  fastio();   // fast input and output
  solve();
}
