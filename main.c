#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define LEARNING_RATE 0.01
#define EPOCHS 500

double forward_pass(const double *w, const double *x, size_t n)
{
  double out = w[0];  // w[0] is the weight for the constant +1 input

  for (size_t i = 0; i < n; i++)
  {
    out += w[i + 1] * x[i];
  }

  return out;
}

static double step(double x) { return (x > 0) ? 1 : 0; }

void adjust_weights(double *w, const double *x, double y, double t, size_t n)
{
  w[0] += LEARNING_RATE * (t - y);

  for (size_t i = 0; i < n; i++)
  {
    w[i + 1] += LEARNING_RATE * (t - y) * x[i]; 
  }
}

int main(__attribute__((unused)) int argC, __attribute__((unused)) char **argV)
{
  // learning AND function
  const double in[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                           {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

  const double t[8] = {0, 1, 1, 1, 1, 1, 1, 1};
  int n = 4 - 1;
  int m = 8;

  double *w = malloc(sizeof(double) * m);

  for (size_t i = 0; i < n; i++)
  {
    w[i] = (double) rand() / (double) RAND_MAX;
  }

  for (size_t e = 0; e < EPOCHS; e++)
  {
    if (e % (EPOCHS / 10) == 0)
    {
      // calculate error
      double error = 0.0;

      for (size_t i = 0; i < m; i++)
      {
        double out = step(forward_pass(w, in[i], n));
        error += pow((out - t[i]), 2);
      }

      error = sqrt(error);

      printf("Epoch %4ld > Error: %.3lf\n", e, error);
    }

    for (size_t i = 0; i < m; i++)
    {
      double y = step(forward_pass(w, in[i], n));
      adjust_weights(w, in[i], y, t[i], n);
    }
  }

  printf("\nFinal weights: [");
  srand(time(NULL));
  for (int i = 0; i < n; i++)
  {
    printf(" %.3f", w[i]);
  }
  printf("]\n\n");

  // do a test prediction
  for (size_t i = 0; i < m; i++)
  {
    double out = step(forward_pass(w, in[i], n));
    printf("in:[%d,%d,%d]\tout:%d\n", (int) in[i][0], (int) in[i][1],
           (int) in[i][2], (int) out);
  }

  printf("\n\n");
  free(w);

  return 0;
}
