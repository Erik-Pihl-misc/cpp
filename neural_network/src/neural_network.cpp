#include <neural_network.hpp>

namespace yrgo {
namespace machine_learning {

NeuralNetwork::NeuralNetwork(const std::size_t num_inputs, 
                             const std::size_t num_hidden_nodes, 
                             const std::size_t num_outputs,
                             const ActFunc hidden_layer_act_func,
                             const ActFunc output_layer_act_func) {
    init(num_inputs, num_hidden_nodes, num_outputs, 
        hidden_layer_act_func, output_layer_act_func);
}

const std::vector<DenseLayer>& NeuralNetwork::hiddenLayers(void) const { 
    return hidden_layers_; 
}

const DenseLayer& NeuralNetwork::outputLayer(void) const { 
    return output_layer_; 
}

const std::vector<double>& NeuralNetwork::output(void) const {
    return output_layer_.output(); 
}

std::size_t NeuralNetwork::numInputs(void) const { 
    return hidden_layers_.size() ? hidden_layers_[0].numNodes() : 0; 
}

std::size_t NeuralNetwork::numOutputs(void) const { 
    return output_layer_.numNodes(); 
}

std::size_t NeuralNetwork::numHiddenLayers(void) const { 
    return hidden_layers_.size(); 
}

std::size_t NeuralNetwork::numTrainingSets(void) const { 
    return train_order_.size(); 
}

void NeuralNetwork::init(const std::size_t num_inputs, 
                         const std::size_t num_hidden_nodes, 
                         const std::size_t num_outputs,
                         const ActFunc hidden_layer_act_func,
                         const ActFunc output_layer_act_func) {
    addFirstHiddenLayer(num_hidden_nodes, num_inputs, hidden_layer_act_func);
    output_layer_.init(num_outputs, num_hidden_nodes, output_layer_act_func);
}

void NeuralNetwork::addHiddenLayer(const std::size_t num_nodes, 
                                   const ActFunc act_func) {
    DenseLayer hidden_layer{num_nodes, lastHiddenLayer().numNodes(), act_func};
    hidden_layers_.push_back(hidden_layer);
    resizeOutputLayer();
}

void NeuralNetwork::addHiddenLayers(const std::size_t num_layers, 
                                    const std::size_t num_nodes, 
                                    const ActFunc act_func) {
    for (std::size_t i{}; i < num_layers; ++i) {
        DenseLayer hidden_layer{num_nodes, lastHiddenLayer().numNodes(), act_func};
        hidden_layers_.push_back(hidden_layer);
    }
    resizeOutputLayer();
}

void NeuralNetwork::addTrainingData(const std::vector<std::vector<double>>& train_in, 
                                    const std::vector<std::vector<double>>& train_out) {
    train_in_ = train_in;
    train_out_ = train_out;
    checkTrainingData();
    initTrainOrderVector();
}

void NeuralNetwork::removeTrainingData(void) {
    train_in_.clear();
    train_out_.clear();
    train_order_.clear();
}

bool NeuralNetwork::train(const std::size_t num_epochs, const double learning_rate) {
    if (!learningRateValid(learning_rate) || numTrainingSets() == 0) { return false; }
    for (std::size_t i{}; i < num_epochs; ++i) {
        randomizeTrainingOrder();
        executeEpoch(learning_rate);
    }
    removeTrainingData();
    return true;
}

const std::vector<double>& NeuralNetwork::predict(const std::vector<double>& input) {
    feedforward(input);
    return output_layer_.output();
}

void NeuralNetwork::printPredictions(const std::vector<std::vector<double>>& inputs,
                                     const std::size_t num_decimals,
                                     std::ostream& ostream) {
    ostream << "\n--------------------------------------------------------------------------------";
    for (const auto& input : inputs) {
        ostream << "\nInput:\t";
        printLine(input, num_decimals, ostream);
        ostream << "Output:\t";
        printLine(predict(input), num_decimals, ostream);
    }
    ostream << "--------------------------------------------------------------------------------\n\n";
}

DenseLayer& NeuralNetwork::firstHiddenLayer(void) { 
    return hidden_layers_[0]; 
}

const DenseLayer& NeuralNetwork::firstHiddenLayer(void) const { 
    return hidden_layers_[0]; 
}

DenseLayer& NeuralNetwork::lastHiddenLayer(void) { 
    return hidden_layers_[hidden_layers_.size() - 1]; 
}

const DenseLayer& NeuralNetwork::lastHiddenLayer(void) const { 
    return hidden_layers_[hidden_layers_.size() - 1]; 
}

void NeuralNetwork::addFirstHiddenLayer(const std::size_t num_nodes, 
                                        const std::size_t num_weights_per_node,
                                        const ActFunc act_func) {
    DenseLayer hidden_layer{num_nodes, num_weights_per_node};
    hidden_layers_.push_back(hidden_layer);
}

 void NeuralNetwork::resizeOutputLayer(void) { 
    output_layer_.resize(output_layer_.numNodes(), lastHiddenLayer().numNodes()); 
}

void NeuralNetwork::executeEpoch(const double learning_rate) {
    for (const auto& i : train_order_) {
        feedforward(train_in_[i]);
        backpropagate(train_out_[i]);
        optimize(train_in_[i], learning_rate);
    }
}

void NeuralNetwork::feedforward(const std::vector<double>& input) {
    firstHiddenLayer().feedforward(input);
    for (auto it{hidden_layers_.begin() + 1}; it != hidden_layers_.end(); ++it) {
        it->feedforward((it - 1)->output());
    }
    output_layer_.feedforward(lastHiddenLayer().output());
}

void NeuralNetwork::backpropagate(const std::vector<double>& reference) {
    output_layer_.backpropagate(reference);
    lastHiddenLayer().backpropagate(output_layer_);
    for (auto it{hidden_layers_.end() - 1}; it != hidden_layers_.begin(); --it) {
        (it - 1)->backpropagate(*it);
    }
}

void NeuralNetwork::optimize(const std::vector<double>& input, const double learning_rate) {
    firstHiddenLayer().optimize(input, learning_rate);
    for (auto it{hidden_layers_.begin() + 1}; it != hidden_layers_.end(); ++it) {
        it->optimize((it - 1)->output(), learning_rate);
    }
    output_layer_.optimize(lastHiddenLayer().output());
}

void NeuralNetwork::checkTrainingData(void) {
    if (train_in_.size() != train_out_.size()) {
        const auto num_sets{train_in_.size() < train_out_.size() ? train_in_.size() : train_out_.size() };
        train_in_.resize(num_sets);
        train_out_.resize(num_sets);
    }
}

void NeuralNetwork::initTrainOrderVector(void) {
    train_order_.resize(train_in_.size());
    for (std::size_t i{}; i < train_order_.size(); ++i) {
        train_order_[i] = i;
    }
}

void NeuralNetwork::randomizeTrainingOrder(void) { 
    utils::random::shuffleVector<std::size_t>(train_order_); 
}

constexpr bool NeuralNetwork::learningRateValid(const double learning_rate) { 
    return learning_rate > 0; 
}

void NeuralNetwork::printLine(const std::vector<double>& data,
                              const std::size_t num_decimals,
                              std::ostream& ostream) {
    ostream << std::fixed << std::setprecision(num_decimals);
    for (const auto& i : data) {
        ostream << i << " ";
    }
    ostream << "\n";
}

} /* namespace machine_learning */
} /* namespace yrgo */