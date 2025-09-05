#pragma once

class InputHelper
{
public:
    static void waitForSpacebar();
    static void waitForAttack();
    static int getValidChoice(int minChoice, int maxChoice);
    static char getYesNoChoice();
};