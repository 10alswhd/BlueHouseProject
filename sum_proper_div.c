int isqrt(int n)
{
	int x = n, y = 1;
	for (;;)
	{
		y = (y + n / y) >> 1;
		if (x <= y)
			return x;
		x = y;
	}
}

// Algorithm to find sum of all proper divisors.
// Below is the straight approach.
// Obviously, it is an O( n ) algorithm.
int sum_proper_div_straight(int a)
{
	int sum = 0;
	for (int i = 1; i < a; ++i)
		if (a % i == 0) sum += i;
	return sum;
}

// Optimized approach.
//
// first stage is to remove powers of 2 because
// half of the possible inputs will have a power of 2
// and since it is a repeated division it is O( log(n) )
// 
// second stage is the search for all other prime factors.
// there is no more prime factors than sqrt(n)
// and for i < sqrt(n) we have repeated division. 
// so, whole stage is O( sqrt(n)*log(n) )
//
// third stage is the sum of all divisors.
// it uses the algebraic equivalence:
// p^e + p^(e-1) + ... + p + 1   =    (p^(e+1) - 1)   /   (p - 1)
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^         ^^^^^^^^^^^         ^^^^^
//      log(n) multiplication          1 pow operation     constant
//      using smart polynomial        takes log(n) time      time
// lhs: O( log(n) )	rhs: O( log(n) )
// concl.: despite having same complexity, rhs is seen to be 
//         faster by a constant factor
//
// In total: O( log(n) + sqrt(n)*log(n) + log(n) ) = O( sqrt(n)*log(n) )
//           which is better than the straight approach by limit at
//           infinity
int sum_pproper_div_optimized(int a)
{
	int p[20] = { 0 }, index = -1, e[20] = { 0 }; // asal sayi ve kuvveti
	int i, n = a, k, result = 1;
	if (!(n & 1))
	{
		n >>= 1;
		p[++index] = 2;
		e[index] = 1;
	}

	while (!(n & 1))
	{
		n >>= 1;
		e[index]++;
	}

	if (n < 3)
		return ((1 << (e[0] + 1)) - a - 1);

	k = isqrt(n);

	for (i = 3; i <= isqrt(n); i += 2)
	{
		if (n % i == 0)
		{
			n /= i;
			p[++index] = i;
			e[index] = 1;
		}
		while (n%i == 0)
		{
			n /= i;
			e[index]++;
		}
		if (n < 5)
			break;
	}

	if (n > 1)
	{
		p[++index] = n;
		e[index] = 1;
	}

	for (i = 0; i <= index; i++)
	{
		if (e[i] > 1)
		{
			int p1 = p[i];
			k = p1;
			int e1 = e[i];
			while (e1-- != 0)
				k *= p1;
			k--;
			k /= p1 - 1;
			result *= k;
		}
		else
		{
			result *= (p[i] + 1);
		}
	}

	return result - a;
}
