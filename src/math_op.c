#include "../include/rt.h"

int		cub_(t_math_cube cub, double *a, double *r)
{
	cub.sqrtbq = sqrt(cub.bq);
	if (cub.br > 0)
	{
		r[0] = -2 * cub.sqrtbq - a[2] / 3;
		r[1] = cub.sqrtbq - a[2] / 3;
		r[2] = cub.sqrtbq - a[2] / 3;
	}
	else
	{
		r[0] = -cub.sqrtbq - a[2] / 3;
		r[1] = -cub.sqrtbq - a[2] / 3;
		r[2] = 2 * cub.sqrtbq - a[2] / 3;
	}
	return (3);
}

int		cub_2(t_math_cube cub, double *a, double *r)
{
	cub.ratio = cub.sgnbr * sqrt(cub.br2 / cub.bq3);
	cub.alfa = acos(cub.ratio);
	cub.norm = -2 * sqrt(cub.bq);
	cub.r1 = cub.norm * cos(cub.alfa / 3) - a[2] / 3;
	cub.r2 = cub.norm * cos((cub.alfa + 2.0 * M_PI) / 3) - a[2] / 3;
	cub.r3 = cub.norm * cos((cub.alfa - 2.0 * M_PI) / 3) - a[2] / 3;
	if (cub.r1 > cub.r2)
		swapd(&cub.r1, &cub.r2);
	if (cub.r2 > cub.r3)
	{
		swapd(&cub.r2, &cub.r3);
		if (cub.r1 > cub.r2)
			swapd(&cub.r1, &cub.r2);
	}
	r[0] = cub.r1;
	r[1] = cub.r2;
	r[2] = cub.r3;
	return (3);
}

int		cub_3(t_math_cube cub, double *a, double *r)
{
	cub.ba = -cub.sgnbr * pow(fabs(cub.br) +
		sqrt(cub.br2 - cub.bq3), 1.0 / 3.0);
	cub.bb = cub.bq / cub.ba;
	r[0] = cub.ba + cub.bb - a[2] / 3;
	return (1);
}

int		math_cub(double *a, double *r)
{
	t_math_cube		cub;

	cub = math_coef(a);
	if (cub.br == 0 && cub.bq == 0)
	{
		while (cub.index++ < 3)
			r[cub.index] = -a[2] / 3;
		return (3);
	}
	else if (cub.cr2 == cub.cq3)
		return (cub_(cub, a, r));
	else if (cub.br2 < cub.bq3)
		return (cub_2(cub, a, r));
	else
		return (cub_3(cub, a, r));
}
