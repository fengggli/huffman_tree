CFLAG=-g
Huffman: Huffman.cpp  Huffman.h
	g++ -std=c++11 -o Huffman Huffman.cpp $(CFLAG)
clean:
	rm -rf *.o
	rm -rf Huffman
