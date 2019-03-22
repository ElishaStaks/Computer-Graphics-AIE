#pragma once
// access to GLF window
struct GLFWwindow;

namespace eli {

	// Pure virtual bass class that wraps up an apllication for us
	// We derive our own applications from this class
	class Application
	{
	public:
		Application();
		virtual ~Application();

		// Add these functions must be implemented by derived classes
		virtual bool startUp() = 0;
		virtual void shutDown() = 0;
		virtual bool update(float deltaTime) = 0;
		virtual void draw() = 0;

	protected:

		GLFWwindow* m_window;
		bool m_gameOver;
	};
} // namespace app