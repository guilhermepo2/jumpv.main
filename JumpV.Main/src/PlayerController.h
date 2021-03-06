#pragma once
#include <Realiti2D.h>
#include "Mover.h"

class PlayerController : public Realiti2D::Component {
public:
	PlayerController() : m_PlayerVelocityX(128.0f), m_Gravity(9.81f), m_Jump(false) {}
	~PlayerController() {}

	virtual void Initialize() {
		DEBUG_INFO("Initializing Player Controller!");

	}

	void ProcessInput(const Realiti2D::InputState& InputState) {

		if (InputState.Keyboard.WasKeyPressedThisFrame(Realiti2D::R2D_Keycode::KEYCODE_SPACE)) {
			m_Jump = true;
		}

		if (InputState.Keyboard.IsKeyDown(Realiti2D::R2D_Keycode::KEYCODE_A)) {
			m_MovementDirection = -1;
		}
		else if (InputState.Keyboard.IsKeyDown(Realiti2D::R2D_Keycode::KEYCODE_D)) {
			m_MovementDirection = 1;
		}
		else {
			m_MovementDirection = 0;
		}
	}

	void Update(float DeltaTime) {
		Realiti2D::Vector2 Movement(m_MovementDirection * m_PlayerVelocityX, 0.0f);

		float SmoothedMovementFactor = 10.0f;
		// Movement.x = Realiti2D::Math::Lerp(Movement.x, m_MovementDirection * m_PlayerVelocityX, SmoothedMovementFactor * DeltaTime);
		// TODO max velocity.y with terminal velocity
		float GravityFactor = ( Movement.y < 0 ) ? 2.0f : 1.0f;
		Realiti2D::Vector2 VerletVelocity(
			Movement.x, 
			Owner->GetComponentOfType<Mover>()->Velocity.y + Movement.y + (GravityFactor * 0.5f * (-m_Gravity * 10000 * DeltaTime * DeltaTime))
		);
		Realiti2D::Vector2 VerletDeltaMovement = VerletVelocity * DeltaTime;
		Owner->GetComponentOfType<Mover>()->Move(VerletDeltaMovement, DeltaTime);

		if (Movement.x != 0) {
			Owner->GetComponentOfType<Realiti2D::Transform>()->ChangeScaleXSign(Realiti2D::Math::Sign(Movement.x));
		}

		Realiti2D::AnimatedSprite* AnimationComponent = Owner->GetComponentOfType<Realiti2D::AnimatedSprite>();
		if (m_Jump) {
			AnimationComponent->Play("jump");

			if (AnimationComponent->IsPlayingAnimation("jump") && AnimationComponent->IsAnimationOnLastFrame()) {
				m_Jump = false;
			}
		} else if (Movement.x != 0) { AnimationComponent->Play("run"); }
		else { AnimationComponent->Play("idle"); }
	}

	float m_PlayerVelocityX;
	float m_Gravity;
private:
	bool m_Jump;

	int m_MovementDirection;
};