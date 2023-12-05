#pragma once

#include "../EntityManager/Entity.h"
#include "../InputManager/InputManager.h"

class SpaceShip : public Entity , public iInputListener
{

public:
	Model* model;
	PhysicsObject* phyObj;
	Shader* alphaShader;
	Camera* camera;

	float followOffset = 5.0f;
	float yOffset = 3;

	float speed = 10;
	float rotateSpeed = 5;

	SpaceShip(Shader* shader);
	void SetCamera(Camera* camera);

private:
	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

