#include "components/stdafx.h"
#include "config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 19th March 2019
// config.cpp - XXX.

Config::Config() {
	weightBFS = true;
	displayWeight = false;
	displayCost = false;
	displayPath = false;
	pause = true;
	fpsCap = true;
	fps = 60;
}

void Config::toggleWeightBFS() {
	weightBFS = !weightBFS;
}

void Config::toggleDisplayWeight() {
	displayWeight = !displayWeight;
}

void Config::toggleDisplayCost() {
	displayCost = !displayCost;
}

void Config::toggleDisplayPath() {
	displayPath = !displayPath;
}

void Config::changeFPS(int val) {
	if(fps > 1 || val > 0)
		fps += val * 1;
}

void Config::toggleFPSCap() {
	fpsCap = !fpsCap;
}

void Config::togglePause() {
	pause = !pause;
}

bool Config::isWeightBFSOn() const {
	return weightBFS;
}

bool Config::isDisplayWeightOn() const {
	return displayWeight;
}

bool Config::isDisplayCostOn() const {
	return displayCost;
}

bool Config::isDisplayPathOn() const {
	return displayPath;
}

bool Config::isRunning() const {
	return !pause;
}

int Config::getFPS() const {
	if(fpsCap)
		return fps;
	return 0;
}
