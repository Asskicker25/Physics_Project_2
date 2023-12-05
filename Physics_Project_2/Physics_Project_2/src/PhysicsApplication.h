#pragma once

#include <Graphics/ApplicationWindow.h>
#include <Physics/PhysicsEngine.h>
#include "EntityManager/EntityManager.h"
#include "InputManager/InputManager.h"

class PhysicsApplication : public ApplicationWindow
{
	PhysicsEngine physicsEngine;


	Model* sphere;
	Model* building;

	PhysicsObject* spherePhy;
	PhysicsObject* buildingPhy;

	glm::vec4 aabbColor[3] = {
		glm::vec4(1.0, 0.0, 0.0f, 1.0f),
		glm::vec4(0.0, 1.0, 0.0f, 1.0f),
		glm::vec4(0.0, 0.0, 1.0f, 1.0f)
	};

	void DrawAABBRecursive(HierarchicalAABBNode* node);

	// Inherited via ApplicationWindow
	void SetUp() override;
	void PreRender() override;
	void PostRender() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;
};

