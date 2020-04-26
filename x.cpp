/*
 * first lets remove all the right nodes the can not be reached by any left node 
 * now we notice that a left node reach contiguous range of right endpoints , this is because the roads don't intersect 
 * then if we know how find the lowest & highest right nodes that can be reached from left node i -> ans of node i is the number of nodes in this intervial 
 * lets find SCCs and compress them , now the resulting graph is a DAG 
 * using Dp on DAG we can find the previous two values 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int n , m , x1 , x2 ;
vpi ord , ret ; 
vi v[300009] , g[300009] ; 
int x[300009] , y[300009] , Left [300009] , Right [300009] , l[300009] , r[300009] , ans [300009] ;
void add_edge ( int a , int b ) {
	v [a] .pb ( b ) ;
}
// SCC
stack < int > st ;
int low[300009] , disc[300009] , in_stack[300009] , Scc[300009] , timer = 1 , CrntScc ;
void dfs ( int node ) {
	disc [ node ] = low [ node ] = timer ++ ;
	st .push ( node ) ;
	in_stack [ node ] = 1 ;
	for ( auto u : v [node] ) {
		if ( !disc [ u ] ) dfs ( u ) ;
		if ( in_stack [u] ) low [node] = min ( low [node] , low [u] ) ;
	}
	if ( low [node] == disc [node] ) {
		while ( 1 ) {
			int u =st .top () ;
			in_stack [u] = 0  ;
			Scc [u] = CrntScc ;
			st .pop () ;
			if ( u == node ) break ; 
		}
		CrntScc ++ ;
	}
}
// DP
int dpl[300009] , dpr[300009] ;
int calcl ( int node ) {
	int &ret = dpl [node] ;
	if ( ret != -1 ) return ret ;
	ret = l[node] ;
	for ( auto u : g[node] ) {
		ret = min ( ret , calcl ( u ) ) ;
	}
	return ret ;
}
int calcr ( int node ) {
 	int &ret = dpr [node] ;
	if ( ret != -1 ) return ret ;
	ret = r[node] ;
	for ( auto u : g[node] ) {
		ret = max ( ret , calcr ( u ) ) ;
	}
	return ret ;
}
int val ( int l , int r ) {
	if ( l == 1e9+9 || r == -1e9 ) return 0;
	int R = r , L = l ;
	r = lb ( ord.begin() , ord.end() , mp ( r , -1 ) ) - ord.begin() ; 
	l = lb ( ord.begin() , ord.end() , mp ( l , -1 ) ) - ord.begin() ;
	return r - l + 1 ;
}
int done [300009] ;
void mark ( int node ) {
	done [ node ] = 1 ;
	for ( auto u : v[node] ) {
		if ( done[u] ) C ;
		mark ( u ) ;
	}
}
int main () {
	mem ( dpl , -1 ) ;
	mem ( dpr , -1 ) ;
	scanf("%d%d%d%d",&n,&m,&x2,&x1) , x1 = 0 ;
	for ( int i = 0 ; i < n ; i ++ ) {
		scanf("%d%d",&x[i],&y[i]);
		Left [i] = ( x[i] == x1 ) ;
		Right[i] = ( x[i] == x2 ) ;
		if ( Left  [i] ) ret .pb ( { y[i] , i } ) ;
	}
	for ( int i = 0 ; i < m ; i ++ ) {
		int a , b , t ;
		scanf("%d%d%d",&a,&b,&t);
		a -- , b -- , t -- ;
		add_edge ( a , b ) ;
		if ( t ) add_edge ( b , a ) ;
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( Left [i] ) {
			mark ( i ) ;
		}
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( done [i] && Right [i] ) {
			ord .pb ( { y[i] , i } ) ;
		}
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( ! disc [i] ) dfs ( i ) ;
	}
	sort ( ord.begin() , ord.end() ) ;
	for ( int i = 0 ; i < n ; i ++ ) {
		for ( auto j : v[i] ) {
			int U = Scc[i] ;
			int V = Scc[j] ;
			if ( U == V ) C ;
			g [U] .pb ( V ) ;
		}
	}
	for ( int i = 0 ; i < CrntScc ; i ++ ) {
		l [i] = 1e9+9 ;
		r [i] = -1e9 ;
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( Right [i] ) {
			l [ Scc[i] ] = min ( l [ Scc[i] ] , y [i] ) ;
			r [ Scc[i] ] = max ( r [ Scc[i] ] , y [i] ) ;
		}
	}
	for ( int i = 0 ; i < n ; i ++ ) {
		if ( Left [i] ) {
			ans [i] = val ( calcl ( Scc[i] ) , calcr ( Scc[i] ) ) ;
		}
	}
	sort ( ret.begin() , ret.end() ) ;
	reverse ( ret.begin() , ret.end() ) ;
	for ( auto u : ret ) printf("%d\n",ans[u.se]) ;
}
