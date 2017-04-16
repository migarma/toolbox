// COMPLEX NUMBERS LIBRARY DEFINITION

#ifndef COMPLEX_LIB_H
#define COMPLEX_LIB_H

typedef struct complex_binomial {
	float real;
	float imag;
} complex_binomial;

typedef struct complex_polar {
	float modulus;
	float phase;
} complex_polar;

typedef enum complex_result {
	COMPLEX_RES_OK = 0,
	COMPLEX_ERROR,
	COMPLEX_NUM_RESULTS
} complex_result;

typedef struct complex_operations_binomial {
	complex_result(*complex_add)(complex_binomial *op_a, complex_binomial *op_b,
				   				 complex_binomial *op_res, uint32_t len);
	complex_result(*complex_subs)(complex_binomial *op_a, complex_binomial *op_b,
				   				  complex_binomial *op_res, uint32_t len);
	complex_result(*complex_mult)(complex_binomial *op_a, complex_binomial *op_b,
				   				  complex_binomial *op_res, uint32_t len);
	complex_result(*complex_div)(complex_binomial *op_a, complex_binomial *op_b,
				   				 complex_binomial *op_res, uint32_t len);
} complex_operations;

typedef struct complex_lib {
	complex_operations_binomial operations_binomial;
} complex_lib;

// COMPLEX LIB PUBLIC FUNCTIONS DEFINITIONS
extern complex_lib* complex_lib_init(void);
extern void complex_lib_close(complex_lib *clib);
extern complex_result complex_lib_conj_binomial(complex_binomial *op, 
												complex_binomial *res, 
												uint32_t len);

#endif
