#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // Required for system() function
#include <stdbool.h> // Required for boolean type
#include <stdint.h>
#include <conio.h> // Required for _getch()
#include <windows.h>
#include <ctype.h>
#include "main.h"
#include "src/ansi.h"
#include "src/menu.c"
#include "src/functions.c"

int main(void)
{
    SetConsoleTitle("PIDWizard v0.2.0");

    // Initialize the PID components and variables
    PIDComponents components;
    PID pid;
    initializePID(&components, &pid);
    uint8_t options = sizeof(str) / sizeof(str[0]);
    uint8_t pos = 0;
    bool select;

    while (1)
    {
        // Clear any remaining text
        system("cls");

        // Display the menu and navigate with up-down arrows. Press ENTER to select or ESC to exit
        select = false;
        while (!select)
        {
            displayMenu(pos, options);
            select = readKeyboard(&pos, options);
        }

        // Starts function based on selection
        switch (pos)
        {
        case 0:
            // Prompt the user to enter the component values with validation
            getInput("Enter R1: ", &components.R1);
            getInput("Enter R2: ", &components.R2);
            getInput("Enter R3: ", &components.R3);
            getInput("Enter R4: ", &components.R4);
            getInput("Enter C1: ", &components.C1);
            getInput("Enter C2: ", &components.C2);

            // Calculate Kp, Ki and Kd based on R1, R2, R3, R4, C1 and C2
            pid.Kp = calculateKp(components.R1, components.R2, components.R3, components.R4, components.C1, components.C2);
            pid.Ki = calculateKi(components.R1, components.R3, components.R4, components.C2);
            pid.Kd = calculateKd(components.R2, components.R3, components.R4, components.C1);
            break;
        case 1:
            // Prompt the user to enter the component values with validation
            getInput("Enter Kp: ", &pid.Kp);
            getInput("Enter Ki: ", &pid.Ki);
            getInput("Enter Kd: ", &pid.Kd);
            getInput("Enter R3: ", &components.R3);
            getInput("Enter C1: ", &components.C1);
            getInput("Enter C2: ", &components.C2);

            // Calculate R1, R2, and R4 based on R3, C1, C2, Kp, Ki, and Kd
            components.R1 = calculateR1(components.C1, pid.Kp, pid.Ki, pid.Kd);
            components.R2 = calculateR2(components.R1, components.C1, components.C2, pid.Ki, pid.Kd);
            components.R4 = calculateR4(components.R2, components.R3, components.C1, pid.Kd);
            break;
        case 2:
            exit(0);
            break;
        default:
            printf("Error! Option does not have function.");
        }

        // Calculate integral and derivative time duration
        pid.Ti = calculateTi(components.R1, components.R2, components.C1, components.C2);
        pid.Td = calculateTd(components.R1, components.R2, components.C1, components.C2);

        // Display the calculated component values
        printf("\nCalculated PID Component Values:\n");
        displayInformation(&components, &pid);
        system("pause");
        initializePID(&components, &pid);
    }

    return 0;
}