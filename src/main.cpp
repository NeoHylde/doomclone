#include "../headers/Tile.h"
#include "../headers/Wall.h"
#include "../headers/Map.h"
#include "../headers/Player.h"
#include "../headers/MeshFactory.h"
#include "../headers/Model.h"
#include "../headers/Enemy.h"
#include "../headers/AStar.h"
#include "../headers/Graph.h"

const unsigned int width = 800;
const unsigned int height = 800;

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
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
    Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");
    Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");

    MeshFactory mf;
    Mesh* floorMesh = mf.createFloorMesh();
    Mesh* light = mf.createLightMesh();

    Map map;
    map.generateGrid(8, floorMesh);

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
    Model model("resources/skeleton/scene.gltf", glm::vec3(8.0f, 0.0f, 4.0f));
    Graph graph(map);
    AStar astar(&graph);
    Enemy enemy(&model, &astar, glm::vec3(8.0f, 0.0f, 4.0f));

    // Main loop
    double previousTime = glfwGetTime(); 
    int frameCount = 0;

    double lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        // Background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Get current time
        double currentTime = glfwGetTime();
        frameCount++;

        // If one second has passed, calculate and show FPS
        
        if (currentTime - previousTime >= 1.0) {
            std::string printable = 
                std::to_string(camera.Position.x) + ", " +
                std::to_string(camera.Position.z) + 
                " FPS: " + std::to_string(frameCount);
            glfwSetWindowTitle(window, printable.c_str());

            // Reset counter and time
            frameCount = 0;
            previousTime = currentTime;
        }

        camera.Inputs(window, &map);
        camera.updateMatrix(90.0f, 0.1f, 100.0f);
        /** light->Draw(
            lightShader,
            camera,
            glm::mat4(1.0f),               // model matrix
            lightPos,                      // translation
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f), // identity rotation
            glm::vec3(1.0f)                // uniform scale
        );*/
        map.Draw(camera, shaderProgram);
        enemy.Draw(shaderProgram, camera);

        static glm::vec3 lastTarget = glm::vec3(0.0f);
        glm::vec3 currentTarget = camera.Position;

        float deltaTime = static_cast<float>(currentTime - lastFrameTime);
        lastFrameTime = currentTime;
        enemy.updatePos(deltaTime);

        if (glm::distance(currentTarget, lastTarget) > 1.0f) {
            enemy.getPath(currentTarget);
            lastTarget = currentTarget;
        }

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    graph.Delete();

    delete light;
    delete floorMesh;
    shaderProgram.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}