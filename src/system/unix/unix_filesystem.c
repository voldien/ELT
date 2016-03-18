#include"system/elt_file.h"
#include<unistd.h>
#include<dirent.h>


int ExCreateDirectory(const ExChar* directory){
	return mkdir(directory,644);
}

ExBoolean ExIsDirectory(const ExChar* cdirectory){
	DIR* dir = opendir(cdirectory);
	if(dir){
		closedir(dir);
		return TRUE;
	}
	return FALSE;
}

Uint32 ExDirectoryCount(const ExChar* cdirectory){
	DIR* dir = opendir(cdirectory);
	int count = 0;
	struct dirent* dirent;
	if(dir){
		while( (dirent = readdir(dir)) != NULL){
			if(dirent->d_type == 4)
				count++;
		}
		count -= 2; /*	remove this and parent node.*/
		closedir(dir);
	}
	return count;
}

const ExChar* ExGetSubDirectory(const ExChar* cdirectory, int index){
	DIR* dir = opendir(cdirectory);
	int count = 0;
	struct dirent* dirent;
	char directory[PATH_MAX];
	if(dir){
		while( (dirent = readdir(dir)) != NULL){
			if(dirent->d_type == 4){
				if(count == index){
					sprintf(directory, "%s%s", cdirectory, dirent->d_name);
					closedir(dir);
					return directory;
				}
				count++;
			}
		}
		closedir(dir);
	}
	return NULL;
}


int ExRemoveDirectory(const ExChar* directory){
	return rmdir(directory);
}

int ExRemoveFile(const ExChar* cfilename){
	return remove(cfilename);
}

int ExExistFile(const ExChar* cfilename){
	return !access(cfilename, F_OK);
}


