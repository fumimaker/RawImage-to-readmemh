DIR="dma_udp"

rm jpeg/*
rm binout/*
scp root@203.178.128.231:~/ultra96_software/$DIR/binout/* ./binout/
./makejpeg