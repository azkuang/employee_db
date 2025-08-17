#ifndef PARSE_H
#define PARSE_H

#define MAGIC_NUMBER 0xABCD1010

struct dbheader_t {
	unsigned int magic;
	unsigned short version;
	unsigned short count;
	unsigned int file_size;
};

int create_dbheader(int fd, struct dbheader_t **header_out);
int validate_dbheader(int fd, struct dbheader_t **header_out);
int output_header(int fd, struct dbheader_t *dbheader);


#endif
