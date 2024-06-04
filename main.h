#ifndef MAIN_H
#define MAIN_H

#define MAX_STRING_TABLE 20

// Program verion
char version[17] = "PIDWizard v0.3.0";

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

// Structure to hold the PID values
typedef struct
{
    double Kp;  // Proportional gain
    double Ki;  // Integrative gain
    double Kd;  // Derivative gain
    double Ti;  // Integration time
    double Td;  // Derivation time
    double R;   // Slope
    double K;   // Steady state output
    double L;   // Lag time
    double T;   // Time constant
    double Tcr; // Critical period
    double Kcr; // Critical value
} PID;

// Menu string
char str[][100] = {"Calculate K-pid, integral-derivative time from series circuit",
                   "Calculate K-pid, integral-derivative time from parallel circuit",
                   "Determine series-circuit components for given K-pid, R3, C1 and C2",
                   "Determine series-circuit components for given K-pid, R2, R4 and assuming C1=C2",
                   "Determine parallel-circuit components for given K-pid, R3, C1 and C2",
                   "Determine parallel-circuit components for given K-pid, R1, R2 and R3",
                   "Determine parallel-circuit components for given K-pid, R4 and assuming C1=C2",
                   "Exit"};

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

double calculateR1(bool type, uint8_t method, double R2, double R3, double R4, double C1, double C2, double Kp, double Ki, double Kd);
double calculateR2(bool type, uint8_t method, double R1, double R3, double R4, double C1, double C2, double Kp, double Ki, double Kd);
double calculateR3(bool type, uint8_t method, double R1, double R2, double R4, double C1, double C2, double Kp, double Ki, double Kd);
double calculateR4(bool type, uint8_t method, double R1, double R2, double R3, double C1, double C2, double Kp, double Ki, double Kd);
double calculateC1(bool type, uint8_t method, double R1, double R2, double R3, double R4, double C2, double Kp, double Ki, double Kd);
double calculateC2(bool type, uint8_t method, double R1, double R2, double R3, double R4, double C1, double Kp, double Ki, double Kd);
double calculateKp(uint8_t type, double R1, double R2, double R3, double R4, double C1, double C2);
double calculateKi(uint8_t type, double R1, double R3, double R4, double C2);
double calculateKd(uint8_t type, double R2, double R3, double R4, double C1);
double calculateTi(uint8_t type, double R1, double R2, double C1, double C2);
double calculateTd(uint8_t type, double R1, double R2, double C1, double C2);

#endif