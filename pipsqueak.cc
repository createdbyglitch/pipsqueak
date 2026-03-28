#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>
#include <string>
#include <algorithm>

class Pipsqueak {
private:
    std::vector<double> parameters;
    double learning_rate;
    int iterations;
    
    struct DataPoint {
        std::vector<double> features;
        double target;
    };
    
    DataPoint training_data;
    
    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }
    
    double forward_pass(const std::vector<double>& features) {
        double sum = parameters[7];
        for(size_t i = 0; i < 7; ++i) {
            sum += parameters[i] * features[i];
        }
        return sigmoid(sum);
    }
    
    double compute_loss(double prediction, double target) {
        double eps = 1e-8;
        prediction = std::max(eps, std::min(1.0 - eps, prediction));
        return -(target * std::log(prediction) + (1 - target) * std::log(1 - prediction));
    }
    
    std::vector<double> compute_gradients(const std::vector<double>& features, double prediction, double target) {
        std::vector<double> gradients(8, 0.0);
        double error = prediction - target;
        
        for(size_t i = 0; i < 7; ++i) {
            gradients[i] = error * features[i];
        }
        gradients[7] = error;
        
        return gradients;
    }
    
    void update_parameters(const std::vector<double>& gradients) {
        for(size_t i = 0; i < 8; ++i) {
            parameters[i] -= learning_rate * gradients[i];
        }
    }
    
    std::vector<double> encode_input(const std::string& text) {
        std::vector<double> features(7, 0.0);
        
        std::string lowercase = text;
        std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
        
        std::vector<std::string> keywords = {"capital", "france", "paris", "french", "city", "country", "europe"};
        
        for(size_t i = 0; i < keywords.size() && i < 7; ++i) {
            if(lowercase.find(keywords[i]) != std::string::npos) {
                features[i] = 1.0;
            }
        }
        
        features[0] = (lowercase.find("capital") != std::string::npos) ? 1.0 : features[0];
        features[1] = (lowercase.find("france") != std::string::npos) ? 1.0 : features[1];
        features[2] = (lowercase.find("paris") != std::string::npos) ? 1.0 : features[2];
        
        return features;
    }
    
public:
    Pipsqueak() : learning_rate(0.1), iterations(10000) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.0, 0.5);
        
        parameters.resize(8);
        for(int i = 0; i < 8; ++i) {
            parameters[i] = dist(gen);
        }
        
        std::vector<double> features = encode_input("Capital of France");
        training_data = {features, 1.0};
    }
    
    void train() {
        for(int epoch = 0; epoch < iterations; ++epoch) {
            double prediction = forward_pass(training_data.features);
            double loss = compute_loss(prediction, training_data.target);
            
            std::vector<double> gradients = compute_gradients(training_data.features, prediction, training_data.target);
            update_parameters(gradients);
            
            if(epoch % 1000 == 0) {
                std::cout << "Epoch " << epoch << " | Loss: " << std::fixed << std::setprecision(6) << loss 
                          << " | Prediction: " << prediction << std::endl;
            }
        }
    }
    
    double predict(const std::string& input) {
        std::vector<double> features = encode_input(input);
        return forward_pass(features);
    }
    
    bool answer(const std::string& input) {
        double result = predict(input);
        return result > 0.5;
    }
    
    void print_parameters() {
        std::cout << "\nFinal Parameters:\n";
        for(size_t i = 0; i < 8; ++i) {
            std::cout << "θ" << i << " = " << std::fixed << std::setprecision(6) << parameters[i] << std::endl;
        }
    }
};

int main() {
    std::cout << "Pipsqueak Machine Learning System\n";
    std::cout << "Training on: 'Capital of France is Paris'\n";
    std::cout << "----------------------------------------\n\n";
    
    Pipsqueak ml;
    
    ml.train();
    
    ml.print_parameters();
    
    std::cout << "\nTesting:\n";
    std::cout << "----------------------------------------\n";
    
    std::vector<std::string> test_cases = {
        "Capital of France",
        "What is the capital of France?",
        "France capital city",
        "Paris is the capital of France",
        "Capital of Germany",
        "London is capital of England",
        "Random question",
        "France"
    };
    
    for(const auto& test : test_cases) {
        double confidence = ml.predict(test);
        bool is_correct = ml.answer(test);
        
        std::cout << "Q: " << std::left << std::setw(35) << test;
        std::cout << " | Confidence: " << std::fixed << std::setprecision(3) << confidence;
        std::cout << " | Answer: " << (is_correct ? "Paris ✓" : "Unknown ✗") << std::endl;
    }
    
    std::cout << "\nInteractive Mode (type 'quit' to exit):\n";
    std::cout << "----------------------------------------\n";
    
    std::string input;
    while(true) {
        std::cout << "You: ";
        std::getline(std::cin, input);
        
        if(input == "quit" || input == "exit") {
            break;
        }
        
        if(ml.answer(input)) {
            std::cout << "Pipsqueak: Paris is the capital of France!" << std::endl;
        } else {
            std::cout << "Pipsqueak: I don't know about that." << std::endl;
        }
    }
    
    return 0;
}
