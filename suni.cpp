#define UNICODE

#include <iostream>
#include <sstream>
#include <windows.h>

void main(void)
{
    wchar_t* strData = "¯\_(ツ)_/¯";

    if (OpenClipboard(0)) {
        EmptyClipboard();
        HGLOBAL hClipboardData;
        hClipboardData = GlobalAlloc(GMEM_DDESHARE, 2 * (wcslen(strData) + 1));

        WCHAR* pchData;
        pchData = (WCHAR*)GlobalLock(hClipboardData);
        wcscpy(pchData, strData);
        GlobalUnlock(hClipboardData);
        SetClipboardData(CF_UNICODETEXT, hClipboardData);
        CloseClipboard();
    }

}
