# mycode

# 0.概要
本レポジトリはsk10271879の主にアルゴ式で用いるコードを保管しておくものです．


# 1.アルゴ式とは
https://algo-method.com/
アルゴ式というプログラミングを勉強できるサイト．
教科書，問題(オンラインジャッジ)，解説(めっちゃ丁寧)がそろっている．



# 2.各ファイルの大まかな説明


*read_me.txt
アルゴ式にグラフをプロットするページがあれば鬼に金棒なので
それの一部をpythonで書いてみたalgo_plot.pyなどの詳細の説明

*algo_plot.txt
ユーザーが入力した関数，プロットデータを以下のように加工した入力
xの最小値
xの最大値
関数の個数
関数0(np.などを省略していきなり sin(x)などと記述する)
関数1
関数2
..
生データの個数
生データ0(x,yの生データをspaceあけて 6.0 3.5 などと記述する)
生データ1
生データ2
..

*algo_plot.py
algo_plot.txtから入力を受け取り
関数やデータ(x,y)を受け取り，
plot.pyを作成する．


plot.py
matplotlibを使ってグラフに関数と生データの散布図を
想定した範囲にプロットするもの．





*shogi.cpp
ここで働かせてくださいの時に将棋プログラムを以下の要件で作成したもの．
bitboardの未熟版
簡単な駒ごとの点数を足した評価関数
αβ探索を用い探索




