#ifndef MAIN_H
#define MAIN_H

#define MAX_STRING_TABLE 20

// Structure to hold the component values for the PID calculator
typedef struct
{
    double R1;
    double R2;
    double R3;
    double R4;
    double C1;
    double C2;
} PIDComponents;

typedef struct
{
    double Kp;
    double Ki;
    double Kd;
    double Ti;
    double Td;
    double R;   // Slope
    double K;   // Steady state output
    double L;   // Lag time
    double T;   // Time constant
    double Tcr; // Critical period
    double Kcr; // Critical value
} PID;

char str[][100] = {"Calculate gains, integral-derivative time from circuit components",
                   "Determine circuit components for given Kp, Ki, Kd, R3, C1, and C2",
                   "Exit"};

// char str[][100] = {"Calculate gains, integral-derivative time from circuit components",
//                    "Determine circuit components for given Kp, Ki, Kd, R3, C1, and C2",
//                    "Determine circuit components for given Kp, Ki, Kd, Ti, Td, and XX",
//                    "Determine circuit components Assuming C1=C2",
//                    "Exit"};

int overflow(int var, int min, int max);
bool readKeyboard(int8_t *pos, uint8_t options);
bool getInput(const char *prompt, double *value);
void zieglerNicholsTuning(PID *pid, uint8_t overshoot);
void displayInformation(PIDComponents *components, PID *pid);
void displayMenu(uint8_t pos, uint8_t options);
void initializePID(PIDComponents *components, PID *pid);
void convertCapacitance(double *capacitance, char *unit);
void convertTime(double *time, char *unit);
void printTableHeader(const char headers[][MAX_STRING_TABLE], int columnCount);
void printTableFooter(const char headers[][MAX_STRING_TABLE], int columnCount);
void printTableRow(const char row[][MAX_STRING_TABLE], int columnCount);
double calculateR1(double C1, double Kp, double Ki, double Kd);
double calculateR2(double R1, double C1, double C2, double Ki, double Kd);
double calculateR4(double R2, double R3, double C1, double Kd);
double calculateKp(double R1, double R2, double R3, double R4, double C1, double C2);
double calculateKi(double R1, double R3, double R4, double C2);
double calculateKd(double R2, double R3, double R4, double C1);
double calculateTi(double R1, double R2, double C1, double C2);
double calculateTd(double R1, double R2, double C1, double C2);

#endif