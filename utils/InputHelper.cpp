#include "InputHelper.h"
#include <iostream>
#include <limits>
#include <conio.h>

void InputHelper::waitForSpacebar()
{
    std::cout << "\nНажмите пробел, чтобы продолжить...";
    int ch;
    do
    {
        ch = _getch();
    } while (ch != 32); // 32 - код пробела
    std::cout << std::endl;
}

void InputHelper::waitForAttack()
{
    std::cout << "Нажмите 'a', чтобы ударить...";
    char ch;
    do
    {
        ch = _getch();
    } while (ch != 'a' && ch != 'A');
    std::cout << std::endl;
}

int InputHelper::getValidChoice(int minChoice, int maxChoice)
{
    int choice;
    while (true)
    {
        if (std::cin >> choice && choice >= minChoice && choice <= maxChoice)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        else
        {
            std::cout << "Неверный ввод! Введите число от " << minChoice << " до " << maxChoice << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

char InputHelper::getYesNoChoice()
{
    char choice;
    while (true)
    {
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        else
        {
            std::cout << "Неверный ввод! Введите 'y' или 'n': ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}