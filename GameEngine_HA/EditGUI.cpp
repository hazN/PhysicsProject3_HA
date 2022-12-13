#include "GUI.h"

#include <iostream>

#include "imgui/imgui.h"
#include "globalThings.h"
bool createNew = false;
int curPhysObj = 0;
int sensitivity = 3;
float sens[5] = { 0.00005f,0.0001f,0.0005f,0.001f, 0.01f};
bool settings = false;
void GUI::render()
{
	//setup ui structure
	ImGui::Begin("Main Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Press ESC to open/close the menu at any time.");
	ImGui::Text(("Targets hit: " + std::to_string(numHitTargets)).c_str());
	if (ImGui::Button("Play"))
	{
		menuMode = !menuMode;
		if (menuMode)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		pVAOManager->Load();
		numHitTargets = 0;
	}
	ImGui::RadioButton("Click Mode", &gameMode, eGameMode::Click); ImGui::SameLine();
	ImGui::RadioButton("Hover Mode", &gameMode, eGameMode::Hover); ImGui::SameLine();
	ImGui::Text("Sensitivity"); ImGui::SameLine();
	ImGui::SliderInt("##sensitivity", &sensitivity, 1, 5, "%0");
	rotateSpeed = sens[sensitivity];
	if (ImGui::Button("Settings"))
		settings = !settings;
	if (settings)
	{
		int current_item = 0;
		int modelSize = g_pMeshObjects.size();

		ImGui::RadioButton("Camera", &theEditMode, eEditMode::MOVING_CAMERA); ImGui::SameLine();
		ImGui::RadioButton("Lights", &theEditMode, eEditMode::MOVING_LIGHT); ImGui::SameLine();
		ImGui::RadioButton("Models", &theEditMode, eEditMode::MOVING_SELECTED_OBJECT);
		ImGui::RadioButton("Physics", &theEditMode, eEditMode::MOVING_PHYSICS_OBJECT);
		if (ImGui::Button("Save"))
			pVAOManager->Save();
		ImGui::SameLine();
		if (ImGui::Button("Load"))
			pVAOManager->Load();
		if (theEditMode == eEditMode::MOVING_LIGHT)
		{
			if (ImGui::BeginCombo("##combo", std::to_string(currentLight).c_str())) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < g_pTheLightManager->vecTheLights.size() - 1; n++)
				{
					bool is_selected = (current_item == n); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(std::to_string(n).c_str(), is_selected))
						currentLight = n;
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
		}
		if (theEditMode == eEditMode::MOVING_PHYSICS_OBJECT)
		{
			if (ImGui::BeginCombo("##combo", g_physics_system.m_PhysicsObjects[curPhysObj]->GetName().c_str())) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < g_physics_system.m_PhysicsObjects.size(); n++)
				{
					bool is_selected = (current_item == n); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(g_physics_system.m_PhysicsObjects[n]->GetName().c_str(), is_selected))
						curPhysObj = n;
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
			ImGui::PushItemWidth(200);
			ImGui::Text("Position: "); ImGui::SameLine();
			ImGui::SliderFloat("posX", &g_physics_system.m_PhysicsObjects[curPhysObj]->position.x, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::SliderFloat("posY", &g_physics_system.m_PhysicsObjects[curPhysObj]->position.y, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::SliderFloat("posZ", &g_physics_system.m_PhysicsObjects[curPhysObj]->position.z, -500.0f, 500.0f, "%.00f");
		}
		if (theEditMode == eEditMode::MOVING_SELECTED_OBJECT)
		{
			if (ImGui::BeginCombo("##combo", g_pMeshObjects[currentModel]->friendlyName.c_str())) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < modelSize; n++)
				{
					bool is_selected = (current_item == n); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(g_pMeshObjects[n]->friendlyName.c_str(), is_selected))
						currentModel = n;
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
			ImGui::PushItemWidth(200);
			ImGui::Text("Position: "); ImGui::SameLine();
			ImGui::SliderFloat("posX", &g_pMeshObjects[currentModel]->position.x, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::SliderFloat("posY", &g_pMeshObjects[currentModel]->position.y, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::SliderFloat("posZ", &g_pMeshObjects[currentModel]->position.z, -500.0f, 500.0f, "%.00f");

			ImGui::Text("Rotation: "); ImGui::SameLine();
			ImGui::PushItemWidth(50); ImGui::InputFloat("rX", &g_pMeshObjects[currentModel]->rotation.x);  ImGui::SameLine(); ImGui::PushItemWidth(200);
			ImGui::SliderFloat("rotX", &g_pMeshObjects[currentModel]->rotation.x, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::PushItemWidth(50); ImGui::InputFloat("rY", &g_pMeshObjects[currentModel]->rotation.y);  ImGui::SameLine(); ImGui::PushItemWidth(200);
			ImGui::SliderFloat("rotY", &g_pMeshObjects[currentModel]->rotation.y, -500.0f, 500.0f, "%.00f");
			ImGui::SameLine();
			ImGui::PushItemWidth(50); ImGui::InputFloat("rZ", &g_pMeshObjects[currentModel]->rotation.z);  ImGui::SameLine(); ImGui::PushItemWidth(200);
			ImGui::SliderFloat("rotZ", &g_pMeshObjects[currentModel]->rotation.z, -500.0f, 500.0f, "%.00f");
			ImGui::PushItemWidth(1000);
			ImGui::SliderFloat("Scale", &g_pMeshObjects[currentModel]->scale, -500.0f, 500.0f, "%.00f");
			ImGui::Text("WireFrame: "); ImGui::SameLine();
			ImGui::Checkbox("##wireframe", &g_pMeshObjects[currentModel]->isWireframe);
			if (ImGui::Button("Make Copy"))
			{
				createNew = !createNew;
				isTyping = !isTyping;
			}
			if (createNew)
			{
				static char name[64] = "";
				cMeshObject* obj = new cMeshObject;
				*obj = *g_pMeshObjects[currentModel];
				ImGui::InputText("Name", name, 64);
				if (ImGui::Button("Create"))
				{
					obj->friendlyName = name;
					pVAOManager->AddObject(*obj);
					g_pMeshObjects.push_back(obj);
					modelSize++;
					isTyping = false;
					createNew = false;
				}
			}
		}
	}

	ImGui::End();
}
void render(const std::string& sound)
{
	ImGui::Begin((sound + " Radio Settings").c_str());
	{
	}
	ImGui::End();
}