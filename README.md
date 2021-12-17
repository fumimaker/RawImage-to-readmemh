# RawImage-to-readmemh
RAW画像(RGB)のバイナリを$readmemhで読めるようにバイナリテキスト+改行ファイルに変換する

## ファイルごとの役割
- raw_readmemh.c
  - RAWのRGBのバイナリをreadmemhで読めるようにテキストバイナリ+RGB24改行をしてくれるファイル
- raw_macroblock.c
  - RAWのバイナリ(RGB)を食わせると**マクロブロックごとに変形した**readmemhで読めるテキストバイナリを出力する
- renzoku.c
  - raw_macroblockのデバッグ用のコード。テスト用の連続したバイナリファイルを出力してくれる。おかしくなったらこれを食わせて様子を見る。

## Usage
- inputimageで入力画像名を指定
- outputimageで出力ファイル名を指定
- DEPTHとWIDTHとHEIGHTを変更
- `gcc raw_readmemh.c -o rawreadmemh` でコンパイル
- 実行すると同じディレクトリにファイルが出力される。
