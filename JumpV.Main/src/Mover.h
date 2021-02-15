#pragma once
#include <Realiti2D.h>

class Mover : public Realiti2D::Component {
public:
	Realiti2D::Vector2 Velocity;

	void Move(Realiti2D::Vector2& DeltaMovement, float DeltaTime) {
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

		// check for grounded
		// check for collision events ?!
	}

private:
	void MoveHorizontal(Realiti2D::Vector2& DeltaMovement) {
		// TODO
		// check for collisions on the left or right and calculate deltamovement.x appropriately
		return;
	}

	void MoveVertical(Realiti2D::Vector2& DeltaMovement) {
		// TODO
		// check for collisions up or down and calculate deltamovement.y appropriately
		return;
	}
};
