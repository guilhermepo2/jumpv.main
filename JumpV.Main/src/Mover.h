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

		/*
		// check for grounded
		// Check for Collision here!!

		Realiti2D::CollisionInfo Info;

		float MoveDown = -1.0f;
		Realiti2D::Vector2 Min = Owner->GetComponentOfType<Realiti2D::Transform>()->Position + Owner->GetComponentOfType<Realiti2D::BoxCollider>()->GetBoundingBox()->MinPoint;
		Min += Realiti2D::Vector2(-0.05f, -0.05f);
		Realiti2D::Vector2 Destination = Min + Realiti2D::Vector2(0.0f, -MoveDown);
		bool bCollided = Realiti2D::CollisionWorld::s_Instance->SegmentCast(
			Min,
			Destination,
			Info
		);

		if (bCollided) {
			DEBUG_INFO("Collided! Position: ({0}, {1}), Entity Name: {2}", Info.PointOfCollision.x, Info.PointOfCollision.y, Info.CollidedEntity->Name);
		}
		else {
			Owner->GetComponentOfType<Realiti2D::Transform>()->Translate(Realiti2D::Vector2(0.0f, MoveDown));
		}
		*/
	}

private:
	void MoveHorizontal(Realiti2D::Vector2& DeltaMovement) {
		// TODO
		// check for collisions on the left or right and calculate deltamovement.x appropriately
		return;
	}

	void MoveVertical(Realiti2D::Vector2& DeltaMovement) {
		Realiti2D::CollisionInfo Info;
		Realiti2D::Vector2 Min = Owner->GetComponentOfType <Realiti2D::Transform>()->Position + Owner->GetComponentOfType<Realiti2D::BoxCollider>()->GetBoundingBox()->MinPoint;
		Min += Realiti2D::Vector2(-0.05f, -0.05f);
		Realiti2D::Vector2 Destination = Min + Realiti2D::Vector2(0.0f, DeltaMovement.y);

		DEBUG_INFO("Checking Collision: Min: ({0}, {1}), Destination: ({2}, {3})", Min.x, Min.y, Destination.x, Destination.y);

		bool bCollided = Realiti2D::CollisionWorld::s_Instance->SegmentCast(Min, Destination, Info);

		if (bCollided) {
			DeltaMovement.y = 0.0f;
		}

		return;
	}
};
