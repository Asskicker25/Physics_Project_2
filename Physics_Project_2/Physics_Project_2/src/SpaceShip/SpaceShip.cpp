#include "SpaceShip.h"
#include "../ImpactSpheres/ImpactSpheres.h"

SpaceShip::SpaceShip(Shader* shader)
{
	alphaShader = shader;
	model = new Model();
	phyObj = new PhysicsObject();
	InitializeEntity(this);

	InputManager::GetInstance().AddListener(this);
}

void SpaceShip::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void SpaceShip::DrawCollisionAabbs(PhysicsObject* phyObj)
{
	if (!drawCollisionAabbs) return;
	renderer->DrawAABB(GetGraphicsAabb(phyObj->GetModelAABB()), glm::vec4(1.0, .0, 0.0f, 1.0f), false);

	std::vector<Aabb> collisionAabb = phyObj->GetCollisionAabbs();

	for (Aabb aabb : collisionAabb)
	{
		renderer->DrawAABB(GetGraphicsAabb(aabb), glm::vec4(0.0, 1.0, 0.0f, 1.0f),false);
	}
}


void SpaceShip::Start()
{
	camera->SetCameraRotation(glm::vec3(-20.0f, 90.0f, 0));
}

void SpaceShip::Update(float deltaTime)
{
	glm::vec3 forward = model->transform.GetForward();
	camera->SetCameraPosition(model->transform.position + forward * followOffset + glm::vec3(0, yOffset, 0));

	DrawCollisionAabbs(phyObj);
	//camera->SetCameraRotation(forward);
}

void SpaceShip::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	this->renderer = renderer;

	model->LoadModel("Assets/Models/SpaceShip.fbx");
	model->transform.SetScale(glm::vec3(0.01f));
	model->transform.SetPosition(glm::vec3(-10.0f, 150.0f, 5.0f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	model->meshes[1]->material->AsMaterial()->SetBaseColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
	renderer->AddModel(model, alphaShader);

	phyObj->Initialize(model, SPHERE, DYNAMIC, TRIGGER, true);
	phyObj->AssignCollisionCallback([this](PhysicsObject* other)
		{
			glm::vec3 normal = phyObj->GetCollisionNormals()[0];
			float dotProduct = glm::dot(phyObj->velocity, normal);
			phyObj->velocity -= dotProduct * normal;
			ImpactSpheres::GetInstance().AddCollisionPoint(phyObj->GetCollisionPoints()[0]);
		});
	physicsEngine->AddPhysicsObject(phyObj);
}

void SpaceShip::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void SpaceShip::OnKeyPressed(const int& key)
{
	glm::vec3 forward = model->transform.GetForward();
	glm::vec3 right = model->transform.GetRight();
	glm::vec3 up = model->transform.GetUp();

	if (key == GLFW_KEY_W)
	{

		phyObj->velocity -= forward * speed;
	}
	else if (key == GLFW_KEY_S)
	{
		phyObj->velocity += forward * speed;
	}
	else if (key == GLFW_KEY_A)
	{
		phyObj->velocity += right * speed;
	}
	else if (key == GLFW_KEY_D)
	{
		phyObj->velocity -= right * speed;
	}
	else if (key == GLFW_KEY_Q)
	{
		phyObj->velocity += up * speed;
	}
	else if (key == GLFW_KEY_E)
	{
		phyObj->velocity -= up * speed;
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		model->transform.SetRotation(glm::vec3
		(model->transform.rotation.x,
			model->transform.rotation.y - rotateSpeed,
			model->transform.rotation.z
		));

	}
	else if (key == GLFW_KEY_LEFT)
	{
		model->transform.SetRotation(glm::vec3
		(model->transform.rotation.x,
			model->transform.rotation.y + rotateSpeed,
			model->transform.rotation.z
		));
	}
	else if (key == GLFW_KEY_UP)
	{
		model->transform.SetRotation(glm::vec3
		(model->transform.rotation.x - rotateSpeed,
			model->transform.rotation.y,
			model->transform.rotation.z
		));
	}
	else if (key == GLFW_KEY_DOWN)
	{
		model->transform.SetRotation(glm::vec3
		(model->transform.rotation.x + rotateSpeed,
			model->transform.rotation.y,
			model->transform.rotation.z
		));
	}
	


	camera->SetCameraPosition(model->transform.position + forward * followOffset + glm::vec3(0, yOffset, 0));

	if (key == GLFW_KEY_SPACE)
	{
		drawCollisionAabbs = !drawCollisionAabbs;
	}
}

void SpaceShip::OnKeyReleased(const int& key)
{
}

void SpaceShip::OnKeyHeld(const int& key)
{
}
