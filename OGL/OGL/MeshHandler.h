#pragma once
#include "NumptyBehavior.h"
#include "Mesh.h"

class MeshHandler : NumptyBehavior
{
public:
	MeshHandler()
	{

	}
	~MeshHandler()
	{
		while (MESHES.size() > 0)
		{
			MESHES.pop_back();
		}
		MESHES.erase(std::remove(MESHES.begin(), MESHES.end(), nullptr), MESHES.end());
	}
	void InitMeshes()
	{
	}
	void Draw()
	{
		if (MESHES.size() > 0)
		{
			for (auto& item : MESHES)
			{
				item->Draw();
			}
		}
	}
	void RecompileMeshes()
	{
		if (MESHES.size() > 0)
		{
			for (auto& item : MESHES)
			{
				item->Compile();
			}
		}
	}
	void AddMesh(std::shared_ptr<Mesh>& mesh)
	{
		MESHES.push_back(mesh);
	}
	void RemoveLastMesh(std::shared_ptr<Mesh>& mesh)
	{
		MESHES.pop_back();
	}
	std::vector<std::shared_ptr<Mesh>> MESHES;
};


