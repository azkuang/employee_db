#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "file.h"
#include "parse.h"
#include "status.h"

#define REQUIRE_PATH (1 << 1) // shifts 1 bit into position 1 0010

// Function to print program usage
void print_usage(char *argv[]) {
	printf("Usage: %s -n -f <file_name>\n", argv[0]);
	printf("\t -n - create new file.\n");
	printf("\t -f - (required) path to file.\n");
	return;
}

int main(int argc, char *argv[]) {
	// Define command line variables
	int opt = 0;
	int require_input = 0;
	bool new_file = false;
	char *file_path = NULL;

	int dbfd = -1;
	struct dbheader_t *dbheader = NULL;

	// Command line controls
	while ((opt = getopt(argc, argv, "nf:")) != -1) {
		switch(opt) {
			case 'n':
				new_file = true;
				break;
			case 'f':
				file_path = optarg;
				require_input |= REQUIRE_PATH;
				break;
			case ':':
				printf("Option -%c requires an argument\n", optopt);
				break;
			case '?':
				printf("Unknown option: %c\n", optopt);
				break;
			default:
				printf("Unexpected input.\n");
				return -1;
		}
	}

	// Check that required flags are set
	if ((REQUIRE_PATH & require_input) != REQUIRE_PATH) {
		print_usage(argv);
		printf("Error: -f file path is missing.\n");
		return -1;
	}

	// Create new file if the new file flag is set
	if (new_file) {
		dbfd = create_new_file(file_path);
		if (dbfd == STATUS_ERROR) {
			printf("Unable to create file.\n");
			return -1;
		}

		if (create_dbheader(dbfd, &dbheader) == STATUS_ERROR) {
			printf("Error creating header.\n");
			return -1;
		}
	} else {
		dbfd = open_file(file_path);
		if (dbfd == STATUS_ERROR) {
			printf("Unable to open file.\n");
			return -1;
		}

		if (validate_dbheader(dbfd, &dbheader) != STATUS_SUCCESS) {
			printf("Unable to validate headers.\n");
			return -1;
		}
	}
		
	return 0;
}
