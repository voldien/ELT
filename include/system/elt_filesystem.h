/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2016  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_FILE_SYSTEM_H_
#define _ELT_FILE_SYSTEM_H_ 1
#include"../system.h"

#ifdef __cplusplus	/*	C++ Environment	*/
extern "C"{
#endif


/**
 *	Change file permission bits.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExChangeFileMode(const char* cpath, unsigned int mode);

/**
 *	Get file permission bits.
 *
 *	@Return
 */
extern ELTDECLSPEC unsigned int ELTAPIENTRY ExGetFileMode(const char* cfilename);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetFileOwner(const char* cpath, const char* user, const char* group);



/**
 *	Create directory.
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExCreateDirectory(const ExChar* directory);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExIsDirectory(const ExChar* cdirectory);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC Uint32 ELTAPIENTRY ExDirectoryCount(const ExChar* cdirectory);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC const ExChar* ELTAPIENTRY ExGetSubDirectory(const ExChar* cdirectory, int index);

/**
 *	Remove directory.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExRemoveDirectory(const ExChar* directory);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExCreateFile(const ExChar* cfilename);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExFilesCount(const char* cdirectory);

/**
 *	Remove file by given name.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExRemoveFile(const ExChar* cfilename);

/**
 *	Return true if file exist.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExExistFile(const ExChar* cfilename);

/**
 *	Check if file is readable of current user permission
 *	of the the process.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExReadableFile(const ExChar* cfilename);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExWritableFile(const ExChar* cfilename);

/**
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExExecutableFile(const ExChar* cfilename);



/**
 *	Get current directory of the process.
 *
 *	@Return
 */
extern ELTDECLSPEC ExChar* ELTAPIENTRY ExGetCurrentDirectory(ExChar* cwd, unsigned int len);

/**
 *	Set current directory of the process.
 *
 *	@Return
 */
extern ELTDECLSPEC int ELTAPIENTRY ExSetCurrentDirectory(const ExChar* cdirectory);


/**
 *	Get Relative Path.
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetRelativePath(const ExChar* cpath, ExChar* basename, Int32 lengthSize);


/**
 *	Get path cfilename
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetBaseName(const ExChar* cpath, ExChar* basename, Int32 lengthSize);

/**
 * 	Get directory
 *	@Return
 */
extern ELTDECLSPEC char* ELTAPIENTRY ExGetDirectory(const ExChar* cpath, ExChar* dirname, Int32 lengthSize);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExGetAbsolutePath(const ExChar* cfilename, ExChar* absolute, Int32 lengthSize);






/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExCreateRamDisk(const ExChar* cdirectory, unsigned int nBytes);


/**
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExMount(const ExChar* source, const ExChar* target, const ExChar* filesystemtype, unsigned long mountflags, const void *data);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExBoolean ELTAPIENTRY ExUMount(const ExChar* cdirectory);



#ifdef __cplusplus	/*	C++ Environment	*/
}
#endif

#endif
