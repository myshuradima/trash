#include <omp.h>
#include <iostream>
#include <Windows.h>
#define N  10
HANDLE myhandle1, myhandle2, myhandle3, myhandle4, myhandle5;
int a_matrix[N][N];
int b_matrix[N][N];
int c_matrix[N][N];
int sum_list[N];

void print_matrix() {
    int i = 0;
    int k = 0;
    while (k < N) {
        i = 0;
        while (i < N) {
            std::cout << c_matrix[k][i] << " " ;
            i++;
        }
        std::cout << std::endl;
        k++;
    }
}

void create_matrix() {
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            a_matrix[i][j] = rand() % 10;
            b_matrix[i][j] = rand() % 10;
            c_matrix[i][j] = rand() % 10;
        }
    }
}

void print_list() {
    for (int i = 0; i < N; i++) {
        std::cout << sum_list[i]<< " ";
    }
    std::cout << std::endl;
}

int main()
{
    double start_time, end_time, tick;
    std::string aaa;
    start_time = omp_get_wtime();
    end_time = omp_get_wtime();
    tick = omp_get_wtick();
    std::cout << "time to calculate time" << end_time - start_time << std::endl;
    std::cout << "acuracy of calculation" << tick << std::endl;
    create_matrix();
    std::cout << "press any key to start" << std::endl;
    std::cin >> aaa;
    start_time = omp_get_wtime();
    for (int i = 0; i <N; i++) {

            for (int j = 0; j < N; j++) {

                int sum = 0;
                for (int k = 0; k < N; k++) {
                    sum += a_matrix[i][k] * b_matrix[k][j];
                }
                c_matrix[i][j] = sum;
            }
        }
    end_time = omp_get_wtime();
    std::cout << "result" << std::endl;
    print_matrix();
    std::cout << "spent time" << std::endl;
    std::cout << end_time - start_time << std::endl;
    start_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = 0; j < N; j++) {

                sum += c_matrix[i][j];

            }
            sum_list[i] = sum;
        }
    end_time = omp_get_wtime();
    print_list();
    std::cout << "spent time" << std::endl;
    std::cout << end_time - start_time << std::endl; 
    
    omp_set_num_threads(2);
   
#pragma omp parallel private (i, j, k)
        {
#pragma omp for
            start_time = omp_get_wtime();
            for (int i = 0; i < N; i++) {

                for (int j = 0; j < N; j++) {
                    int sum = 0;
                    for (int k = 0; k < N; k++) {
                        sum += a_matrix[i][k] * b_matrix[k][j];
                    }
                    c_matrix[i][j] = sum;
                }
            }
            end_time = omp_get_wtime();
        }
    std::cout << "result" << std::endl;
    print_matrix();
    std::cout << "spent time" << std::endl;
    std::cout << end_time - start_time << std::endl;
    std::cout << "sum" << std::endl;
    start_time = omp_get_wtime();
#pragma omp parallel private (i, j)
    {
#pragma omp for
        for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = 0; j < N; j++) {

                sum += c_matrix[i][j];

            }
            sum_list[i] = sum;
        }
        
    }
    end_time = omp_get_wtime();
    print_list();
    std::cout << "spent tine" << std::endl;
    std::cout << end_time - start_time << std::endl;
}

