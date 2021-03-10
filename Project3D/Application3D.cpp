#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D()
{
}

Application3D::~Application3D()
{
}

bool Application3D::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	return true;
}

void Application3D::shutdown()
{
	Gizmos::destroy();
}


void Application3D::update(float deltaTime)
{
	// query time since application started
	float time = getTime();

	
	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	


	mat4 t = glm::rotate(mat4(1), time * 0.45f, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(0, 0, 0, 1);


	Gizmos::addAABBFilled(vec3(0), vec3(1), glm::vec4(1, 0, 0, 1), &t);

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);

	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}

glm::mat4 RotateY(float rads)
{
	return mat4(
		1.f, 0.f, 0.f, 0.f,
		0.f, cos(rads), -sin(rads), 0.f,
		0.f, sin(rads), cos(rads), 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}



void Application3D::SolarSystem(float dt)
{

	
	
	


}






