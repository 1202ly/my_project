#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include<vector>
#include<windows.h>

#include"Heap.h"
#include"Huffman.h"
#include"CompressFile.h"

int main()
{
	CompressDocumentTest1();
	CompressDocumentTest2();
	CompressPhotoTest();
	CompressVideoTest();
	system("pause");
	return 0;
}
