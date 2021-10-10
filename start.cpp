#include "header.h"

int myfun(int argc, char *argv[])
{
	register uint i = 0, j = 0;
	uint nl = 0, is_bal = 0, alg_deg = 0, ci = 0, pc = 0, ai = 0, delta = 0, fixed, opposite_fixed, branch;
	unsigned long long abs_ind = 0, sum_square = 0;
	u8 **tt, **ll;
	int **wt, **ac, **anf;
	uint *non, *cor, *bal, *acor, *acor2, *acor3, *an, *im;
	float robustness = 0.0, snr_dpa_value = 0.0, transparency = 0.0, kappa = 0.0;
	clock_t begin, finish;
	
	prepare(name, argc, argv);

	tt = allocate_matrix_u8 (m_shift, N);//真值表 输入2^m种输入，每种输入对应N位输出 N位中每位占一个数组空间
	ll = allocate_matrix_u8 (m_shift, n_shift - 1);//枚举所有的线性组合   ll[i][j] 表示在输入为i时， 输出点乘j时的结果、即f(i) * j 由于点乘0没有意义，所以从1开始，共n_shift - 1个
	wt = allocate_matrix (m_shift, n_shift - 1);//Walsh变换,没有除2^n wt[i][j]是循环谱S(j, i)，且没有除2^n
	ac = allocate_matrix (m_shift, n_shift - 1);//自相关
	anf = allocate_matrix (m_shift, n_shift - 1);//代数范式
	allocate_memory_multi(n_shift-1, 8, &non, &cor, &bal, &acor, &acor2, &acor3, &an, &im);//统一申请了一片空间?
	
	begin = clock();
	
	truth_table (tt, &is_bal);//计算真值表，同时计算平衡性 is_bal为1时平衡，为0时不平衡

	linear_combinations(tt, ll);//计算所有的线性组合

	walsh_transform (ll, wt);
	/*for (int i = 0; i < m_shift; ++i) {
		for (int j = 0; j < n_shift - 1; ++j) {
			printf("%d ", wt[i][j]);
		}
		printf("\n");
	}*/
	//walsh_transform_naive (ll, wt);
	
//	output_matrix_u8 (ll, m_shift, n_shift-1);
//	store_matrix_u8 (ll, m_shift, n_shift-1, "D:/testiranje1.txt");

	//autocorrelation (ll, ac);
	autocorrelation_fast (ll, ac, wt);
	
	//output_matrix (ac, m_shift, N);

	algebraic_normal_form (ll, anf);//代数范式	anf[i][j]表示输出按照j线性组合时，x相乘项可以表示成i的那一项系数是否为1 有线性组合方便之后计算代数次数

	nl = nonlinearity (wt, non);//非线性性  最后的max和min由于负号的原因与文献中的表达式不一样

	ci = correlation_immunity (wt, cor);//相关免疫性

	abs_ind = absolute_indicator (ac, acor);//绝对值指示器？

	sum_square = sum_of_square_indicator (ac, acor2);//平方和指示器？

	alg_deg = algebraic_degree (anf, an);//代数次数  此处感觉最后的最大值最小值写的有点问题

	ai = algebraic_immunity (ll, im);//代数免疫

	pc = propagation_characteristics ();//k次扩散准则  这里在判断平衡函数那一点进行了更改

	if (N != 1)
	{
		fixed = get_num_fixed_points (1);//不动点
	
		opposite_fixed = get_num_opposite_fixed_points (0);//相对不动点
		
		delta = get_delta_uniformity (&robustness);//差分均匀度？
		
		snr_dpa_value = get_snr_dpa (tt);//信噪比
		
		branch = get_branch_number();//分支数
		
		//lat();//线性近似表
		
		kappa = computeKappaCPA (M, N, M);//混淆系数 抵抗测信道攻击 越高越好？
	}
	else
	{
		//wt_boolean (result, M);
		;
	}
	
	transparency = get_transparency ();
	
	finish = clock();
	get_time(finish, begin);

	s_box_info (name);

	balancedness(is_bal);

	printf("Nonlinearity is %d.\n", nl);
	printf("Corelation immunity is %d.\n", ci);
	//printf("Balance is %d.\n", is_bal);
	printf("Absolute indicator is %lld.\n", abs_ind);
	printf("Sum of square indicator is %lld.\n", sum_square);
	printf("Algebraic degree is %d.\n", alg_deg);
	printf("Algebraic immunity is %d.\n", ai);
	printf("Transparency order is %.3f.\n", transparency);
	printf("Propagation characteristic is %d.\n",  pc);
	strict_avalanche_criterion (pc);//根据pc的值来判断是否满足严格雪崩准则
	if (N != 1)
	{
		printf("Number of fixed points is %d.\n", fixed);
		printf("Number of opposite fixed points is %d.\n", opposite_fixed);
		printf("Composite algebraic immunity is %d.\n", ai);
		printf("Robustness to differential cryptanalysis is %.3f.\n", robustness);
		printf("Delta uniformity is %d.\n", delta);
		printf("SNR (DPA) (F) is %.3f.\n", snr_dpa_value);
		printf("Confusion coefficient variance is %f.\n", kappa);
	}
	else
	{
		printf("Algebraic immunity is %d.\n", ai);
		//wt_boolean (result, M, N);
		;
	}
	
	//output_array_to_file("D:\\testingoutput.txt",res_nonlinearity, n_shift-1, 25);
	//output_matrix (wt, m_shift, n_shift-1);

	//deallocate_memory_multi (14, &res_balance, &res_nonlinearity, &res_ac, &res_sum_square, &res_alg_deg, &res_ci, &res_pc, &res_ai, &result, &component_ac, &component_ssi, &temp_wt, &temp_ac, &temp_anf);

	for (i = 0; i < N; i++)
    {
    	free (tt[i]);
    }
    free (tt);
	system("pause");
}

/////////end of main/////////////


