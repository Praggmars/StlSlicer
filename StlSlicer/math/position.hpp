#pragma once

#include "linalg.hpp"

namespace mth
{
	template <typename T>
	class Position
	{
	public:
		vec3<T> position;
		vec3<T> rotation;
		vec3<T> scale;

	public:
		Position() { Reset(); }

		void MoveForward(T d)
		{
			position.x += sin(rotation.y) * d;
			position.z += cos(rotation.y) * d;
		}
		void MoveBackward(T d)
		{
			position.x -= sin(rotation.y) * d;
			position.z -= cos(rotation.y) * d;
		}
		void MoveRight(T d)
		{
			position.x += cos(rotation.y) * d;
			position.z -= sin(rotation.y) * d;
		}
		void MoveLeft(T d)
		{
			position.x -= cos(rotation.y) * d;
			position.z += sin(rotation.y) * d;
		}
		void MoveUp(T d) { position.y += d; }
		void MoveDown(T d) { position.y -= d; }
		void Move(vec3<T> delta) { position += delta; }
		void MoveInLookDirection(T d) { MoveInLookDirection(vec3<T>(0, 0, d)); }
		void MoveInLookDirection(vec3<T> delta) { position += RotationMatrix3x3() * delta; }

		void LookDown(T r) { rotation.x += r; }
		void LookUp(T r) { rotation.x -= r; }
		void TurnRight(T r) { rotation.y += r; }
		void TurnLeft(T r) { rotation.y -= r; }
		void RollRight(T r) { rotation.z -= r; }
		void RollLeft(T r) { rotation.z += r; }

		void ScaleX(T s) { scale.x *= s; }
		void ScaleY(T s) { scale.y *= s; }
		void ScaleZ(T s) { scale.z *= s; }

		mat4x4<T> PositionMatrix() const { return mat4x4<T>::Translation(position); }
		mat4x4<T> RotationMatrix() const { return mat4x4<T>::Rotation(rotation); }
		mat4x4<T> ScaleMatrix() const { return mat4x4<T>::Scaling(scale); }
		mat4x4<T> WorldMatrix() const { return mat4x4<T>::ScalingRotationTranslation(scale, rotation, position); }
		mat4x4<T> PositionMatrixInv() const { return mat4x4<T>::Translation(-position); }
		mat4x4<T> RotationMatrixInv() const { return mat4x4<T>::Rotation(rotation).Transposed(); }
		mat4x4<T> ScaleMatrixInv() const { return mat4x4<T>::Scaling(vec3<T>(1) / scale); }
		mat4x4<T> WorldMatrixInv() const { return ScaleMatrixInv() * RotationMatrixInv() * PositionMatrixInv(); }
		vec3<T> LookDirection() const { return RotationMatrix3x3() * vec3<T>(0, 0, 1); }
		mat3x3<T> RotationMatrix3x3() const { return mat3x3<T>::Rotation(rotation); }
		mat3x3<T> ScaleMatrix3x3() const { return mat3x3<T>::Scaling(scale); }
		mat3x3<T> RotationMatrixInv3x3() const { return mat3x3<T>::Rotation(rotation).Transposed(); }
		mat3x3<T> ScaleMatrixInv3x3() const { return mat3x3<T>::Scaling(vec3<T>(1) / scale); }
		void Reset()
		{
			position = 0;
			rotation = 0;
			scale = 1;
		}
		T DistanceSquare(Position<T>& other) const { return (position - other.position).LengthSquare(); }
		T Distance(Position<T>& other) const { return (position - other.position).Length(); }

		template <typename S>
		operator Position<S>() const
		{
			return WithType<S>();
		}
		template <typename S>
		Position<S> WithType() const
		{
			Position<S> pos;
			pos.position = (vec3<S>)position;
			pos.rotation = (vec3<S>)rotation;
			pos.scale = (vec3<S>)scale;
			return pos;
		}
	};

	using Positionf = Position<float>;
	using Positiond = Position<double>;
}