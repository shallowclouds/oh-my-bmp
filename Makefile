test.exe:main.o libbmp.o
	g++ -o test.exe main.o libbmp.o

main.o:main.cpp libbmp.h
	g++ -c main.cpp

libbmp.o:libbmp.cpp libbmp.h vardef.h
	g++ -c libbmp.cpp

clean:
	rm main.o libbmp.o test.exe