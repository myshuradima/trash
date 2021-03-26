#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <omp.h>
#include <math.h>

std::string integralReduction(double a, double b, double steps);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::string n = integralReduction(1, 50, 600);
    ui->label->setText(QString::fromStdString(n));
}

std::string integralReduction(double a, double b, double steps)
{
    int st=steps;
    int n = 5;
    double result = 0;
    double function = 0;
    double dx = (b - a) / steps;
    double startTime = 0, endTime = 0;
    omp_set_num_threads(n);
    double x;
    int i;
    std::string final_string = "";
    #pragma omp parallel firstprivate(a, dx, function)
    {
        startTime = omp_get_wtime();
        #pragma omp for reduction (+:result,x)
        for (i = 0; i < st; i++)
        {
            x = a + i * dx;
            function += x - (3 * (3 * x));
            result += function * dx;
        }
        endTime = omp_get_wtime();
        final_string = final_string + "Time work:" + std::to_string(endTime - startTime) + " Thread number: " + std::to_string(omp_get_thread_num()) + "\n";
    }
    final_string = final_string + std::to_string(result);
    return final_string;
}

class Function
{
public:
    double result = 0;
    double calculate(double t)
    {
        result = 3*sqrt(t);
        return result;
    }
};

class IntegralCalculator
{
public:
    double result = 0;
    double calculate(double a, double b, int n_steps, int n_threads)
    {
        int i;
        double h = (b-a)/n_steps;
        double t = a;
        Function func;
        omp_set_num_threads(n_threads);
#pragma omp parallel for shared(result, h, func, t) private(i)
        for(i = 0; i < n_steps-1; i++){
            t = t + h;
            result = result + func.calculate(t)*h;
        }
        return result;
    }
};

void MainWindow::on_pushButton_2_clicked()
{
    IntegralCalculator ic;
    QString n_stepstext = ui->lineEdit->text();
    QString n_threadstext = ui->lineEdit_2->text();
    int n_steps = n_stepstext.toInt();
    int n_threads = n_threadstext.toInt();
    double result = ic.calculate(1, 9, n_steps, n_threads);
    ui->label->setText(QString::number(result));
}
