#ifndef WIDGET_H
#define WIDGET_H

#include <float.h>

#include <QInputDialog>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QWidget>

#ifdef __cplusplus
extern "C" {
#endif
#include "../smart_calc.h"
int calc_label_eq(double *res, char *str_eq, double x_value);
int credit_calc(Stack *res, double total_credit, double period,
                double percentage, int type);
int deposit_calc(Stack *res, double total_deposit, double period,
                 double profit_rate, double tax_rate, double replenishments,
                 double withdrawals, char *replenishments_rate,
                 char *withdrawals_rate, char *pcf_rate, int profit_cap);
Stack *create_stack(int max_elem);
void destroy_stack(Stack *stack);
double pop(Stack *stack);
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private slots:
  void onTabClicked();
  void onButtonClicked();
  void on_pushButton_x_pressed();
  void on_pushButton_x_released();
  void on_pushButton_clear_pressed();
  void on_pushButton_clear_released();
  void onCreditTypeClicked();
  void onProfitCapTypeClicked();
  void onResClicked();
  void stdCalc();
  void creditCalc();
  void debitCalc();
  void showDialog();
  void deleteLabel();
  void createGraph();

 private:
  Ui::Widget *ui;
  int actualIndex;
  int creditType;
  int profitCapState;
  double xValue;

  double gMin, gMax, gStep;
  QVector<double> x, y;

  QTimer *longPressTimerX;
  QTimer *longPressTimerClear;

  void updateLabelText(const QString &text);
  int getLabelRes(double *res, double xTarget);
};
#endif  // WIDGET_H
