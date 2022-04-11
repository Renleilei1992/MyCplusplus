作者：北极
链接：https://www.zhihu.com/question/285907675/answer/2433279260
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#define  _CRT_SECURE_NO_WARNINGS


#include <Windows.h>
#include <string.h>
#include <stdio.h>

int TotalFiles;
int TotalDirectories;

void SearchDirectory(LPCTSTR lpPath)
{
    TCHAR FindDir[MAX_PATH] = { 0 };
    TCHAR SubDir[MAX_PATH] = { 0 };

    WIN32_FIND_DATA FindFileData;
    BOOL bRet;

    wcscpy(FindDir, lpPath);
    wcscat(FindDir, L"\\*.*");

    HANDLE hFind = FindFirstFile(FindDir, &FindFileData);
    if (INVALID_HANDLE_VALUE == hFind)
    {
        return;
    }
    bRet = TRUE;
    while (bRet == TRUE)
    {

        if (wcscmp(FindFileData.cFileName, L".") != 0
            && wcscmp(FindFileData.cFileName, L"..") != 0)
        {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                TotalDirectories++;
                wcscpy(SubDir, lpPath);
                wcscat(SubDir, L"\\");
                wcscat(SubDir, FindFileData.cFileName);

                SearchDirectory(SubDir);
            }
            else
            {
                TotalFiles++;
            }

        }
        bRet = FindNextFile(hFind, &FindFileData);
    }

    FindClose(hFind);
}

int main(int argc, char *argv[])
{
    LARGE_INTEGER Freq, Start, End;
    TCHAR Path[MAX_PATH];

    MultiByteToWideChar(CP_ACP, 0, argv[1], strlen(argv[1]) + 1, Path, sizeof(Path));
    
    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);
    SearchDirectory(Path);
    QueryPerformanceCounter(&End);
    printf("Total Files [%d] Total Directories [%d]\n", TotalFiles, TotalDirectories);
    printf("Counter [%lld] Freq [%lld], Total [%lld] ms\n",
           End.QuadPart - Start.QuadPart, 
           Freq.QuadPart,
           (End.QuadPart - Start.QuadPart) * 1000 / Freq.QuadPart);

    return 0;
}
