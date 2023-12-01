#include "Application.h"

Application::Application()
{

}
Application::~Application()
{

}
void Application::setupLighting(glm::vec3 lightPosition)
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3(lightPosition);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}
void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
}

void Application::InitCamera()
{
	posCamX = 5.0f;
	posCamY = 1.0f;
	posCamZ = 3.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.0025;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}
void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}
void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();
	shader2 = new Shader("vertexShader.vert", "fragmentShader.frag");
	shader2->Init();

	// Create cube diffuse texture and specular texture
	cubeDiffTex = new Texture("crate_diffusemap.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("crate_specularmap.png");
	cubeSpecTex->Init();

	// Create instance of cube
	cube = new Cube(shader, cubeDiffTex, cubeSpecTex);
	cube->Init();
	cube->SetScale(0.2f, 0.2f, 0.2f);

	// setup camera
	InitCamera();

	// setup perspective 
	setupPerspective();

	// setup lighting
	glm::vec3 specificLightPos = glm::vec3(5.0f, 0.0f, -5.0f);
	setupLighting(specificLightPos);

	// setup plane
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	BuildColoredPlane("marble.png");

	///////////////////////////////////////////////////////////////////////////////////////////////

	/*objek*/

	//billiard
	////mejabilliard
	billiardTex = new Texture("biliard.png");
	billiardTex->Init();
	billiard = new Cube(shader, billiardTex, billiardTex);
	billiard->Init();
	billiard->SetScale(0.2f, 0.2f, 0.2f);
	////mejabilliard
	mejabilliardTex = new Texture("mejabilliard.png");
	mejabilliardTex->Init();
	mejabilliard = new Cube(shader, mejabilliardTex, mejabilliardTex);
	mejabilliard->Init();
	mejabilliard->SetScale(0.2f, 0.2f, 0.2f);
	////kakibilliard
	kakibilliardTex = new Texture("kaki.jpeg");
	kakibilliardTex->Init();
	kakibilliard = new Cube(shader, kakibilliardTex, kakibilliardTex);
	kakibilliard->Init();
	billiard->SetScale(0.2f, 0.2f, 0.2f);

	//sofa
	//// dudukan dan sandaransofa
	sofaTex = new Texture("sofa.jpeg");
	sofaTex->Init();
	sofa = new Cube(shader, sofaTex, sofaTex);
	sofa->Init();
	sofa->SetScale(0.2f, 0.2f, 0.2f);
	////kaki sofa
	kakisofaTex = new Texture("kaki.jpeg");
	kakisofaTex->Init();
	kakisofa = new Cube(shader, kakisofaTex, kakisofaTex);
	kakisofa->Init();
	kakisofa->SetScale(0.2f, 0.2f, 0.2f);

	//pintu
	pintuTex = new Texture("pintu.jpeg");
	pintuTex->Init();
	pintu = new Cube(shader, pintuTex, pintuTex);
	pintu->Init();
	pintu->SetScale(0.2f, 0.2f, 0.2f);

	// vending machine
	vendingmachineTex = new Texture("vendingmachine.jpeg");
	vendingmachineTex->Init();
	vendingmachine = new Cube(shader, vendingmachineTex, vendingmachineTex);
	vendingmachine->Init();
	vendingmachine->SetScale(0.2f, 0.2f, 0.2f);

	kotakvendingmachineTex = new Texture("kotakvendingmachine.png");
	kotakvendingmachineTex->Init();
	kotakvendingmachine = new Cube(shader, kotakvendingmachineTex, kotakvendingmachineTex);
	kotakvendingmachine->Init();
	kotakvendingmachine->SetScale(0.2f, 0.2f, 0.2f);

	//resepsionis
	resepsionisTex = new Texture("resepsionis.png");
	resepsionisTex->Init();
	resepsionis = new Cube(shader, resepsionisTex, resepsionisTex);
	resepsionis->Init();
	resepsionis->SetScale(0.2f, 0.2f, 0.2f);

	mejaresepsionisTex = new Texture("marmer.png");
	mejaresepsionisTex->Init();
	mejaresepsionis = new Cube(shader, mejaresepsionisTex, mejaresepsionisTex);
	mejaresepsionis->Init();
	mejaresepsionis->SetScale(0.2f, 0.2f, 0.2f);

	engselTex = new Texture("kaki.jpeg");
	engselTex->Init();
	engsel = new Cube(shader, engselTex, engselTex);
	engsel->Init();
	engsel->SetScale(0.2f, 0.2f, 0.2f);

	//monitor
	monitorTex = new Texture("kaki.jpeg");
	monitorTex->Init();
	monitor = new Cube(shader, monitorTex, monitorTex);
	monitor->Init();
	monitor->SetScale(0.2f, 0.2f, 0.2f);
	//lcd monitor
	lcdmonitorTex = new Texture("lcd.png");
	lcdmonitorTex->Init();
	lcdmonitor = new Cube(shader, lcdmonitorTex, lcdmonitorTex);
	lcdmonitor->Init();
	lcdmonitor->SetScale(0.2f, 0.2f, 0.2f);

	//keyboard
	keyboardTex = new Texture("keyboard.png");
	keyboardTex->Init();
	keyboard = new Cube(shader, keyboardTex, keyboardTex);
	keyboard->Init();
	keyboard->SetScale(0.2f, 0.2f, 0.2f);

	//mouse
	mouseTex = new Texture("mouse.png");
	mouseTex->Init();
	mouse = new Cube(shader, mouseTex, mouseTex);
	mouse->Init();
	mouse->SetScale(0.2f, 0.2f, 0.2f);


	//lukisan 1 dan 2
	lukisan1Tex = new Texture("lukisan1.png");
	lukisan1Tex->Init();
	lukisan1 = new Cube(shader, lukisan1Tex, lukisan1Tex);
	lukisan1->Init();
	lukisan1->SetScale(0.2f, 0.2f, 0.2f);

	lukisan2Tex = new Texture("lukisan2.png");
	lukisan2Tex->Init();
	lukisan2 = new Cube(shader, lukisan2Tex, lukisan2Tex);
	lukisan2->Init();
	lukisan2->SetScale(0.2f, 0.2f, 0.2f);

	lukisan3Tex = new Texture("lukisan3.png");
	lukisan3Tex->Init();
	lukisan3 = new Cube(shader, lukisan3Tex, lukisan3Tex);
	lukisan3->Init();
	lukisan3->SetScale(0.2f, 0.2f, 0.2f);

	lukisan4Tex = new Texture("lukisan4.png");
	lukisan4Tex->Init();
	lukisan4 = new Cube(shader, lukisan4Tex, lukisan4Tex);
	lukisan4->Init();
	lukisan4->SetScale(0.2f, 0.2f, 0.2f);

	//jam
	jamTex = new Texture("jam.jpeg");
	jamTex->Init();
	jam = new Cube(shader, jamTex, jamTex);
	jam->Init();
	jam->SetScale(0.2f, 0.2f, 0.2f);

	//AC
	acTex = new Texture("AC.png");
	acTex->Init();
	ac = new Cube(shader, acTex, acTex);
	ac->Init();
	ac->SetScale(0.2f, 0.2f, 0.2f);

	depanacTex = new Texture("depanAC.png");
	depanacTex->Init();
	depanac = new Cube(shader, depanacTex, depanacTex);
	depanac->Init();
	depanac->SetScale(0.2f, 0.2f, 0.2f);

	//nomor meja
	////1
	nomor1Tex = new Texture("1.jpeg");
	nomor1Tex->Init();
	nomor1 = new Cube(shader, nomor1Tex, nomor1Tex);
	nomor1->Init();
	nomor1->SetScale(0.2f, 0.2f, 0.2f);
	////2
	nomor2Tex = new Texture("2.jpeg");
	nomor2Tex->Init();
	nomor2 = new Cube(shader, nomor2Tex, nomor2Tex);
	nomor2->Init();
	nomor2->SetScale(0.2f, 0.2f, 0.2f);
	////3
	nomor3Tex = new Texture("3.jpeg");
	nomor3Tex->Init();
	nomor3 = new Cube(shader, nomor3Tex, nomor3Tex);
	nomor3->Init();
	nomor3->SetScale(0.2f, 0.2f, 0.2f);
	////4
	nomor4Tex = new Texture("4.jpeg");
	nomor4Tex->Init();
	nomor4 = new Cube(shader, nomor4Tex, nomor4Tex);
	nomor4->Init();
	nomor4->SetScale(0.2f, 0.2f, 0.2f);

	//lampu
	lampuTex = new Texture("lampu.png");
	lampuTex->Init();
	lampu = new Cube(shader, lampuTex, lampuTex);
	lampu->Init();
	lampu->SetScale(0.2f, 0.2f, 0.2f);

	////standlampu
	standlampuTex = new Texture("standlampu.png");
	standlampuTex->Init();
	standlampu = new Cube(shader, standlampuTex, standlampuTex);
	standlampu->Init();
	standlampu->SetScale(0.2f, 0.2f, 0.2f);
		
	/*Ruangan*/
	////dinding
	dindingTex = new Texture("dinding.png");
	dinding = new Cube(shader, dindingTex, dindingTex);
	dinding->Init();
	dinding->SetScale(0.2f, 0.2f, 0.2f);
	////atap 
	atapTex = new Texture("atap.png");
	atap = new Cube(shader, atapTex, atapTex);
	atap->Init();
	atap->SetScale(0.2f, 0.2f, 0.2f);

	///////////////////////////////////////////////////////////////////////////////////////////////
}
void Application::DeInit()
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	/*objek*/
	delete cube, 
	delete billiard, mejabilliard, kakibilliard,
	delete sofa, kakisofa, 
	delete pintu,
	delete vendingmachine, kotakvendingmachine,
	delete resepsionis,mejaresepsionis, engsel,
	delete lukisan1, lukisan2, lukisan3, lukisan4,
	delete jam,
	delete nomor1, nomor2, nomor3, nomor4,
	delete ac,depanac,
	delete monitor, lcdmonitor, keyboard, mouse,
	delete lampu, standlampu;

	/*ruangan*/
	delete dinding, atap;

	/*Plane*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	///////////////////////////////////////////////////////////////////////////////////////////////


}
void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 1.5f) / 1000);
	cube->SetRotation(angle, 0, 1, 0);
}
void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	setupPerspective();

	DrawColoredPlane();

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	/*objek*/

	//billiard	
	////meja biliard 1 (x=0.z=0)
	billiard->SetPosition(-0.105, -6555.0, -1.05);
	billiard->SetScale(6.5f, 0.0001f, 4.5f);
	billiard->Draw();
	////meja bawah billiard 1
	kakibilliard->SetPosition(-0.105, -2.6, -1.32);
	kakibilliard->SetScale(5.63f, 0.5f, 3.63f);
	kakibilliard->Draw();
	////meja atas billiard 1
	mejabilliard->SetPosition(-0.105, -2.14, -1.05);
	mejabilliard->SetScale(6.5f, 0.4f, 4.5f);
	mejabilliard->Draw();
	////kaki billiard 1
	for (int i = 0; i < 4; i++) {
		if (i > 1) {
			kakibilliard->SetPosition(-8.0 + (i - 2) * 13, -1.2, -16);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
		else {
			kakibilliard->SetPosition(-8.0 + i * 13, -1.2, -8);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
	}
	////meja biliard 2 (z)
	billiard->SetPosition(-0.105, -6555.0, -3.6);
	billiard->SetScale(6.5f, 0.0001f, 4.5f);
	billiard->Draw();
	////meja bawah billiard 2
	kakibilliard->SetPosition(-0.105, -2.6, -4.46);
	kakibilliard->SetScale(5.63f, 0.5f, 3.63f);
	kakibilliard->Draw();
	////meja atas billiard 2
	mejabilliard->SetPosition(-0.105, -2.14, -3.6);
	mejabilliard->SetScale(6.5f, 0.4f, 4.5f);
	mejabilliard->Draw();
	////kaki billiard 2 
	for (int i = 0; i < 4; i++) {
		if (i > 1) {
			kakibilliard->SetPosition(-8.0 + (i - 2) * 13, -1.2, -44.5);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
		else {
			kakibilliard->SetPosition(-8.0 + i * 13, -1.2, -36.5);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
	}
	////meja biliard 3 (x)
	billiard->SetPosition(1.932, -6555.0, -1.05);
	billiard->SetScale(6.5f, 0.0001f, 4.5f);
	billiard->Draw();
	////meja bawah billiard 3
	kakibilliard->SetPosition(2.237, -2.6, -1.32);
	kakibilliard->SetScale(5.63f, 0.5f, 3.63f);
	kakibilliard->Draw();
	////meja atas billiard 3
	mejabilliard->SetPosition(1.932, -2.14, -1.05);
	mejabilliard->SetScale(6.5f, 0.4f, 4.5f);
	mejabilliard->Draw();
	////kaki billiard 3
	for (int i = 0; i < 4; i++) {
		if (i > 1) {
			kakibilliard->SetPosition(25.0 + (i - 2) * 13, -1.2, -16);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
		else {
			kakibilliard->SetPosition(25.0 + i * 13, -1.2, -8);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
	}
	////meja biliard 4 (x(meja3),z(meja2))
	billiard->SetPosition(1.932, -6555.0, -3.6);
	billiard->SetScale(6.5f, 0.0001f, 4.5f);
	billiard->Draw();
	////meja bawah billiard 4
	kakibilliard->SetPosition(2.237, -2.6, -4.46);
	kakibilliard->SetScale(5.63f, 0.5f, 3.63f);
	kakibilliard->Draw();
	////meja atas billiard 4
	mejabilliard->SetPosition(1.932, -2.14, -3.6);
	mejabilliard->SetScale(6.5f, 0.4f, 4.5f);
	mejabilliard->Draw();
	////kaki billiard 4 
	for (int i = 0; i < 4; i++) {
		if (i > 1) {
			kakibilliard->SetPosition(25.0 + (i - 2) * 13, -1.2, -44.5);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
		else {
			kakibilliard->SetPosition(25.0 + i * 13, -1.2, -36.5);
			kakibilliard->SetScale(0.4f, 1.5f, 0.4f);
			kakibilliard->Draw();
		}
	}

	//sofa
	////dudukan sofa 1
	sofa->SetPosition(-0.125, -2.9, -11.3);
	sofa->SetScale(5.0f, 0.5f, 2.0f); 
	sofa->Draw();
	////Sandaran Sofa 1
	sofa->SetPosition(-0.125, -0.35, -46.71);
	sofa->SetScale(5.0f, 2.0f, 0.5f); 
	sofa->Draw();
	////kaki Sofa Kiri 1
	kakisofa->SetPosition(-6.75, -0.75, -11.3);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f); 
	kakisofa->Draw();
	////kaki Sofa Kanan 1
	kakisofa->SetPosition(4.25, -0.75, -11.3);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f); 
	kakisofa->Draw();
	////dudukan sofa 2
	sofa->SetPosition(2.525, -2.9, -11.3);
	sofa->SetScale(5.0f, 0.5f, 2.0f);
	sofa->Draw();
	////Sandaran Sofa
	sofa->SetPosition(2.525, -0.35, -46.71);
	sofa->SetScale(5.0f, 2.0f, 0.5f);
	sofa->Draw();
	////kaki Sofa Kiri 
	kakisofa->SetPosition(19.75, -0.75, -11.3);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();
	////kaki Sofa Kanan 
	kakisofa->SetPosition(30.75, -0.75, -11.3);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();
	////dudukan sofa 3
	sofa->SetPosition(-0.125, -2.9, 0.8);
	sofa->SetScale(5.0f, 0.5f, 2.0f);
	sofa->Draw();
	////Sandaran Sofa 3
	sofa->SetPosition(-0.125, -0.35, 4.71);
	sofa->SetScale(5.0f, 2.0f, 0.5f);
	sofa->Draw();
	////kaki Sofa Kiri 3
	kakisofa->SetPosition(-6.75, -0.75, 0.8);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();
	////kaki Sofa Kanan 3
	kakisofa->SetPosition(4.25, -0.75, 0.8);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();
	////dudukan sofa 4
	sofa->SetPosition(2.525, -2.9, 0.8);
	sofa->SetScale(5.0f, 0.5f, 2.0f);
	sofa->Draw();
	////Sandaran Sofa 4
	sofa->SetPosition(2.525, -0.35, 4.71);
	sofa->SetScale(5.0f, 2.0f, 0.5f);
	sofa->Draw();
	////kaki Sofa Kiri 4
	kakisofa->SetPosition(19.75, -0.75, 0.8);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();
	////kaki Sofa Kanan 4
	kakisofa->SetPosition(30.75, -0.75, 0.8);
	kakisofa->SetScale(0.5f, 2.0f, 2.0f);
	kakisofa->Draw();

	//pintu
	pintu->SetPosition(-44.7, 0.075, -2.120);
	pintu->SetScale(0.2f, 6.0f, 5.0f);
	pintu->Draw();

	////vendingmachine
	////kotak
	kotakvendingmachine->SetPosition(1.5, 0.035, -6.55);
	kotakvendingmachine->SetScale(4.0f, 5.5, 3.6f);
	kotakvendingmachine->Draw();
	////depan
	vendingmachine->SetPosition(1.5, 0.035, -21779.55);
	vendingmachine->SetScale(4.0f, 5.5, 0.001f);
	vendingmachine->Draw();

	//resepsionis
	////bawah meja
	resepsionis->SetPosition(35.0, -0.5, -2.85);
	resepsionis->SetScale(0.5f, 2.5f, 3.7f);
	resepsionis->Draw();

	resepsionis->SetPosition(5.26, -0.5, -24.3);
	resepsionis->SetScale(3.625f, 2.5f, 0.5f);
	resepsionis->Draw();

	resepsionis->SetPosition(9.58, -0.5, -17.85);
	resepsionis->SetScale(1.9f, 2.5f, 0.5f);
	resepsionis->Draw();

	////atas meja
	mejaresepsionis->SetPosition(23.15, 0.5, -3.9);
	mejaresepsionis->SetScale(0.75f, 0.25f, 2.7f);
	mejaresepsionis->Draw();

	mejaresepsionis->SetPosition(4.855, 0.5, -16.35);
	mejaresepsionis->SetScale(3.9f, 0.25f, 0.75f);
	mejaresepsionis->Draw();

	mejaresepsionis->SetPosition(8.59, 0.5, -11.74);
	mejaresepsionis->SetScale(2.1f, 0.25f, 0.75f);
	mejaresepsionis->Draw();

	////meja resepsionis
	mejaresepsionis->SetPosition(24.15, -0.0, -3.9);
	mejaresepsionis->SetScale(0.75f, 0.25f, 2.7f);
	mejaresepsionis->Draw();

	////pintu kecil resepsionis
	resepsionis->SetPosition(14.75, -0.5, -89.55);
	resepsionis->SetScale(1.35f, 1.75f, 0.1f);
	resepsionis->Draw();

	////engsel pintu resepsionis
	engsel->SetPosition(96.0, -4.0, -89.5);
	engsel->SetScale(0.2f, 0.1f, 0.1f);
	engsel->Draw();

	engsel->SetPosition(96.0, -14.0, -89.5);
	engsel->SetScale(0.2f, 0.1f, 0.1f);
	engsel->Draw();

	//jam
	jam->SetPosition(20840.55, 5.0, -10.5);
	jam->SetScale(0.001f, 1.0f, 1.0f);
	jam->Draw();

	//lukisan
	lukisan1->SetPosition(20840.55, 0.635, -4.0);
	lukisan1->SetScale(0.001f, 5.5, 4.0f);
	lukisan1->Draw();

	lukisan2->SetPosition(20840.55, 0.635, -1.2);
	lukisan2->SetScale(0.001f, 5.5, 4.0f);
	lukisan2->Draw();

	lukisan3->SetPosition(-8850, 0.635, -4.0);
	lukisan3->SetScale(0.001f, 5.5, 4.0f);
	lukisan3->Draw();

	lukisan4->SetPosition(-8850, 0.635, -1.2);
	lukisan4->SetScale(0.001f, 5.5, 4.0f);
	lukisan4->Draw();

	//nomor meja
	////1
	nomor1->SetPosition(-0.5, 3.0, -25350.0);
	nomor1->SetScale(1.0f, 1.5f, 0.001f);
	nomor1->Draw();
	////2
	nomor2->SetPosition(13.0, 3.0, -25350.0);
	nomor2->SetScale(1.0f, 1.5f, 0.001f);
	nomor2->Draw();
	////3
	nomor3->SetPosition(13.0, 3.0, 4350.0);
	nomor3->SetScale(1.0f, 1.5f, 0.001f);
	nomor3->Draw();
	////4
	nomor4->SetPosition(-0.5, 3.0, 4350.0);
	nomor4->SetScale(1.0f, 1.5f, 0.001f);
	nomor4->Draw();

	//monitor
	////Dudukan Monitor
	monitor->SetPosition(34.8, 5.5, -21);
	monitor->SetScale(0.5f, 0.05f, 0.5f);
	monitor->Draw();
	////Penyangga Monitor
	monitor->SetPosition(116, 0.4, -35);
	monitor->SetScale(0.15f, 1.0f, 0.3f);
	monitor->Draw();
	////Layar Monitor
	monitor->SetPosition(117, 1.0, -7);
	monitor->SetScale(0.15f, 1.0f, 1.5f);
	monitor->Draw();
	////lcd monitor
	lcdmonitor->SetPosition(17630, 1.25, -8.075);
	lcdmonitor->SetScale(0.001f, 0.8f, 1.3f);
	lcdmonitor->Draw();

	//Keyboard
	keyboard->SetPosition(36.3, 3.0, -10.25);
	keyboard->SetScale(0.5f, 0.05f, 1.0f);
	keyboard->Draw();

	//Mouse
	mouse->SetPosition(60.5, 3.0, -55.25);
	mouse->SetScale(0.3f, 0.05f, 0.2f);
	mouse->Draw();

	//lampu
	//Dudukan Lampu 1
	standlampu->SetPosition(-4.0, -9.6, -13.5);
	standlampu->SetScale(1.75f, 0.25f, 1.75f);
	standlampu->Draw();
	//Tiang Lampu 1
	standlampu->SetPosition(-28, -0.1, -94.5);
	standlampu->SetScale(0.25f, 3.75f, 0.25f);
	standlampu->Draw();
	//Lampu 1
	lampu->SetPosition(-4.7, 1.5, -15.75);
	lampu->SetScale(1.5f, 1.5f, 1.5f);
	lampu->Draw();

	//Dudukan Lampu 2
	standlampu->SetPosition(10.925, -9.6, -13.5);
	standlampu->SetScale(1.75f, 0.25f, 1.75f);
	standlampu->Draw();
	//Tiang Lampu 2
	standlampu->SetPosition(76.5, -0.1, -94.5);
	standlampu->SetScale(0.25f, 3.75f, 0.25f);
	standlampu->Draw();
	//Lampu 2
	lampu->SetPosition(12.75, 1.5, -15.75);
	lampu->SetScale(1.5f, 1.5f, 1.5f);
	lampu->Draw();

	////Dudukan Lampu 3
	standlampu->SetPosition(10.925, -9.6, 1.45);
	standlampu->SetScale(1.75f, 0.25f, 1.75f);
	standlampu->Draw();
	//Tiang Lampu 3
	standlampu->SetPosition(76.5, -0.1, 10.25);
	standlampu->SetScale(0.25f, 3.75f, 0.25f);
	standlampu->Draw();
	//Lampu 3
	lampu->SetPosition(12.75, 1.5, 1.7);
	lampu->SetScale(1.5f, 1.5f, 1.5f);
	lampu->Draw();

	//Dudukan Lampu 4
	standlampu->SetPosition(-4.0, -9.6, 1.45);
	standlampu->SetScale(1.75f, 0.25f, 1.75f);
	standlampu->Draw();
	//Tiang Lampu 4
	standlampu->SetPosition(-28, -0.1, 10.25);
	standlampu->SetScale(0.25f, 3.75f, 0.25f);
	standlampu->Draw();
	//Lampu 4
	lampu->SetPosition(-4.7, 1.5, 1.7);
	lampu->SetScale(1.5f, 1.5f, 1.5f);
	lampu->Draw();

	//AC
	ac->SetPosition(-13.65, 5.8, -2.820);
	ac->SetScale(0.625f, 0.75f, 3.75f);
	ac->Draw();
	////depan
	depanac->SetPosition(-8215, 5.8, -2.820);
	depanac->SetScale(0.001f, 0.75f, 3.75f);
	depanac->Draw();


	////kipas angin
	//cube->SetPosition(60.0, 3.04, -105);
	//cube->SetScale(0.1f, 2.5f, 0.1f);
	//cube->Draw();

	//cube->SetPosition(9.615, 41.8, -16.8);
	//cube->SetScale(0.625f, 0.15f, 0.625f);
	//cube->Draw();

	//////bilah
	//cube->SetPosition(2.6075, 62.625, -21.0);
	//cube->SetScale(3.0f, 0.1f, 0.5f);
	//cube->Draw();
	//cube->SetPosition(1.399, 62.625, -21.0);
	//cube->SetScale(3.0f, 0.1f, 0.5f);
	//cube->Draw();

	//cube->SetPosition(12.025, 62.625, -2.895);
	//cube->SetScale(0.5f, 0.1f, 3.0f);
	//cube->Draw();
	//cube->SetPosition(12.025, 62.625, -4.105);
	//cube->SetScale(0.5f, 0.1f, 3.0f);
	//cube->Draw();



	/*ruangan*/
	////dinding
	for (int i = 0; i < 4; i++) {
		if (i > 1) {
			dinding->SetPosition(70 - (i - 2) * 100, 0.275, -0.35);
			dinding->SetScale(0.30f, 11.75f, 30.0f);
			dinding->Draw();
		}
		else {
			dinding->SetPosition(0.2, 0.275, 15 - i * 100);
			dinding->SetScale(30.0f, 11.75f, 0.30f);
			dinding->Draw();
		}
	}
	////atap
	atap->SetPosition(0.2, 30, -0.35);
	atap->SetScale(30.0f, 0.30f, 30.0f);
	atap->Draw();

	///////////////////////////////////////////////////////////////////////////////////////////////

	glDisable(GL_DEPTH_TEST);

}
void Application::ProcessInput(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		posCamY -= CAMERA_SPEED;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		posCamY += CAMERA_SPEED;
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}
void Application::BuildColoredPlane(const char* texturePath)
{
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-0.5, -38.5, -0.5,  0,  0,
		 0.5, -38.5, -0.5, 8,  0,
		 0.5, -38.5,  0.5, 8, 8,
		-0.5, -38.5,  0.5,  0, 8,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO  
	glBindVertexArray(VAO);

	// Bind VBO and set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO and set index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind VAO
	glBindVertexArray(0);

	
}
void Application::DrawColoredPlane()
{
	glBindVertexArray(VAO);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Unbind
	glBindVertexArray(0);
}
int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Billiard Room By Kelompok 2012",
		1920, 1080,
		false,
		true);
}