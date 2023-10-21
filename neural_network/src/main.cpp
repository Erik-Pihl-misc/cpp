/********************************************************************************
 * @brief Demonstration of neural network trained to predict the number of high
 *        inputs as shown below:
 * 
 *        inputs[2:0]    outputs[1:0]
 *            000             00
 *            001             01
 *            010             01
 *            011             10
 *            100             01
 *            101             10
 *            110             10
 *            111             11
 ********************************************************************************/
#include <neural_network.hpp>

using namespace yrgo::machine_learning;

/********************************************************************************
 * @brief Creates neural network trained to predict the number of high input
 *        values as displayed above. The network consists of three inputs, a 
 *        hidden layer with 20 nodes and an output layer with two nodes. The
 *        network is trained during 10 000 epochs with a 5 % learning rate.
 * 
 *        The model is tested with the training data input sets, with the 
 *        predicted output for each input set printed in the terminal.
 ********************************************************************************/
int main(void) {
    const std::vector<std::vector<double>> train_in{{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                                                    {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
    const std::vector<std::vector<double>> train_out{{0, 0}, {0, 1}, {0, 1}, {1, 0},
                                                     {0, 1}, {1, 0}, {1, 0}, {1, 1}};
    NeuralNetwork network{3, 20, 2, ActFunc::TANH};
    network.addTrainingData(train_in, train_out);
    network.train(10000, 0.05); 
    network.printPredictions(train_in);
    return 0;
}