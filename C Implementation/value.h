#ifndef VALUE_H
#define VALUE_H
typedef enum op_t{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
}op

typedef struct value_t{
	float data;
	float grad;
	void (*grad_func)(struct value_t *self);
	char* label;
	struct value_t* parents
} value;

// creates a new value
value* create_value(float data, char* label);

// adds two values together
// returns	- a new value with a proper grad func
value* value_add(value* value1, value* value2);

// subtracts two values
// returns	- a new value with a proper grad func
value* value_sub(value* value1, value* value2);

// multiplies two values together
// returns	- a new value with a proper grad func 
value* value_mul(value* value1, value* value2);

// divides two values
// returns	- a new value with a proper grad func
value* value_div(value* dividend, value* divisor);

// gradient function of a value produced through addition
void grad_add(value* parent1, value* parent2);

// gradient function of a value produced through subtraction
void grad_sub(value* parent1, value* parent2);

// gradient function of a value produced through multiplication
void grad_mul(value* parent1, value* parent2);

// gradient function of a value produced through division
void grad_div(value* parent1, value* parent2);

// computes the partial derivative of every one of
// the given value's parents in terms of the given
// value (each parents gradient will be assigned)
void backwards(value* value);
#endif
