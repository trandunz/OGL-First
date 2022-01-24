#include "Mesh.h"

Mesh::Mesh(Camera& _camera, MESHTYPE _type)
{
	for (int i = -10; i < 10; i++)
	{
		CreateInstance({ {i,1,1},{0,0,0},{1,1,1},0 });
	}

	m_Camera = &_camera;

	Compile();
}

Mesh::~Mesh()
{
	CleanupPointer(m_Shader);
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_InstanceBuffer);
	CleanupPointer(m_IndexBuffer);
	CleanupPointer(m_VertexArray);
	CleanupPointer(m_Texture);
	CleanupPointer(m_Normal);
	m_Camera = nullptr;
}

void Mesh::Compile()
{
	if (m_LightingEnabled)
	{
		CompileShaders("Resources/Shaders/basic_lighting_2.vs", "", "Resources/Shaders/basic_lighting_2.fs");
	}
	else
	{
		CompileShaders("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
	}
	
	CompileTexture("Resources/Textures/3.jpg");
	//CompileNormal("Resources/Textures/normal.png");

	CleanupPointer(m_VertBuffer);
	m_VertBuffer = new VertexBuffer(VERT_CUBE, sizeof(VERT_CUBE));

	CleanupPointer(m_IndexBuffer);
	m_IndexBuffer = new IndexBuffer(INDEX_CUBE, 36);

	unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(m_Shader->m_RendererID, "Matrices");
	glUniformBlockBinding(m_Shader->m_RendererID, uniformBlockIndexYellow, 0);
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();

	m_Shader->Bind();
	{
		m_VertexArray->LinkAttibute(*m_VertBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		m_VertexArray->LinkAttibute(*m_VertBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
		m_VertexArray->LinkAttibute(*m_VertBuffer, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(GLfloat)));

		if (m_InstanceCount != 1)
		{
			CleanupPointer(m_InstanceBuffer);
			m_InstanceBuffer = new VertexBuffer(m_InstanceMatrix, m_InstanceCount);
			{
				m_VertexArray->LinkAttibute(*m_InstanceBuffer, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
				m_VertexArray->LinkAttibute(*m_InstanceBuffer, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
				m_VertexArray->LinkAttibute(*m_InstanceBuffer, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
				m_VertexArray->LinkAttibute(*m_InstanceBuffer, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
				glVertexAttribDivisor(3, 1);
				glVertexAttribDivisor(4, 1);
				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);
			}
		}
	}
	m_VertexArray->UnBind();
	m_Shader->UnBind();
}

void Mesh::CompileShaders(const char* _vs, const char* _gs, const char* _fs)
{
	CleanupPointer(m_Shader);
	m_Shader = new Shader(_vs, _gs, _fs);
}

void Mesh::CompileNormal(const char* _normalMap)
{
	CleanupPointer(m_Normal);
	m_Normal = new Texture(_normalMap, "normal",GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
}

void Mesh::CompileTexture(const char* _defuse)
{
	CleanupPointer(m_Texture);
	m_Texture = new Texture(_defuse, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
}

void Mesh::Draw()
{
	// Light (Body)
	m_Shader->Bind();

	// Light Texture
	m_Texture->Bind();
	glActiveTexture(m_Texture->ID);

	m_VertexArray->Bind();
	if (m_InstanceBuffer)
	{
		m_VertexArray->StreamAttibute(*m_InstanceBuffer, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0, m_InstanceMatrix, m_InstanceCount);
		m_VertexArray->StreamAttibute(*m_InstanceBuffer, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)), m_InstanceMatrix, m_InstanceCount);
		m_VertexArray->StreamAttibute(*m_InstanceBuffer, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)), m_InstanceMatrix, m_InstanceCount);
		m_VertexArray->StreamAttibute(*m_InstanceBuffer, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)), m_InstanceMatrix, m_InstanceCount);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		m_InstanceBuffer->UnBind();
	}

	// if Lighting enabled
	HandleLightingUniforms();

	if (!m_LightingEnabled)
	{
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	}

	m_ProjectionMat = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
	m_ViewMat = m_Camera->GetViewMatrix();

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &m_ProjectionMat[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &m_ViewMat[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader, m_InstanceCount);
	
	m_IndexBuffer->UnBind();
	m_VertexArray->UnBind();
	m_Texture->Unbind();
	m_Shader->UnBind();
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

glm::mat4 Mesh::CalculateModelTransformations(glm::mat4& _model, STransform _transform)
{
	_model = glm::translate(glm::mat4(1.0f), _transform.position);
	if (_transform.rotation.x != 0.0f)
	{
		_model = glm::rotate(_model, _transform.rotation.x, _transform.rotation);
	}
	if (_transform.rotation.y != 0.0f)
	{
		_model = glm::rotate(_model, _transform.rotation.y, _transform.rotation);
	}
	if (_transform.rotation.z != 0.0f)
	{
		_model = glm::rotate(_model, _transform.rotation.z, _transform.rotation);
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

void Mesh::HandleLightingUniforms()
{
	if (m_LightingEnabled)
	{
		// SpotLight Uniforms
		m_Shader->SetUniformVec3f("spotLight.position", m_Camera->Position);
		m_Shader->SetUniformVec3f("spotLight.direction", m_Camera->Front);
		m_Shader->SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		if (m_Camera->m_CamLightEnabled)
		{
			m_Shader->SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			m_Shader->SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_Shader->SetUniform3f("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
			m_Shader->SetUniform3f("spotLight.specular", 0.0f, 0.0f, 0.0f);
		}
		m_Shader->SetUniform1f("spotLight.constant", 1.0f);
		m_Shader->SetUniform1f("spotLight.linear", 0.09f);
		m_Shader->SetUniform1f("spotLight.quadratic", 0.032f);
		m_Shader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_Shader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// View Position Uniform
		m_Shader->SetUniformVec3f("viewPos", m_Camera->Position);

		//m_Normal->Bind();

		//m_Shader->SetUniform1i("material.normal", m_Normal->ID);

		//  'Shininess'
		m_Shader->SetUniform1f("material.shininess", 32.0f);

		// Directional light Uniforms
		m_Shader->SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
		m_Shader->SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		m_Shader->SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// Point Light Uniforms
		for (int i = 0; i < m_InstanceCount; i++)
		{
			glm::vec3 pos = m_InstanceMatrix[i] * glm::vec4(0, 0, 0, 1);
			m_Shader->SetUniformVec3f("pointLights[" + std::to_string(i) + "].position", pos);
			m_Shader->SetUniform3f("pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
			m_Shader->SetUniform3f("pointLights[" + std::to_string(i) + "].diffuse", abs(m_Color[0] - 0.2f), abs(m_Color[1] - 0.2f), abs(m_Color[2] - 0.2f));
			m_Shader->SetUniform3f("pointLights[" + std::to_string(i) + "].specular", m_Color[0], m_Color[1], m_Color[2]);
			m_Shader->SetUniform1f("pointLights[" + std::to_string(i) + "].constant", 1.0f);
			m_Shader->SetUniform1f("pointLights[" + std::to_string(i) + "].linear", 0.09f);
			m_Shader->SetUniform1f("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
		}
	}
}

void Mesh::SetMVPUniform(STransform _transform)
{
	m_ProjectionMat = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
	CalculateModelTransformations(m_ModelMat, _transform);
	m_ViewMat = m_Camera->GetViewMatrix();
	glm::mat4 mvp = m_ProjectionMat * m_ViewMat * m_ModelMat;
	m_Shader->SetUniformMat4fv("u_MVP", mvp);
}
