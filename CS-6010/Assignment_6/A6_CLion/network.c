#include "network.h"

int main() {

    // Generates random seed.
    srand(time(NULL) * 100);

    Node *network = generate_network(numAgents, numNearestNeighbors, pReplaceRandom);

    print_network(network, numAgents, numNearestNeighbors);

    free_memory(network);

    return 0;

}
