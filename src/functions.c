// Function to initialize the PID components
void initializeComponents(PIDComponents *components)
{
    components->R1 = 0;
    components->R2 = 0;
    components->R3 = 0;
    components->R4 = 0;
    components->C1 = 0;
    components->C2 = 0;
    components->Kp = 0;
    components->Ki = 0;
    components->Kd = 0;
    components->Ti = 0;
    components->Td = 0;
}

// Function to convert capacitance value to human-readable format
void convertCapacitance(double *capacitance, char *unit)
{
    if (*capacitance < 999e-12)
    {
        strcpy(unit, "pF");
        *capacitance *= 1e12;
    }
    else if (*capacitance < 999e-9)
    {
        strcpy(unit, "nF");
        *capacitance *= 1e9;
    }
    else if (*capacitance < 999e-6)
    {
        strcpy(unit, "uF");
        *capacitance *= 1e6;
    }
    else if (*capacitance < 999e-3)
    {
        strcpy(unit, "mF");
        *capacitance *= 1e3;
    }
    else
    {
        strcpy(unit, "F");
    }
}

// Function to convert capacitance value to human-readable format
void convertTime(double *time, char *unit)
{
    if (*time < 999e-12)
    {
        strcpy(unit, "ps");
        *time *= 1e12;
    }
    else if (*time < 999e-9)
    {
        strcpy(unit, "ns");
        *time *= 1e9;
    }
    else if (*time < 999e-6)
    {
        strcpy(unit, "us");
        *time *= 1e6;
    }
    else if (*time < 999e-3)
    {
        strcpy(unit, "ms");
        *time *= 1e3;
    }
    else
    {
        strcpy(unit, "s");
    }
}

double calculateR1(double C1, double Kp, double Ki, double Kd)                       { return (Kp - sqrt(pow(Kp, 2) - 4 * Ki * Kd)) / (2 * C1 * Ki); }
double calculateR2(double R1, double C1, double C2, double Ki, double Kd)            { return Kd / (Ki * R1 * C1 * C2);                              }
double calculateR4(double R2, double R3, double C1, double Kd)                       { return (Kd * R3) / (R2 * C1);                                 }
double calculateKp(double R1, double R2, double R3, double R4, double C1, double C2) { return R4 * (R1 * C1 + R2 * C2) / (R1 * R3 * C2);             }
double calculateKi(double R1, double R3, double R4, double C2)                       { return R4 / (R1 * R3 * C2);                                   }
double calculateKd(double R2, double R3, double R4, double C1)                       { return R2 * R4 * C1 / R3;                                     }
double calculateTi(double R1, double R2, double C1, double C2)                       { return (R1 * C1 + R2 * C2);                                   }
double calculateTd(double R1, double R2, double C1, double C2)                       { return (R1 * C1 * R2 * C2) / (R1 * C1 + R2 * C2);             }