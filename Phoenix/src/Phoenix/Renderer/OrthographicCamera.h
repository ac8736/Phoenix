#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Phoenix {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float nearPlane = 0.1f, float farPlane = 100.0f);

		void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
		void SetRotation(float angle) { m_Rotation = angle; CalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const float GetRotation() const { return m_Rotation; }
	private:
		void CalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix; 
		glm::mat4 m_ViewMatrix; 
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;

		float m_Rotation = 0.0f;
	};
}
