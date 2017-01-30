
#include <windows.h>
#include "Antons_maths_funcs.h"
#include "teapot.h" // teapot mesh
#include "Utilities.h"
#include "Particle.h"

using namespace std;

const float width = 1200, height = 950;
/*----------------------------------------------------------------------------
						MESH AND TEXTURE VARIABLES
----------------------------------------------------------------------------*/
/// this mesh is a dae file format but you should be able to use any other format too, obj is typically what is used
/// put the mesh in your project directory, or provide a filepath for it here
///for each new mesh, create new #define for the object, and the texture if required 
#define MONKEYHEAD_MESH	"../Meshes/suzanne.obj"
#define SPHERE_MESH		"../Meshes/polysphere.obj"
#define GEM_MESH		"../Meshes/gem.obj"
#define WALL_MESH		"../Meshes/wall.obj"
#define BEAR_MESH		"../Meshes/bear.obj"
#define LAMP_MESH		"../Meshes/lamp.obj"
#define TORCH_MESH		"../Meshes/torch.obj"
#define SIGN_MESH		"../Meshes/sign.obj"
#define BUDDHA_MESH		"../Meshes/buddha.dae"
#define PARTICLE_MESH	"../Meshes/particle.dae"
#define CUBE_MESH		"../Meshes/cube.obj"


#define BEAR_TEXTURE	"../Textures/bear.tga"
#define BEAR_TEXTURE2	"../Textures/bear2.tga"
#define CUBE_TEXTURE	"../Textures/me.png"
#define REFLECT_TEXTURE	"../Textures/reflection.png"
#define REFRACT_TEXTURE	"../Textures/refraction.png"
#define NORMAL_TEXTURE	"../Textures/normalmapped.png"
#define BRICK_TEXTURE	"../Textures/brickwall.jpg"
#define BRICK_NORMAL	"../Textures/brickwall_normal.jpg"



Mesh monkeyhead_object, torch_object, wall_object, cube, bear_object, signReflect_object, signRefract_object, signNormal_object;
Mesh gem_object, sphere_object, particle_object, cube_object;


//Cube Vertices for the Skybox
GLfloat vertices[] = {
	-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	-10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,

	-10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	-10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	-10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,

	-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f,  10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,

	10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
	10.0f,  10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,

	-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	-10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,

	-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	-10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f
}; 

/*----------------------------------------------------------------------------
								SHADER VARIABLES
----------------------------------------------------------------------------*/


#define SKY_VERT	"../Shaders/skyboxVertexShader.txt"
#define SKY_FRAG	"../Shaders/skyboxFragmentShader.txt"

#define NOTEXTURE_VERT	"../Shaders/noTextureVertexShader.txt"
#define NOTEXTURE_FRAG	"../Shaders/noTextureFragmentShader.txt"

#define REFLECTIVE_FRAG "../Shaders/reflectiveFragmentShader.txt"

#define FRESNEL_FRAG	"../Shaders/fresnelFragmentShader.txt"

#define TEXTURE_VERT	"../Shaders/textureVertexShader.txt"
#define TEXTURE_FRAG	"../Shaders/textureFragmentShader.txt"

#define NORMAL_VERT		"../Shaders/normalisedVertexShader.txt"
#define NORMAL_FRAG		"../Shaders/normalisedFragmentShader.txt"

#define MIRROR_VERT		"../Shaders/mirrorVertexShader.txt"
#define MIRROR_FRAG		"../Shaders/mirrorFragmentShader.txt"

#define TEST_VERT "../Shaders/testVertex.txt"
#define TEST_FRAG "../Shaders/testFragment.txt"

#define DEBUG_VERT "../Shaders/debugSkyboxVertex.txt"
#define DEBUG_FRAG "../Shaders/debugSkyboxFragment.txt"

GLuint noTextureShaderID, textureShaderID, cubeMapTextureID, refractiveShaderID, cubeMapShaderID;
GLuint testID, normalisedShaderID, reflectiveShaderID, multiTextureShaderID, mirrorShaderID, debugSkyboxID;
Shader shaderFactory;
/*----------------------------------------------------------------------------
							CAMERA VARIABLES
----------------------------------------------------------------------------*/

vec3 startingPos = { 0.0f, 0.0f, -20.0f };
vec3 startingFront = { 0.0f, 0.0f, 1.0f };
GLfloat pitCam = 0, yawCam = 0, rolCam = 0, frontCam = 0, sideCam = 0, speed = 1;
float rotateY = 50.0f, rotateLight = 0.0f;
Camera cam(startingPos, startingFront, vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.0f);
RigidBody body;
/*----------------------------------------------------------------------------
							OTHER VARIABLES
----------------------------------------------------------------------------*/

const char* atlas_image = "../freemono.png";
const char* atlas_meta = "../freemono.meta";

float fontSize = 25.0f;
int textID = -1;
void drawloop(mat4 view, mat4 proj, GLuint framebuffer);
bool torque = false;
bool force = false;
bool gravity = false;
bool force1 = false, force2 = false;

/*--------------------------------------------------------------------------*/

void init()
{
	if (!init_text_rendering(atlas_image, atlas_meta, width, height)) 
	{
		fprintf(stderr, "ERROR init text rendering\n");
		exit(1);
	}
	cam.setSensitivity(2.0f);
	//*************************//
	//*****Compile Shaders*****//
	//*************************//
	refractiveShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, FRESNEL_FRAG);
	noTextureShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, NOTEXTURE_FRAG);
	cubeMapShaderID = shaderFactory.CompileShader(SKY_VERT, SKY_FRAG);
	textureShaderID = shaderFactory.CompileShader(TEXTURE_VERT, TEXTURE_FRAG);
	normalisedShaderID = shaderFactory.CompileShader(NORMAL_VERT, NORMAL_FRAG);
	reflectiveShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, REFLECTIVE_FRAG);
	multiTextureShaderID = shaderFactory.CompileShader(TEXTURE_VERT, TEXTURE_FRAG);
	mirrorShaderID = shaderFactory.CompileShader(MIRROR_VERT, MIRROR_FRAG);
	debugSkyboxID = shaderFactory.CompileShader(DEBUG_VERT, DEBUG_FRAG);
	testID = shaderFactory.CompileShader(TEST_VERT, TEST_FRAG);
	//*********************//
	//*****Init Objects*****//
	//*********************//
	monkeyhead_object.init(MONKEYHEAD_MESH);
	cube.initCubeMap(vertices, 36, "desert");
	torch_object.init(TORCH_MESH);
	bear_object.init(BEAR_MESH, BEAR_TEXTURE, BEAR_TEXTURE2);
	wall_object.init(WALL_MESH, NULL, BRICK_NORMAL);
	signReflect_object.init(SIGN_MESH, REFLECT_TEXTURE);
	signRefract_object.init(SIGN_MESH, REFRACT_TEXTURE);
	signNormal_object.init(SIGN_MESH, NORMAL_TEXTURE);
	sphere_object.init(SPHERE_MESH);
	gem_object.init(GEM_MESH);
	particle_object.init(GEM_MESH);
	cube_object.init(CUBE_MESH, BEAR_TEXTURE);

	body = RigidBody(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), 5, 1.0, 1.0, 1.0, cube_object);
}

void display() 
{
	mat4 proj = perspective(87.0, (float)width / (float)(height), 1, 1000.0);
	mat4 view;
	glViewport(0, 0, width, height);
		
	view = look_at(cam.getPosition(), cam.getPosition() + cam.getFront(), cam.getUp());
	proj = perspective(60.0, (float)width / (float)height, 1, 1000.0);
	glViewport(0, 0, width, height);
	drawloop(view, proj, 0);
	draw_texts();
	glutSwapBuffers();
}

void updateScene() {
	static DWORD  last_frame;	//time when last frame was drawn
	static DWORD last_timer = 0;	//time when timer was updated
	DWORD  curr_time = timeGetTime();//for frame Rate Stuff.
	static bool first = true;
	if (first)
	{
		last_frame = curr_time;
		first = false;
	}
	float  delta = (curr_time - last_frame) * 0.001f;
	if (delta >= 0.03f) 
	{
		last_frame = curr_time;
		glutPostRedisplay();
		rotateLight = rotateLight + 0.01f;
		if (rotateLight >= 360.0f)
			rotateLight = 0.0f;

		body.force = vec3(0.0, 0.0, 0.0);
		body.torque = vec3(0.0, 0.0, 0.0);
		body.addForce(vec3(50.0, 0.0, 0.0)*force1, vec3(0.5, 0.0, 0.5));
		body.addForce(vec3(2.0, 50.0, 0.0)*force2, vec3(0.0, 1.0, 0.0));
		if (gravity)
		{
			body.addForce(vec3(0.0, -98.0, 0.0), vec3(0.0, -1.0, 0.0));
		}
		if (torque)
			body.torque = vec3(50.0, 0.0, 0.0);
		if (force)
			body.force = vec3(0.0, 50.0, 0.0);
		cam.movForward(frontCam*speed);
		cam.movRight(sideCam*speed);
		cam.changeFront(pitCam, yawCam, rolCam);

		body.resolveForce(delta);
		string values = "Force: [" + to_string(body.force.v[0]) + ", " + to_string(body.force.v[1]) + ", " + to_string(body.force.v[2]) + "]\n";
		values += "Torque: [" + to_string(body.torque.v[0]) + ", " + to_string(body.torque.v[1]) + ", " + to_string(body.torque.v[2]) + "]\n";
		values += "Linear Momentum: [" + to_string(body.linMomentum.v[0]) + ", " + to_string(body.linMomentum.v[1]) + ", " + to_string(body.linMomentum.v[2]) + "]\n";
		values += "Angular Momentum: [" + to_string(body.angMomentum.v[0]) + ", " + to_string(body.angMomentum.v[1]) + ", " + to_string(body.angMomentum.v[2]) + "]\n";
		values += "\n";
		values += "Orientation Matrix: \n|"+ to_string(body.orientationMat.m[0]) + ", " + to_string(body.orientationMat.m[4]) + ", " + to_string(body.orientationMat.m[8]) + "|\n";
		values += "|" + to_string(body.orientationMat.m[1]) + ", " + to_string(body.orientationMat.m[5]) + ", " + to_string(body.orientationMat.m[9]) + "|\n";
		values += "|" + to_string(body.orientationMat.m[2]) + ", " + to_string(body.orientationMat.m[6]) + ", " + to_string(body.orientationMat.m[10]) + "|\n";
		values += "\n";

		values += "Vertices: \n";
		vector<float> vertices;
		for (int i = 0; i < body.mesh.newpoints.size(); i=i+3)
		{
			vertices.push_back(body.mesh.newpoints[i]);
			vertices.push_back(body.mesh.newpoints[i+1]);
			vertices.push_back(body.mesh.newpoints[i+2]);
			bool add = true;
			for (int j = 0; j < i; j=j+3)
			{
				if ((vertices[i] == vertices[j]) && (vertices[i+1] == vertices[j+1]) && (vertices[i+2] == vertices[j+2]))
				{
					add = false;
					break;
				}
			}
			if (add)
				values += "[" + to_string(body.mesh.newpoints[i]) + "," + to_string(body.mesh.newpoints[i+1]) + "," + to_string(body.mesh.newpoints[i+2]) + "]\n";
		}
		values += "\n";

		update_text(textID, values.c_str());
	}
	
}

#pragma region INPUT FUNCTIONS

void keypress(unsigned char key, int x, int y) 
{
	if (key == (char)27)	//Pressing Escape Ends the game
	{
		exit(0);
	}
	else if (key == 'w' || key == 'W')
		frontCam = 1;
	else if ((key == 's') || (key == 'S'))
		frontCam = -1;
	if ((key == 'a') || (key == 'A'))
		sideCam = -1;
	else if ((key == 'd') || (key == 'D'))
		sideCam = 1;
	if ((key == 't') || (key == 'T'))
		torque = true;
	if ((key == 'f') || (key == 'F'))
		force = true;
	if (key == '1')
		force1 = true;
	if (key == '2')
		force2 = true;
}

void keypressUp(unsigned char key, int x, int y)
{
	if ((key == 'w') || (key == 'W'))
		frontCam = 0;
	else if ((key == 's') || (key == 'S'))
		frontCam = 0;
	if ((key == 'a') || (key == 'A'))
		sideCam = 0;
	else if ((key == 'd') || (key == 'D'))
		sideCam = 0;
	if ((key == 't') || (key == 'T'))
		torque = false;
	if ((key == 'f') || (key == 'F'))
		force = false;
	if (key == '1')
		force1 = false;
	if (key == '2')
		force2 = false;
	if (key == ' ')
	{
		gravity = false;
		body.reset(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
	}
	else if (key == '\\')
	{
		gravity = false;
		body.reset(vec3(0.0, 0.0, 0.0), vec3(500.0, 500.0, 500.0));
	}
	else if (key == 'g')
	{
		gravity = true;
		body.reset(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
	}
}

void specialKeypress(int key, int x, int y) 
{
	switch (key)
	{
	case (GLUT_KEY_SHIFT_L):
	case (GLUT_KEY_SHIFT_R):
		speed = 4;
		break;
	case (GLUT_KEY_LEFT):
		yawCam = -1;
		break;
	case (GLUT_KEY_RIGHT):
		yawCam = 1;
		break;
	case (GLUT_KEY_UP):
		pitCam = 1;
		break;
	case (GLUT_KEY_DOWN):
		pitCam = -1;
		break;
	}
}

void specialKeypressUp(int key, int x, int y) 
{
	switch (key)
	{
	case (GLUT_KEY_SHIFT_L):
	case (GLUT_KEY_SHIFT_R):
		speed = 1;
		break;
	case (GLUT_KEY_LEFT):
		yawCam = 0;
		break;
	case (GLUT_KEY_RIGHT):
		yawCam = 0;
		break;
	case (GLUT_KEY_UP):
		pitCam = 0;
		break;
	case (GLUT_KEY_DOWN):
		pitCam = 0;
		break;
	}
}

void (mouse)(int x, int y)
{
	
}

#pragma endregion INPUT FUNCTIONS

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("GameApp");
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);


	// Tell glut where the display function is
	glutWarpPointer(width / 2, height / 2);
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);

	// Input Function Initialisers //
	glutKeyboardFunc(keypress);
	glutPassiveMotionFunc(mouse);
	glutSpecialFunc(specialKeypress);
	glutSpecialUpFunc(specialKeypressUp);
	glutKeyboardUpFunc(keypressUp);

	// A call to glewInit() must be done after glut is initialized!
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	init();
	textID = add_text("",
		-0.95, 0.9, fontSize, 1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}

void drawloop(mat4 view, mat4 proj, GLuint framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);								// enable depth-testing
	glDepthFunc(GL_LESS);									// depth-testing interprets a smaller value as "closer"
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear the color and buffer bits to make a clean slate
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);					//Create a background


	mat4 model;
	model = identity_mat4();
	// light properties
	vec3 Ls = vec3(0.5f, 0.5f, 0.5f);	//Specular Reflected Light
	vec3 Ld = vec3(0.99f, 0.99f, 0.99f);	//Diffuse Surface Reflectance
	vec3 La = vec3(1.0f, 1.0f, 1.0f);	//Ambient Reflected Light
	vec3 light = vec3(5 * sin(rotateLight), 10, -5.0f*cos(rotateLight));//light source location
	vec3 coneDirection = light + vec3(0.0f, -1.0f, 0.0f);
	float coneAngle = 10.0f;
	// object colour
	vec3 Ks = vec3(0.1f, 0.1f, 0.1f); // specular reflectance
	vec3 Kd = BROWN;
	vec3 Ka = vec3(0.05f, 0.05f, 0.05f); // ambient reflectance
	float specular_exponent = 0.5f; //specular exponent - size of the specular elements

	model = identity_mat4();
	drawCubeMap(cubeMapShaderID, cube.tex, view, proj, model, Ld, La, cam, cube, GL_TRIANGLES);

	model = scale(identity_mat4(), vec3(0.01f, 0.01f, 0.01f));
	model = translate(model, light);
	drawObject(noTextureShaderID, view, proj, model, light, Ls, La, Ld, Ks, Ka, WHITE, specular_exponent, cam, cube, coneAngle, coneDirection, GL_TRIANGLES);

	model = translate(identity_mat4(), vec3(0.0f, -6.3f, 0.0f));
	if(!gravity)
		drawObject(noTextureShaderID, view, proj, model, light, Ls, La, Ld, Ks, Ka, Kd, specular_exponent, cam, torch_object, coneAngle, coneDirection, GL_QUADS);


	model = rotate_z_deg(identity_mat4(), 90.0f);
	model = translate(model, vec3(-7.5, -6.5f, -7.5));
	mat4 root = model;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			model = translate(root, vec3(15.0f*i, 0.0, 0.0));
			model = translate(model, vec3(0.0, 0.0, 15.0f*j));
			if (!gravity)
				drawObject(normalisedShaderID, view, proj, model, vec3(-light.v[0], -light.v[1], -light.v[2]), Ls, La, Ld, Ks, Ka, GREY, 50.0f, cam, wall_object, coneAngle, coneDirection, GL_TRIANGLES);
		}
	}

	//model = body.orientationMat;
	//model = translate(model, body.position);
	drawObject(noTextureShaderID, view, proj, identity_mat4(), vec3(-light.v[0], -light.v[1], -light.v[2]), Ls, La, Ld, Ks, Ka, BLUE, 50.0f, cam, body.mesh, coneAngle, coneDirection, GL_QUADS);
}