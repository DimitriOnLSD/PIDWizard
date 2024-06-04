# PID Component Calculator
## Introduction
This tool simplifies the design and analysis of PID controllers. It calculates the necessary components (resistors, capacitors, etc.) for a given set of PID parameters (Kp, Ki, Kd) in a series PID controller configuration. Additionally, it can determine the PID parameters (Kp, Ki, Kd) along with the integral time (Ti) and derivative time (Td) based on the existing circuit components. This makes it an invaluable resource for both designing new PID controllers and analyzing existing ones.

## Features
- Calculate circuit component values for a given set of PID parameters.
- Determine PID parameters based on existing circuit components:
    - Proportional-integral-derivative gains.
    - Integral-derivative time.
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
Additionally, you have other options for obtaining and compiling the source code:

1. GitHub Desktop:
    - Open GitHub Desktop.
    - Clone the repository by pasting the URL https://github.com/DimitriOnLSD/PIDWizard.git.
    - Navigate to the cloned repository on your local machine.
    - Compile the source code using any C compiler, such as Visual Studio.

2. Download ZIP File:
    - Go to the PIDWizard GitHub repository.
    - Click the "Code" button and select "Download ZIP".
    - Extract the downloaded ZIP file.
    - Navigate to the extracted folder.
    - Compile the source code using any C compiler, such as Visual Studio.

3. Download the Release:
    - Visit the [Releases](https://github.com/DimitriOnLSD/PIDWizard/releases) page of the PIDWizard GitHub repository.
    - Download the latest release.
    - The release is an executable file, a simple click-and-run.
## Usage
This tool was not designed to run on Git, as it contains CMD commands. 

To run the tool, simply compile the ```main.c``` using any compiler. The release version is a simple executable file.

Follow the on-screen instructions to choose your desired operation:

* Determine PID Parameters: 
    - Input the values of all components present to get the corresponding Kp, Ki, Kd, Ti, and Td of the circuit.

* Calculate Component Values: 
    - Input the desired Kp, Ki, and Kd values.
        - Determine R1, R2 and R4 by giving R3, C1 and C2.
        - Determine R4, C1 and C2 by givinig R1, R2 and R3.
        - Determine R1, R3 by givinig R2, R4 and C1=C2.

Ensure to provide accurate measurements and values to obtain precise results.

Here's an example of how you might use the tool:

1. Select whether you want to determine PID parameters or calculate component values.
![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/74bc2725-5957-4cb7-b45c-829ab5d603b8)
2. Follow the prompts to input the necessary values.
3. Receive the calculated output for your PID controller design.
![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/49ccaee1-448d-4f84-9a36-c635340730fc)

# Important Notes
**R3/C1/C2 series-circuit method:** When using the original method of determining PID components through *Kp, Ki, Kd, R3, C1 and C2*, if $(K_p < 2\sqrt{T_i T_d})$, the method will not work correctly. You will receive an error message:
```
Using this method, ( 2 * sqrt(Ti * Td) ) should not be greater than Kp.
```
Ensure that this condition is met to avoid errors.

**Matching R2 with C in series-circuit:** When using the *Determine circuit components for given K-pid, R2, R4, and assuming C1=C2* option, ensure that the larger the R2 resistor is, the smaller the capacitor C should be. For example:

- For a 1k resistor for R2, select a capacitor smaller than 1mF. Ratio = 1
- For a 22k resistor for R2, select a capacitor smaller than 470uF. Ratio = 1.03
- For a 330k resistor for R2, select a capacitor smaller than 3.3uF. Ratio = 0.99

Maintaining this ratio ensures that R2 * C2 gives a value close to one, which helps in achieving optimal performance in the PID controller. If this is not achievable, increasing integral-time through with larger proportional-gain and/or smaller integral-gain should also work, since it will increase the ratio cap.

## Example
Below are examples of series and parallel circuits with indications of the resistor and capacitor placements. These examples provide clear layouts, helping you understand the placement and designation of each component within the PID controller circuits. Please note that the R resistor is arbitrary and should be the same for all references.

### Series circuit
![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/95bfcb31-0f98-40b2-b86a-73815d24fff3)
### Parallel circuit
![image](https://github.com/DimitriOnLSD/PIDWizard/assets/100768973/eb7c885c-006e-49ca-afb1-7e85c5569415)

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
