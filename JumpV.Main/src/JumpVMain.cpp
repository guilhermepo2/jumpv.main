#include <Realiti2D.h>
#include "Mover.h"
#include "PlayerController.h"

#define WIDTH 1024
#define HEIGHT 576

// TODO
// 2. Collision raycast to handle the mover
// 3. Collision Layers?

class JumpVMain : public Realiti2D::Application {
public:
	JumpVMain(const float& Width, const float& Height, const std::string Title) : Application(Width, Height, Title) {}
	~JumpVMain() {}

	void Start() override {
		DEBUG_INFO("Starting Jump V. Main");

		// SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);

		// Background
		Realiti2D::Entity& Background = AddEntity("Background");
		Background.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(3.0f, 4.5f));
		Background.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Environment/Background/BGImage.png", 1);

		Realiti2D::Entity& Character = AddEntity("Character");
		Character.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(3.0f, 3.0f));
		Character.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Character/Idle/I01.png", 5);

		Realiti2D::AnimatedSprite& AnimationComponent = Character.AddComponent<Realiti2D::AnimatedSprite>();
		Realiti2D::AnimationClip* IdleAnimation = new Realiti2D::AnimationClip(6.0f, true);
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I01.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I02.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I03.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I04.png");
		IdleAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Idle/I05.png");
		AnimationComponent.AddAnimationClip("idle", IdleAnimation);
		
		Realiti2D::AnimationClip* RunningAnimation = new Realiti2D::AnimationClip(12.0f, true);
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run01.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run02.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run03.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run04.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run05.png");
		RunningAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Run/Run06.png");
		AnimationComponent.AddAnimationClip("run", RunningAnimation);

		Realiti2D::AnimationClip* JumpAnimation = new Realiti2D::AnimationClip(12.0f, false);
		JumpAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Jump/Jump01.png");
		JumpAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Jump/Jump02.png");
		JumpAnimation->AddAnimationTexture("assets/TreasureHunters/Character/Jump/Jump03.png");
		AnimationComponent.AddAnimationClip("jump", JumpAnimation);

		AnimationComponent.Play("idle");

		Character.AddComponent<Mover>();
		Character.AddComponent<PlayerController>();
	}
};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new JumpVMain(WIDTH, HEIGHT, "Jump V. Main");
}