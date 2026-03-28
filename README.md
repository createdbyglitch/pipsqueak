# Pipsqueak ML System

Pipsqueak is a minimalist, educational machine learning system that demonstrates the core concepts of neural networks. It is trained to recognize statements about the capital of France, showcasing how a simple model can learn from a single data point using gradient descent.

It is a fun, lightweight project to illustrate the fundamentals of AI: feature engineering, logistic regression, and the training loop.

## ✨ Features

- **Simple Neural Network**: A single-neuron model (logistic regression) with 8 parameters (7 feature weights and a bias).
- **Keyword-Based Features**: Converts text input into a 7-dimensional feature vector by detecting keywords like "capital", "france", and "paris".
- **Training from One Example**: Trained on the statement "Capital of France" to predict that the answer is "Paris".
- **Interactive Modes**:
    - **Command-Line Interface (CLI)**: A C++ program you can compile and run in your terminal.
    - **Web Port**: A fully functional browser-based version with a visual interface, training progress bar, and interactive chat.
- **Educational**: The code is intentionally simple and well-commented, making it a perfect starting point for understanding how AI models learn.

## 🚀 Getting Started

You can run Pipsqueak in two ways: via the command-line or in your web browser.

### Option 1: Command-Line (C++)

The quickest way to run the C++ version is to use the provided installation script. This script will download and compile the source code for you.

**Prerequisites**: You need `curl` and a C++ compiler (like `g++` or `clang`).

Run the following command in your terminal:

```bash
curl -fsSL https://createdbyglitch.github.io/pipsqueak/pipsqueak.cc | sh
```

This command will:

1. Download the pipsqueak.cc source file.
2. Compile it using g++ (or clang++).
3. Run the compiled program.

To compile and run it manually:

```bash
# Download the source
curl -O https://createdbyglitch.github.io/pipsqueak/pipsqueak.cc

# Compile it
g++ -std=c++11 -o pipsqueak pipsqueak.cc

# Run it
./pipsqueak
```

Option 2: Web Port

For a more visual and interactive experience, you can use the web port. No installation is required.

Simply visit: https://createdbyglitch.github.io/pipsqueak

The web version offers:

- A live training progress bar.
- Immediate test results on a set of predefined questions.
- An interactive chat interface to ask your own questions.

## 🧠 How It Works

The "neural network" in Pipsqueak is a simple logistic regression model. Here's the process:

1. Feature Extraction: When you input a sentence, the system scans it for a set of keywords (capital, france, paris, french, city, country, europe). It creates a feature vector of 7 numbers (1 if the keyword is present, 0 if not).
2. The Model: It has a set of 8 parameters (weights), θ0 to θ7. The prediction is calculated as:
   prediction = sigmoid(θ0*feature0 + θ1*feature1 + ... + θ6*feature6 + θ7)
   The sigmoid function squashes the result into a probability between 0 and 1.
3. Training: The model is trained on a single, labeled example: the features for "Capital of France" with a target value of 1.0 (meaning "this is about the capital of France").
   - It makes a prediction.
   - It calculates the error (loss) using binary cross-entropy.
   - It computes gradients to see how to adjust the parameters to reduce the error.
   - It updates the parameters slightly in the opposite direction of the gradient. This is repeated 10,000 times.
4. Prediction: After training, for any new input, it calculates the probability. If the probability is > 0.5, it answers with "Paris".

## 📊 Test Cases

The model is evaluated on a set of phrases to see how well it has learned the concept. The web port and CLI will show the confidence score and answer for each.

# Input Expected Answer
"Capital of France"
Paris ✓

"What is the capital of France?" Paris ✓

"France capital city" 
Paris ✓

"Paris is the capital of France" Paris ✓

🛠️ Technical Details

- Language (CLI): C++17
- Language (Web): JavaScript (ES6)
- Model: Logistic Regression (Single Neuron)
- Optimizer: Stochastic Gradient Descent (SGD)
- Loss Function: Binary Cross-Entropy
- Training Iterations: 10,000
- Learning Rate: 0.1

## 📜 License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). This means you are free to use, modify, and distribute this software, but any derivative work must also be open-sourced under the same license.

See the LICENSE file for the full text of the license.

## 🙏 Contributing

Contributions are welcome! As this is an educational project, any improvements to clarity, documentation, or adding small features while maintaining simplicity are appreciated.

Feel free to open an issue or submit a pull request.


## 🌟 Acknowledgments

- Inspired by the desire to make machine learning concepts accessible to beginners.
- Thanks to the open-source community for the tools and knowledge that make projects like this possible.