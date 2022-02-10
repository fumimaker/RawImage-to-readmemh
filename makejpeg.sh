# DIR="dma_udp"
# DIR="rcvudp"

rm jpeg/*
rm binout/*
# scp root@203.178.128.231:~/ultra96_software/dma_udp/binout/* ./binout/
scp fumi@MacBooK-Prokamoshirenai.local:~/GitHub/ultra96_software/rcvudp/binout/* ./binout/
./makejpeg