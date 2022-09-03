#include "Application.hpp"

void Foo(auto x) 
{
    std::cout << x << std::endl;
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    glo::Program lightShader  = glo::Program("res/shaders/light.glsl");
    glo::Program lightSourceShader = glo::Program("res/shaders/lightSource.glsl");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    glo::VertexArray vao = glo::VertexArray(8);
    vao.Bind();

    glo::Buffer vbo = glo::Buffer(GL_ARRAY_BUFFER);
    vbo.Fill(sizeof(vertices), vertices);
    vao.Push(3);
    vao.Push(3);
    vao.Push(2);

    glo::VertexArray lightVao = glo::VertexArray(8);
    lightVao.Bind();
    lightVao.Push(3);

    lightShader.Bind();

    glo::Texture diffuseTexture = glo::Texture(0, "res/textures/container.png");
    diffuseTexture.Bind();
    lightShader.SetUniform1i("material.diffuse", 0);

    glo::Texture specularTexture = glo::Texture(1, "res/textures/container_specular.png");
    specularTexture.Bind();
    lightShader.SetUniform1i("material.specular", 1);

    lightShader.SetUniform1f("material.shininess", 32.0f);

    //set spotlight
    lightShader.SetUniform3f("spotLight.ambient", 0.2f, 0.2f, 0.2f);
    lightShader.SetUniform3f("spotLight.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
    lightShader.SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightShader.SetUniform1f("spotLight.cosInner", cosf(glm::radians(12.5f)));
    lightShader.SetUniform1f("spotLight.cosOuter", cosf(glm::radians(22.5f)));
    


    //set point lights
    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++)
    {
        std::string pointLight = std::string("pointLights") + "[" + std::to_string(i) + "]";
        lightShader.SetUniformVec(pointLight + ".position", pointLightPositions[i]);
        lightShader.SetUniform3f(pointLight + ".ambient", 0.2f, 0.2f, 0.2f);
        lightShader.SetUniform3f(pointLight + ".diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        lightShader.SetUniform3f(pointLight + ".specular", 1.0f, 1.0f, 1.0f);
        lightShader.SetUniform3f(pointLight + ".coefficients", 1.0f, 0.52f, 0.44f);
    }



    lightSourceShader.Bind();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glm::mat4 model;
    glm::mat4 proj;

    while (!glfwWindowShouldClose(window))
    {
        proj = glm::perspective(glm::radians(fov), RATIO, 0.1f, 100.0f);;

        UpdateTime();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ProcessInput();

        lightShader.Bind();
        lightShader.SetUniformMat("view", camera.GetView());
        lightShader.SetUniformVec("viewPos", camera.position);
        lightShader.SetUniformVec("spotLight.direction", camera.front);
        lightShader.SetUniformVec("spotLight.position", camera.position);
        lightShader.SetUniformMat("proj", proj);
        vao.Bind();

        for (int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
        {
            game::Transform t = game::Transform(cubePositions[i], glm::vec3(1.0f));
            t.SetAngle(glm::vec3(1.0f, 0.3f, 0.5f), 20.0f * i);
            t.position = cubePositions[i];
            lightShader.SetUniformMat("model", t.GetModel());
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        lightSourceShader.Bind();
        lightSourceShader.SetUniformMat("view", camera.GetView());
        lightVao.Bind();

        for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++)
        {
            lightSourceShader.SetUniform3f("lightColour", 1.0f, 1.0f, 1.0f);
            model = glm::translate(glm::mat4(1.0f), pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightSourceShader.SetUniformMat("model", model);
            lightSourceShader.SetUniformMat("proj", proj);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void ProcessInput()
{
    if (KeyPressed(GLFW_KEY_ESCAPE))
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (KeyPressed(GLFW_KEY_ENTER))
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);;

    if (KeyPressed(GLFW_KEY_W))
        camera.position += camera.front * camSpeed * dt;
    if (KeyPressed(GLFW_KEY_S))
        camera.position -= camera.front * camSpeed * dt;
    if (KeyPressed(GLFW_KEY_D))
        camera.position += camera.right * camSpeed * dt;
    if (KeyPressed(GLFW_KEY_A))
        camera.position -= camera.right * camSpeed * dt;
}

bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xCur, double yCur) 
{
    if (firstMouse)
    {
        xLast = xCur;
        yLast = yCur;
        firstMouse = false;
    }
    float xOffset = xCur - xLast;
    float yOffset = yLast - yCur;

    xLast = xCur;
    yLast = yCur;

    xOffset *= 180.0f * sensetivity / SCR_WIDTH;
    yOffset *= 180.0f * sensetivity / SCR_HEIGHT;

    yaw += xOffset;
    pitch += yOffset;

    camera.front = glm::vec3
    (
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    );

    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov += yoffset;
    Math::bound(fov, 1.0f, 89.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}