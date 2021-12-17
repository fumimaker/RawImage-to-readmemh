# RawImage-to-readmemh
RAW画像(RGB)のバイナリを$readmemhで読めるようにバイナリテキスト+改行ファイルに変換する

# Usage
- inputimageで入力画像名を指定
- outputimageで出力ファイル名を指定
- DEPTHとWIDTHとHEIGHTを変更
- `gcc raw_readmemh.c -o rawreadmemh` でコンパイル
- 実行すると同じディレクトリにファイルが出力される。