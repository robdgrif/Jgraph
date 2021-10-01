
main: main.cpp
	g++ -Wall -o main main.cpp
	./jj -P ex/test1.jgr | ps2pdf - | convert -density 300 - -quality 100 ex/test1.jpg
	./jj -P ex/test2.jgr | ps2pdf - | convert -density 300 - -quality 100 ex/test2.jpg
	./jj -P ex/test3.jgr | ps2pdf - | convert -density 300 - -quality 100 ex/test3.jpg
	./jj -P ex/test4.jgr | ps2pdf - | convert -density 300 - -quality 100 ex/test4.jpg
	./jj -P ex/test5.jgr | ps2pdf - | convert -density 300 - -quality 100 ex/test5.jpg


