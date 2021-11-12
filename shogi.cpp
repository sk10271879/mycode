#include<bits/stdc++.h>
using namespace std; using ll = long long; using Pa=pair<ll,ll>; // vector<Pa> event; event.emplace_back(a,b);
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
ifstream f1("shogi_in.dat"); // 定跡に使う
ofstream f2("shogi_out.dat"); // hyouzi()など適当なデバッグ作業に使う


class Shogi{
public:
    
    bool b0[29][10][10];// 28種類の駒の9*9を1~9の数字で 
    bool bm0[29][18];// 持ち駒駒16種類についてtrue,false 1~8 and 15~22
    ll turn0;// 1:先手  -1:後手
    random_device rnd; // 非決定的な乱数生成器を生成 適当指しのために必要
    vector<string> kifu;// 各局面を記憶しておく 千日手チェックなどに使う
    map<string,ll> m;// 各局面をstring型にしてもっておいて何回出現したか格納する(千日手チェック)
    map<string,ll> mz;// 各局面(bit_string)を引数にして評価値を得る
    bool on_game;
    ll tesuu;

    
    Shogi(){
        this->on_game=true;
        this->tesuu=0;
        FOR(k,0,29) FOR(i,1,10) FOR(j,1,10) this->b0[k][i][j]=false;
        FOR(k,0,29) FOR(i,0,18) this->bm0[k][i]=false;
        this->turn0=1;

        FOR(i,1,10) this->b0[1][i][7]=true;
        this->b0[2][1][9]=true; this->b0[2][9][9]=true;
        this->b0[3][2][9]=true; this->b0[3][8][9]=true;
        this->b0[4][3][9]=true; this->b0[4][7][9]=true;
        this->b0[5][8][8]=true;
        this->b0[6][2][8]=true; 
        this->b0[7][4][9]=true; this->b0[7][6][9]=true;               
        this->b0[8][5][9]=true;

        FOR(i,1,10) this->b0[15][i][3]=true;
        this->b0[16][1][1]=true; this->b0[16][9][1]=true;
        this->b0[17][2][1]=true; this->b0[17][8][1]=true;
        this->b0[18][3][1]=true; this->b0[18][7][1]=true;
        this->b0[19][2][2]=true;
        this->b0[20][8][2]=true; 
        this->b0[21][4][1]=true; this->b0[21][6][1]=true;               
        this->b0[22][5][1]=true;
        return;        
    }
    
    void ui(){// userの応答から対局モードを選んで対局にもっていく
        OI("nobisiro ver 1.0");
        OI("author sk in 2021.");
        OI("こちらは将棋プログラムです");

        OI("遊ぶモードを選んで数字を入力してください");
        OI("1: 先手:人間 vs 後手:人間");
        OI("2: 先手:人間 vs 後手:PC");
        OI("3: 先手: PC vs 後手:人間");
        OI("4: 先手:PC  vs  後手:PC");
        OI("5:  やめる");
        string mode;
        while(true){
            cout<<"選ぶモード：";
            cin>>mode;
            if(mode=="1" or mode=="2" or mode=="3" or mode=="4"){
                OI("対局を開始します");
                break;
            }
            else if(mode=="5"){
                OI("ありがとうございました");
                return;
            }
            else if(mode=="6"){
                OI("隠しコマンド発動!!");
                OI("今日の占い");
                mt19937 mt(this->rnd());     //  メルセンヌ・ツイスタの32ビット版
                uniform_int_distribution<> rand100(0,12);//一様乱数
                ll u=rand100(mt);
                if(u==0) OI("大吉!!!!!!!!!!!!!!!!!!");
                else if(u==1 or u==2) OI("中吉!!!");
                else if(3<=u and u<=6) OI("小吉!!");
                else if(7<=u and u<=9) OI("末吉");
                else if(u==10 or u==11) OI("凶!!!!!!");
                else if(u==12) OI("大凶!!!!!!!!!!!!!!! ある意味ラッキー!!!!!!!!!!!!!!!");
                
                return;
            }
            else{
                OI("");
                OI("YUKI.N> sleeping beauty_");
                return;
            }            
        }
        
        this->play(mode);

        return;        
    }

    bool play_naibu(string player, bool (&b)[29][10][10], bool(&bm)[29][18], ll &turn){
        bool on_game=true;
        string mozi[29]={"   "," 歩"," 香"," 桂"," 銀"," 角"," 飛"," 金"," 玉"," と"," ky"," ke"," gi"," 馬"," 竜",\
                               " 歩"," 香"," 桂"," 銀"," 角"," 飛"," 金"," 玉"," と"," ky"," ke"," gi"," 馬"," 竜"};
        Vll A(5,0);// 入力を整数で扱う
        if(player=="human"){
            VVll goho=this->gohosyu(b,bm,turn);
            
            bool ok_te=false;// 入力された手が合法か判定
            vector<char> a(5);// 入力は文字なんでも対応
            ll cnt=0;
            while(!ok_te){// 合法になるまでループ
                if(turn==1) OI("先手の人間の手番です");
                else if(turn==-1) OI("後手の人間の手番です");
                OI("76の駒を75に動かす場合は      7 6 7 5 0  と入力してください");
                OI("31の駒を32に動かし成る場合は  3 1 3 2 1  と入力してください");
                OI("持ち駒の数字リスト  1:歩  2:香:2  3:桂  4:銀  5:角  6:飛  7:金");
                OI("(持ち駒の桂馬を17に打つ例) 0 3 1 7 0 と入力してください(先頭は0)");
                OI("やめる場合にはaやbなどを入力してください");
                cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];
                FOR(i,0,5){
                    A[i]=a[i]-'0';
                    if(A[i]<0 and 9<A[i]){// 0~9以外なのでたぶんローマ字だろうと
                        ok_te=true;
                        OI("ありがとうございました");
                        return false;
                    }
                }
                cnt=0;
                for(auto &v: goho){
                    if(v[0]==A[0] and v[1]==A[1] and v[2]==A[2] and v[3]==A[3] and v[4]==A[4]){
                        ok_te=true; 
                        break;
                    }
                    cnt+=1;
                }
                if(!ok_te) OI("入力ミスをしています，バグの場合は担当者にお問い合わせください");
            }
            this->move(A[0],A[1],A[2],A[3],A[4],this->b0,this->bm0,this->turn0);
            this->hyouzi(b,bm,turn,false);

        }
        else if(player=="com"){
            //A=this->random(this->b0,this->bm0,this->turn0);
            A=this->alphabeta(b,bm,turn);
            this->move(A[0],A[1],A[2],A[3],A[4],b,bm,turn);
        }

        string state=this->bit_out(b,bm,turn,false);
        this->m[state]+=1;
        if(this->m[state]==4){
            OI("千日手です!!!");
            this->on_game=false;
            return false;                
        }
        if(this->bm0[8][0]){
            OI("先手の勝ちです！");
            this->on_game=false;
            return false;
        }
        else if(this->bm0[22][0]){
            OI("後手の勝ちです！");
            this->on_game=false;
            return false;                
        }     

        ll koma=0;
        FOR(k,1,29){
            if(b[k][A[2]][A[3]]){
                koma=k;
                break;
            }
        }
        this->tesuu+=1;
        OI(this->tesuu,"手目",A[2],A[3],mozi[koma],"まで");
        this->hyouzi(b,bm,turn,false);
        
        return on_game;
    }

    void play(string mode){

        string sente,gote;
        if(mode=="1" or mode=="2" or mode=="3"){
            OI("あなたの手番です 指し手を入力してください");
            OI("76の駒を75に動かす場合は      7 6 7 5 0  と入力してください");
            OI("31の駒を32に動かし成る場合は  3 1 3 2 1  と入力してください");
            OI("持ち駒の数字リスト  1:歩  2:香:2  3:桂  4:銀  5:角  6:飛  7:金");
            OI("持ち駒を打つ際には(桂馬を17に打つ例) 0 3 1 7 0 と入力してください(先頭は0)");
            OI("やめる場合にはaやbなどのローマ字を入力してください");
            if(mode=="1"){
                sente="human";
                gote="human";                
            }
            else if(mode=="2"){
                sente="human";
                gote="com";                 
            }
            else if(mode=="3"){
                sente="com";
                gote="human";                 
            }            
        }
        else if(mode=="4"){
            OI("勝手に始めさせてもらいます");
            sente="com";
            gote="com";
        }

        OI("よろしくお願いします");
        this->hyouzi(this->b0,this->bm0,this->turn0,false);
        
        bool on_game=true; 
        while(on_game){
            on_game=this->play_naibu(sente,this->b0,this->bm0,this->turn0);
            on_game=this->play_naibu(gote,this->b0,this->bm0,this->turn0);
        }
        OI("ありがとうございました");

        return;
    }

    void bit_in(bool (&b)[29][10][10], bool(&bm)[29][18], ll &turn, bool file, string &s){// 現在の局面をbit(stringで扱う)でもらって局面にコピー
        ll cnt=0;
        FOR(k,1,29){
            FOR(i,1,10){
                FOR(j,1,10){
                    if(s[cnt]=='1') b[k][i][j]=true;
                    else b[k][i][j]=false;
                    cnt+=1;
                }
            }
        }

        ll maisu=0;
        FOR(k,1,29){
            if(k==1) maisu=18;
            else if(k==2 or k==3 or k==4 or k==7) maisu=4;
            else if(k==5 or k==6 or k==8) maisu=2; 
            FOR(m,0,maisu){
                if(s[cnt]=='1') bm[k][m]=true;
                else bm[k][m]=false;
                cnt+=1;
            }           
        }
        if(s[cnt]=='1') turn=1;
        else turn=-1;         

        return;
    }    

    string bit_out(bool (&b)[29][10][10], bool(&bm)[29][18], ll &turn, bool file){// 現在の局面をbit(stringで扱う)で出力 定跡 千日手checkなどに有効
        string s;
        FOR(k,1,29){
            FOR(i,1,10){
                FOR(j,1,10){
                    if(b[k][i][j]) s+="1";
                    else s+="0";
                }
            }
        }

        ll maisu=0;
        FOR(k,1,29){
            if(k==1) maisu=18;
            else if(k==2 or k==3 or k==4 or k==7) maisu=4;
            else if(k==5 or k==6 or k==8) maisu=2; 
            FOR(m,0,maisu){
                if(bm[k][m]) s+="1";
                else s+="0";
            }           
        }
        if(turn==1) s+="1";
        else s+="0";

        if(file) f2<<s<<"\n";
        //else OI(s);            

        return s;
    }

    void zyoseki(){// 定跡を読み込んで，序盤の評価値計算の手間を省く
        return;
    }

    void hyouzi(bool (&b)[29][10][10], bool(&bm)[29][18], ll &turn, bool file){// 現在の局面を表示する file true f2に出力 false terminalに出力
        
        string s[29]={"   "," 歩"," 香"," 桂"," 銀"," 角"," 飛"," 金"," 玉"," と"," ky"," ke"," gi"," 馬"," 竜",\
                            "^歩","^香","^桂","^銀","^角","^飛","^金","^玉","^と","^ky","^ke","^gi","^馬","^竜"};
        string sm[29]={"   "," 歩"," 香"," 桂"," 銀"," 角"," 飛"," 金"," 玉"," と"," ky"," ke"," gi"," 馬"," 竜",\
                            " 歩"," 香"," 桂"," 銀"," 角"," 飛"," 金"," 玉","^と","^ky","^ke","^gi","^馬","^竜"};
        
        if(file){
            f2<<"#############################\n";// display start           
        }
        else{
            cout<<"#############################\n";          
        }

        Vll gmoti={19,20,21,18,17,16,15};// gote motigoma
        for(auto j: gmoti){
            ll ima_maisu=0;
            ll maisu=0;
            if(j==15) maisu=18;
            else if(j==16 or j==17 or j==18 or j==21) maisu=4;
            else if(j==19 or j==20 or j==22) maisu=2;
            for(ll m=maisu-1; 0<=m; m--){
                if(bm[j][m]) ima_maisu+=1;
            }
            if(file) f2<<" "<<sm[j]<<":"<<ima_maisu;
            else cout<<" "<<sm[j]<<":"<<ima_maisu;
        }
        if(file){
            f2<<"\n";
            f2<<"\n";            
        }
        else{
            cout<<"\n";
            cout<<"\n";
        }
        if(file) f2<<"   9  8  7  6  5  4  3  2  1\n";
        else cout<<"   9  8  7  6  5  4  3  2  1\n";
        for(ll j=1; j<=9; j++){ // board  
            if(file) f2<<j<<" "; 
            else cout<<j<<" ";
            for(ll i=9; 1<=i; i--){
                bool ok=false;
                FOR(k,1,28 +1){
                    if(b[k][i][j]){
                        if(file) f2<<s[k];
                        else cout<<s[k];
                        ok=true;
                        break;
                    }
                }
                if(!ok and file) f2<<"   ";
                else if(!ok and !file) cout<<"   ";

            }
            if(file) f2<<"\n";
            else cout<<"\n";
        }
        if(file) f2<<"\n";
        else cout<<"\n";

        Vll smoti={5,6,7,4,3,2,1};// sente_motigoma
        for(auto j: smoti){
            ll ima_maisu=0;
            ll maisu=0;
            if(j==1) maisu=18;
            else if(j==2 or j==3 or j==4 or j==7) maisu=4;
            else if(j==5 or j==6 or j==8) maisu=2;
            for(ll m=maisu-1; 0<=m; m--){
                if(bm[j][m]) ima_maisu+=1;
            }
            if(file) f2<<" "<<sm[j]<<":"<<ima_maisu;
            else cout<<" "<<sm[j]<<":"<<ima_maisu;

        }
        if(file){
            f2<<"\n";
            f2<<"\n";
            if(turn==1) f2<<"次は先手番です\n";
            else if(turn==-1) f2<<"次は後手番です\n"; 
            f2<<"#############################\n";
            f2<<"\n";
            f2<<"\n";            
        }
        else{
            cout<<"\n";
            cout<<"\n";
            if(turn==1) cout<<"次は先手番です\n";
            else if(turn==-1) cout<<"次は後手番です\n"; 
            cout<<"#############################\n";
            cout<<"\n";
            cout<<"\n";            
        }

        return;
    }

    VVll gohosyu(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn){// 局面を受け取り，合法手のリストを返す
        bool bod_sente[10][10];// 先手の駒がいるかどうか
        bool bod_gote[10][10];// 後手の駒がいるかどうか
        bool bod_all[10][10];// 先後の駒がいるかどうか
        ll bod_ll[10][10]; // i,jに何の駒がいるか
        
        FOR(i,1,10) FOR(j,1,10) bod_sente[i][j]=false;
        FOR(i,1,10) FOR(j,1,10) bod_gote[i][j]=false;
        FOR(i,1,10) FOR(j,1,10) bod_all[i][j]=false;
        FOR(i,1,10) FOR(j,1,10) bod_ll[i][j]=0;

        FOR(k,1,15){
            FOR(i,1,10){
                FOR(j,1,10){
                    bod_sente[i][j]=b[k][i][j] or bod_sente[i][j];
                    bod_gote[i][j]=b[k+14][i][j] or bod_gote[i][j];
                    bod_all[i][j] =b[k][i][j] or b[k+14][i][j] or bod_all[i][j];                   
                }
            }
        }
        VVll goho(0,Vll(5));// 合法手を入れる (i,j)->(i1,j1) naru

        if(turn==1){
            Vll ue={1,4,7,8,9,10,11,12,13};
            Vll migi={7,8,9,10,11,12,13};
            Vll hidari={7,8,9,10,11,12,13};
            Vll sita={7,8,9,10,11,12,13};
            Vll migiue={4,7,8,9,10,11,12,14};
            Vll hidariue={4,7,8,9,10,11,12,14};
            Vll migisita={4,8,14};
            Vll hidarisita={4,8,14};

            bool dir[29][8];// 先手14種類について1マスに限り各8方向へ進めるかどうか(長距離は除く)
            FOR(k,1,15) FOR(d,0,8) dir[k][d]=false;
            for(auto v: ue) dir[v][0]=true;
            for(auto v: migi) dir[v][1]=true;
            for(auto v: hidari) dir[v][2]=true;
            for(auto v: sita) dir[v][3]=true;
            for(auto v: migiue) dir[v][4]=true;
            for(auto v: hidariue) dir[v][5]=true;
            for(auto v: migisita) dir[v][6]=true;
            for(auto v: hidarisita) dir[v][7]=true;
            
            FOR(i,1,10){
                FOR(j,1,10){
                    ll k=0;
                    bool ok=false;
                    FOR(koma,1,14 +1){
                        if(b[koma][i][j]){
                            k=koma;
                            bod_ll[i][j]=k;
                            ok=true;
                            break;
                        }
                    }
                    if(!ok) {// 駒がi,jにないので持ち駒を打つ                                           
                        bool moti[9];
                        FOR(k,1,9) moti[k]=false;
                       
                        FOR(k,1,9){// 1枚でもあれば打てるので先頭から確認
                            if(k==1){// 歩
                                FOR(m,0,18) if(bm[k][m]) moti[1]=true;
                            }
                            else if(k==2 or k==3 or k==4 or k==7){
                                FOR(m,0,4) if(bm[k][m]) moti[k]=true;
                            }
                            else if(k==5 or k==6 or k==8){
                                FOR(m,0,2) if(bm[k][m]) moti[k]=true;
                            }
                        }
                        if(not(bod_all[i][j]) and j>=2 and moti[1]){
                            bool nihu=false;
                            FOR(i1,1,10){
                                if(b[1][i][i1]) nihu=true;
                            }
                            if(!nihu) goho.push_back({0,1,i,j,0}); 
                        }
                        if(not(bod_all[i][j]) and 2<=j and moti[2]){
                            goho.push_back({0,2,i,j,0});
                        }
                        if(not(bod_all[i][j]) and 3<=j and moti[3]){
                            goho.push_back({0,3,i,j,0});
                        }
                        FOR(k,4,8){
                            if(not(bod_all[i][j]) and moti[k]){
                                goho.push_back({0,k,i,j,0});
                            }
                        }
                    }

                    // 各方向1マス
                    if(dir[k][0]){// ue
                        if(not(k==1 and j<=2) and b[k][i][j] and  not(bod_sente[i][j-1]))  goho.push_back({i,j,i,j-1,0});
                        else if(k==1 and j==2 and b[k][i][j] and  not(bod_sente[i][j-1]))  goho.push_back({i,j,i,j-1,1});
                    }
                    if(dir[k][1]) if(i>=2 and b[k][i][j] and  not(bod_sente[i-1][j])) goho.push_back({i,j,i-1,j,0});
                    if(dir[k][2]) if(i<=8 and b[k][i][j] and  not(bod_sente[i+1][j])) goho.push_back({i,j,i+1,j,0});
                    if(dir[k][3]) if(j<=8 and b[k][i][j] and  not(bod_sente[i][j+1])) goho.push_back({i,j,i,j+1,0});
                    if(dir[k][4]) if(i>=2 and j>=2 and b[k][i][j] and not(bod_sente[i-1][j-1])) goho.push_back({i,j,i-1,j-1,0});
                    if(dir[k][5]) if(i<=8 and j>=2 and b[k][i][j] and not(bod_sente[i+1][j-1])) goho.push_back({i,j,i+1,j-1,0});
                    if(dir[k][6]) if(i>=2 and j<=8 and b[k][i][j] and not(bod_sente[i-1][j+1])) goho.push_back({i,j,i-1,j+1,0});
                    if(dir[k][7]) if(i<=8 and j<=8 and b[k][i][j] and not(bod_sente[i+1][j+1])) goho.push_back({i,j,i+1,j+1,0});

                    FOR(i1,1,10){// 香
                        if(j-i1>=2 and b[2][i][j] and not(bod_all[i][j-i1])) goho.push_back({i,j,i,j-i1,0});
                        else if(j-i1==1 and b[2][i][j] and not(bod_sente[i][j-i1])){
                            goho.push_back({i,j,i,j-i1,1});
                            break;
                        }
                        else if(j-i1>=1 and b[2][i][j] and (bod_gote[i][j-i1])){
                            goho.push_back({i,j,i,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and b[2][i][j] and bod_sente[i][j-i1]) break;
                        else if(j==i1) break;
                    }
                    // 桂
                    if(5<=j<=9 and 2<=i<=9 and b[3][i][j] and not(bod_sente[i-1][j-2])) goho.push_back({i,j,i-1,j-2,0});
                    if(3<=j<=4 and 2<=i<=9 and b[3][i][j] and not(bod_sente[i-1][j-2])) goho.push_back({i,j,i-1,j-2,1});
                    if(5<=j<=9 and 1<i<=8 and b[3][i][j] and not(bod_sente[i+1][j-2]))  goho.push_back({i,j,i+1,j-2,0});
                    if(3<=j<=4 and 1<=i<=8 and b[3][i][j] and not(bod_sente[i+1][j-2])) goho.push_back({i,j,i+1,j-2,1});                 

                    // 角
                    FOR(i1,1,9){
                        if(j+i1<=9 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and not(bod_all[i+i1][j+i1])){
                            goho.push_back({i,j,i+i1,j+i1,0});
                        }
                        else if(j+i1<=9 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_gote[i+i1][j+i1]){
                            goho.push_back({i,j,i+i1,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_sente[i+i1][j+i1]) break;
                        else if(j+i1>=10 or i+i1>=10) break;                        
                    }
                    FOR(i1,1,9){
                        if(j+i1<=9 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and not(bod_all[i-i1][j+i1])){
                            goho.push_back({i,j,i-i1,j+i1,0});
                        }
                        else if(j+i1<=9 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and bod_gote[i-i1][j+i1]){
                            goho.push_back({i,j,i-i1,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and bod_sente[i-i1][j+i1]) break;
                        else if(j+i1>=10 or i-i1<=0) break;
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and not(bod_all[i-i1][j-i1])){
                            goho.push_back({i,j,i-i1,j-i1,0});
                        }
                        else if(j-i1>=1 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and bod_gote[i-i1][j-i1]){
                            goho.push_back({i,j,i-i1,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and i-i1>=1 and (b[5][i][j] or b[13][i][j]) and bod_sente[i-i1][j-i1]) break;
                        else if(j-i1<=0 or i-i1<=0) break;
                        
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and not(bod_all[i+i1][j-i1])){
                            goho.push_back({i,j,i+i1,j-i1,0});
                        }
                        else if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_gote[i+i1][j-i1]){
                            goho.push_back({i,j,i+i1,j-i1,0});
                            break;
                        }
                            
                        else if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_sente[i+i1][j-i1]) break;                            
                        else if(j-i1<=0 or i+i1>=10) break;
                            
                        
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and not(bod_all[i+i1][j-i1])) {
                            goho.push_back({i,j,i+i1,j-i1,0});
                        }
                        else if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_gote[i+i1][j-i1]){
                            goho.push_back({i,j,i+i1,j-i1,0});
                            break;
                        }   
                        else if(j-i1>=1 and i+i1<=9 and (b[5][i][j] or b[13][i][j]) and bod_sente[i+i1][j-i1]) break;
                        else if(j-i1<=0 or i+i1>=10) break;
                                          
                    }
                    // 飛
                    FOR(i1,1,9){
                        if(j+i1<=9 and (b[6][i][j] or b[14][i][j]) and not(bod_all[i][j+i1])) {
                            goho.push_back({i,j,i,j+i1,0});
                        }
                        else if(j+i1<=9 and (b[6][i][j] or b[14][i][j]) and bod_gote[i][j+i1]){
                            goho.push_back({i,j,i,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and (b[6][i][j] or b[14][i][j]) and bod_sente[i][j+i1]) break;
                        else if(j+i1>=10) break;
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and (b[6][i][j] or b[14][i][j]) and not(bod_all[i][j-i1])){
                            goho.push_back({i,j,i,j-i1,0});
                        }
                        else if(j-i1>=1 and (b[6][i][j] or b[14][i][j]) and bod_gote[i][j-i1]){
                            goho.push_back({i,j,i,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and (b[6][i][j] or b[14][i][j]) and bod_sente[i][j-i1]) break;
                        else if(j-i1<=0)  break;
                    }
                    FOR(i1,1,9){
                        if(i-i1>=1 and (b[6][i][j] or b[14][i][j]) and not(bod_all[i-i1][j])){
                            goho.push_back({i,j,i-i1,j,0});
                        }
                        else if(i-i1>=1 and (b[6][i][j] or b[14][i][j]) and bod_gote[i-i1][j]){
                            goho.push_back({i,j,i-i1,j,0});
                            break;
                        }
                        else if(i-i1>=1 and (b[6][i][j] or b[14][i][j]) and bod_sente[i-i1][j])  break;
                        else if(i-i1<=0) break;
                    }
                    FOR(i1,1,9){
                        if(i+i1<=9 and (b[6][i][j] or b[14][i][j]) and not(bod_all[i+i1][j])){
                            goho.push_back({i,j,i+i1,j,0});
                        }
                        else if(i+i1<=9 and (b[6][i][j] or b[14][i][j]) and bod_gote[i+i1][j]){
                            goho.push_back({i,j,i+i1,j,0});
                            break;
                        }
                        else if(i+i1<=9 and (b[6][i][j] or b[14][i][j]) and bod_sente[i+i1][j])  break;
                        else if(i+i1>=10) break;
                    }
                
                }
            }
            VVll gohonari(0,Vll(6));// 合法手から成る手を追加する (i,j)->(i1,j1) naru
            for(auto &v :goho){
                if(v[0]!=0 and (v[1]<=3 or v[3]<=3) and v[4]==0 and 1<=bod_ll[v[0]][v[1]] and bod_ll[v[0]][v[1]]<=6){
                    gohonari.push_back({v[0],v[1],v[2],v[3],1});
                }
            }
            for(auto &v: gohonari){
                goho.push_back(v);
            }

        }
        
        else if(turn==-1){
            Vll ue={15,18,21,22,23,24,25,26,27};
            Vll migi={21,22,23,24,25,26,27};
            Vll hidari={21,22,23,24,25,26,27};
            Vll sita={21,22,23,24,25,26,27};
            Vll migiue={18,21,22,23,24,25,26,28};
            Vll hidariue={18,21,22,23,24,25,26,28};
            Vll migisita={18,22,28};
            Vll hidarisita={18,22,28};
            
            bool dir[29][8];// 後手14種類について1マスに限り各8方向へ進めるかどうか 後手にとって上など
            FOR(k,1,29) FOR(d,0,8) dir[k][d]=false;
            for(auto v: ue) dir[v][0]=true;
            for(auto v: migi) dir[v][1]=true;
            for(auto v: hidari) dir[v][2]=true;
            for(auto v: sita) dir[v][3]=true;
            for(auto v: migiue) dir[v][4]=true;
            for(auto v: hidariue) dir[v][5]=true;
            for(auto v: migisita) dir[v][6]=true;
            for(auto v: hidarisita) dir[v][7]=true;
            
            FOR(i,1,10){
                FOR(j,1,10){
                    ll k=0;
                    bool ok=false;
                    FOR(koma,15,28 +1){
                        if(b[koma][i][j]){
                            k=koma;
                            bod_ll[i][j]=k;
                            ok=true;
                            break;
                        }
                    }
                    if(!ok){//i,jに駒がなかったので打てる
                        bool moti[9];
                        FOR(k,1,9) moti[k]=false; 
                        FOR(k,15,29){// 1枚でもあれば打てるので先頭から確認
                            if(k==15){// 歩
                                FOR(m,0,18) if(bm[k][m]) moti[k-14]=true;
                            }
                            else if(i==16 or i==17 or i==18 or i==21){// 4枚まで
                                FOR(m,0,4) if(bm[k][m]) moti[k-14]=true;
                            }
                            else if(i==19 or i==20 or i==22){// 2枚まで
                                FOR(m,0,2) if(bm[k][m]) moti[k-14]=true;
                            }
                        }
                        
                        if(not(bod_all[i][j]) and j<=8 and moti[1]){
                            bool nihu=false;
                            FOR(i1,1,10){
                                if(b[15][i][i1]) nihu=true;
                            }
                            if(!nihu) goho.push_back({0,15,i,j,0}); 
                        }
                        if(not(bod_all[i][j]) and j<=8 and moti[2]){
                            goho.push_back({0,16,i,j,0});
                        }
                        if(not(bod_all[i][j]) and j<=7 and moti[3]){
                            goho.push_back({0,17,i,j,0});
                        }
                        FOR(k,4,8){
                            if(not(bod_all[i][j]) and moti[k]){
                                goho.push_back({0,k+14,i,j,0});
                            }
                        }
                    }

                    // 各方向1マス
                    if(dir[k][0]){// ue
                        if(not(k==15 and 8<=j) and b[k][i][j] and not(bod_gote[i][j+1])) goho.push_back({i,j,i,j+1,0});
                        else if(k==15 and j==8 and b[k][i][j] and not(bod_gote[i][j+1])) goho.push_back({i,j,i,j+1,1});
                    }
                    if(dir[k][1]) if(i<=8 and b[k][i][j] and  not(bod_gote[i+1][j])) goho.push_back({i,j,i+1,j,0});              
                    if(dir[k][2]) if(2<=i and b[k][i][j] and  not(bod_gote[i-1][j])) goho.push_back({i,j,i-1,j,0});
                    if(dir[k][3]) if(2<=j and b[k][i][j] and not(bod_gote[i][j-1]))  goho.push_back({i,j,i,j-1,0});                     
                    if(dir[k][4]) if(i<=8 and j<=8 and b[k][i][j] and  not(bod_gote[i+1][j+1])) goho.push_back({i,j,i+1,j+1,0});
                    if(dir[k][5]) if(2<=i and j<=8 and b[k][i][j] and  not(bod_gote[i-1][j+1])) goho.push_back({i,j,i-1,j+1,0});
                    if(dir[k][6]) if(2<=i and 2<=j and b[k][i][j] and  not(bod_gote[i-1][j-1])) goho.push_back({i,j,i-1,j-1,0});
                    if(dir[k][7]) if(i<=8 and 2<=j and b[k][i][j] and  not(bod_gote[i+1][j-1])) goho.push_back({i,j,i+1,j-1,0});

                    //香
                    FOR(i1,1,9){
                        if(j+i1<=8 and b[16][i][j] and not(bod_all[i][j+i1])) goho.push_back({i,j,i,j+i1,0});
                        else if(j+i1==9 and b[16][i][j] and not(bod_gote[i][j+i1])){
                            goho.push_back({i,j,i,j+i1,1});    
                            break;                             
                        }
                        else if(j+i1<=9 and b[16][i][j] and (bod_sente[i][j+i1])){
                            goho.push_back({i,j,i,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and b[16][i][j] and bod_gote[i][j+i1]) break;
                        if(j+i1==9) break;
                    }
                    // 桂
                    if(1<=j and j<=5 and 2<=i and i<=9 and b[17][i][j] and not(bod_gote[i-1][j+2])) goho.push_back({i,j,i-1,j+2,0});
                    if(6<=j and j<=7 and 2<=i and i<=9 and b[17][i][j] and not(bod_gote[i-1][j+2])) goho.push_back({i,j,i-1,j+2,1});
                    if(1<=j and j<=5 and 1<=i and i<=8 and b[17][i][j] and not(bod_gote[i+1][j+2])) goho.push_back({i,j,i+1,j+2,0});
                    if(6<=j and j<=7 and 1<=i and i<=8 and b[17][i][j] and not(bod_gote[i+1][j+2])) goho.push_back({i,j,i+1,j+2,1});

                    // 角
                    FOR(i1,1,9){
                        if(j+i1<=9 and i+i1<=9 and (b[19][i][j] or b[27][i][j])  and not(bod_all[i+i1][j+i1])){
                            goho.push_back({i,j,i+i1,j+i1,0});
                        }
                        else if(j+i1<=9 and i+i1<=9 and (b[19][i][j] or b[27][i][j]) and bod_sente[i+i1][j+i1]){
                            goho.push_back({i,j,i+i1,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and i+i1<=9 and (b[19][i][j] or b[27][i][j]) and bod_gote[i+i1][j+i1]) break;
                        else if(j+i1>=10 or i+i1>=10)  break;                        
                    }
                    FOR(i1,1,9){
                        if(j+i1<=9 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and not(bod_all[i-i1][j+i1])){
                            goho.push_back({i,j,i-i1,j+i1,0});
                        }
                        else if(j+i1<=9 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and bod_sente[i-i1][j+i1]){
                            goho.push_back({i,j,i-i1,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and bod_gote[i-i1][j+i1]) break;
                        else if(j+i1>=10 or i-i1<=0)break;
                                                    
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and not(bod_all[i-i1][j-i1])){
                            goho.push_back({i,j,i-i1,j-i1,0});
                        }
                        else if(j-i1>=1 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and bod_sente[i-i1][j-i1]){
                            goho.push_back({i,j,i-i1,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and i-i1>=1 and (b[19][i][j] or b[27][i][j]) and bod_gote[i-i1][j-i1])break;                         
                        else if(j-i1<=0 or i-i1<=0)break; 
                                                   
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and i+i1<=9 and (b[19][i][j] or b[27][i][j]) and not(bod_all[i+i1][j-i1])){
                            goho.push_back({i,j,i+i1,j-i1,0});
                        }
                            
                        else if(j-i1>=1 and i+i1<=9 and (b[19][i][j] or b[27][i][j]) and bod_sente[i+i1][j-i1]){
                            goho.push_back({i,j,i+i1,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and i+i1<=9 and (b[19][i][j] or b[27][i][j]) and bod_gote[i+i1][j-i1])break;
                        else if(j-i1<=0 or i+i1>=10)break;     
                                               
                    }

                    // 飛
                    FOR(i1,1,9){
                        if(j+i1<=9 and (b[20][i][j] or b[28][i][j]) and not(bod_all[i][j+i1])){
                            goho.push_back({i,j,i,j+i1,0});
                        }
                        else if(j+i1<=9 and (b[20][i][j] or b[28][i][j]) and bod_sente[i][j+i1]){
                            goho.push_back({i,j,i,j+i1,0});
                            break;
                        }
                        else if(j+i1<=9 and (b[20][i][j] or b[28][i][j]) and bod_gote[i][j+i1]) break;                            
                        else if(j+i1>=10)break;  
                                                  
                    }
                    FOR(i1,1,9){
                        if(j-i1>=1 and (b[20][i][j] or b[28][i][j]) and not(bod_all[i][j-i1])){
                            goho.push_back({i,j,i,j-i1,0});
                        }
                        else if(j-i1>=1 and (b[20][i][j] or b[28][i][j]) and bod_sente[i][j-i1]){
                            goho.push_back({i,j,i,j-i1,0});
                            break;
                        }
                        else if(j-i1>=1 and (b[20][i][j] or b[28][i][j]) and bod_gote[i][j-i1]) break;
                        else if(j-i1<=0) break;                              
                    }
                    FOR(i1,1,9){
                        if(i-i1>=1 and (b[20][i][j] or b[28][i][j]) and not(bod_all[i-i1][j])){
                            goho.push_back({i,j,i-i1,j,0});
                        }
                        else if(i-i1>=1 and (b[20][i][j] or b[28][i][j]) and bod_sente[i-i1][j]){
                            goho.push_back({i,j,i-i1,j,0});
                            break;
                        }
                        else if(i-i1>=1 and (b[20][i][j] or b[28][i][j]) and bod_gote[i-i1][j]) break;
                            
                        else if(i-i1<=0) break;                           
                    }
                    FOR(i1,1,9){
                        if(i+i1<=9 and (b[20][i][j] or b[28][i][j]) and not(bod_all[i+i1][j])){
                            goho.push_back({i,j,i+i1,j,0});
                        }   
                        else if(i+i1<=9 and (b[20][i][j] or b[28][i][j]) and bod_sente[i+i1][j]){
                            goho.push_back({i,j,i+i1,j,0});
                            break;
                        }
                        else if(i+i1<=9 and (b[20][i][j] or b[28][i][j]) and bod_gote[i+i1][j])break;
                        else if(i+i1>=10)break;                                   
                    }
                        
                }
            }
            VVll gohonari(0,Vll(5));// 合法手から成る手を追加する (i,j)->(i1,j1) naru
            for(auto v :goho){
                if(v[0]!=0 and (7<=v[1] or 7<=v[3]) and v[4]==0 and 15<=bod_ll[v[0]][v[1]] and bod_ll[v[0]][v[1]]<=20){
                    gohonari.push_back({v[0],v[1],v[2],v[3],1});
                }
            }
            for(auto v: gohonari){
                goho.push_back(v);
            }

        }
        
        return goho;
    }

    VVll move(ll i, ll j, ll i1, ll j1, ll naru, bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn){// 与えられた指し手で与えられた局面を進める
        VVll sabun(0,Vll(4));// 動かす駒の元先 とられる駒の元先，の4種類でひとつ前の局面に戻れる 探索の時に必要
        // {s0,s1,s2,s3} s0:0盤面  s1:種類(0~28)  s2:i(1~9)  s3:j(1~9) 
        // {s0,s1,s2,s3} s0:1駒台  s1:種類(0~28)  s2:m駒台の場所(歩なら0~18)  s3:0(適当に埋める)
        
        if(i==0){// 持ち駒を打つ
            if(j<=8){
                ll maisu=0;
                if(j==1) maisu=18;
                else if(j==2 or j==3 or j==4 or j==7) maisu=4;
                else if(j==5 or j==6 or j==8) maisu=2;
                bool ok=false;
                for(ll m=maisu-1; 0<=m; m--){// 後ろから使う
                    if(bm[j][m]){
                        bm[j][m]=false;
                        sabun.push_back({1,j,m,0});
                        ok=true;
                        break;
                    }
                }
                if(!ok) OI("NO MOTIGOMA !!!"," koma=",j);
            }
            else if(15<=j){
                ll maisu=0;
                if(j==15) maisu=18;
                else if(j==16 or j==17 or j==18 or j==21) maisu=4;
                else if(j==19 or j==20 or j==22) maisu=2;
                bool ok=false;
                for(ll m=maisu-1; 0<=m; m--){// 後ろから使う
                    if(bm[j][m]){
                        bm[j][m]=false;
                        sabun.push_back({1,j,m,0});
                        ok=true;
                        break;
                    }
                }
                if(!ok) OI("NO MOTIGOMA !!!"," koma=",j);
            }
            b[j][i1][j1]=true;
            sabun.push_back({0,j,i1,j1});

        }
        
        else{// 駒を盤上で移動する
            ll koma=0;
            bool ok=true;
            FOR(k,1,29){
                if(b[k][i][j]){
                    koma=k; 
                    ok=true;
                    break;
                }
                else ok=false;
            }
            if(!ok) OI("ILLIGAL MOVE THERE IS NO KOMA !!!");
            
            ll koma1=0;
            ll ok1=true;
            FOR(k,1,29){
                if(b[k][i1][j1]){
                    koma1=k; 
                    ok1=true;
                    break;
                }
                else ok1=false;
            }            
            if(ok1){
                b[koma1][i1][j1]=false;// 行く先にあった駒
                sabun.push_back({0,koma1,i1,j1});
                if(turn==1){
                    if(23<=koma1){// 先手は後手の駒をとる
                        koma1-=8;//とは歩に戻すなど
                    }
                    ll cnt=0;
                    while(bm[koma1][cnt]){
                        cnt+=1;
                    }
                    bm[koma1-14][cnt]=true;// -14は後手の駒が先手の駒になるの意味
                    sabun.push_back({1,koma1-14,cnt,0});
                }
                if(turn==-1){// 後手は先手の駒をとる
                    if(9<=koma1){
                        koma1-=8;//とは歩に戻すなど
                    }
                    ll cnt=0;
                    while(bm[koma1][cnt]){
                        cnt+=1;
                    }
                    bm[koma1+14][cnt]=true;// +14は先手の駒が後手の駒になるの意味
                    sabun.push_back({1,koma1+14,cnt,0});
                }
            }
            b[koma][i][j]=false;// 動かす駒の元の場所
            b[koma][i1][j1]=true;// 動かす駒の移動先
            sabun.push_back({0,koma,i,j});
            sabun.push_back({0,koma,i1,j1});
        }
        turn*=-1;
        return sabun;
    }
  
    ll hyouka(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn){// 受け取った局面の評価値を返す
        string s=this->bit_out(b,bm,turn ,false);
        if(this->mz[s]!=0){// 定跡にある局面なら計算する必要なし
            return mz[s];
        }
        
        Vll hyo={0,100, 200, 200, 400, 600, 700, 500, 90000,\
                   500, 500, 500, 500, 800, 900,\
                  -100,-200,-200,-400,-600,-700,-500,-90000,\
                  -500,-500,-500,-500,-800,-900};
        Vll mhyo={0,105, 210, 210, 420, 630, 735, 525, 90500,\
                    0,0,0,0,0,0,\
                   -105,-210,-210,-420,-630,-735,-525,-90500,\
                    0,0,0,0,0,0};
        
        ll hyouka_sum=0;
        FOR(k,1,29){
            FOR(i,1,10){
                FOR(j,1,10){
                    if(b[k][i][j]){
                        hyouka_sum+=hyo[k];
                    }
                }
            }
        }
        FOR(k,1,9){
            ll maisu=0;
            if(k==1) maisu=18;
            else if(k==2 or k==3 or k==4 or k==7) maisu=4;
            else if(k==5 or k==6 or k==8) maisu=2;            
            for(ll m=maisu-1; 0<=m; m--){// 後ろから使う
                if(bm[k][m]){
                    hyouka_sum+=mhyo[k]; 
                }                 
            }
        }
        FOR(k,15,23){
            ll maisu=0;
            if(k==15) maisu=18;
            else if(k==16 or k==17 or k==18 or k==21) maisu=4;
            else if(k==19 or k==20 or k==22) maisu=2;
            for(ll m=maisu-1; 0<=m; m--){// 後ろから使う
                if(bm[k][m]){
                    hyouka_sum+=mhyo[k]; 
                }                   
            }            
        }
        return hyouka_sum;
    }

    Vll random(bool (&b0)[29][10][10], bool (&bm0)[29][18], ll &turn){// 合法手の内からランダムに選んで指す
        VVll goho(0,Vll(5));
        goho=this->gohosyu(this->b0, this->bm0, this->turn0);
        
        // 生成器をループ内部にいれると初期値が毎回同じになるのでインスタンス変数に隔離した
        mt19937 mt(this->rnd());     //  メルセンヌ・ツイスタの32ビット版
        uniform_int_distribution<> rand100(0,goho.size()-1);//一様乱数
        ll te=rand100(mt);

        Vll A(6,0);// 返す配列 
        A[0]=goho[te][0];
        A[1]=goho[te][1];
        A[2]=goho[te][2];
        A[3]=goho[te][3];
        A[4]=goho[te][4];
        A[5]=0;// 評価値をつける randomでは評価値なしなので適当に0
                
        return A;
    }

    Pa minmax_dfs(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn, ll &depth_max, ll depth){// minmaxの内部 局面を値渡しでなく(元,指し手)(次,元との差分)という感じでもつ
        if(depth_max==depth){// 最も深い層ではその局面の評価値だけ返す
            Pa e;
            e.first=this->hyouka(b,bm,turn);
            e.second=0;// 最深層で(これ以降掘らないので)何番目の指し手とかいらん
            return e;
        }
        
        Pa eval;// この階層で一番おいしい評価値(eval.first)と指し手(eval.second)を持っておく
        VVll goho=this->gohosyu(b,bm,turn);
        ll cnt=0;// 何番目の指し手か指定する
        for(auto v: goho){
            VVll sabun=this->move(v[0],v[1],v[2],v[3],v[4],b,bm,turn);// 元の局面に戻るため sabunを受け取る
            // 再帰開始
            Pa e=this->minmax_dfs(b,bm,turn,depth_max,depth+1);
            if(cnt==0){
                eval.first=e.first;
                eval.second=0;// この階層では最初を基準にしておく
            }
            // 再帰からの帰り
            for(auto &c: sabun){//別の手も試すので局面を元に戻す
                if(c[0]==0){// 盤の上
                    b[c[1]][c[2]][c[3]]=not(b[c[1]][c[2]][c[3]]);
                }
                else if(c[0]==1){// 駒台
                    bm[c[1]][c[2]]=not(bm[c[1]][c[2]]);
                }    
            }
            turn*=-1;// 手番も元に戻す
            
            if(turn==1){// 先手として高い値が欲しい
                if(chmax(eval.first,e.first)) eval.second=cnt;
            }
            else if(turn==-1){// 後手として低い値が欲しい
                if(chmin(eval.first,e.first)) eval.second=cnt;
            }

            cnt+=1;
        }

        return eval;// この階層での結論を返す
    }

    Vll minmax(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn){// minmax法でn手先まで探索する
        ll depth_max=4;
        ll depth=1;
        Pa eval=this->minmax_dfs(b,bm,turn,depth_max,depth);

        ll te=eval.second;
        VVll goho=this->gohosyu(b,bm,turn);
        Vll A(6,0);
        A[0]=goho[te][0];
        A[1]=goho[te][1];
        A[2]=goho[te][2];
        A[3]=goho[te][3];
        A[4]=goho[te][4];
        A[5]=eval.first;
        
        return A;
    }

    Pa alphabeta_dfs(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn, ll &depth_max, ll depth, Vll &ab,ll &alpha, ll &beta){// aplhabeta法の内部 局面を値渡しでなく(元,指し手)(次,元との差分)という感じでもつ
        if(depth_max==depth){// 最も深い層ではその局面の評価値だけ返す
            Pa e;
            e.first=this->hyouka(b,bm,turn);
            e.second=0;// 最深層で(これ以降掘らないので)何番目の指し手とかいらん
            return e;
        }
        
        Pa eval;
        VVll goho=this->gohosyu(b,bm,turn);
        ll cnt=0;// 何番目の指し手か指定する
        for(auto v: goho){
            VVll sabun=this->move(v[0],v[1],v[2],v[3],v[4],b,bm,turn);// 元の局面に戻るため sabunを受け取る

            // 再帰開始
            Pa e=this->alphabeta_dfs(b,bm,turn,depth_max,depth+1,ab,alpha,beta);
            if(cnt==0){
                eval.first=e.first;
                eval.second=0;// 下から来た候補はここの候補を超える可能性がある
            }
            
            // 再帰からの帰り
            for(auto &c: sabun){//別の手も試すので局面を元に戻す
                if(c[0]==0){// 盤の上
                    b[c[1]][c[2]][c[3]]=not(b[c[1]][c[2]][c[3]]);
                }
                else if(c[0]==1){// 駒台
                    bm[c[1]][c[2]]=not(bm[c[1]][c[2]]);
                }    
            }
            turn*=-1;// 手番も元に戻す
            

            if(turn==1){// 先手として高い値が欲しい
                if(chmax(eval.first,e.first)) eval.second=cnt;

                if(alpha<ab[depth] and eval.first<ab[depth]){// 初期値でないabより下の値がきたら先手は採用しない
                    break;
                }
            }
            else if(turn==-1){// 後手として低い値が欲しい
                if(chmin(eval.first,e.first)) eval.second=cnt;
                if(ab[depth]<beta and ab[depth]<eval.first){// 初期値でないabより上の値がきたら後手は採用しない
                    break;
                }                 
            }
            cnt+=1;
        }

        if(turn==1) chmax(ab[depth],eval.first);// その下の集計が終わった
        else if(turn==-1) chmin(ab[depth],eval.first);// その下の集計が終わった

        return eval;// この階層での結論を返す
    }

    Vll alphabeta(bool (&b)[29][10][10], bool (&bm)[29][18], ll &turn){// alphabeta法でn手先まで探索する
        ll depth_max=4;
        ll depth=1;
        Vll ab(depth_max+1,0);// ab[d]:=層dでalpha値or beta値をもって更新していく
        ll alpha=-300000, beta=300000;// 評価値eは alpha<=e<=betaで探索の中で狭まっていく
        
        
        if(turn==1){
            FOR(d,1,depth_max+1){
                if(d%2==1) ab[d]=alpha;
                else if(d%2==0) ab[d]=beta;
            }
        }
        else if(turn==-1){
            FOR(d,1,depth_max+1){
                if(d%2==1) ab[d]=beta;
                else if(d%2==0) ab[d]=alpha;
            }            
        }
        
        Pa eval=this->alphabeta_dfs(b,bm,turn,depth_max,depth,ab,alpha,beta);

        ll te=eval.second;
        VVll goho=this->gohosyu(b,bm,turn);

        Vll A(6,0);
        A[0]=goho[te][0];
        A[1]=goho[te][1];
        A[2]=goho[te][2];
        A[3]=goho[te][3];
        A[4]=goho[te][4];
        A[5]=eval.first;
        OI("ソフトの選んだ手と評価値(数が大きいほど先手もち)")
        OIV(A);

        return A;// 指し手，評価値を返す
    }


};

int main(){
    // 評価値の工夫 NNは序盤中盤までとしてできる範囲で
    // 定跡30手目あたりまで

    Shogi s;
    s.ui();
    

    return 0;
}
