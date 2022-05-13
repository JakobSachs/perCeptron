#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define LEARNING_RATE 0.01
#define EPOCHS 1000

double forward_pass(const double *w, const double *x, size_t n)
{
  double out = w[0];  // w[0] is the weight for the constant +1 input

  for (size_t i = 0; i < n; i++)
  {
    out += w[i + 1] * x[i];
  }

  return out;
}

static double step(double x) { return (x >= 0) ? 1 : 0; }

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
  const double in[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  const double t[4] = {0, 0, 0, 1};

  double w[5] = {0};

  for (size_t i = 0; i < 5; i++)
  {
    w[i] = (double)rand() / (double)RAND_MAX;
  }

  for (size_t e = 0; e < EPOCHS; e++)
  {
    if (e % (EPOCHS / 10) == 0)
    {
      // calculate error
      double error = 0.0;

      for (size_t i = 0; i < 4; i++)
      {
        double out = step(forward_pass(w, in[i], 2));
        error += pow((out - t[i]), 2);
      }

      error = sqrt(error);

      printf("Epoch %zu> Error: %lf\n", e, error);

      printf("Weights: [%.3f, %.3f, %.3f, %.3f, %.3f]\n", w[0], w[1], w[2], w[3], w[4]);
    }

    for (size_t i = 0; i < 4; i++)
    {
      double y = step(forward_pass(w, in[i], 2));
      adjust_weights(w, in[i], y, t[i], 2);
    }
  }

  printf("\nFinal weights: [");
  srand(time(NULL));
  for (int i = 0; i < 5; i++)
  {
    w[i] = (double)rand() / (double) RAND_MAX;

    printf(" %.3f", w[i]);
  }
  printf("]\n\n");

  // do a test prediction
  for (size_t i = 0; i < 4; i++)
  {
    double out = forward_pass(w, in[i], 2);
    printf("in:[%d,%d]\tout:%.3f\n", (int) in[i][0], (int) in[i][1], out);
  }

  printf("\n\n");

  return 0;
}
