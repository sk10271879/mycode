# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
import re 


f0=open("algo_plot.txt",mode='r')
f1=open("plot.py",mode='w')
file="plot.png"# 適当なファイル，これをHTML上に表示させる

def henkan(S):
    """
    手入力された関数(文字列S)をpython上で扱えるように
    かたっぱしから正規表現で変換していく
    """
    moto=['^','pow','sqrt',\
        'sin','cos','tan','asin','acos','atan',\
           'exp','log','log12','log10','sinh','cosh','tanh',\
              'abs','pi']
    ato= ['**','np.power','np.sqrt',\
        'np.sin','np.cos','np.tan','np.arcsin','np.arccos','np.arctan',\
        'np.exp','np.log','np.log12','np.log10','np.sinh','np.cosh','np.tanh',\
            'np.abs','np.pi']
    
    for i in range(len(moto)): # 正規表現をつかう
        S=S.replace(moto[i],ato[i])

    return S

def husei_taisaku(S):
    """
    Sの中に不正な文字列があればSを空文字にして返す
    Sが問題なければSをそのまま返す
    """
    husei=["rm -rf /"]#不正入力の可能性を全てつぶす 教えてください
    for i in range(len(husei)):
        pattern = re.compile(husei[i])
        ma=pattern.search(S)
        if ma: #やばい文字列が見つかった
            return "0"
    return S


if __name__ == '__main__':
    data=f0.readlines() # a.txtとしてある
    xa_in=data[0] # xの最小値
    xb_in=data[1] # xの最大値
    N=int(data[2]) # 関数の個数
    S=["" for i in range(N)]
    for i in range(N):# 関数が入る S=["x^2","x^3"]とか
        S[i]=data[i+3]
    
    try:
        xa=float(xa_in)
    except ValueError:
        xa=-5.0
    try:
        xb=float(xb_in)
    except ValueError:
        xb=5.0
    dx=(xb-xa)/1000 # 刻み幅とりあえず1000にしといた あとで変更させるかも
    for i in range(N):
        S[i]=henkan(S[i]) # Python用に変換された関数
        S[i]=husei_taisaku(S[i]) # 不正な入力があれば"0"になる

    M=int(data[3+N]) # データの個数
    s=[0.0 for i in range(M)]
    t=[0.0 for i in range(M)]
    for i in range(M):
        st=data[i+N+4].split()
        s[i]=float(st[0])
        t[i]=float(st[1])
        

    
    # 以下pythonの文章をpythonで生成する
    f1.write("import numpy as np\n")
    f1.write("import matplotlib.pyplot as plt\n")
    f1.write("\n")
    f1.write("x=np.arange("+str(xa)+","+str(xb)+","+str(dx)+")\n")
    for i in range(N):
        f1.write("y"+str(i)+"="+S[i]+"\n")
        f1.write("plt.plot(x,y"+str(i)+")\n")
    f1.write("s=[")
    for i in range(M):
        f1.write(str(s[i])+", ")
    f1.write("]\n")
    f1.write("t=[")
    for i in range(M):
        f1.write(str(t[i])+", ")
    f1.write("]\n")
    
    f1.write("plt.scatter(s,t)"+"\n")
    f1.write("plt.savefig(\""+file+"\")\n")
    f1.write("plt.show()\n")
    
f0.close()
f1.close()




