#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <mutex>
#include <cmath>
#include <iomanip>
#include <chrono>

#define NUM_THREADS 2

// The rest of the code remains the same

// Structure to represent a neuron
struct Neuron {
    std::vector<double> weights;
    double input = 0.0;
    double output = 0.0;
};

// Neural network layers
std::vector<Neuron> inputLayer;
std::vector<std::vector<Neuron>> hiddenLayers;
std::vector<Neuron> outputLayer;

std::mutex progressMutex;

// Function to initialize random weights
void initializeWeights(std::vector<Neuron>& layer, int numWeights) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    for (auto& neuron : layer) {
        neuron.weights.resize(numWeights);
        for (auto& weight : neuron.weights) {
            weight = dis(gen);
        }
    }
}

// Sigmoid activation function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Function to calculate the output of a neuron
void calculateNeuronOutput(Neuron& neuron, const std::vector<Neuron>& previousLayer) {
    neuron.input = 0.0;
    for (size_t i = 0; i < previousLayer.size(); i++) {
        neuron.input += previousLayer[i].output * neuron.weights[i];
    }
    neuron.output = sigmoid(neuron.input);
}

// Threaded function to process neurons
void processLayer(std::vector<Neuron>& layer, const std::vector<Neuron>& previousLayer, int start, int end) {
    for (int i = start; i < end; i++) {
        calculateNeuronOutput(layer[i], previousLayer);
    }
}

// Function to display a progress bar
void displayProgressBar(int progress, int total) {
    std::lock_guard<std::mutex> lock(progressMutex);
    int barWidth = 50;
    double ratio = static_cast<double>(progress) / total;
    int pos = static_cast<int>(barWidth * ratio);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::setw(3) << static_cast<int>(ratio * 100) << "%\r";
    std::cout.flush();
}

// Function to simulate processing delay
void simulateProcessing(int steps) {
    for (int i = 1; i <= steps; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        displayProgressBar(i, steps);
    }
    std::cout << std::endl;
}

// Function to display the neural network structure
void displayNetworkStructure(int numHiddenLayers) {
    std::cout << "Neural Network Structure:\n";
    std::cout << "Input Layer ->";
    for (int i = 0; i < numHiddenLayers; i++) {
        std::cout << " Hidden Layer " << i + 1 << " ->";
    }
    std::cout << " Output Layer\n";
    std::cout << "\n";
}

int main() {
    int numInputs, numHiddenLayers, neuronsPerHiddenLayer, numOutputs;

    // User inputs for network configuration
    std::cout << "Enter the number of input neurons: ";
    std::cin >> numInputs;
    std::cout << "Enter the number of hidden layers: ";
    std::cin >> numHiddenLayers;
    std::cout << "Enter the number of neurons per hidden layer: ";
    std::cin >> neuronsPerHiddenLayer;
    std::cout << "Enter the number of output neurons: ";
    std::cin >> numOutputs;

    // Resize layers based on user input
    inputLayer.resize(numInputs);
    hiddenLayers.resize(numHiddenLayers, std::vector<Neuron>(neuronsPerHiddenLayer));
    outputLayer.resize(numOutputs);

    // Initialize weights
    initializeWeights(hiddenLayers[0], numInputs);
    for (int i = 1; i < numHiddenLayers; i++) {
        initializeWeights(hiddenLayers[i], neuronsPerHiddenLayer);
    }
    initializeWeights(outputLayer, neuronsPerHiddenLayer);

    // Set example inputs for input layer
    for (int i = 0; i < numInputs; i++) {
        inputLayer[i].output = static_cast<double>(i + 1) / 10.0; // Example inputs
    }

    // Display network structure
    displayNetworkStructure(numHiddenLayers);

    // Process hidden layers
    std::cout << "Processing hidden layers, please wait...\n";
    simulateProcessing(10);

    for (int layerIndex = 0; layerIndex < numHiddenLayers; layerIndex++) {
        std::vector<std::thread> threads;
        int neuronsPerThread = neuronsPerHiddenLayer / NUM_THREADS;
        const std::vector<Neuron>& previousLayer = (layerIndex == 0) ? inputLayer : hiddenLayers[layerIndex - 1];

        for (int i = 0; i < NUM_THREADS; i++) {
            int start = i * neuronsPerThread;
            int end = (i == NUM_THREADS - 1) ? neuronsPerHiddenLayer : start + neuronsPerThread;
            threads.emplace_back(processLayer, std::ref(hiddenLayers[layerIndex]), std::ref(previousLayer), start, end);
        }
        for (auto& thread : threads) thread.join();
    }

    // Process output layer
    std::cout << "Processing output layer, please wait...\n";
    simulateProcessing(10);
    processLayer(outputLayer, hiddenLayers.back(), 0, numOutputs);

    // Display output layer results
    std::cout << "\nOutput Neuron Results:\n";
    for (size_t i = 0; i < outputLayer.size(); i++) {
        std::cout << "Output neuron " << i + 1 << ": " << outputLayer[i].output << std::endl;
    }

    return 0;
}