#include <Amber.h>

class Sandbox : public Amber::Application
{
public:
	Sandbox() {
	}
	
	~Sandbox() {

	}

};
 
Amber::Application* Amber::CreateApplication() {

	return new Sandbox();

}