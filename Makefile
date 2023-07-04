c:
	gcc -O3 -lX11 -lXcursor -lGL -ldl -lm -lasound -pthread demo/test.c
	strip a.out

cpp:
	g++ -O3 -lX11 -lXcursor -lGL -ldl -lm -lasound -pthread -fpermissive -Wnarrowing demo/test.cpp
	strip a.out

wasm:
	emcc -w -s WASM=1 -s USE_WEBGL2=1 -s ASYNCIFY=1 -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_MEMORY=512mb -O1 demo/test.c
