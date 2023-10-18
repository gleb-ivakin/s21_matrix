#include "s21_matrix.h"
#include <check.h>

#define SUCCESS 1
#define FAILURE 0

void fill(matrix_t *m, double c);

START_TEST(create_matrix) {
    int result;
    matrix_t M;
    result = s21_create_matrix(-1, 0, &M);
    ck_assert_int_eq(result, 1);

    result = s21_create_matrix(1, 1, &M);
    ck_assert_int_eq(M.rows, 1);
    ck_assert_int_eq(M.columns, 1);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M);

    result = s21_create_matrix(4, 5, &M);
    ck_assert_int_eq(M.rows, 4);
    ck_assert_int_eq(M.columns, 5);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M);
}
END_TEST

START_TEST(remove_matrix) {
    matrix_t M;

    s21_create_matrix(3, 5, &M);
    s21_remove_matrix(&M);
    ck_assert_int_eq(M.columns, 0);
    ck_assert_int_eq(M.rows, 0);
}
END_TEST

START_TEST(eq_matrix) {
    int result;
    matrix_t M1, M2;
    s21_create_matrix(3, 3, &M1);
    s21_create_matrix(3, 2, &M2);
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M1);

    s21_create_matrix(4, 2, &M1);
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M1);

    s21_create_matrix(3, 2, &M1);
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++)
            M1.matrix[y][x] = M2.matrix[y][x] = 3.50;
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 1);

    M2.matrix[0][0] = 3.62;
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M1);
    s21_remove_matrix(&M2);

    s21_create_matrix(1, 2, &M1);
    s21_create_matrix(1, 2, &M2);
    M1.matrix[0][0] = 1.234567890;
    M1.matrix[0][1] = 0.987654321;
    M2.matrix[0][0] = 1.2345678;
    M2.matrix[0][1] = 0.9876543;
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M1);
    result = s21_eq_matrix(&M1, &M2);
    ck_assert_int_eq(result, 0);

    s21_create_matrix(1, 2, &M1);
    s21_remove_matrix(&M2);
    result = s21_eq_matrix(&M1, &M2);

    s21_remove_matrix(&M1);
}
END_TEST

START_TEST(sum_matrix) {
    int result;
    matrix_t M1, M2, M3;
    s21_create_matrix(3, 3, &M1);
    s21_create_matrix(3, 2, &M2);
    result = s21_sum_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 2);

    s21_remove_matrix(&M1);

    s21_create_matrix(3, 2, &M1);
    double num = 1.2390941841;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++) {
            M1.matrix[y][x] = M2.matrix[y][x] = num;
            num *= num;
        }

    result = s21_sum_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 0);

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++)
            ck_assert_double_eq(M3.matrix[y][x], M1.matrix[y][x] + M2.matrix[y][x]);

    s21_remove_matrix(&M1);
    s21_remove_matrix(&M2);
    result = s21_sum_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M3);
}
END_TEST

START_TEST(sub_matrix) {
    int result;
    matrix_t M1, M2, M3;
    s21_create_matrix(3, 3, &M1);
    s21_create_matrix(3, 2, &M2);
    result = s21_sub_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 2);

    s21_remove_matrix(&M1);

    s21_create_matrix(3, 2, &M1);
    double num = 1.2390941841;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++) {
            M1.matrix[y][x] = M2.matrix[y][x] = num;
            num *= num;
        }

    result = s21_sub_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 0);

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++)
            ck_assert_double_eq(M3.matrix[y][x], M1.matrix[y][x] - M2.matrix[y][x]);

    s21_remove_matrix(&M1);
    s21_remove_matrix(&M2);
    result = s21_sub_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M3);
}
END_TEST

START_TEST(mult_number) {
    int result;
    matrix_t M1, M2;
    s21_create_matrix(3, 2, &M1);
    double num = 1.2390941841;

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++) {
            M1.matrix[y][x] = num;
            num *= num;
        }

    result = s21_mult_number(&M1, 3.50, &M2);
    ck_assert_int_eq(result, 0);

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++)
            ck_assert_double_eq(M2.matrix[y][x], M1.matrix[y][x] * 3.50);

    s21_remove_matrix(&M1);
    result = s21_mult_number(&M1, 3.50, &M2);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M2);
}
END_TEST

START_TEST(mult_matrix) {
    int result;
    matrix_t M1, M2, M3;
    s21_create_matrix(3, 2, &M1);
    s21_create_matrix(2, 3, &M2);
    double num = 1.2390941841;

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 2; x++) {
            M1.matrix[y][x] = num;
            num *= num;
        }

    num = 2.4141231212;
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 3; x++) {
            M2.matrix[y][x] = num;
            num *= num;
        }

    result = s21_mult_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&M2);

    s21_create_matrix(1, 5, &M2);
    result = s21_mult_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 2);

    s21_remove_matrix(&M1);
    result = s21_mult_matrix(&M1, &M2, &M3);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M2);
    s21_remove_matrix(&M3);
}
END_TEST

START_TEST(transpose) {
    int result;
    matrix_t M1, M2;
    s21_create_matrix(3, 2, &M1);
    M1.matrix[0][0] = 1;
    M1.matrix[0][1] = 4;
    M1.matrix[1][0] = 2;
    M1.matrix[1][1] = 5;
    M1.matrix[2][0] = 3;
    M1.matrix[2][1] = 6;

    result = s21_transpose(&M1, &M2);
    ck_assert_int_eq(result, 0);
    for (int y = 0, n = 1; y < 2; y++)
        for (int x = 0; x < 3; x++, n++)
            ck_assert_double_eq(M2.matrix[y][x], (double) n);

    s21_remove_matrix(&M1);
    result = s21_transpose(&M1, &M2);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M2);
}
END_TEST

START_TEST(calc_complements) {
    int result;
    matrix_t Y, M2;
    s21_create_matrix(3, 3, &Y);
    Y.matrix[0][0] = 1;
    Y.matrix[0][1] = 2;
    Y.matrix[0][2] = 3;
    Y.matrix[1][0] = 0;
    Y.matrix[1][1] = 4;
    Y.matrix[1][2] = 2;
    Y.matrix[2][0] = 5;
    Y.matrix[2][1] = 2;
    Y.matrix[2][2] = 1;

    result = s21_calc_complements(&Y, &M2);
    ck_assert_int_eq(result, 0);

    double compl[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
    for (int y = 0, n = 0; y < 3; y++)
        for (int x = 0; x < 3; x++, n++)
            ck_assert_double_eq(M2.matrix[y][x], compl[n]);

    s21_remove_matrix(&Y);
    result = s21_calc_complements(&Y, &M2);
    ck_assert_int_eq(result, 1);

    s21_remove_matrix(&M2);
}
END_TEST

START_TEST(determinant) {
    int result;
    double det;
    matrix_t Y;
    s21_create_matrix(3, 3, &Y);
    Y.matrix[0][0] = 1;
    Y.matrix[0][1] = 2;
    Y.matrix[0][2] = 3;
    Y.matrix[1][0] = 4;
    Y.matrix[1][1] = 5;
    Y.matrix[1][2] = 6;
    Y.matrix[2][0] = 7;
    Y.matrix[2][1] = 8;
    Y.matrix[2][2] = 9;

    result = s21_determinant(&Y, &det);
    ck_assert_int_eq(result, 0);
    ck_assert_double_eq(det, 0);

    s21_remove_matrix(&Y);
    result = s21_determinant(&Y, &det);
    ck_assert_int_eq(result, 1);

    s21_create_matrix(3, 5, &Y);
    result = s21_determinant(&Y, &det);
    ck_assert_int_eq(result, 2);

    s21_remove_matrix(&Y);
}
END_TEST

START_TEST(inverse_matrix) {
    int result;
    matrix_t Y, Z, R;
    s21_create_matrix(3, 3, &Y);
    Y.matrix[0][0] = 2;
    Y.matrix[0][1] = 5;
    Y.matrix[0][2] = 7;
    Y.matrix[1][0] = 6;
    Y.matrix[1][1] = 3;
    Y.matrix[1][2] = 4;
    Y.matrix[2][0] = 5;
    Y.matrix[2][1] = -2;
    Y.matrix[2][2] = -3;

    result = s21_inverse_matrix(&Y, &Z);

    print_matrix(Y);
    print_matrix(Z);

    ck_assert_int_eq(result, 0);
    double inversed[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
    for (int y = 0, n = 0; y < 3; y++)
        for (int x = 0; x < 3; x++, n++)
            ck_assert_double_eq(Z.matrix[y][x], inversed[n]);

    s21_mult_matrix(&Y, &Z, &R);
    print_matrix(R);
    for (int i = 0; i < 3; i++)
        ck_assert_double_eq(R.matrix[i][i], 1.0);

    s21_remove_matrix(&Y);
    s21_remove_matrix(&Z);
    result = s21_inverse_matrix(&Y, &Z);
    ck_assert_int_eq(result, 1);

    s21_create_matrix(3, 3, &Y);
    Y.matrix[0][0] = 1;
    Y.matrix[0][1] = 2;
    Y.matrix[0][2] = 3;
    Y.matrix[1][0] = 4;
    Y.matrix[1][1] = 5;
    Y.matrix[1][2] = 6;
    Y.matrix[2][0] = 7;
    Y.matrix[2][1] = 8;
    Y.matrix[2][2] = 9;
    result = s21_inverse_matrix(&Y, &Z);
    ck_assert_int_eq(result, 2);

    s21_remove_matrix(&Y);
    s21_remove_matrix(&Z);
    s21_remove_matrix(&R);
}
END_TEST

START_TEST(create_matrix_1) {
  matrix_t m;
  int i = s21_create_matrix(2, 2, &m);
  fill(&m, 1);
  s21_remove_matrix(&m);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t m;
  int i = s21_create_matrix(0, 2, &m);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t m;
  int i = s21_create_matrix(2, 0, &m);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(create_matrix_4) {
  matrix_t m;
  int i = s21_create_matrix(0, 0, &m);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(eq_matrix_1) {
  matrix_t m, n;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, 1);
  fill(&n, 1);
  int i = s21_eq_matrix(&m, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t m, n;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(2, 2, &n);
  fill(&m, 1);
  fill(&n, 1);
  int i = s21_eq_matrix(&m, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, 1);
  fill(&n, 1);
  int i = s21_eq_matrix(&m, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(eq_matrix_4) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(2, 3, &n);
  fill(&m, 1);
  fill(&n, 1);
  int i = s21_eq_matrix(&m, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(eq_matrix_5) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, 1);
  fill(&n, 0);
  int i = s21_eq_matrix(&m, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(eq_matrix_6) {
  matrix_t m, n;
  s21_create_matrix(3, 0, &m);
  s21_create_matrix(3, 0, &n);
  int i = s21_eq_matrix(&m, &n);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(eq_matrix_7) {
  matrix_t m;
  matrix_t n;
  matrix_t k;
  s21_create_matrix(5, 5, &m);
  s21_create_matrix(5, 5, &n);
  s21_create_matrix(2, 0, &k);
  fill(&m, 1.0);
  fill(&n, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&m, &n), SUCCESS);
  ck_assert_int_eq(s21_create_matrix(2, 0, &k), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
}
END_TEST

START_TEST(eq_matrix_8) {
  matrix_t m;
  matrix_t n;
  s21_create_matrix(5, 5, &m);
  s21_create_matrix(1, 5, &n);
  fill(&m, 1.0);
  fill(&n, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&m, &n), FAILURE);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 2);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t m, n, k;
  s21_create_matrix(3, 0, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 3, &n);
//   fill(&m, -1);
//   fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 2);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t m, n, k;
  s21_create_matrix(3, 0, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sum_matrix(&m, &n, &k);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t m;
  matrix_t n;
  matrix_t k;
  s21_create_matrix(2, 2, &m);
  s21_create_matrix(2, 2, &n);
  fill(&m, 1.0);
  fill(&n, 1.0);
  s21_sum_matrix(&m, &n, &k);
  matrix_t l;
  s21_create_matrix(2, 2, &l);
  l.matrix[0][0] = 2;
  l.matrix[0][1] = 4;
  l.matrix[1][0] = 6;
  l.matrix[1][1] = 8;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(sub_matrix_5) {
  matrix_t m;
  matrix_t n;
  matrix_t k;
  s21_create_matrix(2, 2, &m);
  s21_create_matrix(2, 2, &n);
  fill(&m, 1.0);
  fill(&n, 1.0);
  s21_sub_matrix(&m, &n, &k);
  matrix_t l;
  s21_create_matrix(2, 2, &l);
  l.matrix[0][0] = 0;
  l.matrix[0][1] = 0;
  l.matrix[1][0] = 0;
  l.matrix[1][1] = 0;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(sub_matrix_6) {
  matrix_t m, n, k;
  s21_create_matrix(3, 0, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sub_matrix(&m, &n, &k);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(sub_matrix_7) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_sub_matrix(&m, &n, &k);
  s21_remove_matrix(&n);
  s21_remove_matrix(&m);
  ck_assert_int_eq(i, 2);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  fill(&m, 4);
  int i = s21_mult_number(&m, 0.33, &n);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 0);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t m, n, k, l;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(2, 3, &n);
  s21_create_matrix(3, 3, &l);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 4;
  m.matrix[1][0] = 2;
  m.matrix[1][1] = 5;
  m.matrix[2][0] = 3;
  m.matrix[2][1] = 6;

  n.matrix[0][0] = 1;
  n.matrix[0][1] = -1;
  n.matrix[0][2] = 1;
  n.matrix[1][0] = 2;
  n.matrix[1][1] = 3;
  n.matrix[1][2] = 4;

  l.matrix[0][0] = 9;
  l.matrix[0][1] = 11;
  l.matrix[0][2] = 17;
  l.matrix[1][0] = 12;
  l.matrix[1][1] = 13;
  l.matrix[1][2] = 22;
  l.matrix[2][0] = 15;
  l.matrix[2][1] = 15;
  l.matrix[2][2] = 27;

  int i = s21_mult_matrix(&m, &n, &k);
  int j = s21_eq_matrix(&k, &l);

  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
  ck_assert_int_eq(i, 0);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_mult_matrix(&m, &n, &k);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 2);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t m, n, k;
  s21_create_matrix(3, 0, &m);
  s21_create_matrix(3, 2, &n);
  fill(&m, -1);
  fill(&n, 7);
  int i = s21_mult_matrix(&m, &n, &k);
  s21_remove_matrix(&n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t m, n;
  s21_create_matrix(3, 0, &m);
  fill(&m, 4);
  int i = s21_mult_number(&m, 0.33, &n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(mult_matrix_6) {
  matrix_t m;
  matrix_t k;
  s21_create_matrix(3, 3, &m);
  fill(&m, 1.0);
  double number = 2;
  s21_mult_number(&m, number, &k);
  matrix_t l;
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = 2;
  l.matrix[0][1] = 4;
  l.matrix[0][2] = 6;
  l.matrix[1][0] = 8;
  l.matrix[1][1] = 10;
  l.matrix[1][2] = 12;
  l.matrix[2][0] = 14;
  l.matrix[2][1] = 16;
  l.matrix[2][2] = 18;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(mult_matrix_7) {
  matrix_t m;
  matrix_t n;
  matrix_t k;
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &n);
  fill(&m, 1.0);
  fill(&n, 2.0);
  s21_mult_matrix(&m, &n, &k);
  matrix_t l;
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = 54;
  l.matrix[0][1] = 66;
  l.matrix[0][2] = 78;
  l.matrix[1][0] = 117;
  l.matrix[1][1] = 147;
  l.matrix[1][2] = 177;
  l.matrix[2][0] = 180;
  l.matrix[2][1] = 228;
  l.matrix[2][2] = 276;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t m, n, k;
  s21_create_matrix(3, 2, &m);
  s21_create_matrix(2, 3, &k);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 4;
  m.matrix[1][0] = 2;
  m.matrix[1][1] = 5;
  m.matrix[2][0] = 3;
  m.matrix[2][1] = 6;

  k.matrix[0][0] = 1;
  k.matrix[0][1] = 2;
  k.matrix[0][2] = 3;
  k.matrix[1][0] = 4;
  k.matrix[1][1] = 5;
  k.matrix[1][2] = 6;

  int i = s21_transpose(&m, &n);
  int j = s21_eq_matrix(&k, &n);

  ck_assert_int_eq(i, 0);
  ck_assert_int_eq(j, 1);

  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t m, n;
  s21_create_matrix(3, 0, &m);
  fill(&m, -1);

  int i = s21_transpose(&m, &n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t m;
  matrix_t k;
  s21_create_matrix(3, 3, &m);
  fill(&m, 1.0);
  s21_transpose(&m, &k);
  matrix_t l;
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = 1;
  l.matrix[0][1] = 4;
  l.matrix[0][2] = 7;
  l.matrix[1][0] = 2;
  l.matrix[1][1] = 5;
  l.matrix[1][2] = 8;
  l.matrix[2][0] = 3;
  l.matrix[2][1] = 6;
  l.matrix[2][2] = 9;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t m;
  s21_create_matrix(3, 3, &m);
  fill(&m, 1);
  double d;
  int i = s21_determinant(&m, &d);
  ck_assert_int_eq(i, 0);
  ck_assert_double_eq_tol(d, 0, 9e-7);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_2) {
  const int rows = 3;
  const int cols = 3;
  matrix_t m1;

  s21_create_matrix(rows, cols, &m1);
  int m = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = m++;
    }
  }
  m1.matrix[2][2] = 0;
  double result = 0;
  int got = s21_determinant(&m1, &result);
  ck_assert_double_eq_tol(result, 27, 1e-6);
  ck_assert_int_eq(got, 0);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_3) {
  const int rows = 5;
  const int cols = 5;
  matrix_t m1 = {
    0
  };
  s21_create_matrix(rows, cols, &m1);
  int m = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = m++;
    }
  }
  double result = 0;
  int got = s21_determinant(&m1, &result);
  ck_assert_double_eq_tol(result, 0, 1e-6);
  ck_assert_int_eq(got, 0);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t m;
  s21_create_matrix(1, 1, &m);
  fill(&m, 1);
  double d;
  int i = s21_determinant(&m, &d);
  ck_assert_int_eq(i, 0);
  ck_assert_double_eq_tol(d, 1, 9e-7);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t m;
  s21_create_matrix(1, 0, &m);
  fill(&m, 1);
  double d;
  int i = s21_determinant(&m, &d);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t m;
  s21_create_matrix(1, 2, &m);
  fill(&m, 1);
  double d;
  int i = s21_determinant(&m, &d);
  ck_assert_int_eq(i, 2);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t m, n;
  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  int i = s21_calc_complements(&m, &n);
  ck_assert_int_eq(i, 0);

  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t test, l, k;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  s21_calc_complements(&test, &k);
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = 0;
  l.matrix[0][1] = 10;
  l.matrix[0][2] = -20;
  l.matrix[1][0] = 4;
  l.matrix[1][1] = -14;
  l.matrix[1][2] = 8;
  l.matrix[2][0] = -8;
  l.matrix[2][1] = -2;
  l.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&l);
  s21_remove_matrix(&k);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  fill(&m, 1);
  int i = s21_calc_complements(&m, &n);
  ck_assert_int_eq(i, 2);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t m, n;
  s21_create_matrix(3, 0, &m);

  fill(&m, 2);

  int i = s21_calc_complements(&m, &n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(inverse_matrix_1) {
  matrix_t m, n, k, l;
  s21_create_matrix(3, 3, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  s21_inverse_matrix(&m, &n);
  s21_mult_matrix(&m, &n, &k);
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = 1;
  l.matrix[1][1] = 1;
  l.matrix[2][2] = 1;
  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&n);
  s21_remove_matrix(&k);
  s21_remove_matrix(&l);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t test, l, k;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 4;
  test.matrix[0][2] = 10;
  test.matrix[1][0] = 10;
  test.matrix[1][1] = 8;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 10;
  test.matrix[2][1] = 6;
  test.matrix[2][2] = 12;
  s21_create_matrix(3, 3, &l);
  l.matrix[0][0] = -0.1875;
  l.matrix[0][1] = -0.0375;
  l.matrix[0][2] = 0.175;
  l.matrix[1][0] = 0.1875;
  l.matrix[1][1] = 0.2375;
  l.matrix[1][2] = -0.275;
  l.matrix[2][0] = 0.0625;
  l.matrix[2][1] = -0.0875;
  l.matrix[2][2] = 0.075;
  s21_inverse_matrix(&test, &k);

  ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&l);
  s21_remove_matrix(&k);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t m, n;
  s21_create_matrix(3, 3, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][0] = 4;
  m.matrix[1][1] = 5;
  m.matrix[1][2] = 6;
  m.matrix[2][0] = 7;
  m.matrix[2][1] = 8;
  m.matrix[2][2] = 9;
  int i = s21_inverse_matrix(&m, &n);
  ck_assert_int_eq(i, 2);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t m, n;
  s21_create_matrix(3, 2, &m);
  fill(&m, 1);
  int i = s21_inverse_matrix(&m, &n);
  ck_assert_int_eq(i, 2);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t m, n;
  s21_create_matrix(3, 0, &m);
  fill(&m, 1);
  int i = s21_inverse_matrix(&m, &n);
  ck_assert_int_eq(i, 1);
}
END_TEST

START_TEST(inverse_matrix_6) {
  matrix_t m, n, k, l;
  s21_create_matrix(4, 4, &m);
  fill(&m, 5.9);
  m.matrix[0][0] = 11;
  m.matrix[1][1] = 11;

  double d;
    s21_determinant(&m, &d);
  ck_assert_double_eq_tol(d, 27151.8, 9e-7);
  s21_inverse_matrix(&m, &n);

    s21_mult_matrix(&m, &n, &k);
    s21_create_matrix(4, 4, &l);
    l.matrix[0][0] = 1.0;
    l.matrix[1][1] = 1.0;
    l.matrix[2][2] = 1.0;
    l.matrix[3][3] = 1.0;

    ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&n);
    s21_remove_matrix(&k);
    s21_remove_matrix(&l);
}
END_TEST

START_TEST(inverse_matrix_7) {
    matrix_t m, n, k, l;
    s21_create_matrix(5, 5, &m);
    fill(&m, 0.2);
    m.matrix[0][0] = 11;
    m.matrix[1][1] = 11;
    m.matrix[2][2] = 11;

    double d;
      s21_determinant(&m, &d);
      ck_assert_double_eq_tol(d, -133.76, 9e-7);
      s21_inverse_matrix(&m, &n);

      s21_mult_matrix(&m, &n, &k);
      s21_create_matrix(5, 5, &l);
      l.matrix[0][0] = 1;
      l.matrix[1][1] = 1;
      l.matrix[2][2] = 1;
      l.matrix[3][3] = 1;
      l.matrix[4][4] = 1;

      ck_assert_int_eq(s21_eq_matrix(&k, &l), SUCCESS);
      s21_remove_matrix(&m);
      s21_remove_matrix(&n);
      s21_remove_matrix(&k);
      s21_remove_matrix(&l);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Matrix");
    TCase *tc1 = tcase_create("Matrix");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1);
    tcase_add_test(tc1, create_matrix);
    tcase_add_test(tc1, remove_matrix);
    tcase_add_test(tc1, eq_matrix);
    tcase_add_test(tc1, sum_matrix);
    tcase_add_test(tc1, sub_matrix);
    tcase_add_test(tc1, mult_number);
    tcase_add_test(tc1, mult_matrix);
    tcase_add_test(tc1, transpose);
    tcase_add_test(tc1, calc_complements);
    tcase_add_test(tc1, determinant);
    tcase_add_test(tc1, inverse_matrix);

    TCase *tc1_1 = tcase_create("New");
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, create_matrix_1);
    tcase_add_test(tc1_1, create_matrix_2);
    tcase_add_test(tc1_1, create_matrix_3);
    tcase_add_test(tc1_1, create_matrix_4);
    tcase_add_test(tc1_1, eq_matrix_1);
    tcase_add_test(tc1_1, eq_matrix_2);
    tcase_add_test(tc1_1, eq_matrix_3);
    tcase_add_test(tc1_1, eq_matrix_4);
    tcase_add_test(tc1_1, eq_matrix_5);
    tcase_add_test(tc1_1, eq_matrix_6);
    tcase_add_test(tc1_1, eq_matrix_7);
    tcase_add_test(tc1_1, eq_matrix_8);
    tcase_add_test(tc1_1, sum_matrix_1);
    tcase_add_test(tc1_1, sum_matrix_2);
    tcase_add_test(tc1_1, sum_matrix_3);
    tcase_add_test(tc1_1, sub_matrix_1);
    tcase_add_test(tc1_1, sub_matrix_2);
    tcase_add_test(tc1_1, sub_matrix_3);
    tcase_add_test(tc1_1, sub_matrix_4);
    tcase_add_test(tc1_1, sub_matrix_5);
    tcase_add_test(tc1_1, sub_matrix_6);
    tcase_add_test(tc1_1, sub_matrix_7);
    tcase_add_test(tc1_1, mult_matrix_1);
    tcase_add_test(tc1_1, mult_matrix_2);
    tcase_add_test(tc1_1, mult_matrix_3);
    tcase_add_test(tc1_1, mult_matrix_4);
    tcase_add_test(tc1_1, mult_matrix_5);
    tcase_add_test(tc1_1, mult_matrix_6);
    tcase_add_test(tc1_1, mult_matrix_7);
    tcase_add_test(tc1_1, transpose_1);
    tcase_add_test(tc1_1, transpose_2);
    tcase_add_test(tc1_1, transpose_3);
    tcase_add_test(tc1_1, determinant_1);
    tcase_add_test(tc1_1, determinant_2);
    tcase_add_test(tc1_1, determinant_3);
    tcase_add_test(tc1_1, determinant_4);
    tcase_add_test(tc1_1, determinant_5);
    tcase_add_test(tc1_1, determinant_6);
    tcase_add_test(tc1_1, calc_complements_1);
    tcase_add_test(tc1_1, calc_complements_2);
    tcase_add_test(tc1_1, calc_complements_3);
    tcase_add_test(tc1_1, calc_complements_4);
    tcase_add_test(tc1_1, inverse_matrix_1);
    tcase_add_test(tc1_1, inverse_matrix_2);
    tcase_add_test(tc1_1, inverse_matrix_3);
    tcase_add_test(tc1_1, inverse_matrix_4);
    tcase_add_test(tc1_1, inverse_matrix_5);
    tcase_add_test(tc1_1, inverse_matrix_6);
    tcase_add_test(tc1_1, inverse_matrix_7);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}

void fill(matrix_t *m, double c) {
  double count = 1;

  for (int i = 0; i < m -> rows; i++)
    for (int j = 0; j < m -> columns; j++) {
      m -> matrix[i][j] = count;
      count += c;
    }
}
