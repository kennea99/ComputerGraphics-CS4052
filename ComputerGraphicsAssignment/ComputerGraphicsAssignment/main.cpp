// Windows includes (For Time, IO, etc.)

#define NOMINMAX
#include<limits>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector> // STL dynamic memory.

// OpenGL includes
#include <GL/glew.h>
#include <GL/freeglut.h>

// Assimp includes
#include <assimp/cimport.h> // scene importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations

// Project includes
#include "maths_funcs.h"
#include "stb_image.h"

#define MOTHS 3
#define TREES 29
#define ROCKS 5
#define PLANES 9

/*----------------------------------------------------------------------------
MESH TO LOAD
----------------------------------------------------------------------------*/
#pragma region Constants
#define BODY "./spider/mesh_body.obj"
#define MAIN_BODY "./spider/mesh_mainbody.obj"
#define EYES "./spider/mesh_eyes.obj"
#define FANGS "./spider/mesh_fangs.obj"

#define PLANE "./spider/mesh_plane.obj"

#define TOPTREE "./spider/toptree.obj"
#define BOTTOMTREE "./spider/bottomtree.obj"

#define BODYJOINT_R1 "./spider/mesh_bodyjoint_r1.obj"
#define BODYJOINT_R2 "./spider/mesh_bodyjoint_r2.obj"
#define BODYJOINT_R3 "./spider/mesh_bodyjoint_r3.obj"
#define BODYJOINT_R4 "./spider/mesh_bodyjoint_r4.obj"

#define BODYJOINT_L1 "./spider/mesh_bodyjoint_l1.obj"
#define BODYJOINT_L2 "./spider/mesh_bodyjoint_l2.obj"
#define BODYJOINT_L3 "./spider/mesh_bodyjoint_l3.obj"
#define BODYJOINT_L4 "./spider/mesh_bodyjoint_l4.obj"

#define UPPERLEG_R1 "./spider/mesh_upperleg_r1.obj"
#define UPPERLEG_R2 "./spider/mesh_upperleg_r2.obj"
#define UPPERLEG_R3 "./spider/mesh_upperleg_r3.obj"
#define UPPERLEG_R4 "./spider/mesh_upperleg_r4.obj"

#define UPPERLEG_L1 "./spider/mesh_upperleg_l1.obj"
#define UPPERLEG_L2 "./spider/mesh_upperleg_l2.obj"
#define UPPERLEG_L3 "./spider/mesh_upperleg_l3.obj"
#define UPPERLEG_L4 "./spider/mesh_upperleg_l4.obj"

#define LEGJOINT_R1 "./spider/mesh_legjoint_r1.obj"
#define LEGJOINT_R2 "./spider/mesh_legjoint_r2.obj"
#define LEGJOINT_R3 "./spider/mesh_legjoint_r3.obj"
#define LEGJOINT_R4 "./spider/mesh_legjoint_r4.obj"

#define LEGJOINT_L1 "./spider/mesh_legjoint_l1.obj"
#define LEGJOINT_L2 "./spider/mesh_legjoint_l2.obj"
#define LEGJOINT_L3 "./spider/mesh_legjoint_l3.obj"
#define LEGJOINT_L4 "./spider/mesh_legjoint_l4.obj"

#define LOWERLEG_R1 "./spider/mesh_lowerleg_r1.obj"
#define LOWERLEG_R2 "./spider/mesh_lowerleg_r2.obj"
#define LOWERLEG_R3 "./spider/mesh_lowerleg_r3.obj"
#define LOWERLEG_R4 "./spider/mesh_lowerleg_r4.obj"

#define LOWERLEG_L1 "./spider/mesh_lowerleg_l1.obj"
#define LOWERLEG_L2 "./spider/mesh_lowerleg_l2.obj"
#define LOWERLEG_L3 "./spider/mesh_lowerleg_l3.obj"
#define LOWERLEG_L4 "./spider/mesh_lowerleg_l4.obj"

#define MOTH_BODY "./moth/moth_body.obj"
#define MOTH_EYES "./moth/moth_eyes.obj" 
#define MOTH_HEAD "./moth/moth_head.obj"
#define MOTH_LEGS "./moth/moth_legs.obj"

#define MOTH_WING_L1 "./moth/moth_wing_l1.obj"
#define MOTH_WING_R1 "./moth/moth_wing_r1.obj"
#define MOTH_WINGJOINT_L1 "./moth/moth_wingjoint_l1.obj"
#define MOTH_WINGJOINT_R1 "./moth/moth_wingjoint_r1.obj"

#define FENCE "fence.obj"
#define LAMP "lamp.obj"
#define LAMPGLASS "lampglass.obj"
#define LAMP_LIGHT "lamplight.obj"

#define ROCK "./spider/rock.obj"

#define BOX "box.obj"

//texture constants
#define TEX_TOPTREE "./textures/leaves.jpg"
#define TEX_TOPTREE_NAME "toptree"
#define TEX_TOPTREE_NUM	 0

#define TEX_BOTTOMTREE "./textures/wood.jpg"
#define TEX_BOTTOMTREE_NAME "bottomtree"
#define TEX_BOTTOMTREE_NUM 1

#define TEX_GROUND "./textures/gravel.jpg"
#define TEX_GROUND_NAME "ground"
#define TEX_GROUND_NUM 2

#define TEX_FENCE "./textures/fence.jpg"
#define TEX_FENCE_NAME "fence"
#define TEX_FENCE_NUM 3

#define TEX_SPIDERBODY "./textures/spiderbody.jpg"
#define TEX_SPIDERBODY_NAME "spiderbody"
#define TEX_SPIDERBODY_Num 4

#define TEX_SPIDERLEG "./textures/spiderbody.jpg"
#define TEX_SPIDERLEG_NAME "spiderleg"
#define TEX_SPIDERLEG_NUM 5

#define TEX_MOTHBODY "./textures/mothbody.jpg"
#define TEX_MOTHBODY_NAME "mothbody"
#define TEX_MOTHBODY_NUM 6

#define TEX_MOTHWING "./textures/mothwing.jpg"
#define TEX_MOTHWING_NAME "mothwing"
#define TEX_MOTHWING_NUM 7

#define TEX_LAMP "./textures/lamp.jpg"
#define TEX_LAMP_NAME "lamp"
#define TEX_LAMP_NUM 8

#define TEX_LAMPGLASS "./textures/orange.jpg"
#define TEX_LAMPGLASS_NAME "lampglass"
#define TEX_LAMPGLASS_NUM 9

#define TEX_BUGEYES "./textures/black.jpg"
#define TEX_BUGEYES_NAME "bugeyes"
#define TEX_BUGEYES_NUM 10

#define TEX_ROCK "./textures/rock.jpg"
#define TEX_ROCK_NAME "rock"
#define TEX_ROCK_NUM 11

#define TEX_BOX "./textures/lamp.jpg"
#define TEX_BOX_NAME "box"
#define TEX_BOX_NUM 12

#pragma endregion Constants



#pragma region SimpleTypes
typedef struct
{
	size_t mPointCount = 0;
	std::vector<vec3> mVertices;
	std::vector<vec3> mNormals;
	std::vector<vec2> mTextureCoords;
} ModelData;
#pragma endregion SimpleTypes

using namespace std;
GLuint shaderProgramID;

#pragma region ModelData&VAO
ModelData mesh_box;

ModelData mesh_mainbody;
ModelData mesh_body;
ModelData mesh_eyes;
ModelData mesh_fangs;

ModelData mesh_plane;

ModelData mesh_bodyjoint_r1;
ModelData mesh_bodyjoint_r2;
ModelData mesh_bodyjoint_r3;
ModelData mesh_bodyjoint_r4;

ModelData mesh_bodyjoint_l1;
ModelData mesh_bodyjoint_l2;
ModelData mesh_bodyjoint_l3;
ModelData mesh_bodyjoint_l4;

ModelData mesh_upperleg_r1;
ModelData mesh_upperleg_r2;
ModelData mesh_upperleg_r3;
ModelData mesh_upperleg_r4;

ModelData mesh_upperleg_l1;
ModelData mesh_upperleg_l2;
ModelData mesh_upperleg_l3;
ModelData mesh_upperleg_l4;

ModelData mesh_legjoint_r1;
ModelData mesh_legjoint_r2;
ModelData mesh_legjoint_r3;
ModelData mesh_legjoint_r4;

ModelData mesh_legjoint_l1;
ModelData mesh_legjoint_l2;
ModelData mesh_legjoint_l3;
ModelData mesh_legjoint_l4;

ModelData mesh_lowerleg_r1;
ModelData mesh_lowerleg_r2;
ModelData mesh_lowerleg_r3;
ModelData mesh_lowerleg_r4;

ModelData mesh_lowerleg_l1;
ModelData mesh_lowerleg_l2;
ModelData mesh_lowerleg_l3;
ModelData mesh_lowerleg_l4;

//Moth1 Model Data
ModelData moth_body;
ModelData moth_head;
ModelData moth_eyes;
ModelData moth_legs;
ModelData moth_wing_l1;
ModelData moth_wing_r1;
ModelData moth_wingjoint_l1;
ModelData moth_wingjoint_r1;

//Moth2 Model Data
ModelData moth_body2;
ModelData moth_head2;
ModelData moth_eyes2;
ModelData moth_legs2;
ModelData moth_wing_l12;
ModelData moth_wing_r12;
ModelData moth_wingjoint_l12;
ModelData moth_wingjoint_r12;

//Moth3 Model Data
ModelData moth_body3;
ModelData moth_head3;
ModelData moth_eyes3;
ModelData moth_legs3;
ModelData moth_wing_l13;
ModelData moth_wing_r13;
ModelData moth_wingjoint_l13;
ModelData moth_wingjoint_r13;

//fence model data
ModelData fence;
ModelData lamp;
ModelData lampglass;
ModelData lamp_light;
ModelData lamp_light2;
ModelData lamp_light3;

ModelData toptrees[TREES];
ModelData bottomtrees[TREES];

ModelData rocks[ROCKS];

ModelData planes[PLANES];


unsigned int boxVAO = 1;

unsigned int mainbodyVAO = 1;
unsigned int bodyVAO = 1;
unsigned int eyesVAO = 1;
unsigned int fangsVAO = 1;

unsigned int planesVAO[PLANES] = { 1,1,1,1,1,1,1,1,1 };

//tree vaos
unsigned int toptreevao[TREES] = { 0 };
unsigned int bottomtreevao[TREES] = { 0 };


unsigned int rocksvao[ROCKS] = { 1,1,1,1,1 };

unsigned int bodyjoint_r1vao = 1;
unsigned int bodyjoint_r2vao = 1;
unsigned int bodyjoint_r3vao = 1;
unsigned int bodyjoint_r4vao = 1;

unsigned int bodyjoint_l1vao = 1;
unsigned int bodyjoint_l2vao = 1;
unsigned int bodyjoint_l3vao = 1;
unsigned int bodyjoint_l4vao = 1;

unsigned int upperleg_r1vao = 1;
unsigned int upperleg_r2vao = 1;
unsigned int upperleg_r3vao = 1;
unsigned int upperleg_r4vao = 1;

unsigned int upperleg_l1vao = 1;
unsigned int upperleg_l2vao = 1;
unsigned int upperleg_l3vao = 1;
unsigned int upperleg_l4vao = 1;

unsigned int legjoint_r1vao = 1;
unsigned int legjoint_r2vao = 1;
unsigned int legjoint_r3vao = 1;
unsigned int legjoint_r4vao = 1;

unsigned int legjoint_l1vao = 1;
unsigned int legjoint_l2vao = 1;
unsigned int legjoint_l3vao = 1;
unsigned int legjoint_l4vao = 1;

unsigned int lowerleg_r1vao = 1;
unsigned int lowerleg_r2vao = 1;
unsigned int lowerleg_r3vao = 1;
unsigned int lowerleg_r4vao = 1;

unsigned int lowerleg_l1vao = 1;
unsigned int lowerleg_l2vao = 1;
unsigned int lowerleg_l3vao = 1;
unsigned int lowerleg_l4vao = 1;

//moth vaos
unsigned int moth_bodyvao[MOTHS] = { 1,1,1 };
unsigned int moth_headvao[MOTHS] = { 1,1,1 };
unsigned int moth_eyesvao[MOTHS] = { 1,1,1 };
unsigned int moth_legsvao[MOTHS] = { 1,1,1 };

unsigned int moth_wing_l1vao[MOTHS] = { 1,1,1 };
unsigned int moth_wing_r1vao[MOTHS] = { 1,1,1 };
unsigned int moth_wingjoint_l1vao[MOTHS] = { 1,1,1 };
unsigned int moth_wingjoint_r1vao[MOTHS] = { 1,1,1 };

//fence vaos
unsigned int fencevao = 1;
unsigned int lampvao = 1;
unsigned int lampglassvao = 1;
unsigned int lamp_lightvao[MOTHS] = { 1,1,1 };

#pragma endregion ModelData&VAO


float radians(float degrees) {
	float pi = 3.14159265359f;
	return(degrees * (pi / 180.0f));
}

unsigned int mesh_vao = 0;
float width = 1920;
float height = 1080;
GLuint loc1, loc2, loc3;

GLfloat rotate_lamplight[MOTHS] = { 0.0f, 0.0f, 0.0f };

//spider variables
boolean rotate_spider = false;
GLfloat turn_around = 0.0;
GLfloat rotate_y = 0.0f;
GLfloat rotate_y_opposite = 0.0f;
GLfloat rotate_z = 0.0f;
GLfloat rotate_z_opposite = 0.0f;
GLfloat rotate_yleg = 0.0f;
GLfloat translate_body = 0.0f;
GLfloat prev_translate = 0.0f;
bool switchRotation = false;
bool switchRotationZ = false;

GLfloat rotate_body_z = 0.0f;
bool switch_mainbody = false;


GLfloat rotate_moth[MOTHS] = { 0.0f, 0.0f, 0.0f };

//moth variables
GLfloat rotate_mothX[MOTHS] = { 0.0f, 0.0f, 0.0f };
GLfloat rotate_mothX_opposite[MOTHS] = { 0.0f, 0.0f, 0.0f };
GLfloat translate_alt[MOTHS] = { 2.0f, 5.0f, 0.0f };
GLfloat translate_side[MOTHS] = { 10.0f, 5.0f, 2.0f };

boolean switchWing[MOTHS] = { false, false, false };
boolean switchAltitude[MOTHS] = { false, true, false };
boolean switchSide[MOTHS] = { true, false, false };

GLfloat translate_moth[MOTHS] = { 10.0f, 5.0f, 2.0f };

bool firstRotate = false;


//tree positions
GLfloat treeX[TREES] = { 30.0f, -30.0f, 40.0f, 30.0f, 10.0f 
						,-90.0f, -150.0f, -110.0f
						, 30.0f, -30.0f, 10.0f
						, 150.0f, 90.0f, 130.0f
						, -90.0f, -150.0f, -110.0f
						, 150.0f, 90.0f, 130.0f
						, -90.0f, -150.0f, -110.0f
						, 30.0f, -30.0f, 10.0f
						, 150.0f, 90.0f, 130.0f};
GLfloat treeZ[TREES] = { 30.0f, -30.0f, 40.0f, -50.0f, -35.0f
						,-90.0f, -150.0f, -155.0f
						,-90.0f, -150.0f, -155.0f
						,-90.0f, -150.0f, -155.0f
						,30.0f, -30.0f, -35.0f
						,30.0f, -30.0f, -35.0f
						,150.0f, 90.0f, 85.0f
						,150.0f, 90.0f, 85.0f
						,150.0f, 90.0f, 85.0f};

GLfloat rockX[TREES] = { 40.0f, -30.0f, 50.0f, 25.0f, -25.0f };
GLfloat rockZ[TREES] = { 10.0f, 5.0f, 10.0f, -20.0f, 50.0f };

//plane positions
GLfloat planeX[PLANES] = { -120.0f, 0.0f, 120.0f, -120.0f, 0.0f,  120.0f, -120.0f, 0.0f, 120.0f };
GLfloat planeZ[PLANES] = { -120.0f, -120.0f, -120.0f, 0.0f,0.0f, 0.0f, 120.0f, 120.0f, 120.f };

//key presses
bool wPressed = false;
bool sPressed = false;
bool pPressed = false;
bool oPressed = false;
bool qPressed = false;
float delta = 0.0f;

//Different Starting variables for camera.

GLuint textures[13];

vec3 positionCam = vec3(0.0f, 10.0f, 40.0f);
vec3 camFront = vec3(0.0f, 0.0f, -1.0f);
vec3 upAxis = vec3(0.0f, 1.0f, 0.0f);

float lastX = width/2.0f;
float lastY = height / 2.0f;;
//for zoom
float fov = 45.0f;

//for camera rotation
float pitch = 0.0f;
float yaw = -90.0f;
float sens = 0.25f;



#pragma region MESH LOADING
ModelData load_mesh(const char* file_name) {
	ModelData modelData;

	/* Use assimp to read the model file, forcing it to be read as    */
	/* triangles. The second flag (aiProcess_PreTransformVertices) is */
	/* relevant if there are multiple meshes in the model file that   */
	/* are offset from the origin. This is pre-transform them so      */
	/* they're in the right position.                                 */
	const aiScene* scene = aiImportFile(
		file_name, 
		aiProcess_Triangulate | aiProcess_PreTransformVertices
	); 

	if (!scene) {
		fprintf(stderr, "ERROR: reading mesh %s\n", file_name);
		return modelData;
	}

	printf("  %i materials\n", scene->mNumMaterials);
	printf("  %i meshes\n", scene->mNumMeshes);
	printf("  %i textures\n", scene->mNumTextures);

	for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
		const aiMesh* mesh = scene->mMeshes[m_i];
		printf("    %i vertices in mesh\n", mesh->mNumVertices);
		modelData.mPointCount += mesh->mNumVertices;
		for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
			if (mesh->HasPositions()) {
				const aiVector3D* vp = &(mesh->mVertices[v_i]);
				modelData.mVertices.push_back(vec3(vp->x, vp->y, vp->z));
			}
			if (mesh->HasNormals()) {
				const aiVector3D* vn = &(mesh->mNormals[v_i]);
				modelData.mNormals.push_back(vec3(vn->x, vn->y, vn->z));
			}
			if (mesh->HasTextureCoords(0)) {
				const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
				modelData.mTextureCoords.push_back(vec2(vt->x, vt->y));
			}
			if (mesh->HasTangentsAndBitangents()) {
				/* You can extract tangents and bitangents here              */
				/* Note that you might need to make Assimp generate this     */
				/* data for you. Take a look at the flags that aiImportFile  */
				/* can take.                                                 */
			}
		}
	}

	aiReleaseImport(scene);
	return modelData;
}

#pragma endregion MESH LOADING

// Shader Functions- click on + to expand
#pragma region SHADER_FUNCTIONS
char* readShaderSource(const char* shaderFile) {
	FILE* fp;
	fopen_s(&fp, shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	buf[size] = '\0';

	fclose(fp);

	return buf;
}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// create a shader object
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		std::cerr << "Error creating shader..." << std::endl;
		std::cerr << "Press enter/return to exit..." << std::endl;
		std::cin.get();
		exit(1);
	}
	const char* pShaderSource = readShaderSource(pShaderText);

	// Bind the source code to the shader, this happens before compilation
	glShaderSource(ShaderObj, 1, (const GLchar**)&pShaderSource, NULL);
	// compile the shader and check for errors
	glCompileShader(ShaderObj);
	GLint success;
	// check for shader related errors using glGetShaderiv
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024] = { '\0' };
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		std::cerr << "Error compiling "
			<< (ShaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader program: " << InfoLog << std::endl;
		std::cerr << "Press enter/return to exit..." << std::endl;
		std::cin.get();
		exit(1);
	}
	// Attach the compiled shader object to the program object
	glAttachShader(ShaderProgram, ShaderObj);
}

GLuint CompileShaders()
{
	//Start the process of setting up our shaders by creating a program ID
	//Note: we will link all the shaders together into this ID
	shaderProgramID = glCreateProgram();
	if (shaderProgramID == 0) {
		std::cerr << "Error creating shader program..." << std::endl;
		std::cerr << "Press enter/return to exit..." << std::endl;
		std::cin.get();
		exit(1);
	}

	// Create two shader objects, one for the vertex, and one for the fragment shader
	AddShader(shaderProgramID, "simpleVertexShader.txt", GL_VERTEX_SHADER);
	AddShader(shaderProgramID, "simpleFragmentShader.txt", GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { '\0' };
	// After compiling all shader objects and attaching them to the program, we can finally link it
	glLinkProgram(shaderProgramID);
	// check for program related errors using glGetProgramiv
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		std::cerr << "Error linking shader program: " << ErrorLog << std::endl;
		std::cerr << "Press enter/return to exit..." << std::endl;
		std::cin.get();
		exit(1);
	}

	// program has been successfully linked but needs to be validated to check whether the program can execute given the current pipeline state
	glValidateProgram(shaderProgramID);
	// check for program related errors using glGetProgramiv
	glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(shaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		std::cerr << "Invalid shader program: " << ErrorLog << std::endl;
		std::cerr << "Press enter/return to exit..." << std::endl;
		std::cin.get();
		exit(1);
	}
	// Finally, use the linked shader program
	// Note: this program will stay in effect for all draw calls until you replace it with another or explicitly disable its use
	glUseProgram(shaderProgramID);
	return shaderProgramID;
}
#pragma endregion SHADER_FUNCTIONS

void loadTexture(int current_texture, GLuint texture, const char* tex_file, const char* texture_name, int texNum)
{
	glActiveTexture(current_texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(tex_file, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	glUniform1i(glGetUniformLocation(shaderProgramID, texture_name), texNum);

	stbi_image_free(data);
}

unsigned int makeCubeMap(vector<std::string> sides) {
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	int width, height, nrChannels;
	for (int i = 0; i < sides.size(); i++) {
		unsigned char* data = stbi_load(sides[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load skybox" << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return id;
}

// VBO Functions - click on + to expand
#pragma region VBO_FUNCTIONS
void generateObjectBufferMesh(ModelData mesh, unsigned int vaoN) {
	/*----------------------------------------------------------------------------
	LOAD MESH HERE AND COPY INTO BUFFERS
	----------------------------------------------------------------------------*/

	unsigned int vp_vbo = 0;
	loc1 = glGetAttribLocation(shaderProgramID, "vertex_position");
	loc2 = glGetAttribLocation(shaderProgramID, "vertex_normal");
	loc3 = glGetAttribLocation(shaderProgramID, "vertex_texture");

	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.mPointCount * sizeof(vec3), &mesh.mVertices[0], GL_STATIC_DRAW);
	unsigned int vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.mPointCount * sizeof(vec3), &mesh.mNormals[0], GL_STATIC_DRAW);

	//	This is for texture coordinates which you don't currently need, so I have commented it out
	unsigned int vt_vbo = 0;
	if (mesh.mTextureCoords.size()) {
		glGenBuffers(1, &vt_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.mPointCount * sizeof(vec2), &mesh.mTextureCoords[0], GL_STATIC_DRAW);
	}

	glBindVertexArray(vaoN);

	glEnableVertexAttribArray(loc1);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(loc2);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//	This is for texture coordinates which you don't currently need, so I have commented it out
	if (mesh.mTextureCoords.size()) {
		glEnableVertexAttribArray(loc3);
		glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
		glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
}

//Changing Material of objects
void resetMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(diffuse_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(specular_loc, 1.0f, 1.0f, 1.0f);
	glUniform1f(shiny_loc, 10.0f);
}

void groundMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(diffuse_loc, 1.0f, 0.9f, 0.5f);
	glUniform3f(specular_loc, 1.0f, 1.0f, 1.0f);
	glUniform1f(shiny_loc, 10.0f);
}

void bugEyesMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 0.2f, 0.5f, 0.31f);
	glUniform3f(diffuse_loc, 0.0f, 0.0f, 0.0f);
	glUniform3f(specular_loc, 6.0f, 6.0f, 6.0f);
	glUniform1f(shiny_loc, 25.0f);
}

void metalBoxMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 0.2f, 0.5f, 0.31f);
	glUniform3f(diffuse_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(specular_loc, 10.0f, 10.0f, 10.0f);
	glUniform1f(shiny_loc, 10.0f);
}

void spiderBodyMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 0.2f, 0.5f, 0.31f);
	glUniform3f(diffuse_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(specular_loc, 0.0f, 0.0f, 0.0f);
	glUniform1f(shiny_loc, 50.0f);
}

void rockMat() {
	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");
	glUniform3f(ambient_loc, 0.2f, 0.5f, 0.31f);
	glUniform3f(diffuse_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(specular_loc, 3.0f, 3.0f, 3.0f);
	glUniform1f(shiny_loc, 50.0f);
}

void display() {
	

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor(0.207f, 0.211f, 0.372f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);


	//Declare your uniform variables that will be used in your shader
	int matrix_location = glGetUniformLocation(shaderProgramID, "model");
	int view_mat_location = glGetUniformLocation(shaderProgramID, "view");
	int proj_mat_location = glGetUniformLocation(shaderProgramID, "proj");
	int texNum = glGetUniformLocation(shaderProgramID, "texNum");
	int light_x_loc = glGetUniformLocation(shaderProgramID, "light_x");
	int light_z_loc = glGetUniformLocation(shaderProgramID, "light_z");

	GLint ambient_loc = glGetUniformLocation(shaderProgramID, "Matambient");
	GLint diffuse_loc = glGetUniformLocation(shaderProgramID, "Matdiffuse");
	GLint specular_loc = glGetUniformLocation(shaderProgramID, "Matspecular");
	GLint shiny_loc = glGetUniformLocation(shaderProgramID, "Matshininess");



	mat4 view = look_at(positionCam, positionCam + camFront, upAxis);
	mat4 persp_proj = perspective(fov, (float)width / (float)height, 0.1f, 1000.0f);

	// update uniforms & draw
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, persp_proj.m);
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view.m);

	glUniform1f(light_x_loc, 0.0f);
	glUniform1f(light_z_loc, 0.0f);
//changing material
	glUniform3f(ambient_loc, 0.2f,0.2f,0.2f);
	glUniform3f(diffuse_loc, 1.0f, 1.0f, 1.0f);
	glUniform3f(specular_loc, 1.0f, 1.0f, 1.0f);
	glUniform1f(shiny_loc, 25.0f);


	groundMat();
	mat4 planesMat[PLANES];
	for (int i = 0; i < PLANES; i++) {
		resetMat();
		planesMat[i] = identity_mat4();
		planesMat[i] = translate(planesMat[i], vec3(planeX[i], -4.0f, planeZ[i]));
		glBindVertexArray(planesVAO[i]);
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, planesMat[i].m);
		glUniform1i(texNum, 2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glDrawArrays(GL_TRIANGLES, 0, planes[i].mPointCount);
	}
	resetMat();
	//mat4 planemodel = identity_mat4();
	//planemodel = translate(planemodel, vec3(0.0f, -4.0f, 0.0f));
	//glBindVertexArray(planeVAO);
	//glUniformMatrix4fv(matrix_location, 1, GL_FALSE, planemodel.m);
	//glUniform1i(texNum, 2);
	//glBindTexture(GL_TEXTURE_2D, textures[2]);
	//glDrawArrays(GL_TRIANGLES, 0, mesh_plane.mPointCount);
	//resetMat();

	mat4 bodymodel = identity_mat4();
	if (rotate_spider == false && translate_body >= 50.0f) {
		bodymodel = translate(bodymodel, vec3(0.0f, -4.0f, 0.0f));
		rotate_spider = true;
		turn_around -=180.0f;
	}
	else if (rotate_spider == true && translate_body <= 0.0f) {
		bodymodel = translate(bodymodel, vec3(0.0f, -4.0f, 0.0f));
		rotate_spider = false;
		turn_around -= 180.0f;
	}

	bodymodel = rotate_y_deg(bodymodel, turn_around);
	bodymodel = translate(bodymodel, vec3(0.0f, -4.0f, translate_body));
	glBindVertexArray(bodyVAO);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodymodel.m);
	glDrawArrays(GL_TRIANGLES, 0, mesh_body.mPointCount);

	spiderBodyMat();
	mat4 mainbody_model = identity_mat4();
	mainbody_model = rotate_y_deg(mainbody_model, rotate_body_z);
	mainbody_model = bodymodel * mainbody_model;
	glBindVertexArray(mainbodyVAO);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, mainbody_model.m);
	glUniform1i(texNum, 4);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_mainbody.mPointCount);
	resetMat();

	//changing material
	bugEyesMat();
	mat4 eyesmodel = identity_mat4();
	eyesmodel = bodymodel * eyesmodel;
	glBindVertexArray(eyesVAO);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, eyesmodel.m);
	//glUniform1i(texNum, 10);
	//glBindTexture(GL_TEXTURE_2D, textures[10]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_eyes.mPointCount);
	resetMat();

	mat4 fangsmodel = identity_mat4();
	fangsmodel = bodymodel * fangsmodel;
	glBindVertexArray(fangsVAO);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, fangsmodel.m);
	glUniform1i(texNum, 4);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_fangs.mPointCount);

//tree
	mat4 topTrees[TREES];
	for (int i = 0; i < TREES; i++) {
		topTrees[i] = identity_mat4();
		topTrees[i] = translate(topTrees[i], vec3(treeX[i], -5.0f, treeZ[i]));
		glBindVertexArray(toptreevao[i]);
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, topTrees[i].m);
		glUniform1i(texNum, 0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glDrawArrays(GL_TRIANGLES, 0, toptrees[i].mPointCount);
	}

	mat4 bottomTrees[TREES];
	for (int i = 0; i < TREES; i++) {
		bottomTrees[i] = identity_mat4();
		bottomTrees[i] = translate(bottomTrees[i], vec3(treeX[i], -5.0f, treeZ[i]));
		glBindVertexArray(bottomtreevao[i]);
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bottomTrees[i].m);
		glUniform1i(texNum, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glDrawArrays(GL_TRIANGLES, 0, bottomtrees[i].mPointCount);
	}
	rockMat();
	mat4 rocksMat[ROCKS];
	for (int i = 0; i < ROCKS; i++) {
		rocksMat[i] = identity_mat4();
		rocksMat[i] = translate(rocksMat[i], vec3(rockX[i], -4.0f, rockZ[i]));
		glBindVertexArray(rocksvao[i]);
		glUniformMatrix4fv(matrix_location, 1, GL_FALSE, rocksMat[i].m);
		glUniform1i(texNum, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glDrawArrays(GL_TRIANGLES, 0, rocks[i].mPointCount);
	}
	resetMat();

//r1
	mat4 bodyjointmodel_r1 = identity_mat4();
	bodyjointmodel_r1 = rotate_z_deg(bodyjointmodel_r1, rotate_z_opposite);
	bodyjointmodel_r1 = rotate_y_deg(bodyjointmodel_r1, rotate_y);
	bodyjointmodel_r1 = bodymodel * bodyjointmodel_r1;
	glBindVertexArray(bodyjoint_r1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_r1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_r1.mPointCount);

	mat4 upperlegmodel_r1 = identity_mat4();
	upperlegmodel_r1 = bodyjointmodel_r1 * upperlegmodel_r1;
	glBindVertexArray(upperleg_r1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_r1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_r1.mPointCount);

	mat4 legjointmodel_r1 = identity_mat4();
	legjointmodel_r1 = upperlegmodel_r1 * legjointmodel_r1;
	glBindVertexArray(legjoint_r1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_r1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_r1.mPointCount);

	mat4 lowerlegmodel_r1 = identity_mat4();
	lowerlegmodel_r1 = legjointmodel_r1 * lowerlegmodel_r1;
	glBindVertexArray(lowerleg_r1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_r1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_r1.mPointCount);
//r2
	mat4 bodyjointmodel_r2 = identity_mat4();
	bodyjointmodel_r2 = rotate_z_deg(bodyjointmodel_r2, rotate_z_opposite);
	bodyjointmodel_r2 = rotate_y_deg(bodyjointmodel_r2, rotate_y_opposite);
	bodyjointmodel_r2 = bodymodel * bodyjointmodel_r2;
	glBindVertexArray(bodyjoint_r2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_r2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_r2.mPointCount);

	mat4 upperlegmodel_r2 = identity_mat4();
	upperlegmodel_r2 = bodyjointmodel_r2 * upperlegmodel_r2;
	glBindVertexArray(upperleg_r2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_r2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_r2.mPointCount);

	mat4 legjointmodel_r2 = identity_mat4();
	legjointmodel_r2 = upperlegmodel_r2 * legjointmodel_r2;
	glBindVertexArray(legjoint_r2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_r2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_r2.mPointCount);

	mat4 lowerlegmodel_r2 = identity_mat4();
	lowerlegmodel_r2 = legjointmodel_r2 * lowerlegmodel_r2;
	glBindVertexArray(lowerleg_r2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_r2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_r2.mPointCount);

//r3
	mat4 bodyjointmodel_r3 = identity_mat4();
	bodyjointmodel_r3 = rotate_z_deg(bodyjointmodel_r3, rotate_z_opposite);
	bodyjointmodel_r3 = rotate_y_deg(bodyjointmodel_r3, rotate_y);
	bodyjointmodel_r3 = bodymodel * bodyjointmodel_r3;
	glBindVertexArray(bodyjoint_r3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_r3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_r3.mPointCount);

	mat4 upperlegmodel_r3 = identity_mat4();
	upperlegmodel_r3 = rotate_y_deg(upperlegmodel_r3, rotate_y);
	upperlegmodel_r3 = bodyjointmodel_r3 * upperlegmodel_r3;
	glBindVertexArray(upperleg_r3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_r3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_r3.mPointCount);

	mat4 legjointmodel_r3 = identity_mat4();
	legjointmodel_r3 = upperlegmodel_r3 * legjointmodel_r3;
	glBindVertexArray(legjoint_r3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_r3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_r3.mPointCount);

	mat4 lowerlegmodel_r3 = identity_mat4();
	lowerlegmodel_r3 = legjointmodel_r3 * lowerlegmodel_r3;
	glBindVertexArray(lowerleg_r3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_r3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_r3.mPointCount);

//r4
	mat4 bodyjointmodel_r4 = identity_mat4();
	bodyjointmodel_r4 = rotate_z_deg(bodyjointmodel_r4, rotate_z_opposite);
	bodyjointmodel_r4 = rotate_y_deg(bodyjointmodel_r4, rotate_y_opposite);
	bodyjointmodel_r4 = bodymodel * bodyjointmodel_r4;
	glBindVertexArray(bodyjoint_r4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_r4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_r4.mPointCount);

	mat4 upperlegmodel_r4 = identity_mat4();
	upperlegmodel_r4 = bodyjointmodel_r4 * upperlegmodel_r4;
	glBindVertexArray(upperleg_r4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_r4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_r4.mPointCount);

	mat4 legjointmodel_r4 = identity_mat4();
	legjointmodel_r4 = upperlegmodel_r4 * legjointmodel_r4;
	glBindVertexArray(legjoint_r4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_r4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_r4.mPointCount);

	mat4 lowerlegmodel_r4 = identity_mat4();
	lowerlegmodel_r4 = legjointmodel_r4 * lowerlegmodel_r4;
	glBindVertexArray(lowerleg_r4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_r4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_r4.mPointCount);

//l1
	mat4 bodyjointmodel_l1 = identity_mat4();
	bodyjointmodel_l1 = rotate_z_deg(bodyjointmodel_l1, rotate_z);
	bodyjointmodel_l1 = rotate_y_deg(bodyjointmodel_l1, rotate_y);
	bodyjointmodel_l1 = bodymodel * bodyjointmodel_l1;
	glBindVertexArray(bodyjoint_l1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_l1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_l1.mPointCount);

	mat4 upperlegmodel_l1 = identity_mat4();
	upperlegmodel_l1 = bodyjointmodel_l1 * upperlegmodel_l1;
	glBindVertexArray(upperleg_l1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_l1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_l1.mPointCount);

	mat4 legjointmodel_l1 = identity_mat4();
	legjointmodel_l1 = upperlegmodel_l1 * legjointmodel_l1;
	glBindVertexArray(legjoint_l1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_l1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_l1.mPointCount);

	mat4 lowerlegmodel_l1 = identity_mat4();
	lowerlegmodel_l1 = legjointmodel_l1 * lowerlegmodel_l1;
	glBindVertexArray(lowerleg_l1vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_l1.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_l1.mPointCount);

//l2
	mat4 bodyjointmodel_l2 = identity_mat4();
	bodyjointmodel_l2 = rotate_z_deg(bodyjointmodel_l2, rotate_z);
	bodyjointmodel_l2 = rotate_y_deg(bodyjointmodel_l2, rotate_y_opposite);
	bodyjointmodel_l2 = bodymodel * bodyjointmodel_l2;
	glBindVertexArray(bodyjoint_l2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_l2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_l2.mPointCount);

	mat4 upperlegmodel_l2 = identity_mat4();
	upperlegmodel_l2 = bodyjointmodel_l2 * upperlegmodel_l2;
	glBindVertexArray(upperleg_l2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_l2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_l2.mPointCount);

	mat4 legjointmodel_l2 = identity_mat4();
	legjointmodel_l2 = upperlegmodel_l2 * legjointmodel_l2;
	glBindVertexArray(legjoint_l2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_l2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_l2.mPointCount);

	mat4 lowerlegmodel_l2 = identity_mat4();
	lowerlegmodel_l2 = legjointmodel_l2 * lowerlegmodel_l2;
	glBindVertexArray(lowerleg_l2vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_l2.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_l2.mPointCount);

//l3
	mat4 bodyjointmodel_l3 = identity_mat4();
	bodyjointmodel_l3 = rotate_z_deg(bodyjointmodel_l3, rotate_z);
	bodyjointmodel_l3 = rotate_y_deg(bodyjointmodel_l3, rotate_y);
	bodyjointmodel_l3 = bodymodel * bodyjointmodel_l3;
	glBindVertexArray(bodyjoint_l3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_l3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_l3.mPointCount);

	mat4 upperlegmodel_l3 = identity_mat4();
	upperlegmodel_l3 = bodyjointmodel_l3 * upperlegmodel_l3;
	glBindVertexArray(upperleg_l3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_l3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_l3.mPointCount);

	mat4 legjointmodel_l3 = identity_mat4();
	legjointmodel_l3 = upperlegmodel_l3 * legjointmodel_l3;
	glBindVertexArray(legjoint_l3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_l3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_l3.mPointCount);

	mat4 lowerlegmodel_l3 = identity_mat4();
	lowerlegmodel_l3 = legjointmodel_l3 * lowerlegmodel_l3;
	glBindVertexArray(lowerleg_l3vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_l3.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_l3.mPointCount);

//l4
	mat4 bodyjointmodel_l4 = identity_mat4();
	bodyjointmodel_l4 = rotate_z_deg(bodyjointmodel_l4, rotate_z);
	bodyjointmodel_l4 = rotate_y_deg(bodyjointmodel_l4, rotate_y_opposite);
	bodyjointmodel_l4 = bodymodel * bodyjointmodel_l4;
	glBindVertexArray(bodyjoint_l4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, bodyjointmodel_l4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_bodyjoint_l4.mPointCount);

	mat4 upperlegmodel_l4 = identity_mat4();
	upperlegmodel_l4 = bodyjointmodel_l4 * upperlegmodel_l4;
	glBindVertexArray(upperleg_l4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, upperlegmodel_l4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_upperleg_l4.mPointCount);

	mat4 legjointmodel_l4 = identity_mat4();
	legjointmodel_l4 = upperlegmodel_l4 * legjointmodel_l4;
	glBindVertexArray(legjoint_l4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, legjointmodel_l4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_legjoint_l4.mPointCount);

	mat4 lowerlegmodel_l4 = identity_mat4();
	lowerlegmodel_l4 = legjointmodel_l4 * lowerlegmodel_l4;
	glBindVertexArray(lowerleg_l4vao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lowerlegmodel_l4.m);
	glUniform1i(texNum, 5);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_lowerleg_l4.mPointCount);

	//fence drawing
	//bindTexture(FENCE_TEXTURE);
	mat4 fence_model = identity_mat4();
	fence_model = rotate_y_deg(fence_model, 90.0f);
	fence_model = translate(fence_model, vec3(0.0f, 15.0f, 0.0f));
	glBindVertexArray(fencevao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, fence_model.m);
	glUniform1i(texNum, 3);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glDrawArrays(GL_TRIANGLES, 0, fence.mPointCount);

	mat4 lamp_model = identity_mat4();
	lamp_model = translate(lamp_model, vec3(0.0f, 15.0f, 0.0f));
	//lamp_model = fence_model * lamp_model;
	glBindVertexArray(lampvao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lamp_model.m);
	glUniform1i(texNum, 8);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glDrawArrays(GL_TRIANGLES, 0, lamp.mPointCount);

	glUniform3f(ambient_loc, 1.0f, 0.5f, 0.31f);
	glUniform3f(diffuse_loc, 1.0f, 0.5f, 0.31f);
	glUniform3f(specular_loc, 4.5f, 4.5f, 4.5f);
	glUniform1f(shiny_loc, 1.0f);
	mat4 lampglass_model = identity_mat4();
	lampglass_model = lamp_model * lampglass_model;
	glBindVertexArray(lampglassvao);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lampglass_model.m);
	glUniform1i(texNum, 9);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glDrawArrays(GL_TRIANGLES, 0, lampglass.mPointCount);
	resetMat();
	//moth drawing
	mat4 lamplight_model = identity_mat4();
	lamplight_model = fence_model * lamplight_model;
	lamplight_model = rotate_y_deg(lamplight_model, rotate_lamplight[0]);
	glBindVertexArray(lamp_lightvao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lamplight_model.m);
	glDrawArrays(GL_TRIANGLES, 0, lamp_light.mPointCount);

	mat4 moth_bodymodel = identity_mat4();
	moth_bodymodel = rotate_y_deg(moth_bodymodel, -90.0f);
	moth_bodymodel = translate(moth_bodymodel, vec3(translate_side[0], translate_alt[0], 0.0f));
	moth_bodymodel = lamplight_model * moth_bodymodel;
	glBindVertexArray(moth_bodyvao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_bodymodel.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_body.mPointCount);

	mat4 moth_headmodel = identity_mat4();
	moth_headmodel = moth_bodymodel * moth_headmodel;
	glBindVertexArray(moth_headvao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_headmodel.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_head.mPointCount);

	bugEyesMat();
	mat4 moth_eyesmodel = identity_mat4();
	moth_eyesmodel = moth_bodymodel * moth_eyesmodel;
	glBindVertexArray(moth_eyesvao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_eyesmodel.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_eyes.mPointCount);
	resetMat();

	mat4 moth_legsmodel = identity_mat4();
	moth_legsmodel = rotate_z_deg(moth_legsmodel, rotate_y);
	moth_legsmodel = moth_bodymodel * moth_legsmodel;
	glBindVertexArray(moth_legsvao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_legsmodel.m);
	glUniform1i(texNum, 10);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glDrawArrays(GL_TRIANGLES, 0, moth_legs.mPointCount);

	mat4 moth_wingjoint_l1model = identity_mat4();
	moth_wingjoint_l1model = rotate_x_deg(moth_wingjoint_l1model, rotate_mothX_opposite[0]);
	moth_wingjoint_l1model = moth_bodymodel * moth_wingjoint_l1model;
	glBindVertexArray(moth_wingjoint_l1vao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_l1model.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_l1.mPointCount);

	mat4 moth_wingjoint_r1model = identity_mat4();
	moth_wingjoint_r1model = rotate_x_deg(moth_wingjoint_r1model, rotate_mothX[0]);
	moth_wingjoint_r1model = moth_bodymodel * moth_wingjoint_r1model;
	glBindVertexArray(moth_wingjoint_r1vao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_r1model.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_r1.mPointCount);

	mat4 moth_wing_l1model = identity_mat4();
	moth_wing_l1model = moth_wingjoint_l1model * moth_wing_l1model;
	glBindVertexArray(moth_wing_l1vao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_l1model.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_l1.mPointCount);

	mat4 moth_wing_r1model = identity_mat4();
	moth_wing_r1model = moth_wingjoint_r1model * moth_wing_r1model;
	glBindVertexArray(moth_wing_r1vao[0]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_r1model.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_r1.mPointCount);
	//second moth
	mat4 lamplight_model2 = identity_mat4();
	lamplight_model2 = fence_model * lamplight_model2;
	lamplight_model2 = rotate_y_deg(lamplight_model2, -rotate_lamplight[1]);
	glBindVertexArray(lamp_lightvao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lamplight_model2.m);
	glDrawArrays(GL_TRIANGLES, 0, lamp_light2.mPointCount);

	mat4 moth_bodymodel2 = identity_mat4();
	moth_bodymodel2 = rotate_y_deg(moth_bodymodel2, 90.0f);
	moth_bodymodel2 = translate(moth_bodymodel2, vec3(translate_side[1], translate_alt[1], 0.0f));
	moth_bodymodel2 = lamplight_model2 * moth_bodymodel2;
	glBindVertexArray(moth_bodyvao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_bodymodel2.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_body2.mPointCount);

	mat4 moth_headmodel2 = identity_mat4();
	moth_headmodel2 = moth_bodymodel2 * moth_headmodel2;
	glBindVertexArray(moth_headvao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_headmodel2.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_head2.mPointCount);

	bugEyesMat();
	mat4 moth_eyesmodel2 = identity_mat4();
	moth_eyesmodel2 = moth_bodymodel2 * moth_eyesmodel2;
	glBindVertexArray(moth_eyesvao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_eyesmodel2.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_eyes2.mPointCount);
	resetMat();

	mat4 moth_legsmodel2 = identity_mat4();
	moth_legsmodel2 = rotate_z_deg(moth_legsmodel2, rotate_y);
	moth_legsmodel2 = moth_bodymodel2 * moth_legsmodel2;
	glBindVertexArray(moth_legsvao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_legsmodel2.m);
	glUniform1i(texNum, 10);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glDrawArrays(GL_TRIANGLES, 0, moth_legs2.mPointCount);

	mat4 moth_wingjoint_l1model2 = identity_mat4();
	moth_wingjoint_l1model2 = rotate_x_deg(moth_wingjoint_l1model2, rotate_mothX_opposite[1]);
	moth_wingjoint_l1model2 = moth_bodymodel2 * moth_wingjoint_l1model2;
	glBindVertexArray(moth_wingjoint_l1vao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_l1model2.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_l12.mPointCount);

	mat4 moth_wingjoint_r1model2 = identity_mat4();
	moth_wingjoint_r1model2 = rotate_x_deg(moth_wingjoint_r1model2, rotate_mothX[1]);
	moth_wingjoint_r1model2 = moth_bodymodel2 * moth_wingjoint_r1model2;
	glBindVertexArray(moth_wingjoint_r1vao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_r1model2.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_r12.mPointCount);

	mat4 moth_wing_l1model2 = identity_mat4();
	moth_wing_l1model2 = moth_wingjoint_l1model2 * moth_wing_l1model2;
	glBindVertexArray(moth_wing_l1vao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_l1model2.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_l12.mPointCount);

	mat4 moth_wing_r1model2 = identity_mat4();
	moth_wing_r1model2 = moth_wingjoint_r1model2 * moth_wing_r1model2;
	glBindVertexArray(moth_wing_r1vao[1]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_r1model2.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_r12.mPointCount);
	//third moth
	mat4 lamplight_model3 = identity_mat4();
	lamplight_model3 = fence_model * lamplight_model3;
	lamplight_model3 = rotate_y_deg(lamplight_model3, rotate_lamplight[2]);
	glBindVertexArray(lamp_lightvao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, lamplight_model3.m);
	glDrawArrays(GL_TRIANGLES, 0, lamp_light3.mPointCount);

	mat4 moth_bodymodel3 = identity_mat4();
	moth_bodymodel3 = rotate_y_deg(moth_bodymodel3, 90.0f);
	moth_bodymodel3 = translate(moth_bodymodel3, vec3(translate_side[2], translate_alt[2], 0.0f));
	moth_bodymodel3 = lamplight_model3 * moth_bodymodel3;
	glBindVertexArray(moth_bodyvao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_bodymodel3.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_body3.mPointCount);

	mat4 moth_headmodel3 = identity_mat4();
	moth_headmodel3 = moth_bodymodel3 * moth_headmodel3;
	glBindVertexArray(moth_headvao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_headmodel3.m);
	glUniform1i(texNum, 6);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glDrawArrays(GL_TRIANGLES, 0, moth_head3.mPointCount);

	bugEyesMat();
	mat4 moth_eyesmodel3 = identity_mat4();
	moth_eyesmodel3 = moth_bodymodel3 * moth_eyesmodel3;
	glBindVertexArray(moth_eyesvao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_eyesmodel3.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_eyes3.mPointCount);
	resetMat();

	mat4 moth_legsmodel3 = identity_mat4();
	moth_legsmodel3 = rotate_z_deg(moth_legsmodel3, rotate_y);
	moth_legsmodel3 = moth_bodymodel3 * moth_legsmodel3;
	glBindVertexArray(moth_legsvao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_legsmodel3.m);
	glUniform1i(texNum, 10);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glDrawArrays(GL_TRIANGLES, 0, moth_legs3.mPointCount);

	mat4 moth_wingjoint_l1model3 = identity_mat4();
	moth_wingjoint_l1model3 = rotate_x_deg(moth_wingjoint_l1model3, rotate_mothX_opposite[2]);
	moth_wingjoint_l1model3 = moth_bodymodel3 * moth_wingjoint_l1model3;
	glBindVertexArray(moth_wingjoint_l1vao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_l1model3.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_l13.mPointCount);

	mat4 moth_wingjoint_r1model3 = identity_mat4();
	moth_wingjoint_r1model3 = rotate_x_deg(moth_wingjoint_r1model3, rotate_mothX[2]);
	moth_wingjoint_r1model3 = moth_bodymodel3 * moth_wingjoint_r1model3;
	glBindVertexArray(moth_wingjoint_r1vao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wingjoint_r1model3.m);
	glDrawArrays(GL_TRIANGLES, 0, moth_wingjoint_r13.mPointCount);

	mat4 moth_wing_l1model3 = identity_mat4();
	moth_wing_l1model3 = moth_wingjoint_l1model3 * moth_wing_l1model3;
	glBindVertexArray(moth_wing_l1vao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_l1model3.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_l13.mPointCount);

	mat4 moth_wing_r1model3 = identity_mat4();
	moth_wing_r1model3 = moth_wingjoint_r1model3 * moth_wing_r1model3;
	glBindVertexArray(moth_wing_r1vao[2]);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, moth_wing_r1model3.m);
	glUniform1i(texNum, 7);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawArrays(GL_TRIANGLES, 0, moth_wing_r13.mPointCount);

	metalBoxMat();
	mat4 box = identity_mat4();
	box = rotate_y_deg(box, -150.0f);
	box = translate(box, vec3(-25.0f, -3.0f, 25.0f));
	glBindVertexArray(boxVAO);
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, box.m);
	glUniform1i(texNum, 12);
	glBindTexture(GL_TEXTURE_2D, textures[12]);
	glDrawArrays(GL_TRIANGLES, 0, mesh_box.mPointCount);
	resetMat();

	glutSwapBuffers();
}

void animate(float threshold, float speed) {
	//moving spider's legs forwards and backwards
	if (switchRotation == false) {
		rotate_y += speed * delta;
		rotate_y_opposite -= speed * delta;
		if (rotate_y >= threshold || rotate_y_opposite <= -threshold) {
			switchRotation = true;
		}
	}
	else if (switchRotation == true) {
		rotate_y -= speed * delta;
		rotate_y_opposite += speed *delta;
		if (rotate_y <= -threshold || rotate_y_opposite >= threshold) {
			switchRotation = false;
		}
	}
	//moving the spider's legs up and down
	if (switchRotationZ == false) {
		rotate_z += 16.0f * delta;
		rotate_z_opposite -= 16.0f *delta;
		if (rotate_z >= 8.0f) {
			switchRotationZ = true;
		}
	}
	else if (switchRotationZ == true) {
		rotate_z -= 16.0f * delta;
		rotate_z_opposite += 16.0f *delta;
		if (rotate_z <= 0.0f) {
			switchRotationZ = false;
		}
	}
	//moving the spider's body
	if (switch_mainbody == false) {
		rotate_body_z += 48.0f * delta;
		if (rotate_body_z >= 4.0f) {
			switch_mainbody = true;
		}
	}
	else if (switch_mainbody == true) {
		rotate_body_z -= 48.0f * delta;
		if (rotate_body_z <= -4.0f) {
			switch_mainbody = false;
		}
	}
	//cout << switchRotationZ;
}

void animateMoth(float threshold, float speed) {
	for (int i = 0; i < MOTHS; i++) {
		float alt_threshold = 5.0f;
		float side_threshold = 12.0f;
		if (switchWing[i] == false) {
			rotate_mothX[i] += speed * delta;
			rotate_mothX_opposite[i] -= speed * delta;
			if (rotate_mothX[i] >= threshold) {
				switchWing[i] = true;
			}
		}
		else if (switchWing[i] == true) {
			rotate_mothX[i] -= speed * delta;
			rotate_mothX_opposite[i] += speed * delta;
			if (rotate_mothX[i] <= -threshold) {
				switchWing[i] = false;
			}
		}

		if (switchAltitude[i] == false) {
			translate_alt[i] += 0.0010f;
			if (translate_alt[i] >= alt_threshold) {
				switchAltitude[i] = true;
			}
		}
		else if (switchAltitude[i] == true) {
			translate_alt[i] -= 0.0010f;
			if (translate_alt[i] <= alt_threshold - 5)
				switchAltitude[i] = false;
		}

		if (switchSide[i] == false) {
			translate_side[i] += 0.0005f;
			if (translate_side[i] >= side_threshold) {
				switchSide[i] = true;
			}
		}
		else if (switchSide[i] == true) {
			translate_side[i] -= 0.0005f;
			if (translate_side[i] <= side_threshold - 4) {
				switchSide[i] = false;
			}
		}
	}
}

void updateScene() {
	static DWORD last_time = 0;
	DWORD curr_time = timeGetTime();
	if (last_time == 0)
		last_time = curr_time;
	delta = (curr_time - last_time) * 0.001f;
	last_time = curr_time;
	if (wPressed == true) {
		if (rotate_spider == false) {
			translate_body = translate_body + 0.005f;
		}
		else if (rotate_spider == true) {
			translate_body = translate_body - 0.005f;
		}
		animate(8.0f, 150.0f);
	}
	if (sPressed == true) {
		translate_body = translate_body - 0.0055f;
		animate(8.0f, 150.0f);
	}
	if (pPressed == true) {
		animate(8.0f, 150.0f);
	}
	if (oPressed == true) {
		translate_body = translate_body + 0.0055f;
	}
	if (qPressed == false) {
		rotate_lamplight[0] += 120.0f *delta;
		rotate_lamplight[1] += 90.0f *delta;
		rotate_lamplight[2] -= 150.0f *delta;
		animateMoth(45.0f, 1500.0f);
	}
	else if (qPressed == true) {
		animateMoth(45.0f, 1500.0f);
	}
	// Draw the next frame
	glutPostRedisplay();
}


void init()
{
	// Set up the shaders
	GLuint shaderProgramID = CompileShaders();
	// load mesh into a vertex buffer array
	mesh_box = load_mesh(BOX);

	mesh_mainbody = load_mesh(MAIN_BODY);
	mesh_body = load_mesh(BODY);
	mesh_eyes = load_mesh(EYES);
	mesh_fangs = load_mesh(FANGS);

	for (int i = 0; i < TREES; i++) {
		toptrees[i] = load_mesh(TOPTREE);
		bottomtrees[i] = load_mesh(BOTTOMTREE);
	}
	for (int i = 0; i < ROCKS; i++) {
		rocks[i] = load_mesh(ROCK);
	}
	for (int i = 0; i < PLANES; i++) {
		planes[i] = load_mesh(PLANE);
	}

	mesh_bodyjoint_r1 = load_mesh(BODYJOINT_R1);
	mesh_bodyjoint_r2 = load_mesh(BODYJOINT_R2);
	mesh_bodyjoint_r3 = load_mesh(BODYJOINT_R3);
	mesh_bodyjoint_r4 = load_mesh(BODYJOINT_R4);

	mesh_bodyjoint_l1 = load_mesh(BODYJOINT_L1);
	mesh_bodyjoint_l2 = load_mesh(BODYJOINT_L2);
	mesh_bodyjoint_l3 = load_mesh(BODYJOINT_L3);
	mesh_bodyjoint_l4 = load_mesh(BODYJOINT_L4);

	mesh_upperleg_r1 = load_mesh(UPPERLEG_R1);
	mesh_upperleg_r2 = load_mesh(UPPERLEG_R2);
	mesh_upperleg_r3 = load_mesh(UPPERLEG_R3);
	mesh_upperleg_r4 = load_mesh(UPPERLEG_R4);

	mesh_upperleg_l1 = load_mesh(UPPERLEG_L1);
	mesh_upperleg_l2 = load_mesh(UPPERLEG_L2);
	mesh_upperleg_l3 = load_mesh(UPPERLEG_L3);
	mesh_upperleg_l4 = load_mesh(UPPERLEG_L4);

	mesh_legjoint_r1 = load_mesh(LEGJOINT_R1);
	mesh_legjoint_r2 = load_mesh(LEGJOINT_R2);
	mesh_legjoint_r3 = load_mesh(LEGJOINT_R3);
	mesh_legjoint_r4 = load_mesh(LEGJOINT_R4);

	mesh_legjoint_l1 = load_mesh(LEGJOINT_L1);
	mesh_legjoint_l2 = load_mesh(LEGJOINT_L2);
	mesh_legjoint_l3 = load_mesh(LEGJOINT_L3);
	mesh_legjoint_l4 = load_mesh(LEGJOINT_L4);

	mesh_lowerleg_r1 = load_mesh(LOWERLEG_R1);
	mesh_lowerleg_r2 = load_mesh(LOWERLEG_R2);
	mesh_lowerleg_r3 = load_mesh(LOWERLEG_R3);
	mesh_lowerleg_r4 = load_mesh(LOWERLEG_R4);

	mesh_lowerleg_l1 = load_mesh(LOWERLEG_L1);
	mesh_lowerleg_l2 = load_mesh(LOWERLEG_L2);
	mesh_lowerleg_l3 = load_mesh(LOWERLEG_L3);
	mesh_lowerleg_l4 = load_mesh(LOWERLEG_L4);

	//moth mesh
	moth_body = load_mesh(MOTH_BODY);
	moth_head = load_mesh(MOTH_HEAD);
	moth_eyes = load_mesh(MOTH_EYES);
	moth_legs = load_mesh(MOTH_LEGS);
	moth_wing_l1 = load_mesh(MOTH_WING_L1);
	moth_wing_r1 = load_mesh(MOTH_WING_R1);
	moth_wingjoint_l1 = load_mesh(MOTH_WINGJOINT_L1);
	moth_wingjoint_r1 = load_mesh(MOTH_WINGJOINT_R1);

	moth_body2 = load_mesh(MOTH_BODY);
	moth_head2 = load_mesh(MOTH_HEAD);
	moth_eyes2 = load_mesh(MOTH_EYES);
	moth_legs2 = load_mesh(MOTH_LEGS);
	moth_wing_l12 = load_mesh(MOTH_WING_L1);
	moth_wing_r12 = load_mesh(MOTH_WING_R1);
	moth_wingjoint_l12 = load_mesh(MOTH_WINGJOINT_L1);
	moth_wingjoint_r12 = load_mesh(MOTH_WINGJOINT_R1);

	moth_body3 = load_mesh(MOTH_BODY);
	moth_head3 = load_mesh(MOTH_HEAD);
	moth_eyes3 = load_mesh(MOTH_EYES);
	moth_legs3 = load_mesh(MOTH_LEGS);
	moth_wing_l13 = load_mesh(MOTH_WING_L1);
	moth_wing_r13 = load_mesh(MOTH_WING_R1);
	moth_wingjoint_l13 = load_mesh(MOTH_WINGJOINT_L1);
	moth_wingjoint_r13 = load_mesh(MOTH_WINGJOINT_R1);

	fence = load_mesh(FENCE);
	lamp = load_mesh(LAMP);
	lampglass = load_mesh(LAMPGLASS);
	lamp_light = load_mesh(LAMP_LIGHT);
	lamp_light2 = load_mesh(LAMP_LIGHT);
	lamp_light3 = load_mesh(LAMP_LIGHT);


	//Generating Vertex Arrays
	glGenVertexArrays(1, &boxVAO);

	glGenVertexArrays(1, &mainbodyVAO);
	glGenVertexArrays(1, &bodyVAO);
	glGenVertexArrays(1, &eyesVAO);
	glGenVertexArrays(1, &fangsVAO);

	glGenVertexArrays(1, &bodyjoint_r1vao);
	glGenVertexArrays(1, &bodyjoint_r2vao);
	glGenVertexArrays(1, &bodyjoint_r3vao);
	glGenVertexArrays(1, &bodyjoint_r4vao);

	glGenVertexArrays(1, &bodyjoint_l1vao);
	glGenVertexArrays(1, &bodyjoint_l2vao);
	glGenVertexArrays(1, &bodyjoint_l3vao);
	glGenVertexArrays(1, &bodyjoint_l4vao);

	glGenVertexArrays(1, &upperleg_r1vao);
	glGenVertexArrays(1, &upperleg_r2vao);
	glGenVertexArrays(1, &upperleg_r3vao);
	glGenVertexArrays(1, &upperleg_r4vao);

	glGenVertexArrays(1, &upperleg_l1vao);
	glGenVertexArrays(1, &upperleg_l2vao);
	glGenVertexArrays(1, &upperleg_l3vao);
	glGenVertexArrays(1, &upperleg_l4vao);

	glGenVertexArrays(1, &legjoint_r1vao);
	glGenVertexArrays(1, &legjoint_r2vao);
	glGenVertexArrays(1, &legjoint_r3vao);
	glGenVertexArrays(1, &legjoint_r4vao);

	glGenVertexArrays(1, &legjoint_l1vao);
	glGenVertexArrays(1, &legjoint_l2vao);
	glGenVertexArrays(1, &legjoint_l3vao);
	glGenVertexArrays(1, &legjoint_l4vao);

	glGenVertexArrays(1, &lowerleg_r1vao);
	glGenVertexArrays(1, &lowerleg_r2vao);
	glGenVertexArrays(1, &lowerleg_r3vao);
	glGenVertexArrays(1, &lowerleg_r4vao);

	glGenVertexArrays(1, &lowerleg_l1vao);
	glGenVertexArrays(1, &lowerleg_l2vao);
	glGenVertexArrays(1, &lowerleg_l3vao);
	glGenVertexArrays(1, &lowerleg_l4vao);

	//gen moth vao
	for (int i = 0; i < MOTHS; i++) {
		glGenVertexArrays(1, &moth_bodyvao[i]);
		glGenVertexArrays(1, &moth_headvao[i]);
		glGenVertexArrays(1, &moth_eyesvao[i]);
		glGenVertexArrays(1, &moth_legsvao[i]);
		glGenVertexArrays(1, &moth_wing_l1vao[i]);
		glGenVertexArrays(1, &moth_wing_r1vao[i]);
		glGenVertexArrays(1, &moth_wingjoint_l1vao[i]);
		glGenVertexArrays(1, &moth_wingjoint_r1vao[i]);
		glGenVertexArrays(1, &lamp_lightvao[i]);
	}

	glGenVertexArrays(1, &lampglassvao);
	glGenVertexArrays(1, &fencevao);
	glGenVertexArrays(1, &lampvao);

	//trees
	for (int i = 0; i < TREES; i++) {
		glGenVertexArrays(1, &toptreevao[i]);
		glGenVertexArrays(1, &bottomtreevao[i]);
	}
	for (int i = 0; i < ROCKS; i++) {
		glGenVertexArrays(1, &rocksvao[i]);
	}
	for (int i = 0; i < PLANES; i++) {
		glGenVertexArrays(1, &planesVAO[i]);
	}


	//generating object buffer.
	generateObjectBufferMesh(mesh_box, boxVAO);

	generateObjectBufferMesh(mesh_mainbody, mainbodyVAO);
	generateObjectBufferMesh(mesh_body, bodyVAO);
	generateObjectBufferMesh(mesh_eyes, eyesVAO);
	generateObjectBufferMesh(mesh_fangs, fangsVAO);

	generateObjectBufferMesh(mesh_bodyjoint_r1, bodyjoint_r1vao);
	generateObjectBufferMesh(mesh_bodyjoint_r2, bodyjoint_r2vao);
	generateObjectBufferMesh(mesh_bodyjoint_r3, bodyjoint_r3vao);
	generateObjectBufferMesh(mesh_bodyjoint_r4, bodyjoint_r4vao);

	generateObjectBufferMesh(mesh_bodyjoint_l1, bodyjoint_l1vao);
	generateObjectBufferMesh(mesh_bodyjoint_l2, bodyjoint_l2vao);
	generateObjectBufferMesh(mesh_bodyjoint_l3, bodyjoint_l3vao);
	generateObjectBufferMesh(mesh_bodyjoint_l4, bodyjoint_l4vao);

	generateObjectBufferMesh(mesh_upperleg_r1, upperleg_r1vao);
	generateObjectBufferMesh(mesh_upperleg_r2, upperleg_r2vao);
	generateObjectBufferMesh(mesh_upperleg_r3, upperleg_r3vao);
	generateObjectBufferMesh(mesh_upperleg_r4, upperleg_r4vao);

	generateObjectBufferMesh(mesh_upperleg_l1, upperleg_l1vao);
	generateObjectBufferMesh(mesh_upperleg_l2, upperleg_l2vao);
	generateObjectBufferMesh(mesh_upperleg_l3, upperleg_l3vao);
	generateObjectBufferMesh(mesh_upperleg_l4, upperleg_l4vao);

	generateObjectBufferMesh(mesh_legjoint_r1, legjoint_r1vao);
	generateObjectBufferMesh(mesh_legjoint_r2, legjoint_r2vao);
	generateObjectBufferMesh(mesh_legjoint_r3, legjoint_r3vao);
	generateObjectBufferMesh(mesh_legjoint_r4, legjoint_r4vao);

	generateObjectBufferMesh(mesh_legjoint_l1, legjoint_l1vao);
	generateObjectBufferMesh(mesh_legjoint_l2, legjoint_l2vao);
	generateObjectBufferMesh(mesh_legjoint_l3, legjoint_l3vao);
	generateObjectBufferMesh(mesh_legjoint_l4, legjoint_l4vao);

	generateObjectBufferMesh(mesh_lowerleg_r1, lowerleg_r1vao);
	generateObjectBufferMesh(mesh_lowerleg_r2, lowerleg_r2vao);
	generateObjectBufferMesh(mesh_lowerleg_r3, lowerleg_r3vao);
	generateObjectBufferMesh(mesh_lowerleg_r4, lowerleg_r4vao);

	generateObjectBufferMesh(mesh_lowerleg_l1, lowerleg_l1vao);
	generateObjectBufferMesh(mesh_lowerleg_l2, lowerleg_l2vao);
	generateObjectBufferMesh(mesh_lowerleg_l3, lowerleg_l3vao);
	generateObjectBufferMesh(mesh_lowerleg_l4, lowerleg_l4vao);

	//gen obj buffer moth
	for (int i = 0; i < MOTHS; i++) {
		generateObjectBufferMesh(moth_body, moth_bodyvao[i]);
		generateObjectBufferMesh(moth_head, moth_headvao[i]);
		generateObjectBufferMesh(moth_eyes, moth_eyesvao[i]);
		generateObjectBufferMesh(moth_legs, moth_legsvao[i]);

		generateObjectBufferMesh(moth_wing_l1, moth_wing_l1vao[i]);
		generateObjectBufferMesh(moth_wing_r1, moth_wing_r1vao[i]);
		generateObjectBufferMesh(moth_wingjoint_l1, moth_wingjoint_l1vao[i]);
		generateObjectBufferMesh(moth_wingjoint_r1, moth_wingjoint_r1vao[i]);
		generateObjectBufferMesh(lamp_light, lamp_lightvao[i]);
	}

	generateObjectBufferMesh(lampglass, lampglassvao);
	generateObjectBufferMesh(fence, fencevao);
	generateObjectBufferMesh(lamp, lampvao);

	//trees
	for (int i = 0; i < TREES; i++) {
		generateObjectBufferMesh(toptrees[i], toptreevao[i]);
		generateObjectBufferMesh(bottomtrees[i], bottomtreevao[i]);
	}
	for (int i = 0; i < ROCKS; i++) {
		generateObjectBufferMesh(rocks[i], rocksvao[i]);
	}
	for (int i = 0; i < PLANES; i++) {
		generateObjectBufferMesh(planes[i], planesVAO[i]);
	}

	glGenTextures(13, textures);
	loadTexture(GL_TEXTURE0, textures[0], TEX_TOPTREE,TEX_TOPTREE_NAME, 0);
	loadTexture(GL_TEXTURE1, textures[1], TEX_BOTTOMTREE, TEX_BOTTOMTREE_NAME, 1);
	loadTexture(GL_TEXTURE2, textures[2], TEX_GROUND, TEX_GROUND_NAME, 2);
	loadTexture(GL_TEXTURE3, textures[3], TEX_FENCE, TEX_FENCE_NAME, 3);
	loadTexture(GL_TEXTURE4, textures[4], TEX_SPIDERBODY, TEX_SPIDERBODY_NAME, 4);
	loadTexture(GL_TEXTURE5, textures[5], TEX_SPIDERLEG, TEX_SPIDERLEG_NAME, 5);
	loadTexture(GL_TEXTURE6, textures[6], TEX_MOTHBODY, TEX_MOTHBODY_NAME, 6);
	loadTexture(GL_TEXTURE7, textures[7], TEX_MOTHWING, TEX_MOTHWING_NAME, 7);
	loadTexture(GL_TEXTURE8, textures[8], TEX_LAMP, TEX_LAMP_NAME, 8);
	loadTexture(GL_TEXTURE9, textures[9], TEX_LAMPGLASS, TEX_LAMPGLASS_NAME, 9);
	loadTexture(GL_TEXTURE10, textures[10], TEX_BUGEYES, TEX_BUGEYES_NAME, 10);
	loadTexture(GL_TEXTURE11, textures[11], TEX_ROCK, TEX_ROCK_NAME, 11);
	loadTexture(GL_TEXTURE12, textures[12], TEX_BOX, TEX_BOX_NAME, 12);
}

void keypress(unsigned char key, int x, int y) {
	if (key == 'w') {
		wPressed = true;
		sPressed = false;
		pPressed = false;
		oPressed = false;
	}
	if (key == 's') {
		sPressed = true;
		wPressed = false;
		pPressed = false;
		oPressed = false;
	}
	if (key == 'a') {

	}
	if (key == 'd') {

	}
	if (key == 'z') {
		wPressed = false;
		sPressed = false;
		pPressed = false;
		oPressed = false;
	}
	if (key == 'p') {
		if (pPressed == false) {
			pPressed = true;
			wPressed = false;
			sPressed = false;
			oPressed = false;
		}
		else if (pPressed == true) {
			pPressed = false;
			wPressed = false;
			sPressed = false;
			oPressed = false;
		}

	}
	if (key == 'o') {
		if (oPressed == false) {
			pPressed = false;;
			wPressed = false;
			sPressed = false;
			oPressed = true;
		}
		else if (oPressed == true) {
			pPressed = false;
			wPressed = false;
			sPressed = false;
			oPressed = false;

		}
	}

	if (key == 'q') {
		if (qPressed == true)
			qPressed = false;
		else if (qPressed == false)
			qPressed = true;
	}

}
void specialkeypress(int arrow, int x, int y) {
	float camSpeed = 1.0f * delta *1000;
	if (arrow == GLUT_KEY_UP) {
		positionCam += camFront * (camSpeed);
	}
	else if (arrow == GLUT_KEY_DOWN) {
		positionCam -= camFront * (camSpeed);
	}
	else if (arrow == GLUT_KEY_RIGHT) {
		positionCam += normalise(cross(camFront, upAxis)) * (camSpeed) ;
	}
	else if (arrow == GLUT_KEY_LEFT) {
		positionCam -= normalise(cross(camFront, upAxis)) * (camSpeed);

	}
}
void mouse(int button, int state,  int x, int y) {
	if (button == 3) {
		fov -= (float)y * 0.001f;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 60.0f)
			fov = 60.0f;
		//cout << fov << " " ;
	}	
	if (button == 4) {
		fov += (float)y * 0.001f;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 45.0f)
			fov = 45.0f;
		//cout << fov << " " ;
	}
}

void mouseMove(int x, int y) {
	//cout << firstRotate;
	float x2 = (float)x;
	float y2 = (float)y;
	if (firstRotate == true)
	{
		lastX = x2;
		lastY = y2;
		firstRotate = false;
	}
	//cout << pitch << " ";
	float offsetX = x2 - lastX;
	float offsetY = lastY - y2;
	lastX = x2; lastY = y2;
	offsetX *= sens;
	offsetY *= sens;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	vec3 camDirection = vec3(cos(radians(yaw)) * cos(radians(pitch)), sin(radians(pitch)), sin(radians(yaw)) * cos(radians(pitch)));
	camFront = normalise(camDirection);
}

int main(int argc, char** argv) {

	// Set up the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("CompGraphics Assignment");

	// Tell glut where the display function is
	glutSetCursor(GLUT_CURSOR_LEFT_SIDE);
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);
	glutKeyboardFunc(keypress);
	glutSpecialFunc(specialkeypress);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	// A call to glewInit() must be done after glut is initialized!
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	// Set up your objects and shaders
	init();
	// Begin infinite event loop
	glutMainLoop();
	return 0;
}
