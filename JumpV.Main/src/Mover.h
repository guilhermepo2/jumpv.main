#pragma once
#include <Realiti2D.h>

class Mover : public Realiti2D::Component {
public:
	Realiti2D::Vector2 Velocity;

	void Move(Realiti2D::Vector2& DeltaMovement, float DeltaTime) {
		
		// DEBUG_INFO("DeltaMovement: {0}, {1}", DeltaMovement.x, DeltaMovement.y);

		// reset collision state
		if (DeltaMovement.x != 0.0f) {
			MoveHorizontal(DeltaMovement);
		}

		if (DeltaMovement.y != 0.0f) {
			MoveVertical(DeltaMovement);
		}

		Owner->GetComponentOfType<Realiti2D::Transform>()->Translate(DeltaMovement);

		if (DeltaTime > 0.0f) {
			Velocity = DeltaMovement / DeltaTime;
		}
	}

private:
	void MoveHorizontal(Realiti2D::Vector2& DeltaMovement) {
		// TODO
		// check for collisions on the left or right and calculate deltamovement.x appropriately
		return;
	}

	void MoveVertical(Realiti2D::Vector2& DeltaMovement) {
		Realiti2D::Vector2 Min = Owner->GetComponentOfType<Realiti2D::Transform>()->Position;
		Realiti2D::Vector2 AABB = Owner->GetComponentOfType<Realiti2D::BoxCollider>()->GetBoundingBox()->MinPoint;
		AABB.x *= Owner->GetComponentOfType<Realiti2D::Transform>()->Scale.x;
		AABB.y *= Owner->GetComponentOfType<Realiti2D::Transform>()->Scale.y;
		Min += AABB;
		Min += Realiti2D::Vector2(-0.05f, -0.05f);
		Realiti2D::Vector2 Destination = Min + Realiti2D::Vector2(0.0f, DeltaMovement.y);

		Realiti2D::CollisionInfo Info;
		bool bCollided = Realiti2D::CollisionWorld::s_Instance->SegmentCast(Min, Destination, Info);

		if (bCollided) {
			Velocity.y = 0.0f;
			DeltaMovement.y = 0.0f;
		}

		return;
	}
};
