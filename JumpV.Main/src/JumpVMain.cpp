#include <Realiti2D.h>
#include "Mover.h"
#include "PlayerController.h"

// TODO: fix lol
// that's a big oof
#include "../thirdparty/dearimgui/imgui.h"
#include "../thirdparty/dearimgui/imgui_impl_sdl.h"
#include "../thirdparty/dearimgui/imgui_impl_opengl3.h"


#define WIDTH 1024
#define HEIGHT 576

// TODO
// 2. Collision raycast to handle the mover
// 3. Collision Layers?

class DebugWindow : public Realiti2D::ImGuiWindow {
public:
	void DrawWindow() override {
		ImGui::Begin("Player Controller variables");
		ImGui::InputFloat("Player Movement Speed", &(PlayerControllerRef->m_PlayerVelocityX));
		ImGui::InputFloat("Gravity", &(PlayerControllerRef->m_Gravity));

		/*
		if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {	
		}
		*/

		// ImGui::SliderFloat("Player Movement Speed", &(PlayerControllerRef->m_PlayerVelocityX), 0.0f, 250.0f);
		// ImGui::SliderFloat("Player Gravity", &(PlayerControllerRef->m_Gravity), 0.0f, 100.0f);
		ImGui::End();
	}

	PlayerController* PlayerControllerRef;
};

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
		Realiti2D::Entity& Clouds = AddEntity("Clouds");
		Clouds.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(64.0f, 160.0f), 0.0f, Realiti2D::Vector2(4.0f, 3.0f));
		Clouds.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Environment/Background/SmallCloud1.png", 2);

		Realiti2D::Entity& Character = AddEntity("Character");
		Character.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(3.0f, 3.0f));
		Character.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Character/Idle/I01.png", 5);
		Character.AddComponent<Realiti2D::BoxCollider>(Realiti2D::Vector2(-10.0f, -12.0f), Realiti2D::Vector2(10.0f, 12.0f));

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
		PlayerController& p = Character.AddComponent<PlayerController>();

		// ---------------------------------------------------------------
		for (int i = 0; i < 12; i++) {
			Realiti2D::Entity& Platform1 = AddEntity("Platform");
			float PlatformX = -500.0f + (i * 96.0f);
			Platform1.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(PlatformX, -256.0f), 0.0f, Realiti2D::Vector2(3.0f, 3.0f));
			Platform1.AddComponent<Realiti2D::Sprite>("assets/TreasureHunters/Environment/Background/AddSky.png", 2);
			Platform1.AddComponent<Realiti2D::BoxCollider>(Realiti2D::Vector2(-16.0f, -16.0f), Realiti2D::Vector2(16.0f, 16.0f));
		}

		// ------------------------------------------------------------------------------------------------------------------------
		DebugWindow* w = new DebugWindow();
		w->PlayerControllerRef = &p;
		Realiti2D::Renderer::s_Instance->PushDearImGuiWindow(w);
	}
};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new JumpVMain(WIDTH, HEIGHT, "Jump V. Main");
}