#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      actualIndex(0),
      creditType(1),
      profitCapState(1),
      xValue(0),
      gMin(-10),
      gMax(10),
      gStep(0.1) {
  ui->setupUi(this);

  QWidget* comboBoxPCF = ui->combo_box_pcf->view()->window();
  comboBoxPCF->setAttribute(Qt::WA_TranslucentBackground, true);
  comboBoxPCF->setStyleSheet(
      "QComboBoxPrivateContainer{background-color: #616161; border: none; "
      "border-radius: 8px; padding: 4px};");
  QWidget* comboBoxR = ui->combo_box_r->view()->window();
  comboBoxR->setAttribute(Qt::WA_TranslucentBackground, true);
  comboBoxR->setStyleSheet(
      "QComboBoxPrivateContainer{background-color: #616161; border: none; "
      "border-radius: 8px; padding: 4px};");
  QWidget* comboBoxW = ui->combo_box_w->view()->window();
  comboBoxW->setAttribute(Qt::WA_TranslucentBackground, true);
  comboBoxW->setStyleSheet(
      "QComboBoxPrivateContainer{background-color: #616161; border: none; "
      "border-radius: 8px; padding: 4px};");

  ui->smartcalc_pages->setCurrentIndex(actualIndex);
  ui->push_button_calc->setStyleSheet(
      "background-color: #C62828;\
                                        border-radius: 10px;\
                                        border: none;");

  ui->graphic->xAxis->setBasePen(QPen(Qt::white, 2));
  ui->graphic->xAxis->setTickPen(QPen(Qt::white, 2));
  ui->graphic->xAxis->setTickLabelColor(Qt::white);
  ui->graphic->xAxis->setLabelColor(Qt::white);
  ui->graphic->xAxis->setRange(gMin, gMax);
  ui->graphic->xAxis->setTickLengthOut(5);
  ui->graphic->xAxis->setTickLengthIn(0);

  ui->graphic->yAxis->setBasePen(QPen(Qt::white, 2));
  ui->graphic->yAxis->setTickPen(QPen(Qt::white, 2));
  ui->graphic->yAxis->setTickLabelColor(Qt::white);
  ui->graphic->yAxis->setLabelColor(Qt::white);
  ui->graphic->yAxis->setRange(gMin, gMax);
  ui->graphic->yAxis->setTickLengthOut(5);
  ui->graphic->yAxis->setTickLengthIn(0);

  ui->graphic->xAxis->grid()->setPen(QPen(Qt::white));
  ui->graphic->yAxis->grid()->setPen(QPen(Qt::white));

  ui->graphic->setBackground(QBrush("#424242"));

  longPressTimerX = new QTimer(this);
  longPressTimerX->setSingleShot(true);

  longPressTimerClear = new QTimer(this);
  longPressTimerClear->setSingleShot(true);

  connect(ui->push_button_calc, SIGNAL(clicked()), this, SLOT(onTabClicked()));
  connect(ui->push_button_credit, SIGNAL(clicked()), this,
          SLOT(onTabClicked()));
  connect(ui->push_button_deposit, SIGNAL(clicked()), this,
          SLOT(onTabClicked()));
  connect(ui->push_button_graphic, SIGNAL(clicked()), this,
          SLOT(onTabClicked()));

  connect(longPressTimerX, SIGNAL(timeout()), this, SLOT(showDialog()));
  connect(ui->push_button_x, SIGNAL(pressed()), this,
          SLOT(on_pushButton_x_pressed()));
  connect(ui->push_button_x, SIGNAL(released()), this,
          SLOT(on_pushButton_x_released()));

  connect(longPressTimerClear, SIGNAL(timeout()), this, SLOT(deleteLabel()));
  connect(ui->push_button_clear, SIGNAL(pressed()), this,
          SLOT(on_pushButton_clear_pressed()));
  connect(ui->push_button_clear, SIGNAL(released()), this,
          SLOT(on_pushButton_clear_released()));

  connect(ui->push_button_res, SIGNAL(clicked()), this, SLOT(onResClicked()));
  connect(ui->push_button_calculate_graph, SIGNAL(clicked()), this,
          SLOT(onResClicked()));
  connect(ui->push_button_calculate_credit, SIGNAL(clicked()), this,
          SLOT(onResClicked()));
  connect(ui->push_button_calculate_deposit, SIGNAL(clicked()), this,
          SLOT(onResClicked()));

  connect(ui->push_button_credit_type, SIGNAL(clicked()), this,
          SLOT(onCreditTypeClicked()));
  connect(ui->push_button_pc_state, SIGNAL(clicked()), this,
          SLOT(onProfitCapTypeClicked()));

  QList<QPushButton*> buttons = this->findChildren<QPushButton*>();
  for (QPushButton* button : buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
  }
}

Widget::~Widget() { delete ui; }

void Widget::onTabClicked() {
  QPushButton* senderButton = qobject_cast<QPushButton*>(sender());

  ui->push_button_calc->setStyleSheet("background-color: #212121;");
  ui->push_button_credit->setStyleSheet("background-color: #212121;");
  ui->push_button_deposit->setStyleSheet("background-color: #212121;");
  ui->push_button_graphic->setStyleSheet("background-color: #212121;");

  if (senderButton == ui->push_button_calc) {
    actualIndex = 0;
  } else if (senderButton == ui->push_button_graphic) {
    actualIndex = 1;
  } else if (senderButton == ui->push_button_credit) {
    actualIndex = 2;
  } else if (senderButton == ui->push_button_deposit) {
    actualIndex = 3;
  }

  senderButton->setStyleSheet(
      "background-color: #C62828; border-radius: 10px; border: none;");

  ui->smartcalc_pages->setCurrentIndex(actualIndex);
}

void Widget::onButtonClicked() {
  QPushButton* senderButton = qobject_cast<QPushButton*>(sender());

  // Map button text to corresponding values
  QMap<QString, QString> buttonMap = {
      {"push_button_0", "0"},        {"push_button_00", "00"},
      {"push_button_1", "1"},        {"push_button_2", "2"},
      {"push_button_3", "3"},        {"push_button_4", "4"},
      {"push_button_5", "5"},        {"push_button_6", "6"},
      {"push_button_7", "7"},        {"push_button_8", "8"},
      {"push_button_9", "9"},        {"push_button_acos", "acos("},
      {"push_button_asin", "asin("}, {"push_button_atan", "atan("},
      {"push_button_cos", "cos("},   {"push_button_sin", "sin("},
      {"push_button_tan", "tan("},   {"push_button_ln", "ln("},
      {"push_button_log", "log("},   {"push_button_mod", "%"},
      {"push_button_pow", "^"},      {"push_button_sqrt", "sqrt("},
      {"push_button_usub", "(-"},    {"push_button_uadd", "(+"},
      {"push_button_lbracket", "("}, {"push_button_rbracket", ")"},
      {"push_button_div", "/"},      {"push_button_mul", "*"},
      {"push_button_sub", "-"},      {"push_button_add", "+"},
      {"push_button_dot", "."}};

  // Update label text based on the button clicked
  QString buttonText = buttonMap.value(senderButton->objectName(), "");
  if (!buttonText.isEmpty()) {
    if (actualIndex == 0) {
      if (ui->text_label_output_calc->text() == "INVALID") deleteLabel();
      updateLabelText(ui->text_label_output_calc->text() + buttonText);
    } else if (actualIndex == 1) {
      if (ui->text_label_input_graphic->text() == "INVALID") deleteLabel();
      updateLabelText(ui->text_label_input_graphic->text() + buttonText);
    }
  }
}

void Widget::keyPressEvent(QKeyEvent* event) {
  // Get the pressed key
  QString keyPressed = event->text();

  // Check if the pressed key corresponds to any of the buttons
  QMap<QString, QString> keyMap = {
      {"0", "push_button_0"},        {"1", "push_button_1"},
      {"2", "push_button_2"},        {"3", "push_button_3"},
      {"4", "push_button_4"},        {"5", "push_button_5"},
      {"6", "push_button_6"},        {"7", "push_button_7"},
      {"8", "push_button_8"},        {"9", "push_button_9"},
      {".", "push_button_dot"},      {"+", "push_button_add"},
      {"-", "push_button_sub"},      {"*", "push_button_mul"},
      {"/", "push_button_div"},      {"(", "push_button_lbracket"},
      {")", "push_button_rbracket"}, {"%", "push_button_mod"},
      {"^", "push_button_pow"},      {"C", "push_button_acos"},
      {"S", "push_button_asin"},     {"T", "push_button_atan"},
      {"c", "push_button_cos"},      {"s", "push_button_sin"},
      {"t", "push_button_tan"},      {"l", "push_button_ln"},
      {"L", "push_button_log"},      {"r", "push_button_sqrt"}};

  // Check if the pressed key is in the keyMap
  if (keyMap.contains(keyPressed)) {
    QPushButton* button = findChild<QPushButton*>(keyMap.value(keyPressed));
    if (button) {
      button->click();  // Simulate button click
    }
  }

  else if (keyPressed == "d" || keyPressed == "D") {
    if (keyPressed == "D") {
      deleteLabel();
    } else {
      on_pushButton_clear_released();
    }
  }

  else if (keyPressed == "x") {
    on_pushButton_x_released();
  }

  else if (keyPressed == "=") {
    onResClicked();
  }

  if (actualIndex == 0) {
    if (keyPressed == "X") {
      showDialog();
    }
  }
}

void Widget::showDialog() {
  bool ok;
  double newValue =
      QInputDialog::getDouble(this, tr("Set X value"), tr("Enter new X value:"),
                              xValue, -DBL_MAX, DBL_MAX, 7, &ok);
  if (ok) {
    xValue = newValue;
    ui->push_button_x->setText("X = " + QString::number(xValue, 'g', 3));
  }

  ui->push_button_x->setDown(false);
}

void Widget::deleteLabel() { updateLabelText(""); }

void Widget::on_pushButton_x_released() {
  longPressTimerX->stop();
  if (actualIndex == 0) {
    ui->text_label_output_calc->setText(ui->text_label_output_calc->text() +
                                        "x");
  } else if (actualIndex == 1) {
    ui->text_label_input_graphic->setText(ui->text_label_input_graphic->text() +
                                          "x");
  }
}

void Widget::on_pushButton_clear_released() {
  longPressTimerClear->stop();
  if (actualIndex == 0) {
    QString currentText = ui->text_label_output_calc->text();
    if (!currentText.isEmpty()) {
      currentText.chop(1);
      ui->text_label_output_calc->setText(currentText);
    }
  } else if (actualIndex == 1) {
    QString currentText = ui->text_label_input_graphic->text();
    if (!currentText.isEmpty()) {
      currentText.chop(1);
      ui->text_label_input_graphic->setText(currentText);
    }
  }
}

void Widget::onCreditTypeClicked() {
  if (creditType == 0) {
    ui->push_button_credit_type->setText("DIFFERENTIATED");
    creditType = 1;
  } else if (creditType == 1) {
    ui->push_button_credit_type->setText("ANNUITY");
    creditType = 0;
  }
}

void Widget::onProfitCapTypeClicked() {
  if (profitCapState == 0) {
    ui->push_button_pc_state->setText("CAPITALIZATION FREQ:");
    profitCapState = 1;
  } else if (profitCapState == 1) {
    ui->push_button_pc_state->setText("PAYMENT FREQ:");
    profitCapState = 0;
  }
}

void Widget::onResClicked() {
  if (actualIndex == 0 || actualIndex == 1) {
    stdCalc();
  } else if (actualIndex == 2) {
    creditCalc();
  } else if (actualIndex == 3) {
    debitCalc();
  }
}

void Widget::stdCalc() {
  if (ui->text_label_output_calc->text() != "" ||
      ui->text_label_input_graphic->text() != "") {
    double val = 0;
    if (!getLabelRes(&val, xValue)) {
      if (actualIndex == 0) {
        ui->text_label_output_calc->setText(QString::number(val, 'g', 7));
      } else if (actualIndex == 1) {
        createGraph();
      }
    } else {
      updateLabelText("INVALID");
    }
  }
}

void Widget::creditCalc() {
  Stack* res = create_stack(4);
  if (res != NULL) {
    double TC = ui->dbl_spin_box_money_input_credit->value();
    double TM = ui->dbl_spin_box_month_input_credit->value();
    double P = ui->dbl_spin_box_percent_input_credit->value();

    credit_calc(res, TC, TM, P, creditType);

    ui->text_label_money_credit_output_0->setText(
        QString::number(pop(res), 'f', 2));
    ui->text_label_money_credit_output_1->setText(
        QString::number(pop(res), 'f', 2));
    ui->text_label_money_credit_output_2->setText(
        QString::number(pop(res), 'f', 2));
    ui->text_label_money_credit_output_3->setText(
        QString::number(pop(res), 'f', 2));

    destroy_stack(res);
  }
}

void Widget::debitCalc() {
  Stack* res = create_stack(3);
  if (res != NULL) {
    double TD = ui->dbl_spin_box_money_input_depo_td->value();
    double P = ui->dbl_spin_box_month_input_depo->value();
    double PR = ui->dbl_spin_box_percent_input_depo_pr->value();
    double TR = ui->dbl_spin_box_percent_input_depo_tr->value();
    double R = ui->dbl_spin_box_money_input_depo_r->value();
    double W = ui->dbl_spin_box_money_input_depo_w->value();

    QByteArray RR = ui->combo_box_r->currentText().toUtf8();
    QByteArray WR = ui->combo_box_w->currentText().toUtf8();
    QByteArray PCF = ui->combo_box_pcf->currentText().toUtf8();

    deposit_calc(res, TD, P, PR, TR, R, W, RR.data(), WR.data(), PCF.data(),
                 profitCapState);
    ui->text_label_money_depo_output_tp->setText(
        QString::number(pop(res), 'f', 2));
    ui->text_label_money_depo_output_tt->setText(
        QString::number(pop(res), 'f', 2));
    ui->text_label_money_depo_output_tb->setText(
        QString::number(pop(res), 'f', 2));

    destroy_stack(res);
  }
}

void Widget::on_pushButton_x_pressed() { longPressTimerX->start(500); }

void Widget::on_pushButton_clear_pressed() { longPressTimerClear->start(500); }

void Widget::updateLabelText(const QString& text) {
  if (actualIndex == 0) {
    ui->text_label_output_calc->setText(text);
  } else if (actualIndex == 1) {
    ui->text_label_input_graphic->setText(text);
  }
}

int Widget::getLabelRes(double* res, double xTarget) {
  QByteArray equation = {0};

  if (actualIndex == 0) {
    equation = ui->text_label_output_calc->text().toUtf8();
  } else if (actualIndex == 1) {
    equation = ui->text_label_input_graphic->text().toUtf8();
  }

  int err_code = calc_label_eq(res, equation.data(), xTarget);

  return err_code;
}

void Widget::createGraph() {
  ui->graphic->clearGraphs();
  ui->graphic->clearPlottables();

  x.clear();
  y.clear();

  QCPGraph* graph = ui->graphic->addGraph();

  for (double xTmp = gMin; xTmp <= gMax; xTmp += gStep) {
    double val = 0;
    getLabelRes(&val, xTmp);
    x.append(xTmp);
    y.append(val);
    ;
  }

  graph->setData(x, y);
  graph->setPen(QPen(Qt::red, 2));

  ui->graphic->replot();
}
