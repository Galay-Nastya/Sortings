#pragma once

#define ASC "asc"
#define DES "des"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char **lines;
	size_t size;
} FileContent;

int8_t comparator_asc(const char *a, const char *b);
int8_t comparator_des(const char *a, const char *b);

void sort_bubble(char **arr, size_t size, int8_t (*comparator)(const char *, const char *));
void sort_insertion(char **arr, size_t size, int8_t (*comparator)(const char *, const char *));
void sort_merge(char **arr, size_t size, int8_t (*comparator)(const char *, const char *));
void sort_quick(char **arr, size_t size, int8_t (*comparator)(const char *, const char *));
void sort_radix(char **arr, size_t size, int8_t (*comparator)(const char *, const char *),
				const char *type_comparator);
FileContent read_file_API(const char *filename, size_t num_lines);
FileContent read_file_mapped(const char *filename, size_t num_lines);
void free_content(FileContent *content);