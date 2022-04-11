作者：北极
链接：https://www.zhihu.com/question/285907675/answer/2433279260
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

int TotalFiles;
int TotalDirectories;

int SearchDirectory(char * path)
{
	DIR * dirfd;
	struct dirent * entry;
	char subpath[256];
	
	dirfd = opendir(path);

	while((entry = readdir(dirfd)) != NULL)
	{
		strcpy(subpath, path);
		strcat(subpath, "/");
		strcat(subpath, entry->d_name);
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
		{
			if (entry->d_type == DT_DIR)
			{
				TotalDirectories++;
				SearchDirectory(subpath);
			}
			else
			{
				TotalFiles++;
			}
		}
	}
	closedir(dirfd);
	return 0;
}

int main(int argc, char * argv[])
{
	time_t st, ed;
	st = clock();
	SearchDirectory(argv[1]);
	ed = clock();
	printf("Total Files [%d] Total Directories [%d]\n", TotalFiles, TotalDirectories);
	
	printf("Counter [%ld] Freq [%ld], Total [%ld] ms\n", 
		ed - st, 
		CLOCKS_PER_SEC,
		(ed - st) * 1000 / CLOCKS_PER_SEC);
	
	return 0;
}
