#ifndef MAIN_H
#define MAIN_H

// Structure to hold the component values for the PID calculator
typedef struct
{
    double R1;
    double R2;
    double R3;
    double R4;
    double C1;
    double C2;
    double Kp;
    double Ki;
    double Kd;
    double Ti;
    double Td;
} PIDComponents;

char str[][30] = {"Find Kp, Ki and Kd values",
                  "Make PID (R1, R2, R4)",
                  "Exit"};

int overflow(int var, int min, int max);
bool readKeyboard(int8_t *pos, uint8_t options);
bool getInput(const char *prompt, double *value);
void displayComponents(const PIDComponents *components);
void displayMenu(uint8_t pos, uint8_t options);
void initializeComponents(PIDComponents *components);
void convertCapacitance(double *capacitance, char *unit);
void convertTime(double *time, char *unit);
double calculateR1(double C1, double Kp, double Ki, double Kd);
double calculateR2(double R1, double C1, double C2, double Ki, double Kd);
double calculateR4(double R2, double R3, double C1, double Kd);
double calculateKp(double R1, double R2, double R3, double R4, double C1, double C2);
double calculateKi(double R1, double R3, double R4, double C2);
double calculateKd(double R2, double R3, double R4, double C1);
double calculateTi(double R1, double R2, double C1, double C2);
double calculateTd(double R1, double R2, double C1, double C2);

#endif