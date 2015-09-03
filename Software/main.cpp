#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include "Neuron.h"
#include "NeuralNet.h"
#include "Backpropagation.h"
#include "QLearn.h"
#include "WireFitQLearn.h"


int main() {
    srand(time(NULL));
    
    net::NeuralNet * network = new net::NeuralNet(1, 6, 3, 6, "sigmoid");
	network->setOutputActivationFunction("simpleLinear");
	net::Backpropagation backprop = net::Backpropagation(0.4, 0.2, 0.0001, 10000);
	backprop.setDerivedOutputActivationFunction("simpleLinear");
	net::WireFitQLearn learn = net::WireFitQLearn(network, backprop, 1, 0, 1, 3);

	std::vector<double> state(1);
	state[0] = 0;
	double reward;
    double explorationConstant = 5;

	for(int a = 0; a < 1000; a++) {
		double action = learn.chooseBoltzmanAction(state, explorationConstant)[0];
		std::cout << "Iter: " << a << "\n";
		if(state[0] == 0) learn.applyReinforcementToLastAction(action - 0.5, state, 1);
		else learn.applyReinforcementToLastAction(0.5 - action, state, 1);

		state[0] = ((int)state[0] + 1) % 2;
	}

	std::cout << "input plz\n";
	std::cin >> state[0];
	while(true) {
		std::cout << "Action taken: " << learn.chooseBestAction(state)[0] << "\n";
		std::cout << "reward plz\n";
		std::cin >> reward;
		std::cout << "new state plz\n";
		std::cin >> state[0];
		learn.applyReinforcementToLastAction(reward, state, 1);
	}

} 