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
DP

a(0)=0
a(n)=2*a(n-1)+1 (n>=1)
についてn<=Nまで解く

漸化式に興味があれば興味アリ
DPの入り口
*/

int main(){
    ll N; cin>>N;
    vector<ll> A(N);
    A[0]=0;
    for(ll n=1; n<=N; n++){
        A[n]=2*A[n-1]+1;
    }

    for(ll i=0; i<=N; i++){
        cout<<i<<" "<<A[i]<<"\n";
    }
    return 0;
}

/*
10
0 0
1 1 
2 3 
3 7 
4 15
5 31   
6 63   
7 127  
8 255  
9 511  
10 1023

一般解2^n -1と照らし合わせる
*/
