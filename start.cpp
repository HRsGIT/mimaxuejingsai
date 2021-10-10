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

	tt = allocate_matrix_u8 (m_shift, N);//��ֵ�� ����2^m�����룬ÿ�������ӦNλ��� Nλ��ÿλռһ������ռ�
	ll = allocate_matrix_u8 (m_shift, n_shift - 1);//ö�����е��������   ll[i][j] ��ʾ������Ϊiʱ�� ������jʱ�Ľ������f(i) * j ���ڵ��0û�����壬���Դ�1��ʼ����n_shift - 1��
	wt = allocate_matrix (m_shift, n_shift - 1);//Walsh�任,û�г�2^n wt[i][j]��ѭ����S(j, i)����û�г�2^n
	ac = allocate_matrix (m_shift, n_shift - 1);//�����
	anf = allocate_matrix (m_shift, n_shift - 1);//������ʽ
	allocate_memory_multi(n_shift-1, 8, &non, &cor, &bal, &acor, &acor2, &acor3, &an, &im);//ͳһ������һƬ�ռ�?
	
	begin = clock();
	
	truth_table (tt, &is_bal);//������ֵ��ͬʱ����ƽ���� is_balΪ1ʱƽ�⣬Ϊ0ʱ��ƽ��

	linear_combinations(tt, ll);//�������е��������

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

	algebraic_normal_form (ll, anf);//������ʽ	anf[i][j]��ʾ�������j�������ʱ��x�������Ա�ʾ��i����һ��ϵ���Ƿ�Ϊ1 ��������Ϸ���֮������������

	nl = nonlinearity (wt, non);//��������  ����max��min���ڸ��ŵ�ԭ���������еı��ʽ��һ��

	ci = correlation_immunity (wt, cor);//���������

	abs_ind = absolute_indicator (ac, acor);//����ֵָʾ����

	sum_square = sum_of_square_indicator (ac, acor2);//ƽ����ָʾ����

	alg_deg = algebraic_degree (anf, an);//��������  �˴��о��������ֵ��Сֵд���е�����

	ai = algebraic_immunity (ll, im);//��������

	pc = propagation_characteristics ();//k����ɢ׼��  �������ж�ƽ�⺯����һ������˸���

	if (N != 1)
	{
		fixed = get_num_fixed_points (1);//������
	
		opposite_fixed = get_num_opposite_fixed_points (0);//��Բ�����
		
		delta = get_delta_uniformity (&robustness);//��־��ȶȣ�
		
		snr_dpa_value = get_snr_dpa (tt);//�����
		
		branch = get_branch_number();//��֧��
		
		//lat();//���Խ��Ʊ�
		
		kappa = computeKappaCPA (M, N, M);//����ϵ�� �ֿ����ŵ����� Խ��Խ�ã�
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
	strict_avalanche_criterion (pc);//����pc��ֵ���ж��Ƿ������ϸ�ѩ��׼��
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


