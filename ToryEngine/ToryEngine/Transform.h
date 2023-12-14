#pragma once
#include "Component.h"


class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Init() override;
	virtual void Update() override;
	
	void UpdateTransform();

	// Local
	Vector3 GetLocalScale() { return _localScale; }
	void SetLocalScale(const Vector3& localScale) { _localScale = localScale; UpdateTransform(); }
	Vector3 GetLocalRotation() { return _localRotation; }
	void SetLocalRotation(const Vector3& localRotation) { _localRotation = localRotation; UpdateTransform(); }
	Vector3 GetLocalPosition() { return _localPosition; }
	void SetLocalPosition(const Vector3& localPosition) { _localPosition = localPosition; UpdateTransform(); }

	// World
	Vector3 GetScale() { return _scale; }
	void SetScale(const Vector3& worldScale);
	Vector3 GetRotation() { return _rotation; }
	void SetRotation(const Vector3& worldRotation);
	Vector3 GetPosition() { return _position; }
	void SetPosition(const Vector3& worldPosition);

	Matrix GetWorldMatrix() { return _matWorld; }

	// °èÃþ °ü°è
	bool HasParent() { return _parent != nullptr; }
	
	shared_ptr<Transform> GetParent() { return _parent; }
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	const vector<shared_ptr<Transform>>& GetChildren() { return _children; }
	void AddChild(shared_ptr<Transform> child) { _children.push_back(child); }

private:
	Vector3 _localScale = { 1.f, 1.f, 1.f };
	Vector3 _localRotation = { 0.f, 0.f, 0.f };
	Vector3 _localPosition = { 0.f, 0.f, 0.f };

	// Cache
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld= Matrix::Identity;

	Vector3 _scale;
	// x y z w(?)
	Vector3 _rotation;
	Vector3 _position;

	Vector3 _right;
	Vector3 _up;
	Vector3 _look;

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

