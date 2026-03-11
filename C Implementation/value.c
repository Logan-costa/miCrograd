#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "value.h"

value* create_value(float data, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = data;
	val->label = label; // this is lowkey sloppy and I should copy it into a new string but meh

	printf("%f\n", val->data);

	// default values
	val->op = NONE;
	val->grad_func = NULL;
	val->parents = NULL;
	val->grad = 0.0;

	return val;	
}

value* value_add(value* value1, value* value2, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = value1->data + value2->data;
	val->label = label;

	val->op = ADD;
	val->grad_func = grad_add;
	
	//value** parents = (value**)calloc(2, sizeof(value*));
	//parents[0] = value1;
	//parents[1] = value2;
	//val->parents = parents;
	
	val->parents = (value**)calloc(2, sizeof(value*));
	val->parents[0] = value1;
	val->parents[1] = value2;
	return val;
}

value* value_sub(value* value1, value* value2, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = value1->data - value2->data;
	val->label = label;

	val->op = SUBTRACT;
	val->grad_func = grad_sub;
	
	value** parents = (value**)calloc(2, sizeof(value*));
	parents[0] = value1;
	parents[1] = value2;
	val->parents = parents;
	return val;
}


value* value_mul(value* value1, value* value2, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = value1->data * value2->data;
	val->label = label;

	val->op = MULTIPLY;
	val->grad_func = grad_mul;
	
	value** parents = (value**)calloc(2, sizeof(value*));
	parents[0] = value1;
	parents[1] = value2;
	val->parents = parents;
	return val;
}


value* value_div(value* dividend, value* divisor, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = dividend->data / divisor->data;
	val->label = label;

	val->op = DIVIDE;
	val->grad_func = grad_div;
	
	value** parents = (value**)calloc(2, sizeof(value*));
	parents[0] = dividend;
	parents[1] = divisor;
	val->parents = parents;
	return val;
}


value* value_pow(value* base, value* exponent, char* label){
	value* val = (value*)calloc(1, sizeof(value));
	val->data = pow(base->data, exponent->data);
	val->label = label;

	val->op = SUBTRACT;
	val->grad_func = grad_pow;
	
	value** parents = (value**)calloc(2, sizeof(value*));
	parents[0] = base;
	parents[1] = exponent;
	val->parents = parents;
	return val;
}

// stub out functions for testing

void grad_add(value* value){
	value->parents[0]->grad += 1 * value->grad;
	value->parents[1]->grad += 1 * value->grad;
}

void grad_sub(value* value){
	value->parents[0]->grad += 1 * value->grad;
	value->parents[1]->grad += -1 * value->grad;
}

void grad_mul(value* value){
	value->parents[0]->grad += value->parents[1]->data * value->grad;
	value->parents[1]->grad += value->parents[0]->data * value->grad;
}

void grad_div(value* value){
	value->parents[0]->grad += (1/value->parents[1]->data) * value->grad;
	value->parents[1]->grad += ((-1 * value->parents[0]->data)/(value->parents[1]->data * value->parents[1]->data)) * value->grad;
}

void grad_pow(value* value){
	// just gonna compute the derivative for the base, since I don't have logs implemented
	value->parents[0]->grad += value->parents[1]->data * pow(value->parents[0]->data, value->parents[1]->data - 1) * value->grad;
}

// bfs parents
// params	- a value with a gradient value of 1.0
void compute_grad(value* value){
	if(value->grad_func == NULL)
		return;
	
	value->grad_func(value);
	compute_grad(value->parents[0]);
	compute_grad(value->parents[1]);
}
