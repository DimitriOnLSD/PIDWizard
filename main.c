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
    uint8_t method;
    bool type; // Type of circuit. 0 - Series, 1 - Parallel
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
        case 0: // Calculate K-pid, integral-derivative time from series circuit
            type = 0;

            // Prompt the user to enter the component values with validation
            getInput("Enter R1: ", &components.R1);
            getInput("Enter R2: ", &components.R2);
            getInput("Enter R3: ", &components.R3);
            getInput("Enter R4: ", &components.R4);
            getInput("Enter C1: ", &components.C1);
            getInput("Enter C2: ", &components.C2);

            // Calculate Kp, Ki and Kd based on R1, R2, R3, R4, C1 and C2
            pid.Kp = calculateKp(type, components.R1, components.R2, components.R3, components.R4, components.C1, components.C2);
            pid.Ki = calculateKi(type, components.R1, components.R3, components.R4, components.C2);
            pid.Kd = calculateKd(type, components.R2, components.R3, components.R4, components.C1);
            break;
        case 1: // Calculate K-pid, integral-derivative time from parallel circuit
            type = 1;

            // Prompt the user to enter the component values with validation
            getInput("Enter R1: ", &components.R1);
            getInput("Enter R2: ", &components.R2);
            getInput("Enter R3: ", &components.R3);
            getInput("Enter R4: ", &components.R4);
            getInput("Enter C1: ", &components.C1);
            getInput("Enter C2: ", &components.C2);

            // Calculate Kp, Ki and Kd based on R1, R2, R3, R4, C1 and C2
            pid.Kp = calculateKp(type, components.R1, components.R2, components.R3, components.R4, components.C1, components.C2);
            pid.Ki = calculateKi(type, components.R1, components.R3, components.R4, components.C2);
            pid.Kd = calculateKd(type, components.R2, components.R3, components.R4, components.C1);
            break;
        case 2: // Series: Determine circuit components for given K-pid, R3, C1 and C2
            type = 0;
            method = 0;

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
                components.R1 = calculateR1(type, method, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
                components.R2 = calculateR2(type, method, components.R1, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
                components.R4 = calculateR4(type, method, components.R1, components.R2, components.R3, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            }
            break;
        case 3: // Series: Determine circuit components for given K-pid, R2, R4 and assuming C1=C2
            type = 0;
            method = 1;

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
                components.R1 = calculateR1(type, method, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
                components.R3 = calculateR3(type, method, components.R1, components.R2, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            }
            break;
        case 4: // Parallel: Determine circuit components for given K-pid, R3, C1 and C2
            type = 1;

            // Prompt the user to enter the component values with validation
            getInput("Enter Kp: ", &pid.Kp);
            getInput("Enter Ki: ", &pid.Ki);
            getInput("Enter Kd: ", &pid.Kd);
            getInput("Enter R3: ", &components.R3);
            getInput("Enter C1: ", &components.C1);
            getInput("Enter C2: ", &components.C2);

            // Calculate R1, R2, and R4 based on R3, C1, C2, Kp, Ki, and Kd
            components.R1 = calculateR1(type, method, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.R2 = calculateR2(type, method, components.R1, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.R4 = calculateR4(type, method, components.R1, components.R2, components.R3, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            break;
        case 5: // Parallel: Determine circuit components for given K-pid, R1, R2 and R3
            type = 1;

            // Prompt the user to enter the component values with validation
            getInput("Enter Kp: ", &pid.Kp);
            getInput("Enter Ki: ", &pid.Ki);
            getInput("Enter Kd: ", &pid.Kd);
            getInput("Enter R1: ", &components.R1);
            getInput("Enter R2: ", &components.R2);
            getInput("Enter R3: ", &components.R3);

            // Calculate R4, C1 and C2
            components.R4 = calculateR4(type, method, components.R1, components.R2, components.R3, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.C1 = calculateC1(type, method, components.R1, components.R2, components.R3, components.R4, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.C2 = calculateC2(type, method, components.R1, components.R2, components.R3, components.R4, components.C1, pid.Kp, pid.Ki, pid.Kd);
            break;
        case 6: // Parallel: Determine circuit components for given K-pid, R1, R2 and R3
            type = 1;

            // Prompt the user to enter the component values with validation
            getInput("Enter Kp: ", &pid.Kp);
            getInput("Enter Ki: ", &pid.Ki);
            getInput("Enter Kd: ", &pid.Kd);
            getInput("Enter R4: ", &components.R4);
            getInput("Enter C: ", &components.C1);

            components.C2 = components.C1;

            // Calculate R1, R2, and R3
            components.R1 = calculateR1(type, method, components.R2, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.R2 = calculateR2(type, method, components.R1, components.R3, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            components.R3 = calculateR3(type, method, components.R1, components.R2, components.R4, components.C1, components.C2, pid.Kp, pid.Ki, pid.Kd);
            break;
        case 7: // Exit
            exit(0);
        default:
            printf("Error! Option does not have function.\n");
            error = true;
        }

        if (!error)
        {
            // Calculate integral and derivative time duration
            pid.Ti = calculateTi(type, components.R1, components.R2, components.C1, components.C2);
            pid.Td = calculateTd(type, components.R1, components.R2, components.C1, components.C2);

            // Display the calculated component values
            printf("\nCalculated PID Component Values:\n");
            displayInformation(&components, &pid);
        }

        system("pause");
        initializePID(&components, &pid);
    }

    return 0;
}