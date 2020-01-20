output: dwmblocks.c blocks.h
	cc `pkg-config --cflags x11` `pkg-config --libs x11` dwmblocks.c -o dwmblocks
	cc -o internetav internetav.c
clean:
	rm -f *.o *.gch dwmblocks internetav
install: output
	mkdir -p /usr/local/bin
	cp -f dwmblocks /usr/local/bin
	cp -f internetav /usr/local/bin
