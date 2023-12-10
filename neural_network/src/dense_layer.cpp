#include <dense_layer.hpp>

namespace yrgo {
namespace machine_learning {

namespace {
double getActFuncOutput(const double sum, const enum ActFunc act_func) {
    return act_func == ActFunc::RELU ? 
        utils::math::relu(sum) : utils::math::tanh(sum);
}

double getActFuncDelta(const double output, const enum ActFunc act_func) {
    return act_func == ActFunc::RELU ? 
        utils::math::reluDelta(output) : utils::math::tanhDelta(output);
}

} /* namespace */

DenseLayer::DenseLayer(const std::size_t num_nodes, 
                       const std::size_t num_weights_per_node,
                       const enum ActFunc act_func) {
    init(num_nodes, num_weights_per_node, act_func);
}

const std::vector<double>& DenseLayer::output(void) const { 
    return this->output_; 
}

std::size_t DenseLayer::numNodes(void) const { 
    return output_.size(); 
}

std::size_t DenseLayer::numWeightsPerNode(void) const { 
    return weights_.size() > 0 ? weights_[0].size() : 0;
}

void DenseLayer::init(const std::size_t num_nodes, 
                      const std::size_t num_weights_per_node,
                      const enum ActFunc act_func) {
    utils::random::init();
    act_func_ = act_func;
    resize(num_nodes, num_weights_per_node);
}

void DenseLayer::feedforward(const std::vector<double>& input) {
    for (std::size_t i{}; i < numNodes(); ++i) {
        double sum{bias_[i]};
        for (std::size_t j{}; j < numWeightsPerNode() && j < input.size(); ++j) {
            sum += input[j] * weights_[i][j];
        }
        output_[i] = getActFuncOutput(sum, act_func_);
    }
}

void DenseLayer::backpropagate(const std::vector<double>& reference) {
    for (std::size_t i{}; i < numNodes() && i < reference.size(); ++i) {
        const double error = reference[i] - output_[i];
        error_[i] = error * getActFuncDelta(output_[i], act_func_);
    }
}

void DenseLayer::backpropagate(const DenseLayer& next_layer) {
    for (std::size_t i{}; i < numNodes(); ++i) {
        double error{};
        for (std::size_t j{}; j < next_layer.numNodes(); ++j) {
            error += next_layer.error_[j] * weights_[j][i];
        }
        error_[i] = error * getActFuncDelta(output_[i], act_func_);
    }
}

void DenseLayer::optimize(const std::vector<double>& input, const double learning_rate) {
    for (std::size_t i{}; i < numNodes(); ++i) {
        bias_[i] += error_[i] * learning_rate;
        for (std::size_t j{}; j < numWeightsPerNode() && j < input.size(); ++j) {
            weights_[i][j] += error_[i] * learning_rate * input[j];
        }
    }
}

void DenseLayer::resize(const std::size_t num_nodes, const std::size_t num_weights_per_node) {
    output_.resize(num_nodes, 0); 
    utils::random::initVector<double>(bias_, num_nodes, 0, 1);
    error_.resize(num_nodes, 0);
    utils::random::initVector<double>(weights_, num_nodes, num_weights_per_node, 0, 1);
}

} /* namespace machine_learning */
} /* namespace yrgo */