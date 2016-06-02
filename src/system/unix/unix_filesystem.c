#include"system/elt_file.h"
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int ExCreateDirectory(const ExChar* directory){
	return mkdir(directory, 644);
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


ExBoolean ExCreateFile(const ExChar* cfilename){
	return creat(cfilename, O_CREAT | O_RDWR) != -1;
}

int ExRemoveFile(const ExChar* cfilename){
	return remove(cfilename);
}

int ExExistFile(const ExChar* cfilename){
	return !access(cfilename, F_OK);
}








ExChar* ExGetCurrentDirectory(ExChar* cwd, unsigned int len){
	if (getcwd(cwd, len) != NULL){
	   fprintf(stdout, "Current working dir: %s\n", cwd);
	}
	else{
	   perror("getcwd() error");
	}
	return cwd;

}

Int32 ExSetCurrentDirectory(const ExChar* cdirectory){
	return chdir(cdirectory);
}





















ExBoolean ExCreateRamDisk(const ExChar* cdirectory, unsigned int nBytes){
	ExChar buf[PATH_MAX];
	int result;
	int size;
	ExChar* src = "none";
	if(nBytes > 1024)
		size = nBytes / 1024;
	if(nBytes > 1048576)
		size = nBytes / 1048576;
	if(nBytes > 1073741824)
		size = nBytes / 1073741824;

	//-t -size=%dk
	sprintf(buf, "mode=0700,uid=65534");
	const unsigned long mntflags = 0;
	const char* type = "tmpfs";
	if( (result = mount("none", cdirectory, type, mntflags,  buf)) < 0){
		char* strerr = strerror(errno);
		ExPrintf("Error : Failed to mount %s\nReason: %s [%d]\n",
				cdirectory, strerr, errno);
		return FALSE;
	}
	return TRUE;
}

ExBoolean ExUMount(const ExChar* cdirectory){
	if(umount(cdirectory) < 0){
		ExPrintf("Error : Failed to mount %s\nReason: %s [%d]\n",
				cdirectory, strerror(errno), errno);
		return FALSE;
	}
	return TRUE;
}



