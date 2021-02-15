#include <Realiti2D.h>
#define WIDTH 1024
#define HEIGHT 576

// TODO
// 2. Collision raycast to handle the mover
// 3. Collision Layers?

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

class PlayerController : public Realiti2D::Component {
public:
	PlayerController() : m_PlayerVelocityX(128.0f), m_Gravity(0.0f) {}
	~PlayerController() {}

	virtual void Initialize() {
		DEBUG_INFO("Initializing Player Controller!");
	}

	void ProcessInput(const Realiti2D::InputState& InputState) {
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
		
		Realiti2D::Vector2 VerletVelocity(Movement.x, Movement.y + (0.5f * m_Gravity * DeltaTime * DeltaTime) );
		Realiti2D::Vector2 VerletDeltaMovement = VerletVelocity * DeltaTime;
		Owner->GetComponentOfType<Mover>()->Move(VerletDeltaMovement, DeltaTime);

		Realiti2D::AnimatedSprite* AnimationComponent = Owner->GetComponentOfType<Realiti2D::AnimatedSprite>();
		if (Movement.x != 0) { AnimationComponent->Play("run"); } 
		else { AnimationComponent->Play("idle"); }
	}

private:
	float m_PlayerVelocityX;
	float m_Gravity;

	int m_MovementDirection;
};

class JumpVMain : public Realiti2D::Application {
public:
	JumpVMain(const float& Width, const float& Height, const std::string Title) : Application(Width, Height, Title) {}
	~JumpVMain() {}

	void Start() override {
		DEBUG_INFO("Starting Jump V. Main");

		// SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);

		Realiti2D::Entity& Character = AddEntity("Character");
		Character.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(4.0f, 4.0f));
		Character.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Character/Idle/I01.png", 5);

		Realiti2D::AnimatedSprite& AnimationComponent = Character.AddComponent<Realiti2D::AnimatedSprite>();
		Realiti2D::AnimationClip* IdleAnimation = new Realiti2D::AnimationClip(12.0f);
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I01.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I02.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I03.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I04.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I05.png");
		AnimationComponent.AddAnimationClip("idle", IdleAnimation);
		
		Realiti2D::AnimationClip* RunningAnimation = new Realiti2D::AnimationClip(12.0f);
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run01.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run02.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run03.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run04.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run05.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run06.png");
		AnimationComponent.AddAnimationClip("run", RunningAnimation);

		AnimationComponent.Play("idle");

		Character.AddComponent<Mover>();
		Character.AddComponent<PlayerController>();
	}
};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new JumpVMain(WIDTH, HEIGHT, "Jump V. Main");
}