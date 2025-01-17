/*
	Alison Ueda
	CS 3060 X02
	Assignment 1

	Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.

*/

#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("This is the first assignment of the semester\n\n");

	// if there's user input, parse and print
	if(argc > 1) {
		int j = 0;

		for(int i = 0; i < argc; i++) {
			printf("Argument %d: %s\n", i, argv[i])
		}

		printf("Number of arguments printed: %d", j);

	} else {
		printf("Error: no user input\n");
		return 0;
	}
	
	return 0;
}
