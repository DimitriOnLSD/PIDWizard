// Function to display the PID component values
void displayInformation(PIDComponents *components, PID *pid)
{
    uint8_t overshoot[3] = {0, 20, 25};
    char unitC1[3], unitC2[3];
    char unitTi[3], unitTd[3];
    double convertedC1 = components->C1, convertedC2 = components->C2;
    double convertedTi = pid->Ti, convertedTd = pid->Td;
    convertCapacitance(&convertedC1, unitC1);
    convertCapacitance(&convertedC2, unitC2);
    convertTime(&convertedTi, unitTi);
    convertTime(&convertedTd, unitTd);

    // Print Resistors, Capacitors and basic PID values 
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
    printf("Kp: %.3lf\n", pid->Kp);
    printf("Ki: %.3lf\n", pid->Ki);
    printf("Kd: %.3lf\n", pid->Kd);
    printf("Ti: %.3lf %s\n", convertedTi, unitTi);
    printf("Td: %.3lf %s\n", convertedTd, unitTd);
    printf("#=============#\n");

    // Ziegler-Nichols table headers
    const char headers[][MAX_STRING_TABLE] = {
        "Overshoot",
        "Time constant",
        "Lag time",
        "Slope",
        "Steady State",
        "Critical period",
        "Critical value"};
    int columnCount = sizeof(headers) / sizeof(headers[0]);

    // Print title
    char c = '=';
    int count = 51;
    printf("\n#");
    for (uint8_t i = 0; i < count; i++)
    {
        putchar(c);
    }
    printf("# Ziegler-Nichols table #");
    for (uint8_t i = 0; i < count - 1; i++)
    {
        putchar(c);
    }
    printf("#\n");

    // Print header
    printTableHeader(headers, columnCount);

    // Print rows
    for (uint8_t i = 0; i < 3; i++)
    {
        zieglerNicholsTuning(pid, overshoot[i]);

        // Prepare data for the table
        char data[1][7][MAX_STRING_TABLE]; // Single row with 7 columns
        snprintf(data[0][0], MAX_STRING_TABLE, "%d%%", overshoot[i]);
        snprintf(data[0][1], MAX_STRING_TABLE, "%.3lf", pid->T);
        snprintf(data[0][2], MAX_STRING_TABLE, "%.3lf", pid->L);
        snprintf(data[0][3], MAX_STRING_TABLE, "%.3lf", pid->R);
        if (overshoot[i] == 25)
        {
            snprintf(data[0][4], MAX_STRING_TABLE, "%s", "-");
            snprintf(data[0][5], MAX_STRING_TABLE, "%.3lf", pid->Tcr);
            snprintf(data[0][6], MAX_STRING_TABLE, "%.3lf", pid->Kcr);
        }
        else
        {
            snprintf(data[0][4], MAX_STRING_TABLE, "%.3lf", pid->K);
            snprintf(data[0][5], MAX_STRING_TABLE, "%s", "-");
            snprintf(data[0][6], MAX_STRING_TABLE, "%s", "-");
        }

        printTableRow(data[0], columnCount);
    }
    // Print footer
    printTableFooter(headers, columnCount);
}

// Function to display the main menu and selection
void displayMenu(uint8_t pos, uint8_t options)
{
    printf("\033[H"); // Cursor to top-left corner
    printf("===================================\n");
    printf("||       %s        ||\n", version);
    printf("===================================\n");
    printf("UP-ARROW & DOWN-ARROW to navigate\n");
    printf("ENTER to select | ESC to exit\n\n");
    printf("Additional help and an example series PID circuit is available here:\nhttps://github.com/DimitriOnLSD/PIDWizard.git\n\n");
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

// Function to navigate the menu
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
    fflush(stdin);
    while (scanf("%lf", value) == isdigit(*value))
    {
        while (getchar() != '\n'); // Clear the input buffer
        printf("\nInvalid input. %s", prompt);
    }
    return true;
}

// Function to print a table header
void printTableHeader(const char headers[][MAX_STRING_TABLE], int columnCount)
{
    printf("#");
    for (int i = 0; i < columnCount; i++)
    {
        printf("==================");
    }
    printf("#\n");

    for (int i = 0; i < columnCount; i++)
    {
        printf("%-19s", headers[i]);
    }
    printf("\n");

    printf("#");
    for (int i = 0; i < columnCount; i++)
    {
        printf("==================");
    }
    printf("#\n");
}

// Function to print a table footer
void printTableFooter(const char headers[][MAX_STRING_TABLE], int columnCount)
{
    printf("#");
    for (int i = 0; i < columnCount; i++)
    {
        printf("==================");
    }
    printf("#\n");
}

// Function to print a table row
void printTableRow(const char row[][MAX_STRING_TABLE], int columnCount)
{
    for (int i = 0; i < columnCount; i++)
    {
        printf("%-19s", row[i]);
    }
    printf("\n");
}