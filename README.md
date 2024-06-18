# Neural-Networks-Simulation

## Description

This program simulates a simple neural network with an input layer, hidden layer, and output layer. It utilizes threading to parallelize the processing of the hidden layer neurons, providing a more efficient execution. The program also includes a visual representation of the neural network structure, a progress bar to simulate processing time, and finally outputs the results from the output layer neurons.

## Features

1. **Random Weight Initialization**: Weights are randomly initialized between -1 and 1.
2. **Threaded Processing**: The hidden layer neurons are processed in parallel using threads.
3. **ASCII Neural Network Representation**: A simple ASCII art to show the structure of the neural network.
4. **Progress Bar**: A progress bar to indicate that the neurons are being processed.
5. **Output Display**: Outputs from the output layer neurons are displayed after processing.

## Running the Code

### Prerequisites

- A C++ compiler (e.g., `g++`).
- POSIX-compliant system (Linux, macOS, or Windows with Cygwin).

### Steps

1. **Copy the Code**

   Copy the entire code provided above into a file named `neural_network.cpp`.

2. **Compile the Code**

   Open a terminal and navigate to the directory where the `neural_network.cpp` file is located. Compile the code using the following command:
   ```sh
   g++ -o neural_network neural_network.cpp -pthread
   ```

3. **Run the Program**

   After successful compilation, run the program using the following command:
   ```sh
   ./neural_network
   ```

4. **Observe the Output**

   The program will display the following:
   - An ASCII representation of the neural network structure.
   - A progress bar indicating the processing of the neurons.
   - The final output values of the output neurons.

### Example Output

Here is an example of what you might see when you run the program:

```
Neural Network Structure:
Input Layer -> Hidden Layer -> Output Layer
  (I1) ->  (I2) ->  (I3) ->  (I4)
  (H1) ->  (H2) ->  (H3) ->  (H4) ->  (H5) ->  (H6) ->  (H7) ->  (H8)
  (O1) ->  (O2) ->  (O3)

Processing the neurons, please wait...
[==================================================] 100 %

Output neuron 1: 0.5678
Output neuron 2: 0.4321
Output neuron 3: 0.6789
```

### Troubleshooting

- **Compilation Errors**: Ensure you have the necessary permissions and the correct path to your source file.
- **Missing `pthread` Library**: Ensure your compiler and environment support POSIX threads.
- **Runtime Errors**: If you encounter any runtime errors, make sure your system meets the POSIX compliance requirements and that you have sufficient resources.

If there are any issues or questions, feel free to seek help from me or further documentation.
