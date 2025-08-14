#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

// #define REQUIRE_FILE (1 << 0) // shifts 1 bit into position 0 0001
#define REQUIRE_PATH (1 << 1) // shifts 1 bit into position 1 0010
// #define REQUIRED (REQUIRE_FILE | REQUIRE_PATH)

int main(int argc, char *argv[]) {
	int opt = 0;
	int require_input = 0;
	bool new_file = false;
	char *file_path = NULL;
	
	while ((opt = getopt(argc, argv, "nf:")) != -1) {
		switch(opt) {
			case 'n':
				// do something with new file?
				new_file = true;
				break;
			case 'f':
				// file path?
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
		}
	}

	if ((REQUIRE_PATH & require_input) != REQUIRE_PATH)
		printf("Error: -f (path) is required.\n");

//	if ((require_input & REQUIRED) != REQUIRED) {
//		printf("Error: missing required flags.\n");
//		if (!(require_input & REQUIRE_FILE))
//			printf("-n (file) is required.\n");
//		if (!(require_input & REQUIRE_PATH))
//			printf("-f (path) is required.\n");
//		return -1;
//	}

	printf("File name: %d\n", new_file);
	printf("File path: %s\n", file_path);
		
	return 0;
}
