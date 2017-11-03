#include "CharString.h"
#include <cstdlib>
#include <iostream>

CharString::CharString()
{
	size = CHARSTRING_SIZE_INIT;
	s = (wchar_t*)malloc(sizeof(wchar_t) * size);
	len = 0;
	//std::wcout.imbue(std::locale::locale("chs"));
}

CharString::CharString(CharString& m)
{
	//printf("in CharString(CharString&)\n");
	size = m.size;
	len = 0;
	s = (wchar_t*)malloc(sizeof(wchar_t) * size);
	for (int i = 0; i < m.len; ++i)
		s[len++] = m.s[i];
	s[len] = '\0';
}

CharString::CharString(std::wstring str)
{
	size = CHARSTRING_SIZE_INIT;
	s = (wchar_t*)malloc(sizeof(wchar_t) * size);
	len = 0;
	while (str.size() + len >= size) {
		s = (wchar_t*)realloc(s, sizeof(wchar_t) * (size + CHARSTRING_SIZE_INCREMENT));
		size += CHARSTRING_SIZE_INCREMENT;
	}
	for (int i = 0; i < str.size(); ++i)
		s[len++] = str[i];
}

CharString::~CharString()
{
	free(s);
}

void CharString::concat(std::wstring str)
{
	while (str.size() + len >= size) {
		s = (wchar_t*)realloc(s, sizeof(wchar_t) * (size + CHARSTRING_SIZE_INCREMENT));
		size += CHARSTRING_SIZE_INCREMENT;
	}
	for (int i = 0; i < str.size(); ++i)
		s[len++] = str[i];
	s[len] = '\0';
}

void CharString::concat(wchar_t ch)
{
	while (len + 1 >= size) {
		s = (wchar_t*)realloc(s, sizeof(wchar_t) * (size + CHARSTRING_SIZE_INCREMENT));
		size += CHARSTRING_SIZE_INCREMENT;
	}
	s[len++] = ch;
	s[len] = '\0';
}

void CharString::concat(CharString& str)
{
	while (len + str.len >= size) {
		s = (wchar_t*)realloc(s, sizeof(wchar_t) * (size + CHARSTRING_SIZE_INCREMENT));
		size += CHARSTRING_SIZE_INCREMENT;
	}
	for (int i = 0; i < str.len; ++i)
		s[len++] = str.s[i];
}

void CharString::assign(std::wstring str)
{
	len = 0;
	concat(str);
}

CharString& CharString::operator=(CharString& m)
{
	len = 0;
	if (size < m.size) {
		free(s);
		size = m.size;
		s = (wchar_t*)malloc(sizeof(wchar_t) * size);
	}
	for (int i = 0; i < m.len; ++i)
		s[len++] = m.s[i];
	s[len] = '\0';
	return *this;
}

bool CharString::equal(CharString& m)
{
	if (len != m.len)return false;
	for (int i = 0; i < len; ++i)
		if (s[i] != m.s[i])
			return false;
	return true;
}

CharString& CharString::substring(int frindex, int toindex)
{
	CharString* nstr = new CharString;
	for (int i = frindex; i < toindex; ++i)
		nstr->concat(s[i]);
	return *nstr;
}

int CharString::toInt()
{
	int num = 0, k = 1;
	for (int i = 0; i < len; ++i)
		num = num * 10 + s[i] - '0';
	return num;
}

//Test
void CharString::output(bool space)
{
	if (space) {
		for (int i = 0; i < len; ++i)
			printf("%Lc", s[i]);
	}
	else {
		for (int i = 0; i < len; ++i)
			if (s[i] != ' ' && s[i] != '\n')
				printf("%Lc", s[i]);
	}
	
}