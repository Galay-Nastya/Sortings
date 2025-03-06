#include "sortings.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void free_content(FileContent *content) {
	if (content && content->lines) {
		for (size_t i = 0; i < content->size; i++) {
			free(content->lines[i]);
		}
		free(content->lines);
		content->lines = NULL;
		content->size = 0;
	}
}

FileContent read_file_API(const char *filename, size_t num_lines) {
	FileContent content = {NULL, 0};
	FILE *file = fopen(filename, "r");

	if (!file) {
		fprintf(stderr, "Unable to open file %s\n", filename);
		return content;
	}

	char **lines = malloc(num_lines * sizeof(char *));
	if (!lines) {
		fprintf(stderr, "Unable to allocate memory\n");
		fclose(file);
		return content;
	}

	size_t i = 0;
	char buffer[1024];
	while (i < num_lines && fgets(buffer, sizeof(buffer), file)) {
		lines[i] = strdup(buffer);
		if (!lines[i]) {
			fprintf(stderr, "Unable to allocate memory\n");
			for (size_t j = 0; j < i; j++) {
				free(lines[j]);
			}
			free(lines);
			fclose(file);
			return content;
		}
		i++;
	}

	fclose(file);
	content.lines = lines;
	content.size = i;
	return content;
}

FileContent read_file_mapped(const char *filename, size_t num_lines) {
	FileContent content = {NULL, 0};
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Unable to open file %s\n", filename);
		return content;
	}

	struct stat sb;
	if (fstat(fd, &sb) == -1) {
		fprintf(stderr, "Unable to get file size %s\n", filename);
		close(fd);
		return content;
	}

	char *addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED) {
		fprintf(stderr, "Error: Unable to map file %s\n", filename);
		close(fd);
		return content;
	}

	char **lines = malloc(num_lines * sizeof(char *));
	if (!lines) {
		fprintf(stderr, "Error: Unable to allocate memory\n");
		munmap(addr, sb.st_size);
		close(fd);
		return content;
	}

	size_t i = 0;
	char *start = addr;
	char *end = addr + sb.st_size;
	while (start < end && i < num_lines) {
		char *newline = memchr(start, '\n', end - start);
		if (newline) {
			lines[i] = strndup(start, newline - start + 1);
			start = newline + 1;
		} else {
			lines[i] = strdup(start);
			break;
		}
		i++;
	}

	munmap(addr, sb.st_size);
	close(fd);
	content.lines = lines;
	content.size = i;
	return content;
}