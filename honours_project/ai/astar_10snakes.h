#ifndef __ASTAR10_H__
#define __ASTAR10_H__

#include <vector>
#include <SFML/Graphics.hpp>

#include "../define.h"
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Astar10 {
	private:
		class Node10 {
			private:
				Node10* parent;						// To know where we come from and find path back once we reached the destination
				std::vector<Node10*> neighbors;		// Pointers to the grid neighbors
				sf::Vector2i val;					// Position on the grid
				float estimated_cost;				// Distance to destination
				float cost_so_far;					// Cost for going from departure to node, change depending on the path we took
				float weight;						// Weight that is added to the cost_so_far when passing through the node
				bool visited;						// To know if we already explored the node

			public:
				Node10();
				Node10(sf::Vector2i& v, const std::vector<Node10*>& nb, Node10* p = NULL, float ec = 0, float w = 0, bool vis = false);
				void setParent(Node10* p);
				void setCost(float ec, float csf);
				void setWeight(float w);
				void setVisited(bool v);
				Node10* getParent() const;
				std::vector<Node10*> getNeighbors() const;
				sf::Vector2i getVal() const;
				float getEstimatedCost() const;
				float getCostSoFar() const;
				float getWeight() const;
				bool isVisited() const;

				class Comparator {
					public:
						bool operator()(const Node10* a, const Node10* b);
				};
		};

		static sf::Vector2i from;					// Departure
		static sf::Vector2i to;						// Destination
		static Node10 graph[G_WIDTH][G_HEIGHT];		// Map grid

	public:
		static void init();															// To create nodes and their neighbors
		static std::vector<sf::Vector2i> findPath(Config& config);					// Main function, calculate the path
		static void hardReset(std::vector<sf::Vector2i>& obstacles);				// Calculate weight with heatmap around snake (using BFS)
		static void softReset(std::vector<sf::Vector2i>& obstacles);				// Just put all weights to 0
		static void update(sf::Vector2i v);											// To set the weight of a Node where a snake moved to MAX
		static void setTo(sf::Vector2i t, Config& config);							// Change destination
		static void setFrom(sf::Vector2i f);										// Change departure
		static float manhattan(const sf::Vector2i& v1, const sf::Vector2i& v2);		// Basic manhattan distance calculation
		static float getWeight(int i, int j);
		static float getCost(int i, int j);
};

#endif

