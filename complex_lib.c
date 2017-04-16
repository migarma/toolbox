#include "include/complex_lib.h"

static complex_result complex_lib_add_binomial_float_basic(
										complex_binomial *op_a,
										complex_binomial *op_b,
				   				 		complex_binomial *op_res, uint32_t len);

static complex_result complex_lib_subs_binomial_float_basic(
										complex_binomial *op_a,
										complex_binomial *op_b,
				   				 		complex_binomial *op_res, uint32_t len);

static complex_result complex_lib_mult_binomial_float_basic(
										complex_binomial *op_a,
										complex_binomial *op_b,
				   				 		complex_binomial *op_res, uint32_t len);

static complex_result complex_lib_div_binomial_float_basic(
										complex_binomial *op_a,
										complex_binomial *op_b,
				   				 		complex_binomial *op_res, uint32_t len);

complex_lib* complex_lib_init(void)
{
	complex_lib *clib;

	if (!(clib = (complex_lib*)malloc(sizeof(complex_lib)))) {
		return NULL;
	}
	
#ifdef OPERATIONS_COMPLEX_FLOAT_BASIC
	// Init operations
	clib->operations_binomial.complex_add = complex_lib_add_binomial_float_basic;
	clib->operations_binomial.complex_subs = complex_lib_subs_binomial_float_basic;
	clib->operations_binomial.complex_mult = complex_lib_mult_binomial_float_basic;
	clib->operations_binomial.complex_div = complex_lib_div_binomial_float_basic;
#elif OPERATIONS_COMPLEX_XXX
#warning complex lib has not operations
	// Init operations
	clib->operations_binomial.complex_add = NULL;
	clib->operations_binomial.complex_subs = NULL;
	clib->operations_binomial.complex_mult = NULL;
	clib->operations_binomial.complex_div = NULL;
#endif
	
	return clib;
}

void complex_lib_close(complex_lib *clib)
{
	free(clib);
}

complex_result complex_lib_conj_binomial(complex_binomial *op, 
												complex_binomial *res, 
												uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++) {
		res[i].imag = - op[i].imag;
	}

	return COMPLEX_RES_OK;
}

complex_result complex_lib_add_binomial_float_basic(
 								complex_binomial *op_a,
 								complex_binomial *op_b,
 		   				 		complex_binomial *op_res, uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++) {
		op_res[i].real = op_a[i].real + op_b[i].real;
		op_res[i].imag = op_a[i].imag + op_b[i].imag;
	}

	return COMPLEX_RES_OK;
}

complex_result complex_lib_subs_binomial_float_basic(
 								complex_binomial *op_a,
 								complex_binomial *op_b,
 		   				 		complex_binomial *op_res, uint32_t len)
{
	uint32_t i;

	for (i = 0; i < len; i++) {
		op_res[i].real = op_a[i].real - op_b[i].real;
		op_res[i].imag = op_a[i].imag - op_b[i].imag;
	}

	return COMPLEX_RES_OK;
}


complex_result complex_lib_mult_binomial_float_basic(
 								complex_binomial *op_a,
 								complex_binomial *op_b,
 		   				 		complex_binomial *op_res, uint32_t len)
{
	uint32_t i;
	float a, b, c, d;

	for (i = 0; i < len; i++) {
		a = op_a[i].real;
		b = op_a[i].imag;
		c = op_b[i].real;
		d = op_b[i].imag;

		op_res[i].real = (a * c) - (b * d);
		op_res[i].imag = (a * d) + (b * c);
	}

	return COMPLEX_RES_OK;
}


complex_result complex_lib_div_binomial_float_basic(
										complex_binomial *op_a,
										complex_binomial *op_b,
				   				 		complex_binomial *op_res, uint32_t len)
{
	uint32_t i;
	float den;
	complex_binomial conj_num[len];
	complex_binomial conj_b[len];

	// Compute conjugate
	complex_lib_conj_binomial(op_b, conj_b);
	
	// Compute numerator
	conj_num = complex_lib_mult_binomial_float_basic(op_a, conj_b, len)

	for (i = 0; i < len; i++) {
		den = op_b[i].real ^ 2 + op_b[i] ^ 2;
		op_res[i].real = conj_num[i].real / den;
		op_res[i].imag = conj_num[i].imag / den;
	}

	return COMPLEX_RES_OK;
}
