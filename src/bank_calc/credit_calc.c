#include "bank_calc.h"

double calc_annuity_mp(double TC, double TM, double P);
double calc_differentiated_mp(double TC, double* RC, double TM, double P);

int credit_calc(Stack* res, double total_credit, double period,
                double percentage, int type) {
  if (res == NULL) return ARGS_ERR;
  double FMP = 0.0, LMP = 0.0, O = 0.0, TP = 0.0;
  double TC = total_credit, TM = period, P = percentage / 100.0;
  if (TC > EPSILON && TM > EPSILON && P > EPSILON) {
    if (type == ANNUITY) {
      FMP = LMP = calc_annuity_mp(TC, TM, P);
      TP = FMP * TM;
      O = TP - total_credit;
    } else if (type == DIFFERENTIATED) {
      double RC = TC;
      FMP = calc_differentiated_mp(TC, &RC, TM, P);
      TP += FMP;
      while (RC > EPSILON) {
        LMP = calc_differentiated_mp(TC, &RC, TM, P);
        TP += LMP;
      }
      O = TP - total_credit;
    }
  }
  push(res, FMP, 1), push(res, LMP, 1), push(res, O, 1), push(res, TP, 1);
  reverse_stack(res);
  return NO_ERR;
}

double calc_annuity_mp(double TC, double TM, double P) {
  double PM = P / YEAR_MONTH;
  double PM_RAITO = 1.0 + PM;
  double FACTOR = pow(PM_RAITO, TM);
  return TC * ((PM * FACTOR) / (FACTOR - 1));
}

double calc_differentiated_mp(double TC, double* RC, double TM, double P) {
  double PM = P / YEAR_MONTH;
  double PC = TC / TM;
  double PP = *RC * PM;
  *RC -= PC;
  return PC + PP;
}