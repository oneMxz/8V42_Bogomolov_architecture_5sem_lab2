#include "tasks.h"
#include <iostream>

int main(){
    int n=1;
    while (n!=0){
        std::cout << "Введите номер блока (1 или 2) или введите 0 для выхода: \n";
        std::cin >> n;
        switch(n)
        {
            case 0:
                std::cout <<"Выход из программы";
                break;
            case 1: 
                program_1();
                break;
            case 2: 
                program_2();
                break;
            default: 
                std::cout << "Неверный номер задания" << "\n";
                break;
        }
    }  
    return 0;
}