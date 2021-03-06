#include "../components/stdafx.h"
#include <queue>
#include <iostream>
#include "../ai/astar_50snakes.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

using namespace sf;

Vector2i Astar50::from;
Vector2i Astar50::to;
Astar50::Node50 Astar50::graph[G_WIDTH][G_HEIGHT];

// Set each node's neighbors.
void Astar50::init() {
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			std::vector<Node50*> neighbors(0);
			if (i > 0)
				neighbors.push_back(&graph[i - 1][j]);
			if (j > 0)
				neighbors.push_back(&graph[i][j - 1]);
			if (i < G_WIDTH - 1)
				neighbors.push_back(&graph[i + 1][j]);
			if (j < G_HEIGHT - 1)
				neighbors.push_back(&graph[i][j + 1]);

			graph[i][j] = Node50(Vector2i(i, j), neighbors);
		}
	}
}

std::vector<Vector2i> Astar50::findPath(Config& config) {
	// Set all obstacles Node as already visited and all others as not visited
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			if (graph[i][j].getWeight() == WEIGHT_REF)
				graph[i][j].setVisited(true);
			else
				graph[i][j].setVisited(false);
		}
	}

	Node50* start = &graph[from.x][from.y];
	Node50* goal = NULL;

	// Priority queue using pointers to the grid's nodes
	std::priority_queue<Node50*, std::vector<Node50*>, Node50::Comparator> frontier;
	// We start by adding the departure point
	frontier.push(start);

	// While there are somme unvisited nodes
	while (!frontier.empty()) {
		// Recover first element...
		auto current = frontier.top();
		// ...and remove it from queue
		frontier.pop();

		// If we've reached destination we exit the loop
		if (current->getVal() == to) {
			goal = current;
			break;
		}

		// Recover the node's neighbors
		std::vector<Node50*> nb = current->getNeighbors();
		for (auto n : nb) {
			// If we never went to that node and he is not an obstacles
			if (!n->isVisited()) {
				if(config.isDisplayCostOn())
					n->setCost(n->getEstimatedCost(), current->getCostSoFar() + 1 + n->getWeight() / WEIGHT_REF);
				else
					n->setCost(manhattan(Vector2i(n->getVal().x, n->getVal().y), to), current->getCostSoFar() + 1 + n->getWeight() / WEIGHT_REF);
				// We set it as visited, set where we came from and add it to the queue
				n->setVisited(true);
				n->setParent(current);
				frontier.push(n);
			}
		}
	}

	std::vector<Vector2i> res;
	// We just go back in the parents node to figure out the path until we reach the last one
	while (goal != NULL && goal->getParent() != NULL) {
		res.push_back(goal->getVal());
		goal = goal->getParent();
	}

	return res;
}

void Astar50::hardReset(std::vector<Vector2i>& obstacles) {
	// Set all nodes as not visited
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			graph[i][j].setVisited(false);
		}
	}

	std::queue<Node50*> q;
	for (auto v : obstacles) {
		graph[v.x][v.y].setParent(NULL);
		graph[v.x][v.y].setWeight(WEIGHT_REF);
		graph[v.x][v.y].setVisited(true);
		q.push(&graph[v.x][v.y]);
	}

	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		std::vector<Node50*> nb = current->getNeighbors();
		for (auto n : nb) {
			if (!n->isVisited()) {
				n->setParent(NULL);
				n->setWeight(current->getWeight() - 1);
				n->setVisited(true);
				q.push(n);
			}
		}
	}
}

void Astar50::softReset(std::vector<Vector2i>& obstacles) {
	for (int i = 0; i < G_WIDTH; i++) {
		for (int j = 0; j < G_HEIGHT; j++) {
			graph[i][j].setVisited(false);
			graph[i][j].setParent(NULL);
			graph[i][j].setWeight(0);
		}
	}

	for (auto v : obstacles) {
		graph[v.x][v.y].setParent(NULL);
		graph[v.x][v.y].setWeight(WEIGHT_REF);
	}
}

void Astar50::update(Vector2i v) {
	graph[v.x][v.y].setWeight(WEIGHT_REF);
}


// If the cost is displayed, we calculate the distance of each node to the crystal.
// Slower and only to be used for visual purposes.
void Astar50::setTo(Vector2i t, Config& config) {
	to = t;
	if (config.isDisplayCostOn()) {
		for (int i = 0; i < G_WIDTH; i++) {
			for (int j = 0; j < G_HEIGHT; j++) {
				graph[i][j].setCost(manhattan(Vector2i(i, j), to), 0);
			}
		}
	}
}

void Astar50::setFrom(Vector2i f) {
	from = f;
}

float Astar50::manhattan(const sf::Vector2i& v1, const sf::Vector2i& v2) {
	return (float)(abs(v2.x - v1.x) + abs(v2.y - v1.y));
}

float Astar50::getWeight(int i, int j) {
	return graph[i][j].getWeight();
}

float Astar50::getCost(int i, int j) {
	return graph[i][j].getEstimatedCost();
}

Astar50::Node50::Node50() {
	parent = NULL;
	val = Vector2i(0, 0);
	estimated_cost = 0;
	cost_so_far = 0;
	weight = 0;
	visited = false;
}

Astar50::Node50::Node50(Vector2i& v, const std::vector<Node50*>& nb, Node50* p, float ec, float w, bool vis) {
	val = v;
	neighbors = nb;
	parent = p;
	estimated_cost = ec;
	cost_so_far = 0;
	weight = w;
	visited = vis;
}

void Astar50::Node50::setParent(Node50* p) {
	parent = p;
}

void Astar50::Node50::setCost(float ec, float csf) {
	estimated_cost = ec;
	cost_so_far = csf;
}

void Astar50::Node50::setWeight(float w) {
	weight = w;
}

void Astar50::Node50::setVisited(bool v) {
	visited = v;
}

Astar50::Node50* Astar50::Node50::getParent() const{
	return parent;
}

std::vector<Astar50::Node50*> Astar50::Node50::getNeighbors() const {
	return neighbors;
}

Vector2i Astar50::Node50::getVal() const {
	return val;
}

float Astar50::Node50::getEstimatedCost() const {
	return estimated_cost;
}

float Astar50::Node50::getCostSoFar() const {
	return cost_so_far;
}

float Astar50::Node50::getWeight() const{
	return weight;
}

bool Astar50::Node50::isVisited() const {
	return visited;
}

// Comparator
bool Astar50::Node50::Comparator::operator()(const Node50* a, const Node50* b) {
	return (a->getEstimatedCost()+a->getCostSoFar()) > (b->getEstimatedCost()+b->getCostSoFar());
}