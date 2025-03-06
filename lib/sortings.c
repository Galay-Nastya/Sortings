#include "sortings.h"

int8_t comparator_asc(const char *string1, const char *string2) {
	return (int8_t)strcmp(string1, string2);
}

int8_t comparator_des(const char *string1, const char *string2) {
	return (int8_t)strcmp(string2, string1);
}

void merge(char **arr, size_t left, size_t mid, size_t right,
		   int8_t (*comparator)(const char *, const char *)) {
	size_t size_left = mid - left + 1;
	size_t size_right = right - mid;

	char **left_arr = malloc(size_left * sizeof(char *));
	char **right_arr = malloc(size_right * sizeof(char *));

	for (size_t i = 0; i < size_left; i++)
		left_arr[i] = arr[left + i];
	for (size_t j = 0; j < size_right; j++)
		right_arr[j] = arr[mid + 1 + j];

	size_t i = 0, j = 0, k = left;
	while (i < size_left && j < size_right) {
		if (comparator(left_arr[i], right_arr[j]) <= 0) {
			arr[k] = left_arr[i];
			i++;
		} else {
			arr[k] = right_arr[j];
			j++;
		}
		k++;
	}

	while (i < size_left) {
		arr[k] = left_arr[i];
		i++;
		k++;
	}

	while (j < size_right) {
		arr[k] = right_arr[j];
		j++;
		k++;
	}

	free(left_arr);
	free(right_arr);
}

size_t partition(char **arr, size_t low, size_t high,
				 int8_t (*comparator)(const char *, const char *)) {
	char *pivot = arr[high];
	size_t i = low;

	for (size_t j = low; j < high; j++) {
		if (comparator(arr[j], pivot) <= 0) {
			char *temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
	}

	char *temp = arr[i];
	arr[i] = arr[high];
	arr[high] = temp;

	return i;
}

void quick_sort_recursion(char **arr, size_t low, size_t high,
						  int8_t (*comparator)(const char *, const char *)) {
	if (low < high) {
		size_t pi = partition(arr, low, high, comparator);
		if (pi > 0)
			quick_sort_recursion(arr, low, pi - 1, comparator);
		quick_sort_recursion(arr, pi + 1, high, comparator);
	}
}

void reverse_string_array(char **arr, size_t size) {
	for (size_t i = 0; i < size / 2; i++) {
		char *temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}
}

char get_char_at(const char *str, size_t pos) {
	if (pos < strlen(str))
		return str[pos];
	return 0;
}

void sort_bubble(char **arr, size_t size, int8_t (*comparator)(const char *, const char *)) {
	for (size_t i = 0; i < size - 1; i++) {
		int swapped = 0;
		for (size_t j = 0; j < size - 1 - i; j++) {
			if (comparator(arr[j], arr[j + 1]) > 0) {
				char *temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
}

void sort_insertion(char **arr, size_t size, int8_t (*comparator)(const char *, const char *)) {

	for (size_t i = 1; i < size; i++) {
		char *key = arr[i];
		size_t j = i;
		while (j > 0 && comparator(arr[j - 1], key) > 0) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = key;
	}
}

void sort_merge(char **arr, size_t size, int8_t (*comparator)(const char *, const char *)) {
	if (size < 2)
		return;

	size_t mid = size / 2;
	sort_merge(arr, mid, comparator);
	sort_merge(arr + mid, size - mid, comparator);
	merge(arr, 0, mid - 1, size - 1, comparator);
}

void sort_quick(char **arr, size_t size, int8_t (*comparator)(const char *, const char *)) {
	quick_sort_recursion(arr, 0, size - 1, comparator);
}

void sort_radix(char **arr, size_t size, int8_t (*comparator)(const char *, const char *),
				const char *type_comparator) {
	(void)comparator;
	size_t max_len = 0;
	for (size_t i = 0; i < size; i++) {
		size_t len = strlen(arr[i]);
		if (len > max_len)
			max_len = len;
	}

	for (size_t pos = max_len; pos > 0; pos--) {
		size_t count[256] = {0};
		char **output = malloc(size * sizeof(char *));

		for (size_t i = 0; i < size; i++) {
			unsigned char c = (unsigned char)get_char_at(arr[i], pos - 1);
			count[c]++;
		}

		for (size_t i = 1; i < 256; i++) {
			count[i] += count[i - 1];
		}

		for (size_t i = size; i > 0; i--) {
			unsigned char c = (unsigned char)get_char_at(arr[i - 1], pos - 1);
			output[count[c] - 1] = arr[i - 1];
			count[c]--;
		}

		for (size_t i = 0; i < size; i++) {
			arr[i] = output[i];
		}
		free(output);
	}
	if (strcmp(type_comparator, DES) == 0)
		reverse_string_array(arr, size);
}