#include "s21_math.h"

long double s21_cos(double x) {
  x = delete (x);
  return s21_sin(s21_PI / 2 - x);
}

double delete (double x) {
  while (x > s21_PI || x < -s21_PI) {
    x += x > s21_PI ? -2 * s21_PI : 2 * s21_PI;
  }
  return x;
}

long double s21_sin(double x) {
  x = delete (x);
  long double result = x, temp = x;
  long double i = 1.;
  while (s21_fabs(result) > s21_EPS) {
    result = -1 * result * x * x / (2 * i * (2 * i + 1));
    i += 1.;
    temp += result;
  }
  return temp;
}

long double s21_tan(double x) {
    struct special _special;
    long double temp, c = s21_cos(x);
    translate(c, &_special);;
    temp = _special.sign * s21_sin(x) / _special.mantisa;
    temp /= _special.pow;
    return (x != -s21_PI / 2 && x != s21_PI / 2) ? temp : s21_NAN;
}

long int s21_abs(int x) { return x < 0 ? x *= -1 : x; }


long double s21_ceil(double x) {
  int i;
  double temp = x < 0 ? -x : x;
  for (i = 0; i < temp; i++) {
  }
  return x < 0 ? -i + 1 : i;
}


long double s21_floor(double x) {
    int i;
    double temp = x < 0? -x: x;
    for (i = 0; i < temp; i++) {}
    return x < 0 ? -i : x == 0 ? 0: i - 1;
}

long double s21_atan(double x) {
    long double temp = 0;
    temp = (x < 1 && x > -1) ? atan_1_1(x): temp;
    temp =  x == 1 ? s21_PI / 4: x == -1 ? -s21_PI / 4: x == 0 ? 0: temp;
    temp = x > 1 ? s21_PI / 2 - atan_1_1(1 / x): x < -1 ? -s21_PI/2 - atan_1_1(1 / x): temp;
    return temp;
}

long double atan_1_1(double x) {
  long double result = x, temp = x, i = 1;
  while (s21_fabs(result) > s21_EPS) {
    result = -1 * result * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1;
    temp += result;
  }
  return temp;
}

long double s21_acos(double x) {
    return (x <= 1 && x >= -1) ? s21_abs(x) == 1 ? s21_PI * (1 - x) / 2 : s21_PI / 2. - s21_asin(x) : s21_NAN;
}

long double s21_asin(double x) {
    long double result = x, temp = x;
    long double i = 1;
    while (s21_fabs(result) > s21_EPS) {
        if (x < -1 || x > 1) {
            temp = s21_NAN;
            break;
        }
        if (x == 1 || x == -1) {
            temp = s21_PI / 2 * x;
            break;
        }
        result *= x * x * (2 * i - 1) * (2 * i) * (2 * i - 1) / ((2 * i + 1) * 4 * i * i);
        i += 1;
        temp += result;
    }
    return temp;
}

long double s21_fmod(double x, double y) {
  long double result = s21_fabs(x);
  y = s21_fabs(y);
  int i = 1;
  while (result > y) {
    result = s21_fabs(x) - y * i;
    i++;
  }
  return x < 0 ? -result : result;
}

long double s21_exp(double x) {
    long double result = 1, temp = 1;
    long double i = 1;
    int flag = 0;
    if (x < 0) {
        x *= -1;
        flag = 1;
    }
    while (s21_fabs(result) > s21_EPS) {
        result *= x / i;
        i += 1;
        temp += result;
        if (temp > s21_MAX_double) {
            temp = s21_INF;
            break;
        }
    }
    temp = flag == 1 ? temp > s21_MAX_double ? 0 : 1. / temp : temp;
    return temp = temp > s21_MAX_double ? s21_INF : temp;
}

long double s21_log(double x) {
  long double temp;
  return temp = (x > 0 && x < 2) ? log_0_2(x) : log_other(x);
}

long double log_0_2(double x) {
  x--;
  long double result = x, temp = x;
  long double i = 2;
  while (s21_fabs(result) > s21_EPS) {
    result *= -x * (i - 1) / i;
    i += 1;
    temp += result;
  }
  return temp;
}

long double log_other(double x) {
    struct special _special;
    translate(x, &_special);
    x = _special.mantisa * _special.sign / 10;
    long double result;
    result = x < 0 ? -s21_NAN : x == 0 ? -s21_INF : log_0_2(x) + (_special.e + 1) * s21_ln10;
    return result;
}

long double s21_sqrt(double x) {
  long double result = 4, temp = 0;
  while (s21_fabs(result - temp) > s21_EPS) {
    if (x < 0) {
      result = -s21_NAN;
      break;
    }
    temp = result;
    result = (temp + x / temp) / 2;
  }
  return result;
}

long double s21_pow(double base, double exp) {
    long double result;
    result = s21_exp(exp * s21_log(base));
    return result;
}

long double s21_fabs(long double x) {
    return x < 0 ? x *= -1. : x;
    }

void translate(double x, struct special *_special) {
  long double i = 1;
  int es = 0;
  _special->sign = x < 0 ? -1 : 1;
  x *= _special->sign;
  if (x >= 10) {
    while (x >= 10) {
      x /= 10.;
      i *= 10;
      es++;
    }
  } else if (x < 1 && x > 0) {
    while (x < 1) {
      x *= 10;
      i /= 10;
      es--;
    }
  }
  _special->mantisa = x;
  _special->pow = i;
  _special->e = es;
}
