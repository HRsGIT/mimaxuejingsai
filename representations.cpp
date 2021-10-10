#include "header.h"

void truth_table (u8 **tt, uint* is_bal)
{
	uint i, j;
	int tem = *is_bal;
	int num = m_shift / n_shift;//每个输出函数值应该出现几次
	int* count = (int*)malloc(n_shift * sizeof(int));
	//memset(count, 0, (int)n_shift);
	for (int i = 0; i < n_shift; ++i)count[i] = 0;
	for (i = 0; i < m_shift; i++) {
		count[input_array[i]]++;
		for (j = 0; j < N; j++) {
			tt[i][j] = input_array[i] >> (N - j - 1) & 0x01;
		}
	}
	int test;
	for (int i = 0; i < n_shift; ++i) {
		//printf("%d %d\n", i, count[i]);
		//if (i == 255)
			// test = 0;
		//tem += ((count[i] - num < 0) ? (num - count[i]) : (count[i] - num));
		if (count[i] != num) {
			*is_bal = 0;
			free(count);
			return;
		}
	}
	free(count);
	*is_bal = 1;
}
int isbal(uint* f, int n) {//判断一个单输出布尔函数是否平衡,有几个输出
	int num1 = 0, num0 = 0;
	int ans = 0;
	int i = 0;
	for (i = 0; i < n; ++i) {
		if (f[i] == 1)ans++;
		else ans--;
	}
	return ans;

}

void linear_combinations (u8 **tt, u8 **ll)
{
	uint i, j;
	if (N == 1) //for Boolean function there is no linear combinations
		for (i = 0; i < m_shift; i++)
			ll[i][0] = tt[i][0]; 
	else
	{
		for (i = 1; i < n_shift; i++) // start from 1, 0 does not have any interesting case, all linear combinations
			for (j = 0; j < N; j++)
				if (i >> j & 0x01) 
					xor_elements(ll, tt, ll, i-1, j);
	}
}


int walsh_transform (u8 **ll, int **wt)
{
    int m, halfm, t1, t2, a, b, r, j;
	uint i, z, rows, columns;
	rows = m_shift;
	columns = n_shift - 1;

	for (z = 0; z < columns; z++)
	{
		for (i = 0; i < rows; ++i)//此时v是0，所以只用考虑f(x) * z, v * x是0.所以下边的循环中i从1开始?
			wt[i][z] = (ll[i][z] == 0) ? 1 : -1;

		for (i = 1; i <= M; ++i) 
		{
			m  = (1 << i);
			halfm = m/2;
			for (r = 0; r < (int) rows; r += m) 
			{
				t1 = r;
				t2 = r + halfm;
				for (j = 0; j < halfm; ++j, ++t1, ++t2) 
				{
					a = wt[t1][z];
					b = wt[t2][z];
					wt[t1][z] = a + b;
					wt[t2][z] = a - b;
				}
			}
		}
	}
	return 1;
}

int walsh_transform_naive (u8 **ll, int **wh) 
{
	int  tmp = 0, res = 0;
	uint i, j, z, columns, rows;

	rows = m_shift;
	columns = n_shift - 1;
	for (z = 0; z < columns; z++)
	{
		for (i = 0; i < rows; i++)	
		{
			for (j = 0; j < rows; j++)
			{
				res +=  (((int) ll[j][z] ^ inner_product(i, j)) == 1) ? -1 : 1;
			}
			wh[i][z] = res;
			res = 0;
		}
	}

	return 1;
}



int autocorrelation (u8 **ll, int **ac) //not unique, used to return sum-of-square indicator
{
	int  res = 0;
	uint i, j, z, rows, columns;

	rows = m_shift;
	columns = n_shift - 1;
	for (z = 0; z < columns; z++)
	{
		for (i = 0; i < rows; i++)	//going through all autocorrelation elements
		{
			for(j = 0; j < rows; j++)
			{
				res += (((int) ll[j][z] ^ ll[i^j][z]) == 1) ? -1 : 1;
			}
			ac[i][z] = res;
			res = 0;
		}
	}
	return 1;
}


int autocorrelation_fast (u8 **ll, int **ac, int ** wh)
{
    int m, halfm, t1, t2, r, a, b, j;
	uint i, z, rows, columns;
	rows = m_shift;
	columns = n_shift - 1;

	for (z = 0; z < columns; z++)
	{
		for (i = 0; i < rows; i++)
			ac[i][z] = -1* wh[i][z]*wh[i][z];

		for (i = 1; i <= M; ++i) 
		{
			m  = (1 << i);
			halfm = m/2;
			for (r = 0; r < (int) rows; r += m) 
			{
				t1 = r;
				t2 = r + halfm;
				for (j = 0; j < halfm; ++j, ++t1, ++t2) 
				{
					a = ac[t1][z];
					b = ac[t2][z];
					ac[t1][z] = a + b;
					ac[t2][z] = a - b;
				}
			}
		}
		for (i = 0; i < rows; i++)
			ac[i][z] /= (1 << M)*(-1);
	}
	return 1;
}


int algebraic_normal_form (u8 **ll, int **anf)
{
	int tmp = 0, res = 0;
	uint i, j, k, z, rows, columns;
	int *t = 0, *u = 0;
	rows = 1 << (M - 1);
	columns = n_shift -1;

	u = (int *) malloc (rows * sizeof(int));
	t = (int *) malloc (rows * sizeof(int));

	for (z = 0; z < columns; z++)
	{
		for (i = 0; i < (rows << 1); ++i)
			anf[i][z] = (int) ll[i][z];//ll可以看作一个特殊的真值表，对应的函数是z * F(i)
		for (i = 0; i < rows; ++i)
			u[i] = t[i] = 0;

		for (i = 0; i < M; ++i)
		{
			for (j = 0; j < rows; ++j)
			{
				t[j] = anf[2*j][z];
				u[j] = (anf[2*j][z] == anf[2*j+1][z]) ? 0 : 1;
			}
			for (k = 0; k < rows; ++k)
			{
				anf[k][z] = t[k];
				anf[rows + k][z] = u[k];
			}
		}
	}
	/*if (columns == 1) {
		printf("\n");
		for (int i = 0; i < (rows << 1); ++i) {
			printf("%d\n", anf[i][0]);
		}
	}*/
	return 1;
}


//currently not used, if necessary, call the function with appropriate parameters
void polar_representation (int *tt)
{
	uint i;
	int *res = 0;

	res = (int *) malloc (m_shift * sizeof(int));

	for (i = 0; i < m_shift; i++)
	{
        res[i] = (tt[i] == 0) ? 1 : -1;
	}
	printf("Polar representation is\n");
	for (i = 0; i < m_shift; i++)
		printf("%d", res[i]);
	printf("\n");
}
