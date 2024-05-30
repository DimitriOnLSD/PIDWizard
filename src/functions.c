// Function to initialize the PID components
void initializePID(PIDComponents *components, PID *pid)
{
    components->R1 = 0;
    components->R2 = 0;
    components->R3 = 0;
    components->R4 = 0;
    components->C1 = 0;
    components->C2 = 0;
    pid->Kp = 0;
    pid->Ki = 0;
    pid->Kd = 0;
    pid->Ti = 0;
    pid->Td = 0;
    pid->R = 0;
    pid->K = 0;
    pid->L = 0;
    pid->T = 0;
    pid->Tcr = 0;
    pid->Kcr = 0;
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

void zieglerNicholsTuning(PID *pid, uint8_t overshoot)
{
    switch (overshoot)
    {
    case 0:
        pid->L = pid->Td / 0.5;
        pid->T = pid->Ti;
        pid->R = 0.6 / (pid->Kp * pid->L);
        pid->K = pid->R * pid->T;
        break;
    case 20:
        pid->L = pid->Td / 0.47;
        pid->T = 1.4 * pid->Ti;
        pid->R = 0.95 / (pid->Kp * pid->L);
        pid->K = pid->R * pid->T;
        break;
    case 25:
        pid->L = pid->Ti / 2;
        pid->R = 1.2 / (pid->Kp * pid->L);
        pid->Tcr = pid->Ti / 0.5;
        pid->Kcr = pid->Kp / 0.6;
        break;
    }
}

double calculateR1(double C1, double Kp, double Ki, double Kd) { return (Kp - sqrt(pow(Kp, 2) - 4 * Ki * Kd)) / (2 * C1 * Ki); }
double calculateR2(double R1, double C1, double C2, double Ki, double Kd) { return Kd / (Ki * R1 * C1 * C2); }
double calculateR4(double R2, double R3, double C1, double Kd) { return (Kd * R3) / (R2 * C1); }
double calculateKp(double R1, double R2, double R3, double R4, double C1, double C2) { return R4 * (R1 * C1 + R2 * C2) / (R1 * R3 * C2); }
double calculateKi(double R1, double R3, double R4, double C2) { return R4 / (R1 * R3 * C2); }
double calculateKd(double R2, double R3, double R4, double C1) { return R2 * R4 * C1 / R3; }
double calculateTi(double R1, double R2, double C1, double C2) { return (R1 * C1 + R2 * C2); }
double calculateTd(double R1, double R2, double C1, double C2) { return (R1 * C1 * R2 * C2) / (R1 * C1 + R2 * C2); }