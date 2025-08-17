#include <stdio.h>
#include <fcntl.h>

#include "status.h"

int create_new_file(char *file_path) {
	// Check if the file name already exists
	printf("%s\n", file_path);
	int fd = open(file_path, O_RDONLY);
	if (fd != -1) {
		printf("File already exists.\n");
		return STATUS_ERROR;
	}
	
	// Create a new file if the file does not already exist
	fd = open(file_path, O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		return STATUS_ERROR;
	}

	return fd;
}

int open_file(char *file_path) {
	int fd = open(file_path, O_RDWR, 0644);
	if (fd < 0) {
		perror("open");
		return STATUS_ERROR;
	}
	
	return fd;
}
