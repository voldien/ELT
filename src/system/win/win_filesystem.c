#include"system/elt_file.h"



int ExCreateDirectory(const ExChar* directory){
	return CreateDirectory(directory,NULL);

}

ExBoolean ExIsDirectory(const ExChar* cdirectory){
	return EX_FALSE;
}

int ExRemoveFile(const ExChar* cfilename){
	return 0;
}

int ExExistFile(const ExChar* cfilename){
	return 0;

}
