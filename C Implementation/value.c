#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "value.h"

value* create_value(float data, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = data;
	val->label = label; // this is lowkey sloppy and I should copy it but meh

	printf("%f\n", val->data);

	// default values
	val->op = NONE;
	val->grad_func = NULL;
	val->parents = NULL;

	return val;	
}

value* value_add(value* value1, value* value2, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = value1->data + value2->data;
	val->label = label;

	val->op = ADD;
	val->grad_func = grad_add;
	
	value** parents = (value**)calloc(2, sizeof(value));
	parents[0] = value1;
	parents[1] = value2;
	val->parents = parents;
	return val;
}

value* value_sub(value* value1, value* value2, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = value1->data - value2->data;
	val->label = label;

	val->op = SUBTRACT;
	val->grad_func = grad_sub;
	
	value** parents = (value**)calloc(2, sizeof(value));
	parents[0] = value1;
	parents[1] = value2;
	val->parents = parents;
	return val;
}

// stub out functions for testing

void grad_add(value* value){
	printf("grad add\n");
}

void grad_sub(value* value){
	printf("grad sub\n");
}
