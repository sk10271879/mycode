#include<bits/stdc++.h>
using namespace std; using ll = long long; using Pa=pair<ll,ll>; using Vll=vector<ll>; using VVll=vector<Vll>;// VVll G(N+1,Vll(0)); // vector<Pa> event; event.emplace_back(a,b);
template<class t,class u> bool chmax(t&a,u b){if(a<b){a=b; return true;} else{return false;}} template<class t,class u> bool chmin(t&a,u b){if(b<a){a=b; return true;} else{return false;}} 
void oi(){}template<class Head, class... Tail>void oi(Head&& head,Tail&&... tail){if(sizeof...(tail)!=0){cerr<<head<<" ";} else{cerr<<head<<"\n";}oi(move(tail)...);} void OI(){}template<class Head, class... Tail>void OI(Head&& head,Tail&&... tail){if(sizeof...(tail)!=0){cout<<head<<" ";} else{cout<<head<<"\n";}OI(move(tail)...);}
#define INF (ll)1<<60// 10^18 < 1<<60 = 1152921504606846976  #define MOD (ll)1000000007
#define FOR(i,a,b) for(ll i=(ll)(a); i<(ll)(b); i++)// a ~ b-1 i++ 
#define ALL(a) (a).begin(),(a).end() // printf("%8.10lf\n",(ans)); 
#define OIV(a) if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++) if((a)[i00]!=INF and i00!=(a).size()-1){cout<<(a)[i00]<<" ";} else if((a)[i00]==INF and i00!=(a).size()-1){cerr<<"I ";} else if((a)[i00]!=INF and i00==(a).size()-1){cerr<<(a)[i00]<<"\n";} else if((a)[i00]==INF and i00==(a).size()-1){cerr<<"I\n";}}
#define OIVV(a)if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++){for(ll j00=0;j00<(a[i00]).size();j00++){if(j00!=(a)[i00].size()-1 and (a)[i00][j00]!=INF){cerr<<a[i00][j00]<<" ";}else if(j00!=(a)[i00].size()-1 and (a)[i00][j00]==INF){cerr<<"I ";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]!=INF){cerr<<a[i00][j00]<<"\n";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]==INF){cerr<<"I\n";}}}}



int main(){//未完成
    // 1990~2021とする
    ll y,m,d; cin>>y>>m>>d;
    ll N=31;// 調べる年代の幅
    Vll A(N+1,0);// A[i]:=年i + 1990に対して日の累積和
    FOR(i,1,N +1){
        if((i+1990)%100==0 and (i+1990)%400!=0) A[i]=A[i-1]+365;
        else if((i+1990)%4==0) A[i]=A[i-1]+366;
        else A[i]=A[i-1]+365;
    }
    bool uruu=false;// yがうるう年かどうか
    if(y%100==0 and y%400!=0) uruu=false;
    else if(y%4==0) uruu=true;
    else uruu=false;
    
    // その年の1/1からのdistance
    ll dis=0;
    FOR(i,1,m){
        if(i==1 or i==3 or i==5 or i==7 or i==8 or i==10 or i==12) dis+=31;
        else if(i==2 and uruu) dis+=29;
        else if(i==2 and !uruu) dis+=28;
        else if(i==4 or i==6 or i==9 or i==11) dis+=30;
    }
    dis+=d;// その月の日付までたす
    // 1990 1/0 は日曜日(google調べ) 日 mod 0
    ll all =A[y-1990]+dis;
    ll mod=all%7;
    vector<string> S={"日","月","火","水","木","金","土"};
    oi(S[mod]);
    
    
    return 0;
}


/*
最初から答えをいうと
チェラーの公式がある
https://ja.wikipedia.org/wiki/%E3%83%84%E3%82%A7%E3%83%A9%E3%83%BC%E3%81%AE%E5%85%AC%E5%BC%8F

しかし実装をよりよくしていく教科書の題材としては非常によい
昨日の話をきいて
中高大はパズル向きの話
社会人や専門もちは実務で使えそうな話
にくいつくのかなと思いました．



*/