/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:11:23 by jarredon          #+#    #+#             */
/*   Updated: 2022/09/04 13:51:44 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	swap(void *x, void *y, unsigned int l)
{
	char	*a;
	char	*b;
	char	c;

	a = x;
	b = y;
	while (l--)
	{
		c = *a;
		*a++ = *b;
		*b++ = c;
	}
}

static void	sort(char *array, unsigned int size,
		int (*cmp)(void*, void*), int begin, int end)
{
	void	*pivot;
	int		l;
	int		r;

	pivot = array + begin;
	l = begin + size;
	r = end;
	if (end <= begin)
		return ;
	while (l < r)
	{
		if (cmp(array + l, pivot) <= 0)
			l += size;
		else if (cmp(array + r, pivot) > 0)
			r -= size;
		else if (l < r)
			swap(array + l, array + r, size);
	}
	l -= size;
	if (cmp(array + r, pivot) < 0)
		swap(array + begin, array + r, size);
	else
		swap(array + begin, array + l, size);
	sort(array, size, cmp, begin, l);
	sort(array, size, cmp, r, end);
}

void	ft_qsort(void *array, unsigned int nitems,
		unsigned int size, int (*cmp)(void*, void*))
{
	if (nitems > 0)
		sort(array, size, cmp, 0, (nitems - 1) * size);
}

static int	dbl_cmp(void *a, void *b)
{
	if ((*(double *)a) > (*(double *)b))
		return (1);
	if ((*(double *)a) < (*(double *)b))
		return (-1);
	else
		return (0);
}

void	ft_qsort_dbl(double *array, unsigned int nitems)
{
	ft_qsort(array, nitems, sizeof(double), dbl_cmp);
}
