#pragma once

#include "../EntityManager/Entity.h"

class ImpactSpheres : public Entity
{

public:

	ImpactSpheres();
	static ImpactSpheres& GetInstance();
	void AddCollisionPoint(const glm::vec3& point);

	void CalcualteTime(float deltaTime);

private:

	bool canAddPoint = true;

	float timeStep = 0;
	float addInterval = 0.5;

	Model* model;
	Renderer* renderer;
	Shader* shader;


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

