#ifndef VALUE_H
#define VALUE_H
typedef enum op_t{
	NONE,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
}op;

typedef struct value_t{
	float data;
	float grad;
	void (*grad_func)(struct value_t*);
	op op;
	char* label;
	struct value_t** parents;
}value;

// creates a new value
value* create_value(float data, char* label);

// adds two values together
// returns	- a new value with a proper grad func
value* value_add(value* value1, value* value2, char* label);

// subtracts two values
// returns	- a new value with a proper grad func
value* value_sub(value* value1, value* value2, char* label);

// multiplies two values together
// returns	- a new value with a proper grad func 
value* value_mul(value* value1, value* value2, char* label);

// divides two values
// returns	- a new value with a proper grad func
value* value_div(value* dividend, value* divisor, char* label);

// raises one value to another
// returns	- a new value with a proper grad func
value* value_pow(value* base, value* exponent, char* label);

// gradient function of a value produced through addition
void grad_add(value* value);

// gradient function of a value produced through subtraction
void grad_sub(value* value);

// gradient function of a value produced through multiplication
void grad_mul(value* value);

// gradient function of a value produced through division
void grad_div(value* value);

// gradient function of a value produced through exponentiation
void grad_pow(value* value);

// computes the partial derivative of every one of
// the given value's parents in terms of the given
// value (each parents gradient will be assigned)
// params	- value who's gradient is 1.0
void compute_grad(value* value);
#endif
