#pragma once
#include "engine.h"

class BossLevelScene : public Scene {
public:
	void Load() override;
	void UnLoad() override;
	void SetTitle();
	void SetBackground();
	void Update(const double& dt) override;
	void Render() override;
};

