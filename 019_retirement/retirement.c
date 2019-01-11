#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double compute_balance(double balance, double contribution, double rate_of_return) {
  balance = balance + balance * rate_of_return + contribution;
  return balance;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  double balance = initial;
  int retire_age = startAge + working.months;
  int final_age = retire_age + retired.months;
  for (int i = startAge; i < retire_age; i++) {
    int age = i / 12;
    int month = i % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance = compute_balance(balance, working.contribution, working.rate_of_return);
  }
  for (int j = retire_age; j < final_age; j++) {
    int age = j / 12;
    int month = j % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance = compute_balance(balance, retired.contribution, retired.rate_of_return);
  }
}

int main() {
  retire_info_t Working;
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045 / 12;
  retire_info_t Retired;
  Retired.months = 384;
  Retired.contribution = -4000;
  Retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, Working, Retired);
  return EXIT_SUCCESS;
}
