CFLAG=-g
Huffman: Huffman.cpp  Huffman.h
	g++ -o Huffman Huffman.cpp $(CFLAG)
clean:
	rm -rf *.o
	rm -rf Huffman
