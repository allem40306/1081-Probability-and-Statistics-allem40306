# 作業
請用 Least Square 找出 $n$ 次多項式 $P(x)\to f(x)$，分析， $n$ 次多項式的最佳選擇為何?

# 執行說明
* 請在 command 輸入 g++ gauss.cpp && a > test.out
* 輸出在 test.out
* 內容為 1~44 次多項式的 error(6 和 8 為空白行)，以及最佳解 42 次多項次的點

# 結果
* 最佳選擇為 n = 28(28次多項式)
* 判斷法
    * ![](https://i.imgur.com/6MkjjEh.png)
* 結果如下(黃線為 28次多項式，紅點為測試資料)：
    * ![](https://i.imgur.com/0aGwsRk.png)