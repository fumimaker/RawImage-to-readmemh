# RawImage-to-readmemh
RAW画像(RGB)のバイナリを$readmemhで読めるようにバイナリテキスト+改行ファイルに変換する

## ファイルごとの役割
- raw_readmemh.c
  - RAWのRGBのバイナリをreadmemhで読めるようにテキストバイナリ+RGB24改行をしてくれるファイル
- raw_macroblock.c
  - RAWのバイナリ(RGB)を食わせると**マクロブロックごとに変形した**readmemhで読めるテキストバイナリを出力する
- renzoku.c
  - raw_macroblockのデバッグ用のコード。テスト用の連続したバイナリファイルを出力してくれる。おかしくなったらこれを食わせて様子を見る。

# raw_macrobrock.cの使い方
1. 元の画像を用意する。
2. 1:1にトリミングする(ペイント3Dなどでできる)
3. IrfanViewなどで96*96にリサイズしてraw形式(RGB)で保存する。
4. [raw_macroblock.c](https://github.com/fumimaker/RawImage-to-readmemh/blob/main/raw_macroblock.c)を使ってRawをマクロブロック配列に並び替えてテキストバイナリに変換。.txtになる
5. txtをコピーしてVivadoの.memに貼り付ける
6. Simを回す
7. Simの結果、simフォルダにoutput.binがあるのでBZなどバイナリエディタで編集してヘッダ+Simの結果のBin+FFD9をつける
8. 画像が完成する。


# quant.cの使い方
Qualityを指定してコンパイル実行するとターミナルに結果が出てくるのでそれをVivadoの.memにコピペする

# header.cの使い方
QualityとHeight Widthを指定してコンパイル実行する。outputnameに指定したところに.binが出てくる。これがヘッダになっているのでVivadoのSimで生成したJpegのBitstreamと結合するとJpegになる。
