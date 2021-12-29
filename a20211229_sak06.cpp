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
Union Find

入力N,Mに対して
無向グラフが与えられる
頂点0からたどれる頂点を全て出力

初心者相手なので
Nを小さくして
今どこにいて，どの頂点視点に移動するのかも出力する

(DFS,UnionFindでも全く同じ問題をだして攻め方の違いを認識させる)
(解説でそれぞれのアルゴリズムの良さを押し出す，)
UnionFindは仲間をすべて塊として認識する
仲間分けなどに用いられる

*/

class UnionFind{ 

public:
    Vll par,saizu; // par[i]:iの親の番号　(例) par[3] = 2 なら3の親が2

    UnionFind(ll N) : par(N),saizu(N,1) {// [0~N)の数字について，仲間かどうか構築する 最初は全てが根であるとして初期化,サイズは最初自分自身なので1
        FOR(i,0,N) {
            par[i] = i;//自分自身が親が初期値
        }
    }

    ll root(ll x){ // データxが属する木の根を再帰で得る：root(x) = {xの木の根} 
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(ll x, ll y){  // xとyの木を併合
        ll rx = root(x); //xの根をrx
        ll ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        if(saizu[rx]<saizu[ry]) {
            swap(rx,ry);// 主幹を値が大きい方:xとする
        }
        par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：yの根ryをxの根rxにつける
        saizu[rx] += saizu[ry];// 木の直径より，これを持っておいて渡すほうが速い
        return;
    }

    bool same(ll x, ll y){ // 2つのデータx, yが属する木が同じならtrueを返す
        if(root(x)==root(y)) return true;
        else return false;
    }

    ll size(ll x){
        return saizu[root(x)];
    }

};


int main(){
    ll N,M; cin>>N>>M;

    UnionFind uf(N);// ufというUnionFindを備えたモノ
    for(ll i=0; i<M; i++){
        ll a,b; cin>>a>>b;// 0-indexed
        cout<<a<<"と"<<b<<"は仲間になりました"<<"\n";
        uf.unite(a,b);
    }
    
    
    for(ll i=0; i<N; i++){// 仲間のうち一番数が小さいものが0であるかどうか
        if(uf.root(i)==0){
            cout<<i<<"\n";
        }
    }
        

    return 0;
}

/*
入力
6 5
0 1
0と1は仲間になりました
1 2
1と2は仲間になりました
1 3
1と3は仲間になりました
1 4
1と4は仲間になりました
2 5
2と5は仲間になりました

出力
0
1
2
3
4
5


*/

