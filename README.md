# mycode

# 0.概要<br>
本レポジトリはsk10271879の主にアルゴ式で用いるコードを保管しておくものです．
<br>
<br>

# 1.アルゴ式とは<br>
https://algo-method.com/<br>

アルゴ式というプログラミングを勉強できるサイト．
教科書，問題(オンラインジャッジ)，解説(めっちゃ丁寧)がそろっている．
<br>
<br>


# 2.各ファイルの大まかな説明<br>

* read_me.txt<br>
アルゴ式にグラフをプロットするページがあれば鬼に金棒なので，<br>
それの一部をpythonで書いてみたalgo_plot.pyなどの詳細の説明．
<br>

* algo_plot.txt<br>
ユーザーが入力した関数，プロットデータを以下のように加工した入力ファイル<br>
xの最小値<br>
xの最大値<br>
関数の個数<br>
関数0(np.などを省略していきなり sin(x)などと記述する)<br>
関数1<br>
関数2<br>
..<br>
生データの個数<br>
生データ0(x,yの生データをspaceあけて 6.0 3.5 などと記述する)<br>
生データ1<br>
生データ2<br>
..<br>
<br>

* algo_plot.py<br>
algo_plot.txtから入力を受け取り，<br>
関数をpython用に変換し，新たにplot.pyを生成する．<br>
<br>



* plot.py<br>
matplotlibを使ってグラフに関数と生データの散布図を
指定された範囲にプロットするもの．plot.pngも同時に作成する．
<br>



* shogi.cpp<br>
ここで働かせてくださいの時に将棋プログラムを以下の要件で作成したもの．<br>
bitboardの未熟版<br>
簡単な駒ごとの点数を足した評価関数<br>
αβ探索を用い探索<br>
<br>






