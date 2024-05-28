// Function to display the PID component values
void displayComponents(const PIDComponents *components)
{
    char unitC1[3], unitC2[3];
    char unitTi[3], unitTd[3];
    double convertedC1 = components->C1, convertedC2 = components->C2;
    double convertedTi = components->Ti, convertedTd = components->Td;
    convertCapacitance(&convertedC1, unitC1);
    convertCapacitance(&convertedC2, unitC2);
    convertTime(&convertedTi, unitTi);
    convertTime(&convertedTd, unitTd);

    printf("\n#===# RESISTORS #===#\n");
    printf("R1: %.0lf\n", components->R1);
    printf("R2: %.0lf\n", components->R2);
    printf("R3: %.0lf\n", components->R3);
    printf("R4: %.0lf\n", components->R4);
    printf("#===================#\n");
    printf("\n#===# CAPACITORS #===#\n");
    printf("C1: %.2lf %s\n", convertedC1, unitC1);
    printf("C2: %.2lf %s\n", convertedC2, unitC2);
    printf("#====================#\n");
    printf("\n#===# PID #===#\n");
    printf("Kp: %.3lf\n", components->Kp);
    printf("Ki: %.3lf\n", components->Ki);
    printf("Kd: %.3lf\n", components->Kd);
    printf("Ti: %.3lf %s\n", convertedTi, unitTi);
    printf("Td: %.3lf %s\n", convertedTd, unitTd);
    printf("#=============#\n");
    printf("\n");
}

void displayMenu(uint8_t pos, uint8_t options)
{
    printf("\033[H");
    printf("===================================\n");
    printf("|| PID Component Calculator v0.2 ||\n");
    printf("===================================\n");
    printf("UP-ARROW | DOWN-ARROW to navigate\n");
    printf("ENTER to select | ESC to exit\n\n");
    printf("Choose any of the following:\n\n");
    for (int j = 0; j < pos; j++)
        printf("%s\n", str[j]);
    printf(BLK_WHTB "%s\n" COLOR_RESET, str[pos]);
    for (int k = ++pos; k < options; k++)
        printf("%s\n", str[k]);
}

int overflow(int var, int min, int max)
{
    return (var > max) ? min : ((var < min) ? max : var);
}

bool readKeyboard(int8_t *pos, uint8_t options)
{
    switch (_getch())
    {
    case 27: // ESC
        exit(0);
    case 13: // ENTER
        return true;
        break;
    case 80: // ARROW_KEY DOWN
        (*pos)++;
        break;
    case 72: // ARROW_KEY UP
        (*pos)--;
        break;
    }
    *pos = overflow(*pos, 0, options - 1);
}

// Function to prompt the user for input and validate it
bool getInput(const char *prompt, double *value)
{
    printf("%s", prompt);
    while (scanf("%lf", value) != 1)
    {
        while (getchar() != '\n')
            ; // Clear the input buffer
        printf("Invalid input. %s", prompt);
    }
    return true;
}