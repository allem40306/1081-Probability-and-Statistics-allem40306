1. Backpropagation 與 Perceptron 算法比較：Perceptron 的算出的結果固定($0$ 或 $1$)，所以終止迴圈的條件可以是 ”所有的訓練資料得出來的結果與目標值都吻合”。Backpropagation 得出來的結果則是一個區間($0$ 到 $1$)，相較Perceptron 能呈現更精準的特徵值，但也不易讓得出來的結果與目標值吻
合，所以控制誤差值，只要誤差值小於特定數即可終止。
2. 不同 neuron 個數比較(下面兩張圖為參考資料)：大多數時候都是 neuron多的時候正確率較高，這代表著 neuron 數越多，越能修正 weight 和 bias。
3. 不同 learning rate 比較：以本實驗來說， $0.3$ 及 $0.4$ 比 $0.1$ 及 $0.2$ 好，$0.5$ 則幅度太大，反而使正確率降低。
4. Training data 和 Testing data 討論：理論上來說，Training data 的正確率會比較高，但我做出來的結果反而是 Testing Data 比較高，原因可能是因為我的 weight 和 bias 初始值影響，或是我的誤差容忍度需要調整。

![](https://i.imgur.com/9brBjUq.png)
![](https://i.imgur.com/H42HtAg.png)
