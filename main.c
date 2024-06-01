#include <stdio.h>
#include <math.h>    // Required for pow() and sqrt() functions
#include <stdlib.h>  // Required for system() function
#include <stdbool.h> // Required for boolean type
#include <stdint.h>  // Required for uint8_t variable type
#include <conio.h>   // Required for _getch()
#include <windows.h>
#include <ctype.h>
#include "main.h"
#include "src/ansi.h"
#include "src/menu.c"
#include "src/functions.c"

int main(void)
{
    SetConsoleTitle(version);

    // Initialize the PID components and variables
    PIDComponents components;
    PID pid;
    initializePID(&components, &pid);
    uint8_t options = sizeof(str) / sizeof(str[0]);
    uint8_t pos = 0;
    bool select;
    bool error;

    while (1)
    {
        // Clear any remaining text
        system("cls");

        // Display the menu and navigate with up-down arrows. Press ENTER to select or ESC to exit
        select = false;
        error = false;
        while (!select)
        {
            displayMenu(pos, options);
            select = readKeyboard(&pos, options);
        }

        printf("\n");
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

            if (pow(pid.Kp, 2) < 4 * pid.Ki * pid.Kd)
            {
                printf("\nUsing this method, ( 2 * sqrt(Ti * Td) ) should not be greater than Kp.");
                printf("\nYou can:\n1. Increase Kp.\n2. Decrease Ki or Kd.\n3. Use another option.\n");
                error = true;
            }
            else
            {
                // Calculate R1, R2, and R4 based on R3, C1, C2, Kp, Ki, and Kd
                components.R1 = calculateR1(2, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd, pid.Ti);
                components.R2 = calculateR2(components.R1, components.C1, components.C2, pid.Ki, pid.Kd);
                components.R4 = calculateR4(2, components.R1, components.R2, components.R3, components.C1, components.C2, pid.Ki, pid.Kd);
            }
            break;
        case 2:
            // Prompt the user to enter the component values with validation
            getInput("Enter Kp: ", &pid.Kp);
            getInput("Enter Ki: ", &pid.Ki);
            getInput("Enter Kd: ", &pid.Kd);
            getInput("Enter R2: ", &components.R2);
            getInput("Enter R4: ", &components.R4);
            getInput("Enter C: ", &components.C1);

            components.C2 = components.C1;

            if ((components.R2 * components.C2) > (pid.Kp / pid.Ki))
            {
                printf("\nUsing this method, ensure that the larger the R2 resistor is, the smaller the capacitor C should be.\nFor example: R2 = 22k, C = 4.7uF");
                printf("\n\nYou can:\n1. Increase Kp.\n2. Decrease Ki.\n3. Use another option.\n");
                error = true;
            }
            else
            {
                // Calculate R1, and R3 based on R2, C, Kp, Ki, and Kd
                components.R1 = calculateR1(4, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd, pid.Ti);
                components.R3 = calculateR3(components.R1, components.R4, components.C2, pid.Ki);
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Error! Option does not have function.");
        }

        if (!error)
        {
            // Calculate integral and derivative time duration
            pid.Ti = calculateTi(components.R1, components.R2, components.C1, components.C2);
            pid.Td = calculateTd(components.R1, components.R2, components.C1, components.C2);

            // Display the calculated component values
            printf("\nCalculated PID Component Values:\n");
            displayInformation(&components, &pid);
        }

        system("pause");
        initializePID(&components, &pid);
    }

    return 0;
}