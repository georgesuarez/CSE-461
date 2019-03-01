/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rand.h"

int *
get_next_random_1_svc(params *argp, struct svc_req *rqstp)
{
	static int  result;
	int xl, xr;
	
	xl = argp->xleft;
	xr = argp->xright;

	result = ( 11 * xl + 13 * result + 5 * xr ) % 31;
	printf("%d\n", result);

	return &result;
}
