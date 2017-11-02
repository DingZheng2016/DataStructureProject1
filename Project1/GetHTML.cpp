#include "GetHTML.h"

GetHTML* GetHTML::mInstance = nullptr;

GetHTML::GetHTML() {

}

GetHTML* GetHTML::getIns(){
	if (mInstance == nullptr)
		mInstance = new GetHTML;
	return mInstance;
}

void GetHTML::generate(char* url1, char* url2) {
	HINTERNET hInternet = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //��ʼ��WinINet
	HINTERNET hConnect = InternetConnectA(hInternet, url1, INTERNET_DEFAULT_HTTP_PORT,
		NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0); //���ӷ�����
	HINTERNET hOpenRequest = HttpOpenRequestA(hConnect, "GET", url2, NULL, NULL,
		(LPCSTR*)"*/*", INTERNET_FLAG_DONT_CACHE, 1); //����http����
	BOOL bRequest = HttpSendRequestA(hOpenRequest, NULL, 0, NULL, 0); //����http����
	char szBuffer[1024] = { 0 };
	DWORD dwByteRead = 0;
	FILE* fp = NULL;
	fopen_s(&fp, "a.html", "w");
	while (InternetReadFile(hOpenRequest, szBuffer, sizeof(szBuffer), &dwByteRead) && dwByteRead > 0)
	{
		fwrite(szBuffer, dwByteRead, 1, fp);
		ZeroMemory(szBuffer, dwByteRead);
	}
	fclose(fp);
}