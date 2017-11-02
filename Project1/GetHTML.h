#ifndef GETHTML_H
#define GETHTML_H

#include <Windows.h>
#include <WinInet.h>
#include <string>
#pragma comment(lib, "WinInet.lib")

class GetHTML {
private:
	static GetHTML *mInstance;

private:
	GetHTML();

public:
	static GetHTML* getIns();
	static void generate(char*, char*);
};

#endif
