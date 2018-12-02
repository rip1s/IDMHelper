// Author: @unamer(https://github.com/unamer)

#import "IDManTypeInfo.tlb" 
#include "IDManTypeInfo.h"            
#include "IDManTypeInfo_i.c"
#include <atlbase.h>    //for CComBSTR class

void usage()
{
	printf("Usage:\tidmhelpr.exe <Option1> <Option2>...\n\nAvailable options:\n");
	puts("\t-u: your target url <Required>");
	puts("\t-a: your user-agent");
	puts("\t-c: your cookies");
	puts("\t-d: your post data");
	puts("\t-r: your referer");
	puts("\t-U: your username");
	puts("\t-P: your password");
	puts("\t-o: your download path (where your files will be downloaded)");
	puts("\t-s: your download file name");
	puts("\t-f: download without any confirmations");
	puts("\t-q: do not download, insert to queue only");
	puts("Example:\n");
	puts("\tidmhelper.exe -u https://www.google.com/ -a \"What ever ua\" -c \"my cookies\" -f");
	ExitProcess(0);
}
void main()
{
	int argc = 0;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	CComBSTR url;
	CComBSTR ua;
	CComBSTR cookies;
	CComBSTR data;
	CComBSTR referer;
	CComBSTR user;
	CComBSTR pass;
	CComBSTR path;
	CComBSTR fname;
	long flags = 0;

	puts("IDM Download helper by @unamer(https://github.com/unamer)\n");

	for (int i = 1; i < argc; i++)
	{
		if (!lstrcmp(argv[i], L"-h"))
		{
			usage();
		}
	}
	// roughly parse 
	// issues: parse error when user specify multi argv like -u url -u url2.
	for (int i = 1; i < argc; i++)
	{
		if (!lstrcmp(argv[i], L"-u") && (i + 1 != argc))
		{
			printf("[+] Current url: %S\n", argv[i + 1]);
			url.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-a") && (i + 1 != argc))
		{
			printf("[+] Current user-agent: %S\n", argv[i + 1]);
			ua.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-c") && (i + 1 != argc))
		{
			printf("[+] Current cookies: %S\n", argv[i + 1]);
			cookies.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-r") && (i + 1 != argc))
		{
			printf("[+] Current referer: %S\n", argv[i + 1]);
			referer.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-d") && (i + 1 != argc))
		{
			printf("[+] Current data: %S\n", argv[i + 1]);
			data.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-U") && (i + 1 != argc))
		{
			printf("[+] Current user: %S\n", argv[i + 1]);
			user.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-P") && (i + 1 != argc))
		{
			printf("[+] Current password: %S\n", argv[i + 1]);
			pass.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-o") && (i + 1 != argc))
		{
			printf("[+] Current download path: %S\n", argv[i + 1]);
			path.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-s") && (i + 1 != argc))
		{
			printf("[+] Current download file name: %S\n", argv[i + 1]);
			fname.Append(argv[i + 1]);
			i++;
		}
		if (!lstrcmp(argv[i], L"-f"))
		{
			printf("[+] Download without any confirmations\n");
			flags |= 1;
		}
		if (!lstrcmp(argv[i], L"-q"))
		{
			printf("[+] Do not download, add to queue only\n");
			flags |= 2;
		}
	}

	if (!url)
	{
		puts("[-] What do you want IDM to do?\n");
		usage();
	}

	CoInitialize(NULL);

	ICIDMLinkTransmitter2* pIDM;
	HRESULT hr = CoCreateInstance(CLSID_CIDMLinkTransmitter,
		NULL,
		CLSCTX_LOCAL_SERVER,
		IID_ICIDMLinkTransmitter2,
		(void**)&pIDM);
	if (S_OK == hr)
	{

		VARIANT var1, var2;
		VariantInit(&var1);
		VariantInit(&var2);
		if (ua)
		{
			var1.vt = VT_BSTR;
			var1.bstrVal = ua;
		}
		else
			var1.vt = VT_EMPTY;
		var2.vt = VT_EMPTY;
		
		hr = pIDM->SendLinkToIDM2(url, referer, cookies, data, user, pass, path, fname, flags, var1, var2);

		if (S_OK != hr)
		{
			puts("[-] SendLinkToIDM2 fail!");
		}
		else
		{
			puts("[+] SendLinkToIDM2 success!");
		}

		pIDM->Release();
	}
	else
	{
		puts("[-] CoCreateInstance fail!");
	}

	CoUninitialize();
	return ;
}