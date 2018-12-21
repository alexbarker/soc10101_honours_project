#pragma once
#include "engine.h"

class PrototypeScene : public Scene {
public:
	void Load() override;
	//void SetTitle1();
	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};
#pragma once
