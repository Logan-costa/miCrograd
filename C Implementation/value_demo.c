#include <stdlib.h>
#include <stdio.h>
#include "value.h"

int main(int argc, char** argv){
	printf("program start\n");
	value* a = create_value(2, "a");
	printf("%s created\n", a->label);
	value* b = create_value(4, "b");
	printf("%s created\n", b->label);
	value* result = value_add(a, b, "add");
	printf("%s created\n", result->label);


	printf("result value = %f\n", result->data);
	printf("grad func = ");
	result->grad_func(result);
	return 0;
}
