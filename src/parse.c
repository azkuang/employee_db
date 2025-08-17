#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "status.h"

int create_dbheader(int fd, struct dbheader_t **header_out) {
	struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
	if (header == NULL) {
		perror("calloc");
		return STATUS_ERROR;
	}

	header->magic = MAGIC_NUMBER;
	header->version = 0x01;
	header->count = 0;
	header->file_size = sizeof(struct dbheader_t);

	*header_out = header;

	return STATUS_SUCCESS;
}

