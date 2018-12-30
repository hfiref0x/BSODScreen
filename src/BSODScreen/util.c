/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2018
*
*  TITLE:       UTIL.C
*
*  VERSION:     1.01
*
*  DATE:        29 Dec 2018
*
*  Program support routines.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#include "global.h"

/*
* IsReactOS
*
* Purpose:
*
* Return TRUE if the given system is identified as ReactOS.
*
*/
BOOL IsReactOS(
    VOID
)
{
    BOOL bResult = FALSE;
    HKEY hKey;
    DWORD dwType, dwSize;
    LPTSTR lpBuffer;
    HANDLE hSection = NULL;
    CONST WCHAR szRegKey[] = TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
    STATIC_UNICODE_STRING(usSectionName, (PWSTR)L"\\KnownDlls\\kernel32_vista.dll");
    OBJECT_ATTRIBUTES obja = RTL_INIT_OBJECT_ATTRIBUTES(&usSectionName, OBJ_CASE_INSENSITIVE);

    if (NT_SUCCESS(NtOpenSection(&hSection, SECTION_QUERY, &obja))) {
        CloseHandle(hSection);
        bResult = TRUE;
    }

    if (bResult == FALSE) {

        if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            szRegKey, 0, KEY_QUERY_VALUE, &hKey))
        {
            if (ERROR_SUCCESS == RegQueryValueEx(hKey,
                TEXT("ProductName"), NULL, &dwType, NULL, &dwSize))
            {
                if (dwType == REG_SZ) {
                    lpBuffer = (LPTSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
                    if (lpBuffer) {

                        if (ERROR_SUCCESS == RegQueryValueEx(hKey,
                            TEXT("ProductName"), NULL, &dwType, (LPBYTE)lpBuffer, &dwSize))
                        {
                            bResult = (_strcmpi(lpBuffer, TEXT("ReactOS")) == 0);
                        }
                        HeapFree(GetProcessHeap(), 0, lpBuffer);
                    }
                }
            }

            RegCloseKey(hKey);
        }
    }

    return bResult;
}
