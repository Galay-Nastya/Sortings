#include "../lib/sortings.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_sort_bubble() {
	FileContent content = read_file_API("/home/nastya/myHomework/input.txt", 3);
	sort_bubble(content.lines, content.size, comparator_asc);
	assert(strcmp(content.lines[0], "Hello\n") == 0);
	assert(strcmp(content.lines[1], "Hello World!\n") == 0);
	assert(strcmp(content.lines[2], "Hello!\n") == 0);

	free_content(&content);
}

void test_sort_insertion() {
	FileContent content = read_file_API("../input.txt", 3);
	sort_insertion(content.lines, content.size, comparator_asc);
	assert(strcmp(content.lines[0], "Hello\n") == 0);
	assert(strcmp(content.lines[1], "Hello World!\n") == 0);
	assert(strcmp(content.lines[2], "Hello!\n") == 0);

	free_content(&content);
}

void test_sort_merge() {
	FileContent content = read_file_API("../input.txt", 3);
	sort_merge(content.lines, content.size, comparator_des);
	assert(strcmp(content.lines[0], "Hello!\n") == 0);
	assert(strcmp(content.lines[1], "Hello World!\n") == 0);
	assert(strcmp(content.lines[2], "Hello\n") == 0);

	free_content(&content);
}

void test_sort_quick() {
	FileContent content = read_file_API("../input.txt", 3);
	sort_quick(content.lines, content.size, comparator_des);
	assert(strcmp(content.lines[0], "Hello!\n") == 0);
	assert(strcmp(content.lines[1], "Hello World!\n") == 0);
	assert(strcmp(content.lines[2], "Hello\n") == 0);

	free_content(&content);
}

void test_sort_radix() {
	FileContent content = read_file_API("../input.txt", 3);
	sort_radix(content.lines, content.size, comparator_des, DES);
	assert(strcmp(content.lines[0], "Hello!\n") == 0);
	assert(strcmp(content.lines[1], "Hello World!\n") == 0);
	assert(strcmp(content.lines[2], "Hello\n") == 0);

	free_content(&content);
}

int main() {
	test_sort_bubble();
	test_sort_insertion();
	test_sort_merge();
	test_sort_quick();
	test_sort_radix();

	printf("All tests passed!\n");
	return 0;
}