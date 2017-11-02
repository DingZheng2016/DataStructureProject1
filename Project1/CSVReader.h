#ifndef CSVREADER_H
#define CSVREADER_H

#include <cstdio>
#include <iostream>
#include <string>

#define MAX_LINE 2048

class CSVReader {
private:
	FILE *fp;
public:
	CSVReader(std::string);
	~CSVReader();

	char* getUrl();
};

#endif