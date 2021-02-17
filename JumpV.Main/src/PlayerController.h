#pragma once
#include <Realiti2D.h>
#include "Mover.h"

class PlayerController : public Realiti2D::Component {
public:
	PlayerController() : m_PlayerVelocityX(128.0f), m_Gravity(0.0f), m_Jump(false) {}
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

		Realiti2D::Vector2 VerletVelocity(Movement.x, Movement.y + (0.5f * m_Gravity * DeltaTime * DeltaTime));
		Realiti2D::Vector2 VerletDeltaMovement = VerletVelocity * DeltaTime;
		Owner->GetComponentOfType<Mover>()->Move(VerletDeltaMovement, DeltaTime);

		Realiti2D::AnimatedSprite* AnimationComponent = Owner->GetComponentOfType<Realiti2D::AnimatedSprite>();

		if (m_Jump) {
			AnimationComponent->Play("jump");

			if (AnimationComponent->IsPlayingAnimation("jump") && AnimationComponent->IsAnimationOnLastFrame()) {
				m_Jump = false;
			}
		} else if (Movement.x != 0) { AnimationComponent->Play("run"); }
		else { AnimationComponent->Play("idle"); }
	}

private:
	float m_PlayerVelocityX;
	float m_Gravity;
	bool m_Jump;

	int m_MovementDirection;
};