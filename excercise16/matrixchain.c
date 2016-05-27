#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 100

int m[MATRIX_SIZE][MATRIX_SIZE];
int p[MATRIX_SIZE];
int n;
int c[MATRIX_SIZE][MATRIX_SIZE];

void print_bracket (const int i, const int j);
int matrix_chain (void);

int
main (void)
{
  int p_temp[] = { 1, 3, 2, 4, 6, 1, 3, 2, 5 };
  memcpy (p, p_temp, sizeof (p_temp));
  n = (sizeof (p_temp) / sizeof (int));

  printf ("%d\n", matrix_chain ());

  print_bracket (1, n - 1);
  printf ("\n");
}

void
print_bracket (const int i, const int j)
{
  static int num = 0;
  if (i >= j)
    {
      printf ("A%d", ++num);
      return;
    }

  printf ("(");
  print_bracket (i, c[i][j]);
  printf (")(");
  print_bracket (c[i][j] + 1, j);
  printf (")");
}

int
matrix_chain (void)
{
  int i, j, k, r;

  for (i = 1; i <= n; i++)
    m[i][i] = 0;
  for (r = 1; r <= n - 1; r++)
    {
      for (i = 1; i <= n - r; i++)
	{
	  j = i + r;
	  m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
	  c[i][j] = i;
	  for (k = i + 1; k <= j - 1; k++)
	    {
	      if (m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j])
		{
		  m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
		  c[i][j] = k;
		}
	    }
	}
    }

  return m[1][n - 1];
}
