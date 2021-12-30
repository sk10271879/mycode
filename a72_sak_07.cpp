#include<bits/stdc++.h>
using namespace std; using ll = long long; using Pa=pair<ll,ll>; using Vll=vector<ll>; using VVll=vector<Vll>;// VVll G(N+1,Vll(0)); // vector<Pa> event; event.emplace_back(a,b);
template<class t,class u> bool chmax(t&a,u b){if(a<b){a=b; return true;} else{return false;}} template<class t,class u> bool chmin(t&a,u b){if(b<a){a=b; return true;} else{return false;}} 
void oi(){}template<class Head, class... Tail>void oi(Head&& head,Tail&&... tail){if(sizeof...(tail)!=0){cerr<<head<<" ";} else{cerr<<head<<"\n";}oi(move(tail)...);} void OI(){}template<class Head, class... Tail>void OI(Head&& head,Tail&&... tail){if(sizeof...(tail)!=0){cout<<head<<" ";} else{cout<<head<<"\n";}OI(move(tail)...);}
#define INF (ll)1<<60// 10^18 < 1<<60 = 1152921504606846976  #define MOD (ll)1000000007
#define FOR(i,a,b) for(ll i=(ll)(a); i<(ll)(b); i++)// a ~ b-1 i++ 
#define ALL(a) (a).begin(),(a).end() // printf("%8.10lf\n",(ans)); 
#define OIV(a) if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++) if((a)[i00]!=INF and i00!=(a).size()-1){cout<<(a)[i00]<<" ";} else if((a)[i00]==INF and i00!=(a).size()-1){cerr<<"I ";} else if((a)[i00]!=INF and i00==(a).size()-1){cerr<<(a)[i00]<<"\n";} else if((a)[i00]==INF and i00==(a).size()-1){cerr<<"I\n";}}
#define OIVV(a)if(a.empty()){cout<<"\n";}else{for(ll i00=0;i00<(a).size();i00++){for(ll j00=0;j00<(a[i00]).size();j00++){if(j00!=(a)[i00].size()-1 and (a)[i00][j00]!=INF){cerr<<a[i00][j00]<<" ";}else if(j00!=(a)[i00].size()-1 and (a)[i00][j00]==INF){cerr<<"I ";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]!=INF){cerr<<a[i00][j00]<<"\n";}else if(j00==(a)[i00].size()-1 and (a)[i00][j00]==INF){cerr<<"I\n";}}}}

char kaesaru(char c){
    ll n=c-'A';
    n+=3;
    if(n>=26) n-=26;
    
    return 'A'+n;
}

char kaesaru_rev(char s){
    ll n=c-'A';
    n-=3;
    if(n<0) n+=26;
    
    return 'A'+n;    
}

int main(){
    string S; cin>>S;
    string ans="";
    FOR(i,0,S.size()){
        ans+=kaesaru(S[i]);
    }
    oi(ans);
    

    return 0;
}

/*
紀元前50年ごろ(めっちゃ古いよのインパクト)
カエサル暗号があった．
当時としては文字も読めない者も多く，これによるセキュリティはかなり万全だった．(良さを強調)
(悪いコード良いコード，改善していく様子は教科書としてかなり良いと思います)
(良いコードには良い思想がやどっている by sakさん(うろ覚え))

(対応するコンテンツをアルゴ式につくっておく)
以下の文章をカエサル式暗号にせよ
～
以下のカエサル式暗号を解け
～(できればメッセージを隠したい)

*/