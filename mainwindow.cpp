#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::refreshComplexStack(Stack<ComplexNumber> *s) {
    ui->ComlexStack->clear();
    auto evaluationStack = s->reversed();
    while (!evaluationStack.empty()) {
        ui->ComlexStack->addItem(QString::fromStdString(evaluationStack.pop().toString()));
    }
    std::cout << "Stack renewed" << std::endl;
}

void MainWindow::on_popButton_clicked() {
    if (stack.empty()) {
        std::cout << "Stack is empty!" << std::endl;
    } else {
        stack.pop();
        refreshComplexStack(&stack);
    }
}

void MainWindow::on_pushButton_clicked() {
    double rl = ui->doubleSpinBoxR->value();
    double im = ui->doubleSpinBoxI->value();
    stack.push({rl, im});
    refreshComplexStack(&stack);
    std::cout << "Added " << ComplexNumber(rl, im).toString() << std::endl;
}

void MainWindow::on_calculateButton_clicked() {
    int i = ui->comboBox->currentIndex(); // +, -, *, /, R, I, abs
    Operator o('+');
    if (i == 0)
        o.ChangeType('+');
    else if (i == 1)
        o.ChangeType('-');
    else if (i == 2)
        o.ChangeType('*');
    else if (i == 3)
        o.ChangeType('/');
    else if (i == 4)
        o.ChangeType('R');
    else if (i == 5)
        o.ChangeType('I');
    else if (i == 6)
        o.ChangeType('A');

    ui->calcLabel->setText(QString::fromStdString(o.Calculate(stack).toString()));

}
