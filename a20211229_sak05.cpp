#include<bits/stdc++.h>
using namespace std; using ll = long long; using Pa=pair<ll,ll>; using LL=__int128_t; // vector<Pa> event; event.emplace_back(a,b);
using Vll=vector<ll>; using VVll=vector<Vll>;// VVll G(N+1,Vll(0));
void oi(){}template<class Head, class... Tail>void oi(Head&& head,Tail&&... tail){if(sizeof...(tail)!=0){cout<<head<<" ";} else{cout<<head<<"\n";}oi(move(tail)...);}
template<class t,class u> bool chmax(t&a,u b){if(a<b){a=b; return true;} else{return false;}} 
template<class t,class u> bool chmin(t&a,u b){if(b<a){a=b; return true;} else{return false;}} 
#define INF (ll)1<<60// 10^18 < 1<<60 = 1152921504606846976  //#define MOD (ll)998244353// #define MOD (ll)1000000007
#define FOR(i,a,b) for(ll i=(ll)(a); i<(ll)(b); i++)// a ~ b-1 i++ for   //#define FOR_(i,b,a)  for(ll i=(ll)(b)-1; (ll)(a); i--)//  b-1 ~ a i-- for
#define ALL(a) (a).begin(),(a).end() // min,max,sort,find,lower_bound
#define OI(...) oi(__VA_ARGS__)  //  printf("%8.10lf\n",(ans));   // <-改行しない場合は\nを消す
#define OIV(a) if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++) if((a)[i00]!=INF and i00!=(a).size()-1){cout<<(a)[i00]<<" ";} else if((a)[i00]==INF and i00!=(a).size()-1){cout<<"I ";} else if((a)[i00]!=INF and i00==(a).size()-1){cout<<(a)[i00]<<"\n";} else if((a)[i00]==INF and i00==(a).size()-1){cout<<"I\n";}}
#define OIVV(a)if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++){for(ll j00=0;j00<(a[i00]).size();j00++){if(j00!=(a)[i00].size()-1 and (a)[i00][j00]!=INF){cout<<a[i00][j00]<<" ";}else if(j00!=(a)[i00].size()-1 and (a)[i00][j00]==INF){cout<<"I ";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]!=INF){cout<<a[i00][j00]<<"\n";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]==INF){cout<<"I\n";}}}}

/*
どの分野に興味があるか診断&紹介
BFS

入力N,Mに対して
無向グラフが与えられる
頂点0からたどれる頂点を全て出力

初心者相手なので
Nを小さくして
今どこにいて，どの頂点視点に移動するのかも出力する

(DFS,UnionFindでも全く同じ問題をだして攻め方の違いを認識させる)
(解説でそれぞれのアルゴリズムの良さを押し出す，)
BFSは距離が近いものから確認していく
簡単な迷路などに用いられる

*/


int main(){
    ll N,M; cin>>N>>M;
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++){
        ll a,b; cin>>a>>b;// 0-indexed
        G[a].push_back(b);
        G[b].push_back(a);
    }
    
    vector<bool> A(N,false);// 0からたどれる true    たどれない false
    
    deque<ll> Q;
    Q.push_back(0);
    A[0]=true;

    while(!Q.empty()){// Qの中身がある限り続ける
        ll now=Q.front();
        Q.pop_front();
        for(ll u: G[now]){// nowからたどれる先をQに追加する
            if(A[u]==false){
                A[u]=true;
                cout<<u<<"を新たにQに追加しました!!!"<<"\n";
                Q.push_back(u);
            }
        }
    }
    

    for(ll i=0; i<N; i++){
        if(A[i]==true) cout<<i<<"\n";
    }
        

    return 0;
}

/*
入力
6 5
0 1
1 2
1 3
1 4
2 5

出力
1を新たにQに追加しました!!!
2を新たにQに追加しました!!!
3を新たにQに追加しました!!!
4を新たにQに追加しました!!!
5を新たにQに追加しました!!!
0
1
2
3
4
5


*/

