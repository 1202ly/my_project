#define CRTDBG_MAP_ALLOC
#include<iostream>
using namespace std;
#include<assert.h>
#include<string>
#include<vector>
#include<windows.h>
#include<time.h>
#include<stdio.h>
#include<tchar.h>
#include<sys/timeb.h>
#include<stdlib.h>
#include<crtdbg.h>//检测内存泄漏
#include"Heap.h"
#include"Huffman.h"
#include"CompressFile.h"

//定义检测内存函数
//该函数可以放在主函数的任意位置，都可以检测出内存泄漏
inline void EnableMemLeakCheak()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

/*############################黑盒测试用例#########################################*/
//压缩txt文件和docx文件
void CompressDocumentTest()
{
	cout << "//////////////////////////////压缩文档(.txt)时间///////////////////////////////////" << endl;
	DWORD start_time = GetTickCount();
	CompressFile cf;
	cf.Compress("file.txt");
	DWORD end_time = GetTickCount();
	cout << "The Document compress time is:" << (end_time - start_time) << "ms!" << endl;
	cout << "//////////////////////////////解压文档(.txt)时间///////////////////////////////////" << endl;
	DWORD start1_time = GetTickCount();
	CompressFile cf1;
	cf1.uncompress("file.compress");
	DWORD end1_time = GetTickCount();
	cout << "The Document uncompress time is:" << (end1_time - start1_time) << "ms!" << endl;

	//cout << "//////////////////////////////压缩文档(.docx)时间///////////////////////////////////" << endl;
	//DWORD start2_time = GetTickCount();
	//CompressFile cf2;
	//cf2.Compress("卢莹.docx");
	//DWORD end2_time = GetTickCount();
	//cout << "The Document compress time is:" << (end2_time - start2_time) << "ms!" << endl;
	//cout << "//////////////////////////////解压文档(.docx)时间///////////////////////////////////" << endl;
	//DWORD start3_time = GetTickCount();
	//CompressFile cf3;
	//cf3.uncompress("卢莹.compress");
	//DWORD end3_time = GetTickCount();
	//cout << "The Document uncompress time is:" << (end3_time - start3_time) << "ms!" << endl;
}
//压缩图片
void CompressPhotoTest()
{
	cout << "//////////////////////////////压缩图片时间///////////////////////////////////" << endl;
	DWORD start_time = GetTickCount();
	CompressFile cf;
	cf.Compress("挖坑.png");
	DWORD end_time = GetTickCount();
	cout << "The Photo compress time is:" << (end_time - start_time) << "ms!" << endl;
	cout << "//////////////////////////////解压图片时间///////////////////////////////////" << endl;
	DWORD start1_time = GetTickCount();
	CompressFile cf1;
	cf1.Compress("挖坑.png");
	DWORD end1_time = GetTickCount();
	cout << "The Photo uncompress time is:" << (end1_time - start1_time) << "ms!" << endl;
}
//压缩视频
void CompressVideoTest()
{
	cout << "//////////////////////////////压缩视频时间///////////////////////////////////" << endl;
	DWORD start_time = GetTickCount();
	CompressFile cf;
	cf.Compress("爱很美.mp4");
	DWORD end_time = GetTickCount();
	cout << "The Video compress time is:" << (end_time - start_time) << "ms!" << endl;
	cout << "/////////////////////////////////解压视频时间////////////////////////////////////" << endl;
	DWORD start1_time = GetTickCount();
	CompressFile cf1;
	cf1.uncompress("爱很美.compress");
	DWORD end1_time = GetTickCount();
	cout << "The Video uncompress time is:" << (end1_time - start1_time) << "ms!" << endl;

	//cout << "//////////////////////////////压缩BIG视频时间///////////////////////////////////" << endl;
	//DWORD start2_time = GetTickCount();
	//CompressFile cf3;
	//cf3.Compress("EP01.mp4");
	//DWORD end2_time = GetTickCount();
	//cout << "The Video compress time is:" << (end2_time - start2_time) << "ms!" << endl;
	//cout << "/////////////////////////////////解压BIG视频时间////////////////////////////////////" << endl;
	//DWORD start3_time = GetTickCount();
	//CompressFile cf4;
	//cf4.uncompress("EP01.compress");
	//DWORD end3_time = GetTickCount();
	//cout << "The Video uncompress time is:" << (end3_time - start3_time) << "ms!" << endl;
}
//压缩音频
void CompressMusicTest()
{
	cout << "//////////////////////////////压缩音频时间///////////////////////////////////" << endl;
	DWORD start_time = GetTickCount();
	CompressFile cf;
	cf.Compress("丫头.mp3");
	DWORD end_time = GetTickCount();
	//cf.uncompress("爱很美.compress");
	cout << "The Music compress time is:" << (end_time - start_time) << "ms!" << endl;
	cout << "/////////////////////////////////解压音频时间////////////////////////////////////" << endl;
	DWORD start1_time = GetTickCount();
	CompressFile cf1;
	cf1.uncompress("丫头.compress");
	DWORD end1_time = GetTickCount();
	cout << "The Music uncompress time is:" << (end1_time - start1_time) << "ms!" << endl;
}
int main()
{
	cout << "############################黑盒和白盒结合测试用例#########################################" << endl;
	EnableMemLeakCheak();//检测内存泄漏函数调用
	CompressDocumentTest();
	CompressPhotoTest();
	CompressVideoTest();
	CompressMusicTest();
	system("pause");
	return 0;
}
