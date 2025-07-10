#include "../headers/Tile.h"
#include "../headers/Wall.h"
#include "../headers/Map.h"
#include "../headers/Player.h"

const unsigned int width = 800;
const unsigned int height = 800;

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Vertices coordinates
Vertex verticesTile[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Vertices coordinates
Vertex verticesWall[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


// Create mesh helper function
Mesh createMesh(Vertex* vertices, size_t vCount, GLuint* indices, size_t iCount, Texture* textures, size_t tCount) {
    std::vector <Vertex> verts(vertices, vertices + vCount/sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + iCount/ sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + tCount / sizeof(Texture));
    return Mesh(verts, ind, tex);
}

Mesh createFloorMesh() {
    Texture texturesPlank[] {
        Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("planksSpec.png", "specular", 1 , GL_RED, GL_UNSIGNED_BYTE),
    };

    return createMesh(verticesTile, sizeof(verticesTile), indices, sizeof(indices), texturesPlank, sizeof(texturesPlank));
}

Mesh createLightMesh() {
    Texture texturesPlank[] {
        Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("planksSpec.png", "specular", 1 , GL_RED, GL_UNSIGNED_BYTE),
    };

    return createMesh(lightVertices, sizeof(lightVertices), lightIndices, sizeof(lightIndices), texturesPlank, sizeof(texturesPlank));
}

Mesh createWallMesh() {
    Texture texturesBrick[] {Texture("brick.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)};

    return createMesh(verticesWall, sizeof(verticesWall), indices, sizeof(indices), texturesBrick, sizeof(texturesBrick));
}

void setUpLight(Shader& lightShader, glm::vec3 lightPos, glm::mat4 lightModel, glm::vec4 lightColor) {
    lightModel = glm::translate(lightModel, lightPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}

int main()
{   
    //--- Window Setup ---
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow *window;
    window = glfwCreateWindow(width, height, "DoomClone", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Scene Setup

    Mesh floorMesh = createFloorMesh();
    Mesh wallMesh = createWallMesh();

    Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
    

    Map map;

    //map.addCorridor(glm::vec3(0.0f, 0.0f, 0.0f), &floorMesh, &wallMesh);
    //map.addCorridor(glm::vec3(2.0f, 0.0f, 0.0f), &floorMesh, &wallMesh);
    map.generateGrid(4, &floorMesh);

    Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");
    Mesh light = createLightMesh();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    setUpLight(lightShader, lightPos, lightModel, lightColor);
    
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    //Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    Player camera(width, height, glm::vec3(4.0f, 2.0f, 2.0f));

    // Main loop

    while (!glfwWindowShouldClose(window))
    {
        // Background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 pos = camera.Position;
        std::string printable = std::to_string(pos.x) + ", " +  std::to_string(pos.z);

        glfwSetWindowTitle(window, printable.c_str());

        // 4. Handle player input
        camera.Inputs(window, &map);

        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        
        light.Draw(lightShader, camera);
        map.Draw(camera, shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}