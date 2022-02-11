#include "Mesh.h"
namespace Harmony
{
	Mesh::Mesh(Camera& _camera, TextureMaster& _textureMaster)
	{
		BuildNormals();
		BuildVertexPoints();
		m_TextureMaster = &_textureMaster;
		srand(10000000);

		for (int i = -10; i < 10; i++)
		{
			STransform transform;
			transform.position = { i + i,20 ,0 };
			transform.scale = { 1, 1,1 };
			CreateInstance(transform);
		}
		STransform transform;
		transform.position = { 0,-20 ,0 };
		transform.scale = { 40, 1,10 };
		CreateInstance(transform);
		for (int i = 0; i < m_InstanceMatrix.size(); i++)
		{
			m_PreviousPositions.push_back(m_InstanceMatrix[i]);
		}
		
		m_Camera = &_camera;

		RAW_Compile();
	}

	Mesh::~Mesh()
	{
		// Unbind
		{
			glBindTexture(m_TextureMaster->m_Textures[0]->Type, 0);
			glBindTexture(m_TextureMaster->m_Textures[1]->Type, 0);
			glBindTexture(m_TextureMaster->m_Textures[2]->Type, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
		// Delete
		{
			glDeleteVertexArrays(1, &m_VertexArrayID);
			glDeleteBuffers(1, &m_UniformBufferID);
			glDeleteBuffers(1, &m_VertBufferID);
			glDeleteBuffers(1, &m_InstanceBufferID);
			glDeleteBuffers(1, &m_IndexBufferID);
			glDeleteProgram(m_ShaderID);
		}

		m_TextureMaster = nullptr;
	}

	void Mesh::RAW_Recompile()
	{
		// Unbind
		{
			m_TextureMaster->m_Textures[0]->Unbind();
			m_TextureMaster->m_Textures[2]->Unbind();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
		// Delete
		{
			glDeleteVertexArrays(1, &m_VertexArrayID);
			glDeleteBuffers(1, &m_UniformBufferID);
			glDeleteBuffers(1, &m_VertBufferID);
			glDeleteBuffers(1, &m_InstanceBufferID);
			glDeleteBuffers(1, &m_IndexBufferID);
			glDeleteProgram(m_ShaderID);
		}
		RAW_Compile();
	}

	void Mesh::RAW_Compile()
	{
		if (m_LightingEnabled)
		{
			m_ShaderID = CShaderLoader::CreateShader("Resources/Shaders/basic_lighting_2.vs", "Resources/Shaders/TestShader_FILL.gs", "Resources/Shaders/basic_lighting_2.fs");
		}
		else
		{
			m_ShaderID = CShaderLoader::CreateShader("Resources/Shaders/TestShader.vs", "Resources/Shaders/TestShader_FILL.gs", "Resources/Shaders/TestShader.fs");
		}

		// VertexBuffer
		glCreateBuffers(1, &m_VertBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBufferID);
		if (m_Vertices.size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
		}
		else
			glBufferData(GL_ARRAY_BUFFER, sizeof(VERT_CUBE), VERT_CUBE, GL_STATIC_DRAW);
		
		// Index Buffer
		glCreateBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		if (m_Indices.size() > 0)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
		}
		else
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), INDEX_CUBE, GL_STATIC_DRAW);

		// Uniform Buffer
		unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(m_ShaderID, "Matrices");
		glUniformBlockBinding(m_ShaderID, uniformBlockIndexYellow, 0);
		glCreateBuffers(1, &m_UniformBufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, uniformBlockIndexYellow, m_UniformBufferID, 0, 2 * sizeof(glm::mat4));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Vertex Array
		glCreateVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		// Layouts
		glUseProgram(m_ShaderID);
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VertBufferID);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(1);
			if (m_Vertices.size() > 0)
			{
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoords)));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			else
			{
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GLfloat)));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			// Instance Matrix Layout
			if (m_InstanceCount != 1)
			{
				glCreateBuffers(1, &m_InstanceBufferID);
				glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferID);
				glBufferData(GL_ARRAY_BUFFER, m_InstanceCount * sizeof(glm::mat4), &m_InstanceMatrix[0], GL_STATIC_DRAW);
				{
					glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferID);
					glEnableVertexAttribArray(3);
					glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
					glEnableVertexAttribArray(4);
					glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
					glEnableVertexAttribArray(5);
					glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
					glEnableVertexAttribArray(6);
					glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glVertexAttribDivisor(3, 1);
					glVertexAttribDivisor(4, 1);
					glVertexAttribDivisor(5, 1);
					glVertexAttribDivisor(6, 1);
				}
			}
		}

		glUniform1i(glGetUniformLocation(m_ShaderID, "material.diffuse"), m_TextureMaster->m_Textures[0]->Unit);
		glUniform1i(glGetUniformLocation(m_ShaderID, "material.specular"), m_TextureMaster->m_Textures[2]->Unit);
		glUniform1f(glGetUniformLocation(m_ShaderID, "material.shininess"), 128);

		glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(m_ShaderID, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(m_ShaderID, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(m_ShaderID, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(m_ShaderID, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(m_ShaderID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		glUniform3f(glGetUniformLocation(m_ShaderID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(m_ShaderID, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(m_ShaderID, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(m_ShaderID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		glm::vec3 pos = glm::vec3(1, 1, 1);
		std::string uniformName;
		for (unsigned int i = 0; i < 20; i++)
		{
			uniformName = "pointLights[" + std::to_string(i) + "].position";
			glUniform3f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), pos.x, pos.y, pos.z);
			uniformName = "pointLights[" + std::to_string(i) + "].ambient";
			glUniform3f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), 1.05f, 1.05f, 1.05f);
			uniformName = "pointLights[" + std::to_string(i) + "].constant";
			glUniform1f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), 1.0f);
			uniformName = "pointLights[" + std::to_string(i) + "].linear";
			glUniform1f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), 0.09f);
			uniformName = "pointLights[" + std::to_string(i) + "].quadratic";
			glUniform1f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), 0.032f);
			uniformName = "pointLights[" + std::to_string(i) + "].specular";
			glUniform3f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), abs(m_Color[0] - 0.2f), abs(m_Color[1] - 0.2f), abs(m_Color[2] - 0.2f));
			uniformName = "pointLights[" + std::to_string(i) + "].diffuse";
			glUniform3f(glGetUniformLocation(m_ShaderID, uniformName.c_str()), m_Color[0], m_Color[1], m_Color[2]);

		}
	}

	void Mesh::RAW_Draw()
	{
		for (int i = 0; i < m_InstanceMatrix.size(); i++)
		{
			m_PreviousPositions[i] = m_InstanceMatrix[i];
		}
		glUseProgram(m_ShaderID);

		glBindVertexArray(m_VertexArrayID);

		glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferID);
		glBufferData(GL_ARRAY_BUFFER, m_InstanceCount * sizeof(glm::mat4), &m_InstanceMatrix[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glBufferData(GL_ARRAY_BUFFER, m_InstanceCount * sizeof(glm::mat4), &m_InstanceMatrix[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		glBufferData(GL_ARRAY_BUFFER, m_InstanceCount * sizeof(glm::mat4), &m_InstanceMatrix[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glBufferData(GL_ARRAY_BUFFER, m_InstanceCount * sizeof(glm::mat4), &m_InstanceMatrix[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_TextureMaster->m_Textures[0]->Bind();
		
		// Calculated View Mat And Proj Mat
		m_ProjectionMat = m_Camera->GetProjectionMatrix();
		m_ViewMat = m_Camera->GetViewMatrix();

		// If Lighting
		if (m_LightingEnabled)
		{
			m_TextureMaster->m_Textures[1]->Bind();
			m_TextureMaster->m_Textures[2]->Bind();

			if (m_Camera->m_CamLightEnabled)
			{
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.position"), m_Camera->Position.x, m_Camera->Position.y, m_Camera->Position.z);
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.direction"), m_Camera->Front.x, m_Camera->Front.y, m_Camera->Front.z);
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
			}
			else
			{
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
				glUniform3f(glGetUniformLocation(m_ShaderID, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
			}

			glUniform3f(glGetUniformLocation(m_ShaderID, "viewPos"), m_Camera->Position.x, m_Camera->Position.y, m_Camera->Position.z);
		}
		else
		{
			glUniform1i(glGetUniformLocation(m_ShaderID, "u_Texture"), m_TextureMaster->m_Textures[0]->Unit);
			glUniform4f(glGetUniformLocation(m_ShaderID, "u_Color"), m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		}

		// Stream In Proj Mat
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &m_ProjectionMat[0]);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Stream In View Mat
		glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &m_ViewMat[0]);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Draw
		glUseProgram(m_ShaderID);
		glBindVertexArray(m_VertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		{
			if (m_InstanceCount > 1)
			{
				if (m_Indices.size() > 0)
					glDrawElementsInstanced(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0, m_InstanceCount);
				else
					glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, m_InstanceCount);
			}
			else
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		}

		// Unbind
		{
			m_TextureMaster->m_Textures[0]->Unbind();
			m_TextureMaster->m_Textures[2]->Unbind();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	}

	void Mesh::ImGuiHandler()
	{
		if (ImGui::BeginMenu("Copy"))
		{
			if (ImGui::MenuItem("Mesh", "Single Mesh"))
			{
				CreateInstance({ { m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5) }, { glm::vec3(0,0,0) }, { glm::vec3(1,1,1) } });
			}
			ImGui::EndMenu();
		}
	}

	glm::mat4 Mesh::CalculateModelTransformations(glm::mat4& _model, STransform& _transform)
	{
		_model = glm::translate(glm::mat4(1), _transform.position);
		if (_transform.rotation.x != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		if (_transform.rotation.y != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		if (_transform.rotation.z != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		_model = glm::scale(_model, _transform.scale);
		return _model;
	}

	glm::mat4 Mesh::ModifyModelTransformations(glm::mat4& _model, STransform _transform)
	{
		_model = glm::translate(_model, _transform.position);
		if (_transform.rotation.x != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		if (_transform.rotation.y != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		if (_transform.rotation.z != 0.0f)
		{
			_model = glm::rotate(_model, _transform.rotation_amount, _transform.rotation);
		}
		_model = glm::scale(_model, _transform.scale);
		return _model;
	}

	void Mesh::CreateInstance(STransform _transform)
	{
		glm::mat4 tempMat;
		CalculateModelTransformations(tempMat, _transform);
		m_InstanceMatrix.push_back(tempMat);
		m_InstanceCount++;
	}

	void Mesh::ModifyInstanceMatrix(unsigned int _index, STransform _transform)
	{
		glm::mat4 tempMat = m_InstanceMatrix[_index];
		ModifyModelTransformations(tempMat, _transform);
		m_InstanceMatrix[_index] = tempMat;
	}

	void Mesh::ModifyInstance(unsigned int _index, STransform _transform)
	{
		glm::mat4 tempMat;
		CalculateModelTransformations(tempMat, _transform);
		m_InstanceMatrix[_index] = tempMat;
	}

	void Mesh::ModifyInstance(unsigned int _index, float _color[4])
	{
		m_Color[0] = _color[0];
		m_Color[1] = _color[1];
		m_Color[2] = _color[2];
		m_Color[3] = _color[3];
	}

	int Mesh::GetInstanceMatrixSize()
	{
		return m_InstanceMatrix.size();
	}

	bool Mesh::Contains(glm::vec3 _point)
	{
		Physics::Cube meshCube;
		for (int i = 0; i < m_InstanceMatrix.size(); i++)
		{
			meshCube.ModelMat = m_InstanceMatrix[i];
			if (Physics::Point(meshCube, _point))
			{
				//std::cout << "Total Instances : " << m_InstanceMatrix.size() << " !" << std::endl;
				//std::cout << "Collision On Instance : " << i + 1 << " !" << std::endl;
				return true;
			}
		}
		
		return false;
	}

	std::vector<bool> Mesh::Intersects()
	{
		Physics::Cube meshCube;
		Physics::Cube otherCube;
		std::vector<bool> collisions;
		for (int i = 0; i < m_InstanceMatrix.size(); i++)
		{
			collisions.push_back(false);
		}

		for (int i = 0; i < m_InstanceMatrix.size(); i++)
		{
			meshCube.ModelMat = m_InstanceMatrix[i];
			
			for (int j = i + 1; j < m_InstanceMatrix.size(); j++)
			{
				otherCube.ModelMat = m_InstanceMatrix[j];
				if (Physics::Intersection(meshCube, otherCube))
				{
					collisions[i] = true;
					break;
					std::cout << "Collision" << std::endl;
				}
			}
		}

		return collisions;
	}

	std::vector<float> Mesh::BuildSphereUnitPositiveX(int subdivision)
	{
		const float DEG2RAD = acos(-1) / 180.0f;

		std::vector<float> vertices;
		float n1[3];        // normal of longitudinal plane rotating along Y-axis
		float n2[3];        // normal of latitudinal plane rotating along Z-axis
		float v[3];         // direction vector intersecting 2 planes, n1 x n2
		float a1;           // longitudinal angle along Y-axis
		float a2;           // latitudinal angle along Z-axis

		// compute the number of vertices per row, 2^n + 1
		int pointsPerRow = (int)pow(2, subdivision) + 1;

		// rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
		for (unsigned int i = 0; i < pointsPerRow; ++i)
		{
			// normal for latitudinal plane
			// if latitude angle is 0, then normal vector of latitude plane is n2=(0,1,0)
			// therefore, it is rotating (0,1,0) vector by latitude angle a2
			a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
			n2[0] = -sin(a2);
			n2[1] = cos(a2);
			n2[2] = 0;

			// rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
			for (unsigned int j = 0; j < pointsPerRow; ++j)
			{
				// normal for longitudinal plane
				// if longitude angle is 0, then normal vector of longitude is n1=(0,0,-1)
				// therefore, it is rotating (0,0,-1) vector by longitude angle a1
				a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
				n1[0] = -sin(a1);
				n1[1] = 0;
				n1[2] = -cos(a1);

				// find direction vector of intersected line, n1 x n2
				v[0] = n1[1] * n2[2] - n1[2] * n2[1];
				v[1] = n1[2] * n2[0] - n1[0] * n2[2];
				v[2] = n1[0] * n2[1] - n1[1] * n2[0];

				// normalize direction vector
				float scale = 1 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
				v[0] *= scale;
				v[1] *= scale;
				v[2] *= scale;

				// add a vertex into array
				vertices.push_back(v[0]);
				vertices.push_back(v[1]);
				vertices.push_back(v[2]);
			}
		}

		return vertices;
	}

	std::vector<float> Mesh::BuildSphereUnitNegativeX(int subdivision)
	{
		const float DEG2RAD = acos(-1) / 180.0f;

		std::vector<float> vertices;
		float n1[3];        // normal of longitudinal plane rotating along Y-axis
		float n2[3];        // normal of latitudinal plane rotating along Z-axis
		float v[3];         // direction vector intersecting 2 planes, n1 x n2
		float a1;           // longitudinal angle along Y-axis
		float a2;           // latitudinal angle along Z-axis

		// compute the number of vertices per row, 2^n + 1
		int pointsPerRow = (int)pow(2, subdivision) + 1;

		// rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
		for (unsigned int i = 0; i < pointsPerRow; ++i)
		{
			// normal for latitudinal plane
			// if latitude angle is 0, then normal vector of latitude plane is n2=(0,1,0)
			// therefore, it is rotating (0,1,0) vector by latitude angle a2
			a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
			n2[0] = -sin(a2);
			n2[1] = cos(a2);
			n2[2] = 0;

			// rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
			for (unsigned int j = 0; j < pointsPerRow; ++j)
			{
				// normal for longitudinal plane
				// if longitude angle is 0, then normal vector of longitude is n1=(0,0,-1)
				// therefore, it is rotating (0,0,-1) vector by longitude angle a1
				a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
				n1[0] = -sin(a1);
				n1[1] = 0;
				n1[2] = -cos(a1);

				// find direction vector of intersected line, n1 x n2
				v[0] = n1[1] * n2[2] - n1[2] * n2[1];
				v[1] = n1[2] * n2[0] - n1[0] * n2[2];
				v[2] = n1[0] * n2[1] - n1[1] * n2[0];

				// normalize direction vector
				float scale = 1 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
				v[0] *= scale;
				v[1] *= scale;
				v[2] *= scale;

				// add a vertex into array
				vertices.push_back(v[0]);
				vertices.push_back(v[1]);
				vertices.push_back(v[2]);
			}
		}

		return vertices;
	}
	void Mesh::BuildNormals(std::string _shapeType)
	{
		for (int i = 0; i < 6; i++)
		{
			m_Indices.push_back(0 + (6 * i));
			m_Indices.push_back(1 + (6 * i));
			m_Indices.push_back(2 + (6 * i));
			m_Indices.push_back(2 + (6 * i));
			m_Indices.push_back(4 + (6 * i));
			m_Indices.push_back(0 + (6 * i));
		}
		//	0, 1, 2,
		//	2, 4, 0,

		//	6, 7, 8,
		//	8, 10, 6,

		//	12, 13, 14,
		//	14, 16, 12,

		//	18, 19, 20,
		//	20, 22, 18,

		//	24, 25, 26,
		//	26, 28, 24,

		//	30, 31, 32,
		//	32, 34, 30
	}
	void Mesh::BuildVertexPoints(std::string _shapeType)
	{
		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f, -0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{0.0f,  0.0f, -1.0f},{0.0f,  0.0f} });

		m_Vertices.push_back({ {-0.5f, -0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f, -0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f,  0.5f},{0.0f,  0.0f, 1.0f},{0.0f,  0.0f} });

		m_Vertices.push_back({ {-0.5f,  0.5f,  0.5f},{-1.0f,  0.0f,  0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f, -0.5f},{-1.0f,  0.0f,  0.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{-1.0f,  0.0f,  0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{-1.0f,  0.0f,  0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f,  0.5f},{-1.0f,  0.0f,  0.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f,  0.5f},{-1.0f,  0.0f,  0.0f},{1.0f,  0.0f} });

		m_Vertices.push_back({ {0.5f,  0.5f,  0.5f},{1.0f,  0.0f,  0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ {0.5f,  0.5f, -0.5f},{1.0f,  0.0f,  0.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ {0.5f, -0.5f, -0.5f},{1.0f,  0.0f,  0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {0.5f, -0.5f, -0.5f},{1.0f,  0.0f,  0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ {0.5f, -0.5f,  0.5f},{1.0f,  0.0f,  0.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ {0.5f,  0.5f,  0.5f},{1.0f,  0.0f,  0.0f},{1.0f,  0.0f} });

		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{0.0f,  -1.0f, 0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f, -0.5f, -0.5f},{0.0f,  -1.0f, 0.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f, -0.5f,  0.5f},{0.0f,  -1.0f, 0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f, -0.5f,  0.5f},{0.0f,  -1.0f, 0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f,  0.5f},{0.0f,  -1.0f, 0.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f, -0.5f, -0.5f},{0.0f,  -1.0f, 0.0f},{0.0f,  1.0f} });

		m_Vertices.push_back({ {-0.5f,  0.5f, -0.5f},{0.0f,  1.0f, 0.0f},{0.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f, -0.5f},{0.0f,  1.0f, 0.0f},{1.0f,  1.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f,  0.5f},{0.0f,  1.0f, 0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ { 0.5f,  0.5f,  0.5f},{0.0f,  1.0f, 0.0f},{1.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f,  0.5f},{0.0f,  1.0f, 0.0f},{0.0f,  0.0f} });
		m_Vertices.push_back({ {-0.5f,  0.5f, -0.5f},{0.0f,  1.0f, 0.0f},{0.0f,  1.0f} });
	}
}
