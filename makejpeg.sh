# DIR = "dma_udp"
# DIR = "rcvudp"

rm jpeg/*
rm binout/*
# scp root@203.178.128.231:~/ultra96_software/dma_udp/binout/* ./binout/ #Ultra96自身のデータをjpegにしたいとき
# scp fumi@MacBooK-Prokamoshirenai.local:~/GitHub/ultra96_software/rcvudp/binout/* ./binout/ # Macのデータをjpegにしたいとき
scp fumi@203.178.128.70:/home/fumi/github/receivejpeg/rcvudp/binout/* ./binout/
./makejpeg # VM CUIのデータをjpegにしたいとき