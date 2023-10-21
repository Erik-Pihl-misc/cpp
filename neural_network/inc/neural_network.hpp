/********************************************************************************
 * @brief Contains class for implementation of conventional neural networks.
 ********************************************************************************/
#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <dense_layer.hpp>
#include <utils.hpp>

namespace yrgo {
namespace machine_learning {

/********************************************************************************
 * @brief Class for implementation of conventional neural networks.
 ********************************************************************************/
class NeuralNetwork {
  public:

    /********************************************************************************
     * @brief Creates empty neural network.
     ********************************************************************************/
    NeuralNetwork(void) = default;

    /********************************************************************************
     * @brief Creates new neural network with specified parameters. The network
     *        contains one hidden layer as default, but more layers can be added
     *        by calling the addHiddenLayer or addHiddenLayers member functions.
     * 
     * @param num_inputs            The number if inputs in the neural network.
     * @param num_hidden_nodes      The number of nodes in the hidden layer.
     * @param num_outputs           The number of outputs in the neural network.
     * @param hidden_layer_act_func The activation function of the hidden layer
     *                              (default = ReLU).
     * @param output_layer_act_func The activation function of the output layer
     *                              (default = ReLU).
     ********************************************************************************/
    NeuralNetwork(const std::size_t num_inputs, 
                  const std::size_t num_hidden_nodes, 
                  const std::size_t num_outputs,
                  const ActFunc hidden_layer_act_func = ActFunc::RELU,
                  const ActFunc output_layer_act_func = ActFunc::RELU);

    /********************************************************************************
     * @brief Provides the hidden layers of the neural network.
     * 
     * @return Reference to vector holding the hidden layers of the neural network.
     ********************************************************************************/
    const std::vector<DenseLayer>& hiddenLayers(void) const;

    /********************************************************************************
     * @brief Provides the output layer of the neural network.
     * 
     * @return Reference to the output layer of the neural network.
     ********************************************************************************/
    const DenseLayer& outputLayer(void) const;

     /********************************************************************************
     * @brief Provides the output of the neural network.
     * 
     * @return Reference to the vector holding the output of the neural network.
     ********************************************************************************/
    const std::vector<double>& output(void) const;

     /********************************************************************************
     * @brief Provides the number of inputs in the neural network.
     * 
     * @return The number of inputs as an unsigned integer.
     ********************************************************************************/
    std::size_t numInputs(void) const;

     /********************************************************************************
     * @brief Provides the number of outputs in the neural network.
     * 
     * @return The number of outputs as an unsigned integer.
     ********************************************************************************/
    std::size_t numOutputs(void) const;

     /********************************************************************************
     * @brief Provides the number of hidden layers in the neural network.
     * 
     * @return The number of hidden layers as an unsigned integer.
     ********************************************************************************/
    std::size_t numHiddenLayers(void) const;

    /********************************************************************************
     * @brief Provides the number of stored training sets for training of the 
     *        neural network.
     * 
     * @return The number of stored training sets as an unsigned integer.
     ********************************************************************************/
    std::size_t numTrainingSets(void) const;

  public:

    /********************************************************************************
     * @brief Initializes neural network with specified parameters. The network
     *        contains one hidden layer as default, but more layers can be added
     *        by calling the addHiddenLayer or addHiddenLayers member functions.
     * 
     * @param num_inputs            The number if inputs in the neural network.
     * @param num_hidden_nodes      The number of nodes in the hidden layer.
     * @param num_outputs           The number of outputs in the neural network.
     * @param hidden_layer_act_func The activation function of the hidden layer
     *                              (default = ReLU).
     * @param output_layer_act_func The activation function of the output layer
     *                              (default = ReLU).
     ********************************************************************************/
    void init(const std::size_t num_inputs, 
              const std::size_t num_hidden_nodes, 
              const std::size_t num_outputs,
              const ActFunc hidden_layer_act_func = ActFunc::RELU,
              const ActFunc output_layer_act_func = ActFunc::RELU);

    /********************************************************************************
     * @brief Adds a new hidden layer with specified parameters.
     * 
     * @param num_nodes The number of nodes in the new hidden layer.
     * @param act_func  The activation function of the new hidden layer 
     *                  (default = ReLU).
     ********************************************************************************/
    void addHiddenLayer(const std::size_t num_nodes, const ActFunc act_func = ActFunc::RELU);

    /********************************************************************************
     * @brief Adds new hidden layers with specified parameters.
     * 
     * @param num_layers The number of hidden layers to add.
     * @param num_nodes  The number of nodes in the new hidden layers.
     * @param act_func   The activation function of the new hidden layers 
     *                   (default = ReLU).
     ********************************************************************************/
    void addHiddenLayers(const std::size_t num_layers, 
                         const std::size_t num_nodes,
                         const ActFunc act_func = ActFunc::RELU);

    /********************************************************************************
     * @brief Adds new training data for the neural network by copying the specified
     *        data. The copied data is removed after training is complete.
     * 
     * @param train_in  Reference to vector holding input data for training.
     * @param train_out Reference to vector holding reference data for training.
     ********************************************************************************/
    void addTrainingData(const std::vector<std::vector<double>>& train_in, 
                         const std::vector<std::vector<double>>& train_out);

    /********************************************************************************
     * @brief Removes stored training data.
     ********************************************************************************/
    void removeTrainingData(void);

     /********************************************************************************
     * @brief Trains the neural network with stored training data.
     * 
     * @param num_epochs    The number of epochs to train the neural network.
     * @param learning_rate Learning rate, determines the adjustment rate when the
     *                      neural network predicts incorrectly (default = 1 %).
     * 
     * @return True if training was performed, else false due to missing training
     *         sets or invalid learning rate.
     ********************************************************************************/
    bool train(const std::size_t num_epochs, const double learning_rate = 0.01);

    /********************************************************************************
     * @brief Performs prediction with specified input values.
     * 
     * @param input Reference to vector holding input values.
     ********************************************************************************/
    const std::vector<double>& predict(const std::vector<double>& input);

    /********************************************************************************
     * @brief Performs prediction with specified sets of input values and prints 
     *        the predicted output along with the corresponding input.
     * 
     * @param input        Reference to vector holding sets of input values.
     * @param num_decimals The number of decimals of the printed values.
     * @param ostream      Reference to output stream for printing the values
     *                     (default = terminal print).
     ********************************************************************************/
    void printPredictions(const std::vector<std::vector<double>>& inputs,
                          const std::size_t num_decimals = 1,
                          std::ostream& ostream = std::cout);

  private:
    std::vector<DenseLayer> hidden_layers_{};
    DenseLayer output_layer_{};
    std::vector<std::vector<double>> train_in_{};
    std::vector<std::vector<double>> train_out_{};
    std::vector<std::size_t> train_order_{};

    DenseLayer& firstHiddenLayer(void);
    const DenseLayer& firstHiddenLayer(void) const;
    DenseLayer& lastHiddenLayer(void);
    const DenseLayer& lastHiddenLayer(void) const;
    
  private:
    void addFirstHiddenLayer(const std::size_t num_nodes, 
                             const std::size_t num_weights_per_node,
                             const ActFunc act_func);
    void resizeOutputLayer(void);
    void executeEpoch(const double learning_rate);
    void feedforward(const std::vector<double>& input);
    void backpropagate(const std::vector<double>& reference);
    void optimize(const std::vector<double>& input, const double learning_rate);
    void checkTrainingData(void);
    void initTrainOrderVector(void);
    void randomizeTrainingOrder(void);
    static constexpr bool learningRateValid(const double learning_rate);
    static void printLine(const std::vector<double>& data,
                          const std::size_t num_decimals,
                          std::ostream& ostream);
};

} /* namespace machine_learning */
} /* namespace yrgo */