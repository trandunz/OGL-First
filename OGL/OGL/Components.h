#pragma once
#include <GLM/glm.hpp>
#include "GameObject.h"
#include "MousePicker.h"
#include "Cubemap.h"

namespace Harmony
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string _tag)
			: Tag(_tag) {}

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};
	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& _transform)
			: Transform(_transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};
	struct CameraComponent
	{
		Harmony::Camera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const Harmony::Camera& _camera)
			:Camera(_camera) {}
		CameraComponent(std::map<int,bool>& _keyMap, glm::vec3 _pos)
			:Camera(_keyMap, _pos) {}
		CameraComponent(const CameraComponent&) = default;

		operator Harmony::Camera& () { return Camera; }
		operator const Harmony::Camera& () const { return Camera; }
	};
	struct MousePickerComponent
	{
		Harmony::MousePicker MousePicker;

		MousePickerComponent() = default;
		MousePickerComponent(const Harmony::MousePicker& _mousePicker)
			:MousePicker(_mousePicker) {}
		MousePickerComponent(Harmony::Camera& _camera)
			:MousePicker(&_camera) {}
		MousePickerComponent(const MousePickerComponent&) = default;

		operator Harmony::MousePicker& () { return MousePicker; }
		operator const Harmony::MousePicker& () const { return MousePicker; }
	};
	struct MeshComponent
	{
		Harmony::Mesh Mesh;

		MeshComponent() = default;
		MeshComponent(const Harmony::Mesh _mesh)
			:Mesh(_mesh) {}
		MeshComponent(Camera& _camera, TextureMaster& _textureMaster)
			:Mesh(_camera, _textureMaster) {}
		MeshComponent(const MeshComponent&) = default;

		operator Harmony::Mesh& () { return Mesh; }
		operator const Harmony::Mesh& () const { return Mesh; }
	};
	struct CubemapComponent
	{
		Harmony::Cubemap Cubemap;

		CubemapComponent() = default;
		CubemapComponent(const Harmony::Cubemap _cubemap)
			:Cubemap(_cubemap) {}
		CubemapComponent(Harmony::Camera& _camera)
			:Cubemap(_camera) {}
		CubemapComponent(const CubemapComponent&) = default;

		operator Harmony::Cubemap& () { return Cubemap; }
		operator const Harmony::Cubemap& () const { return Cubemap; }
	};
}

