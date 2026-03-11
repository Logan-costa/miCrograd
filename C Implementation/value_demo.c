#include <stdlib.h>
#include <stdio.h>
#include "value.h"

void print_grads(value* cur){
	printf("%s val = %f, grad = %f\n", cur->label, cur->data, cur->grad);
	if(cur->grad_func == NULL)
		return;
	else{
		print_grads(cur->parents[0]);
		print_grads(cur->parents[1]);
	}
}

int main(int argc, char** argv){
	// create expressions
	value* a = create_value(2.0, "a");
	value* b = create_value(-3.0, "b");
	value* c = create_value(10.0, "c");

	// e = a * b
	value* e = value_mul(a, b, "e");
	// d = e + c
	value* d = value_add(e, c, "d");
	value* f = create_value(-2.0, "f");

	// L = d * f
	value* L = value_mul(d, f, "L");

	// compute gradient
	L->grad = 1.0; // set grad to 1.0 to work properly
	compute_grad(L);

	print_grads(L);
}
