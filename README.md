# PID Component Calculator
## Introduction
This tool simplifies the design and analysis of PID controllers. It calculates the necessary components (resistors, capacitors, etc.) for a given set of PID parameters (Kp, Ki, Kd) in a series PID controller configuration. Additionally, it can determine the PID parameters (Kp, Ki, Kd) along with the integral time (Ti) and derivative time (Td) based on the existing circuit components. This makes it an invaluable resource for both designing new PID controllers and analyzing existing ones.

## Features
- Calculate circuit component values for a given set of PID parameters.
- Determine PID parameters based on existing circuit components:
    - Proportional-integral-derivative gains.
    - Integral-derivatime time.
    - Ziegler-Nichols table with 0%, 20% and 25% overshoot.
- Supports both series and parallel PID controller configurations.
- Provides a clear layout of component placements.

## Installation
To use this tool, clone the repository and compile the source code:
```
git clone https://github.com/DimitriOnLSD/PIDWizard.git
cd PIDWizard
make
```
## Usage
To run the tool, use the following command:
```
./pid_calculator
```
Follow the on-screen instructions to choose your desired operation:

Determine PID Parameters: Input the values of R1, R2, R3, R4, C1, and C2 to get the corresponding Kp, Ki, Kd, Ti, and Td of the circuit.

Calculate Component Values: Input the desired Kp, Ki, and Kd values along with the values of R3, C1, and C2 to get the required R1, R2, and R4 component values.

Ensure to provide accurate measurements and values to obtain precise results.

Here's an example of how you might use the tool:

- Select whether you want to determine PID parameters or calculate component values.

![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/bf99af9f-e848-44bd-a27b-9515fe5453ca)

- Follow the prompts to input the necessary values.

![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/3591ba36-322c-4d22-afc0-291ccc869c3a)

- Receive the calculated output for your PID controller design.

# Important Notes
**Original method:** When using the original method of determining PID components through *Kp, Ki, Kd, R3, C1 and C2*, if $(K_p < 2\sqrt{T_i T_d})$, the method will not work correctly. You will receive an error message:
```
Using this method, ( 2 * sqrt(Ti * Td) ) should not be greater than Kp.
```
Ensure that this condition is met to avoid errors.

**Matching R2 with C:** When using the *Determine circuit components for given K-pid, R2, R4, and assuming C1=C2* option, ensure that the larger the R2 resistor is, the smaller the capacitor C should be. For example:

- For a 1k resistor for R2, select a capacitor smaller than 1mF. Ratio = 1
- For a 22k resistor for R2, select a capacitor smaller than 470uF. Ratio = 1.03
- For a 330k resistor for R2, select a capacitor smaller than 3.3uF. Ratio = 0.99

Maintaining this ratio ensures that R2 * C2 gives a value close to one, which helps in achieving optimal performance in the PID controller. If this is not achievable, increasing integral-time through with larger proportional-gain and/or smaller integral-gain should also work, since it will increase the ratio cap.

## Example
Below is an example of the circuit with indications of the resistor and capacitor placements. This example provides a clear layout, helping you to understand the placement and designation of each component within the PID controller circuit.

![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/95bfcb31-0f98-40b2-b86a-73815d24fff3)

## Input Parameters
Please note that the input to this tool takes into account the difference between two voltages. Ensure that your voltage measurements reflect this differential to obtain accurate calculations for the PID parameters and corresponding circuit components.

## Output
The tool outputs the calculated component values or PID parameters, along with Ti and Td times if applicable. Ensure to double-check the provided values against your design requirements.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your improvements or bug fixes. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contact
For any questions or feedback, use the issues section.
