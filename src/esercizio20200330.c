#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long fibonacci(unsigned int n){
	unsigned long result;
	if (n==0)
		result = 0;
	else if(n==1)
		result = 1;
	else
		result = fibonacci(n-1)+fibonacci(n-2);

	return result;
}

unsigned long * fibonacci_array(unsigned int n){

	unsigned long * array = calloc(n+1,sizeof(unsigned long));
	if (array == NULL) {
			perror("calloc error!");
			exit(EXIT_FAILURE);
		}
	for(int i=0; i<n+1; i++){
		array[i]=fibonacci(i);
	}

	return array;
}

void swap_ulong(unsigned long *x, unsigned long *y) {
	unsigned long t = *x;
	*x = *y;
	*y = t;
}

unsigned long * reverse_ulong(unsigned long * array, unsigned int i, unsigned int j){
	while (i < j)
		swap_ulong(&array[i++], &array[--j]);

	return array;
}

unsigned long * complete_reverse_ulong(unsigned long * array, unsigned int array_len) {
	return reverse_ulong(array, 0, array_len);
}

void bubble_sort(unsigned long * array, unsigned int array_dimension) {

	int i;
	int n = array_dimension;
	int newn =  0;
	while(n > 1){
		for(int i=1; i<n; i++){
			if (array[i-1]>array[i]){
				swap_ulong(&array[i-1],&array[i]);
				newn = i;
			}
		}
		n = newn;
	}
}

void test_array(unsigned long * array,unsigned int length){
	for(int i=0; i<length; i++)
		printf("%lu ",array[i]);
	printf("\n\n");
}

int main(int argc, char *argv[]) {

	unsigned long * fibonacci_result = fibonacci_array(39);
		printf("Ecco la serie di fibonacci fino a n=39:\n");
			test_array(fibonacci_result,40);

	unsigned long * fibonacci_result_copy = calloc(40,sizeof(unsigned long));
		if (fibonacci_result_copy == NULL) {
				perror("calloc error!");
				exit(EXIT_FAILURE);
			}

	memcpy(fibonacci_result_copy,fibonacci_result,40*sizeof(unsigned long));
	fibonacci_result_copy = complete_reverse_ulong(fibonacci_result_copy,40);
		printf("Ecco la serie di fibonacci fino a n=39 ribaltata:\n");
			test_array(fibonacci_result_copy,40);

	bubble_sort(fibonacci_result_copy,40);
		printf("Ecco la serie di fibonacci fino a n=39 riordinata dal reverse:\n");
			test_array(fibonacci_result_copy,40);

	unsigned long result;
	result = memcmp(fibonacci_result,fibonacci_result_copy,40*sizeof(unsigned long));
	//aggiungere printf per verifica
		printf("Il risultato della verifica tra i due array è: %lu",result);

	return 0;
}
