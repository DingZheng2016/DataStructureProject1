#define _CRT_SECURE_NO_WARNINGS
#include "CSVReader.h"
#include "Stack.h"

CSVReader::CSVReader(std::string filename) {
	fp = fopen(filename.c_str(), "r");
	char st[1000];
	fgets(st, 1024, fp);
}

CSVReader::~CSVReader() {
	fclose(fp);
}

char* CSVReader::getUrl() {
	char st[1024];
	char pre[] = "http://";
	char* url = new char[1024];
	memset(url, '\0', sizeof(url));
	fgets(st, 1024, fp);
	for(int i = 0; i < strlen(st); ++i)
		if (st[i] == '"') {
			bool fail = false;
			for(int j = 0; j < strlen(pre) && j + i + 1 < strlen(st); j++)
				if (pre[j] != st[i + j + 1]) {
					fail = true;
					break;
				}
			if (fail)
				continue;
			for (int j = i + strlen(pre) + 1; j < strlen(st); ++j)
				if (st[j] != '"') {
					url[j - i - strlen(pre) - 1] = st[j];
				}
				else {
					url[j - i - strlen(pre) - 1] = '\0';
					return url;
				}
		}
	return NULL;
}
