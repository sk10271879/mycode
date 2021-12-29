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
二分探索

入力N (1<=N<=100)に対して
謎の整数a (1<=a<=1024)
a=(N*2530831+103519)%1024 +1

をYes Noで答えられる質問10回以内で特定せよ
二分探索の入り口

*/

bool is_small(ll x, ll a){
    if(x<=a) return true;
    return false;
}

int main(){// 適当な数aを当てよう
    // Yes Noで答えられる質問のみ 質問回数は10回まで
    ll N; cin>>N;
    // 謎の数 a 1~1024の値をとる
    ll a=(N*2530831+103519)%1024 +1;

    ll kaisu=0;
    ll ok=1, ng=1025;// ok<=x<ngの範囲 やがてaを特定する
    cout<<"質問回数"<<" 特定範囲"<<"\n";
    while(ok+1 < ng){//ok +1==ngなら終了
        kaisu +=1;
        ll x = (ok + ng)/2;
        // 求める値a a<=xならtrue
        if(is_small(x,a)) ok = x; // ok-------x---a----ng なのでokをxにする
        else ng = x;              // ok---a---x--------ng なのでngをxにする
        cout<<kaisu<<" "<<ok<<" "<<ng<<"\n";
    }
    cout<<"質問回数 "<<kaisu<<"でaを特定しました!! a= "<<ok<<"\n";
    // gnuplot
    // plot "a72.dat" u 1:2 ps 3 pointtype 7
    // rep "a72.dat" u 1:3 ps 3 pointtype 7
    
    
    return 0;
}


/*
N=69
質問回数 特定範囲
1 513 1025
2 513 769
3 513 641
4 577 641
5 609 641
6 609 625
7 617 625
8 617 621
9 619 621
10 619 620
質問回数 10でaを特定しました!! a= 619
*/

