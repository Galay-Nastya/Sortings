#include "sortings.h"

#define BUBBLE "bubble"
#define INSERTION "insertion"
#define MERGE "merge"
#define QUICK "quick"
#define RADIX "radix"

int main(int32_t argc, char **argv) {
	if (argc != 5) {
		fprintf(stderr, "Incorrect input data\n");
		return -1;
	}

	size_t num_lines = atoi(argv[1]);
	char *file_name = argv[2];
	char *algo_sort = argv[3];
	char *comparator_name = argv[4];

	FileContent content;
#ifdef USE_MMAP
	content = read_file_mapped(file_name, num_lines);
#else
	content = read_file_API(file_name, num_lines);
#endif

	if (content.lines == NULL && content.size == 0) {
		return -1;
	}

	if (content.size != num_lines) {
		fprintf(stderr, "Unable to read %zu lines from file %s\n", num_lines, file_name);
		free_content(&content);
		return -1;
	}

	int8_t (*comparator)(const char *, const char *) = NULL;
	if (strcmp(comparator_name, ASC) == 0) {
		comparator = comparator_asc;
	} else if (strcmp(comparator_name, DES) == 0) {
		comparator = comparator_des;
	} else {
		fprintf(stderr, "Invalid comparator name\n");
		free_content(&content);
		return -1;
	}

	if (strcmp(algo_sort, BUBBLE) == 0) {
		sort_bubble(content.lines, content.size, comparator);
	} else if (strcmp(algo_sort, INSERTION) == 0) {
		sort_insertion(content.lines, content.size, comparator);
	} else if (strcmp(algo_sort, MERGE) == 0) {
		sort_merge(content.lines, content.size, comparator);
	} else if (strcmp(algo_sort, QUICK) == 0) {
		sort_quick(content.lines, content.size, comparator);
	} else if (strcmp(algo_sort, RADIX) == 0) {
		sort_radix(content.lines, content.size, comparator, comparator_name);
	} else {
		fprintf(stderr, "Invalid algorithm name\n");
		free_content(&content);
		return -1;
	}

	for (size_t i = 0; i < content.size; i++) {
		printf("%s", content.lines[i]);
	}
	free_content(&content);

	return 0;
}