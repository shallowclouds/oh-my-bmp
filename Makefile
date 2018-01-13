test.exe:main.o libbmp.o
	clang++ -o test.exe main.o libbmp.o --target=x86_64-w64-mingw

main.o:main.cpp libbmp.h light.h
	clang++ -c main.cpp --target=x86_64-w64-mingw

libbmp.o:libbmp.cpp libbmp.h vardef.h
	clang++ -c libbmp.cpp --target=x86_64-w64-mingw

clean:
	rm main.o libbmp.o test.exe

multi:libbmp.o
	clang++ multi.cpp -o thread.exe libbmp.o -std=c++11 --target=x86_64-w64-mingw

compare:multi test.exe
	compare.bat
