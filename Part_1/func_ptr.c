#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 1			//change this to 1 to enable verbose output

/**
 * Signature for an function pointer that can compare
 * You need to cast the input into its actual 
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer) (const void *a, const void *b);

/**
 * compares 2 processes
 * You can assume: 
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 */
int compareFunction(const void *this, const void *that)
{
	Process *p_1 = (Process*)this;
	Process *p_2 = (Process*)that;
	
	// Sorted based on priority in descending order 
	if (p_1->priority > p_2->priority) {
		return -1; 
	}
	else if(p_1->priority < p_2->priority) {
		return 1;
	}
	else{
		// If priority values are equal, 
		// they are sorted based on arrival time based on ascending order 
		if (p_1->arrival_time > p_2->arrival_time) {
			return 1;
		}
		else{
			return -1;
		}
	}
}

int main(int argc, char *argv[])
{

	if (argc < 2) {
		fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
		fflush(stdout);
		return 1;
	}

	/*******************/
	/* Parse the input */
	/*******************/
	FILE *input_file = fopen(argv[1], "r");
	if (!input_file) {
		fprintf(stderr, "Error: Invalid filepath\n");
		fflush(stdout);
		return 1;
	}

	Process *processes = parse_file(input_file);

	/*******************/
	/* sort the input  */
	/*******************/
	Comparer process_comparer = &compareFunction;

#if DEBUG
	for (int i = 0; i < P_SIZE; i++) {
		printf("%d (%d, %d) ",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	printf("\n");
#endif

	qsort(processes, P_SIZE, sizeof(Process), process_comparer);

	/**************************/
	/* print the sorted data  */
	/**************************/

	for (int i = 0; i < P_SIZE; i++) {
		printf("%d (%d, %d)\n",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	fflush(stdout);
	fflush(stderr);

	/************/
	/* clean up */
	/************/
	free(processes);
	fclose(input_file);
	return 0;
}
