#pragma once
#include "engine.h"

class LoadScene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};

