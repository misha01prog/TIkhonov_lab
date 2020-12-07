#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stack.h"
#include "complexnumber.h"
#include "operator.h"
#include <iostream>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void refreshComplexStack(Stack <ComplexNumber> *s);

private slots:
    void on_popButton_clicked();
    void on_pushButton_clicked();
    void on_calculateButton_clicked();

private:
    Ui::MainWindow* ui;
    Stack<ComplexNumber> stack;
};
#endif // MAINWINDOW_H
