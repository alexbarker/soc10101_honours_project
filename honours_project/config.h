#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "SFML/Graphics.hpp"
#include "define.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// define.h - XXX.

// To change some options without having to restart
// and change the #define all the time
class Config {
	private:
		bool weightBFS;			// Toggle between hardReset() and softReset()
		bool displayWeight;		// Display heatmap around snake
		bool displayCost;		// Display heatmap around crystal
		bool displayPath;		// Display snake's path to crystal
		bool pause;             // Pause game.
		bool fpsCap;			// Toggle fps cap
		int fps;				// Fps cap value

	public:
		Config();
		void toggleWeightBFS();
		void toggleDisplayWeight();
		void toggleDisplayCost();
		void toggleDisplayPath();
		void changeFPS(int val);
		void toggleFPSCap();
		void togglePause();
		bool isWeightBFSOn() const;
		bool isDisplayWeightOn() const;
		bool isDisplayCostOn() const;
		bool isDisplayPathOn() const;
		bool isRunning() const;
		int getFPS() const;
};

#endif
