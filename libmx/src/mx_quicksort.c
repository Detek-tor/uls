#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
	if (!arr) return -1;
	
	int count = 0;
	if (left < right) {
		char *middle = arr[(left + right)/2];
		int i = left;
		int j = right;
		
		while (i <= j) {
			while (mx_strlen(arr[i]) < mx_strlen(middle)) {
				i++;
			}
			while (mx_strlen(arr[j]) > mx_strlen(middle)) {
				j--;
			}
			if (i <= j) {
				if(mx_strlen(arr[i]) != mx_strlen(arr[j])){
					char *tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
					count++;
				}
				i++;
				j--;
			}
		}
		
		count += mx_quicksort(arr, left, j);
		count += mx_quicksort(arr, i, right);
	}
	return count;
}


