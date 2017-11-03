#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <string>

#define CHARSTRING_SIZE_INIT 20
#define CHARSTRING_SIZE_INCREMENT 500

class CharString {
public:
	wchar_t *s;
	unsigned int len;
	unsigned int size;

public:
	CharString();
	CharString(CharString&);
	CharString(std::wstring);
	~CharString();
	
	//Interface
	void concat(std::wstring);
	void concat(wchar_t);
	void concat(CharString&);
	void assign(std::wstring);
	CharString& operator = (CharString&);
	bool equal(CharString&);
	CharString& substring(int, int); //左闭右开
	int toInt(); //转成数字，处理形如 &#*****; 


	void output(bool space = true); //为false是自动忽略空格回车，主要用于帖子内容的输出
	
};

#endif