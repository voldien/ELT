#include"system/elt_zip.h"
#include<zlib.h>
#include<zip.h>
#include<errno.h>
#include<assert.h>


long int ExLoadZipFile(const char* archive, const char **cfilename, void **pbuf){
	struct zip_file *zfile;
	struct zip_stat stat;
	long int nbytes;
	struct zip *zip;
	int err;

	/*  Check arguments.    */
	if (!cfilename || !pbuf)
		return -1;

	zip = zip_open(archive, 0, &err);

	/*	Load zip file.	*/
	err = zip_stat(zip, cfilename, 0, &stat);
	if (err != 0) {
		char errorMsg[4096];
		char buf[1024];

		zip_error_to_str(buf, sizeof(buf), err, errno);
		sprintf(errorMsg, "%s - can't open `%s':\n", cfilename, buf);
		return -1;
	}

	/*	Open file inside zip.	*/
	zfile = zip_fopen(zip, cfilename, 0);
	if (!zfile)
		return -1;

	/*	Allocate size for file.	*/
	*pbuf = malloc(stat.size);
	assert(*pbuf);

	/*	Read file content.	*/
	nbytes = zip_fread(zfile, *pbuf, stat.size);

	/*	*/
	zip_fclose(zfile);
	zip_close(zip);
	return nbytes;
}

long int ExSaveZipFile(const char* archive, const char **cfilename, void *pbuf, int long size){
	struct zip_file *zfile;
	struct zip_stat stat;
	long int nbytes;
	struct zip *zip;
	int err;
	zip_source_t *s;

	/*  Check arguments.    */
	if (!cfilename || !pbuf)
		return -1;

	zip = zip_open(archive, 0, &err);

	/*	Write file content.	*/
	if ((s=zip_source_buffer(zip, pbuf, size, 0)) == NULL ||
	    zip_file_add(zip, cfilename, s, ZIP_FL_ENC_UTF_8) < 0) {
		zip_source_free(s);
		fprintf(stderr, "error adding file: %s\n", zip_strerror(zip));
		return -1;
	}

	/*	*/
	zip_fclose(zfile);
	zip_close(zip);
	return nbytes;
}
