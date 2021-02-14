#include <Realiti2D.h>
#define WIDTH 1024
#define HEIGHT 576

class JumpVMain : public Realiti2D::Application {
public:
	JumpVMain(const float& Width, const float& Height, const std::string Title) : Application(Width, Height, Title) {}
	~JumpVMain() {}

	void Start() override {
		DEBUG_INFO("Starting Jump V. Main");

		// SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);

		Realiti2D::Entity& Character = AddEntity("Character");
		Character.AddComponent<Realiti2D::Transform>(Realiti2D::Vector2(0.0f, 0.0f), 0.0f, Realiti2D::Vector2(4.0f, 4.0f));
		Character.AddComponent<Realiti2D::Sprite>("assets/character_idle.png", 5);
	}
};

Realiti2D::Application* Realiti2D::CreateApplication() {
	return new JumpVMain(WIDTH, HEIGHT, "Jump V. Main");
}