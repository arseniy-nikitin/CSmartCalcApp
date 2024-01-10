QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../bank_calc/credit_calc.c \
    ../bank_calc/deposit_calc.c \
    ../common/s21_strnstr.c \
    ../common/stack.c \
    ../std_calc/calc_label_eq.c \
    ../std_calc/calc_rpn_eq.c \
    ../std_calc/infix_to_rpn.c \
    ../std_calc/str_eq_validator.c \
    ../std_calc/str_to_stack.c \
    main.cpp \
    qcustomplot.cpp \
    widget.cpp

HEADERS += \
    ../bank_calc/bank_calc.h \
    ../common/s21_strnstr.h \
    ../common/stack.h \
    ../smart_calc.h \
    qcustomplot.h \
    widget.h

FORMS += \
    widget.ui

TRANSLATIONS += \
    smart_calc_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
