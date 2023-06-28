c:
	gcc -O3 -lX11 -lXcursor -lGL -ldl -lm -lasound -pthread demo/test.c
	strip a.out

cpp:
	g++ -O3 -lX11 -lXcursor -lGL -ldl -lm -lasound -pthread -fpermissive -Wnarrowing demo/test.cpp
	strip a.out
