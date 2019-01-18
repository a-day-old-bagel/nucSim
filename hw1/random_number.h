/*
 *  Title: 	randomnumber
 *  Last Mod: 	Fri Mar 18 07:28:57 1988
 *  Author: 	Vincent Broman
 *		<broman@schroeder.nosc.mil>
 */  

extern void start_random_number();
    
extern double next_random_number();
    
/*  
 *  This package makes available Marsaglia's highly portable generator 
 *  of uniformly distributed pseudo-random numbers.
 *  
 *  The sequence of 24 bit pseudo-random numbers produced has a period 
 *  of about 2**144, and has passed stringent statistical tests 
 *  for randomness and independence.
 *  
 *  Supplying two seeds to start_random_number is required once
 *  at program startup before requesting any random numbers, like this:
 *      start_random_number(101, 202);
 *      r := next_random_number();
 *  The correspondence between pairs of seeds and generated sequences 
 *  of pseudo-random numbers is many-to-one.
 *  
 *  This package should compile and run identically on any 
 *  machine/compiler which supports >=16 bit integer arithmetic
 *  and >=24 bit floating point arithmetic.
 *  
 *  References:
 *      M G Harmon & T P Baker, ``An Ada Implementation of Marsaglia's
 *      "Universal" Random Number Generator'', Ada Letters, late 1987.
 *      
 *      G Marsaglia, ``Toward a universal random number generator'',
 *      to appear in the Journal of the American Statistical Association.
 *  
 *  George Marsaglia is at the Supercomputer Computations Research Institute
 *  at Florida State University.
 */  


/*
 *  Title: 	random_number
 *  Last Mod: 	Fri Mar 18 08:52:13 1988
 *  Author: 	Vincent Broman
 *		<broman@schroeder.nosc.mil>
 */

#define P 179
#define PM1 (P - 1)
#define Q (P - 10)
#define STATE_SIZE 97
#define MANTISSA_SIZE 24
#define RANDOM_REALS 16777216.0
#define INIT_C    362436.0
#define INIT_CD  7654321.0
#define INIT_CM 16777213.0
/* global varibles used by the RNG which may be sved to a log file in order
to restart the RNG.*/
static unsigned int ni;
static unsigned int nj;
static double u[STATE_SIZE];
static double c, cd, cm;


static unsigned int collapse (anyint, size)
int anyint;
unsigned int size;
/*
 * return a value between 0 and size-1 inclusive.
 * this value will be anyint itself if possible, 
 * otherwise another value in the required interval.
 */
{
    if (anyint < 0)
	anyint = - (anyint / 2);
    while (anyint >= size)
	anyint /= 2;
    return (anyint);
}


void start_random_number (seed_a, seed_b)
int seed_a;
int seed_b;
/*
 * This procedure initialises the state table u for a lagged 
 * Fibonacci sequence generator, filling it with random bits 
 * from a small multiplicative congruential sequence.
 * The auxilliaries c, ni, and nj are also initialized.
 * The seeds are transformed into an initial state in such a way that
 * identical results are guaranteed across a wide variety of machines.
 */
{
double s, bit;
unsigned int ii, jj, kk, mm;
unsigned int ll;
unsigned int sd;
unsigned int elt, bit_number;

    sd = collapse (seed_a, PM1 * PM1);
    ii = 1 + sd / PM1;
    jj = 1 + sd % PM1;
    sd = collapse (seed_b, PM1 * Q);
    kk = 1 + sd / PM1;
    ll = sd % Q;
    if (ii == 1 && jj == 1 && kk == 1)
	ii = 2;

    ni = STATE_SIZE - 1;
    nj = STATE_SIZE / 3;
    c  = INIT_C;
    c /= RANDOM_REALS;		/* compiler might mung the division itself */
    cd = INIT_CD;
    cd /= RANDOM_REALS;
    cm = INIT_CM;
    cm /= RANDOM_REALS;

    for (elt = 0; elt < STATE_SIZE; elt += 1) {
	s = 0.0;
	bit = 1.0 / RANDOM_REALS;
	for (bit_number = 0; bit_number < MANTISSA_SIZE; bit_number += 1) {
	    mm = (((ii * jj) % P) * kk) % P;
	    ii = jj;
	    jj = kk;
	    kk = mm;
	    ll = (53 * ll + 1) % Q;
	    if (((ll * mm) % 64) >= 32)
		s += bit;
	    bit += bit;
	}
	u[elt] = s;
    }
}
    
    
double next_random_number()
/*
 * Return a uniformly distributed pseudo random number
 * in the range 0.0 .. 1.0-2**(-24) inclusive.
 * There are 2**24 possible return values.
 * Side-effects the non-local variables: u, c, ni, nj.
 */
{
  double uni;
    if (u[ni] < u[nj])
	uni = u[ni] + (1.0 - u[nj]);
    else
	uni = u[ni] - u[nj];
    u[ni] = uni;

    if (ni > 0)
	ni -= 1;
    else
	ni = STATE_SIZE - 1;

    if (nj > 0)
	nj -= 1;
    else
	nj = STATE_SIZE - 1;

    if (c < cd)
	c = c + (cm - cd);
    else
	c = c - cd;

    if (uni < c)
	return (uni + (1.0 - c));
    else
	return (uni - c);
}




