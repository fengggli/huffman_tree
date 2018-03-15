Program 3: Huffman tree implementation
CSCI 58000 Introduction of Algorithm
Author: Feng Li, CIS Department, IUPUI

[![Build Status](https://travis-ci.org/fengggli/huffman_tree.svg?branch=master)](https://travis-ci.org/fengggli/huffman_tree)

use Huffman tree to encoding a cleartext file

# input file:
```
    path:
        freq.txt
    content:
        contains only characters form standard ASCII code, with its frequency in text, ordering by ascii value
    example:
        LF 2
        . 1
        M 7
        c 3
        d 5
        e 14
        f 2
```
    
# output file:
```
    path: 
        codetable.txt
    content:
        charaters from standard ASCii code, with its huffman encoding, ordering by ascii value 
    example:
        LF 1100
        . 11010
        M 111
        c 100
        d 101
        e 0
        f 11011
```
    
    
