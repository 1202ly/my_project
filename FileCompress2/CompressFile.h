#define _CRT_SECURE_NO_WARNINGS 1
#pragma once;
typedef long long LongType;
struct CharInfo
{
	CharInfo(size_t count=0)
	    :_count(count)
	{}
	bool operator !=(const CharInfo& info)
	{
		return _count != info._count;
	}
	bool operator ==(const CharInfo& info)
	{
		return _count == info._count;
	}
	CharInfo operator+(const CharInfo& ch)
	{
		CharInfo ret;
		ret._count = this->_count + ch._count;
		return ret;
	}
	bool operator<(const CharInfo& ch)
	{
		return this->_count < ch._count;
	}
	char _ch;//字符
	LongType _count;//字符的次数
	string code;//编码
};
#define MAXSIZE 1024
typedef struct Head//头部信息结构
{
	string filepostfix;//文件后缀
	string codeinfo;//编码规则信息
	char strcount[32];//保存转化后的字符数字（有效字符出现的次数）
	size_t linecount = 0;//保存有效字符的行数
}Head;
#define MAXSIZE 1024

class CompressFile
{
public:
	typedef HuffmanTreeNode<CharInfo>* node;
	CompressFile()
	{
		for (size_t i = 0; i < 256; i++)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
		//测试案例1
	}
	void Compress(const string& filename)
	{
		//1.读取源文件，统计每个字符出现的次数
		FILE* fin = fopen(filename.c_str(), "rb");
		if (NULL == fin)
		{
			cout << "找不到该文件" << endl;
			return;
		}
		char* readbuf = new char[MAXSIZE];//将读取的文件写入缓冲区中
		//测试1：输出源文件的字符总数
		size_t SourceCount = 0;
		while (true)
		{
			//fread是一个函数，它从文件流中读数据，最多读取count个项，每个项size个字节，
			//如果调用成功返回实际读取到的项个数（小于或等于count），如果不成功或读到文件末尾返回 0。
			size_t readsize = fread(readbuf, 1, 1024, fin);
			if (0 == readsize)
			{
				break;
			}
			for (size_t i = 0; i < readsize; i++)
			{
				_infos[(unsigned char)readbuf[i]]._count++;
				SourceCount++;
			}
			readsize = 0;
		}
		cout << "源文件出现的字符总数：" << SourceCount << endl;

		//2.以某个字符出现的次数为权值构建huffman树
		CharInfo index;//无效字符
		index._count = 0;
		HuffmanTree<CharInfo> ht(_infos, 256, index);

		//3.根据Huffman树来获取Huffman编码
		gethuffmancode(ht.Getroot());

		//写压缩文件的头部信息
		Head header;
		header.filepostfix = getfilepostfix(filename);//文件后缀
		//压缩文件中要保存的信息
		//1、文件后缀信息
		//2、编码规则
		//3、压缩信息
		for (size_t i = 0; i < 256; i++)
		{
			if (_infos[i]._count)//当前字符出现的次数不等于0
			{
				header.codeinfo += _infos[i]._ch;//保存字符
				header.codeinfo += ':';
				_itoa_s((int)_infos[i]._count, header.strcount, 10);
				header.codeinfo += header.strcount;
				header.codeinfo += '\n';
				header.linecount++;
			}
		}
		string headinfo;//保存头部信息
		headinfo += header.filepostfix;//先保存后缀
		headinfo += '\n';//换行
		_itoa_s(header.linecount, header.strcount, 10);//保存编码规则一共多少行
		headinfo += header.strcount;
		headinfo += '\n';//换行
		headinfo += header.codeinfo;//编码信息
		
		//4用每个字符的编码改写源文件
		string  compressfile = getfilepath(filename);//获取文件前缀
		compressfile += ".compress";//然后在前缀后面加上压缩之后的后缀
		FILE* fout = fopen(compressfile.c_str(), "wb");
		assert(fout);

		//先写的是压缩编码的信息(也就是上述保存的头部信息)
	    fwrite(headinfo.c_str(), 1, headinfo.size(), fout);	
		char *writebuf = new char[MAXSIZE];//一次性往文件中写1024个字节
		char pos = 0;//标记目前移位了多少位，够不够8次
		char ptr = 0;//保存字符对应的编码（依次取出每个字符的编码，然后放进去）8位 10010110
		size_t writesize = 0;//往writebuf里存放了多少个字节
		fseek(fin, 0, SEEK_SET);//（很重要啊）重置文件指针的位置，第二个参数是相对于第三个参数的偏移量
		//测试打印信息：保存压缩之后的字符总数
		int CompreeCount = 0;

		while (true)
		{
			size_t readsize = fread(readbuf, 1, MAXSIZE, fin);//一次性读取1024个字符（如果没将文件指针重置，这里的指针还在文件的结尾）
			if (0 == readsize)//一直读到文件结尾
			{
				break;
			}
			for (size_t i = 0; i < readsize; ++i)
			{
				string& code = _infos[(unsigned char)readbuf[i]].code;//取到编码
				for (size_t j = 0; j < code.size(); ++j)//放到字节中，每个字节8个比特位
				{
					pos++;			
					if ('1' == code[j])
					{
						ptr |= 1;
					}
					else
					{
						ptr |= 0;
					}
					if (pos == 8)
					{
						writebuf[writesize++] = ptr;
						ptr = 0;
						if (MAXSIZE == writesize)
						{
							fwrite(writebuf, 1, MAXSIZE, fout);
							writesize = 0;//写完一次置0
						}
						CompreeCount++;
						pos = 0;//置0
					}
					//move  pos change x//
					ptr <<= 1;
				}//for j
			}
		}
		//如果没满8个比特位
		if (pos < 8)
		{
			writebuf[writesize++] = (ptr << (8 - pos));
			CompreeCount++;
		}
		fwrite(writebuf, 1, writesize, fout);
		fclose(fin);
		fclose(fout);
		cout << "压缩了的字符个数：" << CompreeCount << endl;
		delete[] readbuf;
		delete[] writebuf;
	}
	string getfilepostfix(string filename)//获取文件的后缀
	{
		size_t pos = filename.find_last_of('.');//从后向前找到'.'所在的位置
		return filename.substr(pos);
	}
	string getfilepath(string filename)//获取文件路径（物理路径/当前路径）
	{
		size_t pos = filename.find_last_of('.');
		return filename.substr(0, pos);
	}
	void uncompress(const string& filename)
	{
		FILE* fin = fopen(filename.c_str(), "rb");//以只读方式读取文件信息
		assert(fin);

		//读取信息，一次性读取一行
		string strinfo;//保存（读取的文件后缀）
		strinfo = '1';
		ReadLine(fin, strinfo);//一次性读取一行
		string strlinecount;//保存（读取的行号）
		ReadLine(fin, strlinecount);
		size_t linecount = atoi(strlinecount.c_str());//获取行号（字符串转为整型）
		string strcodeinfo;//保存字符编码信息
		char ctemp = 0;
		int count = 0;
		//读每个字符出现的次数，方便还原Huffman编码
		for (size_t i = 0; i < linecount; i++)
		{
			strcodeinfo.clear();//清空字符串内容，方便下一次读取
			ReadLine(fin, strcodeinfo);
			if (i == 255)//eof ungetc() 不能把eof放回到流里面
			{
				count = atoi(strcodeinfo.c_str() + 1);
				_infos[255]._count = count;//读每个字符出现的次数
			}
			else
			{
				count = atoi(strcodeinfo.c_str() + 2);
				_infos[(unsigned char)strcodeinfo[0]]._count = count;//读每个字符出现的次数
			}
		}
		
		//还原Huffman树
		HuffmanTree<CharInfo> ht(_infos, 256, CharInfo(0));
		//解压缩
		size_t writesize = 0;
		size_t pos = 8;
		//string compressFiltpath = getfilepath(filename);//先找到压缩文件的路径
		//compressFiltpath += strinfo;//路径+后缀就是压缩文件的路径
		//FILE* fout = fopen(compressFiltpath.c_str(), "w");//这里会覆盖源文件
		//为了对比明显，我们这里重新输出到另外一个文件
		string compressFilepath = getfilepath(filename);
		compressFilepath +=/*"1.png"*/ strinfo;
		FILE* fout = fopen(compressFilepath.c_str(), "wb");
		assert(fout);


		node cur = ht.Getroot();
		LongType filesize = cur->_weight._count;//源文件一共有多少个字符
		size_t UnCompressCount = 0;
		char* readbuf = new char[MAXSIZE];
		char* writebuf = new char[MAXSIZE];
		while (true)
		{
			size_t readsize = fread(readbuf, 1, MAXSIZE, fin);
			if (0 == readsize)
			{
				break;
			}
			for (size_t i = 0; i < readsize; i++)
			{
				pos = 8;
				while (pos--)
				{
					if (NULL == cur->_pleft&&NULL == cur->_pright)//一个字符解析成功
					{
						writebuf[writesize++] = cur->_weight._ch;
						if (writesize == MAXSIZE)
						{
							fwrite(writebuf, 1, MAXSIZE, fout);
							writesize = 0;
						}
						if (--filesize==0)
						{
							fwrite(writebuf, 1, writesize, fout);
							break;
						}
						cur = ht.Getroot();//走到叶子，又从根开始
					}
					if (readbuf[i] & 1 << pos)//结果为1，表示该比特位为1
					{
						cur = cur->_pright;
					}
					else
					{
						cur = cur->_pleft;
					}
				}//while
				UnCompressCount++;
			}//for
		}//while
		cout << "解压了的字符个数：" << UnCompressCount << endl;
		delete[]readbuf;
		delete[]writebuf;
		fclose(fin);
		fclose(fout);
	} 

	void ReadLine(FILE*fin, string& strinfo)//有问题
	{
		//if (feof(fin))
		//{
		//	return;
		//}
		char next = 0;
		char c = fgetc(fin);
		while (c != '\n')
		{
			strinfo += c;
			c = fgetc(fin);
			//if (feof(fin))//读到结尾
			//{
			//	return;
			//}
		}
		if ((next = fgetc(fin)) == ':')
		{
			char next_next = fgetc(fin);
			if (next_next == ':')
			{
				ungetc(next, fin);
				ungetc(next_next, fin);
			}
			else
			{
			
				strinfo += c ;
				strinfo += next;
				strinfo += next_next;
				ReadLine(fin, strinfo);
			}
		}
		else
			ungetc(next, fin);
	}
private:
	void gethuffmancode(node root)//huffman编码代码块
	{
		if (root == NULL)
		{
			return;                                                                             
		}
		if (NULL == root->_pleft&&NULL == root->_pright)//到达叶子节点
		{
			node cur = root;
			node parent = cur->_parent;
			string& code = _infos[(unsigned char)cur->_weight._ch].code;
			while (parent)
			{
				if (cur == parent->_pleft)
				{
					code += '0';
				}
				else
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}//编码是反的
			reverse(code.begin(), code.end());
		}
		gethuffmancode(root->_pleft);
		gethuffmancode(root->_pright);
	}
	CharInfo _infos[256];
};
