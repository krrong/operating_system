#include <stdio.h>


void make_history(char command[], char** history, int i);

void print_history(char** history, int count);

void print_help();

void do_exec(char command[]);

void do_background(char command[]);

