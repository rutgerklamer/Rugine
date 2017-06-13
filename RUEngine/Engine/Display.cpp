
#include "Display.h"
#include "math.h"

Display::Display()
{
  //Make the input before initializing glfw
  //So glfw knows where to refer the callbacks to.
  input = new Input();
  input->setCamera(&camera);
  //Make the resourcemanager
  resourcemanager = new ResourceManager();
  //Initialize glfw
  initGlfw();
  //Make a renderer
  renderer = new Renderer();
  //Make a shader after initializing glew
  shader = new Shader("Shaders/3D/shader.vert", "Shaders/3D/shader.frag","","","");
  shaderNormals = new Shader("Shaders/Normals/shader.vert", "Shaders/Normals/shader.frag","","","Shaders/Normals/shader.geom");
  shaderExplode = new Shader("Shaders/Explode/shader.vert", "Shaders/Explode/shader.frag","","","Shaders/Explode/shader.geom");
  scene = new Scene(input);
  scene0 = new Scene0(input);
  scene1 = new Scene1(input);
  scenes.push_back(scene);
  scenes.push_back(scene0);
  scenes.push_back(scene1);
  dtime = new Time();
  std::cout << "Display initialized" << std::endl;
  scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
  //We want to run this atleast once.
  //Get the projection matrix

  do {
    //Clear window with a red-"ish" color
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (input->isDown(93) && currentscene < scenes.size() - 1) {
      currentscene++;
      input->setKey(93, false);
      scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    }
    if (input->isDown(91) && currentscene > 0) {
      currentscene--;
      input->setKey(91, false);
      scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    }
    scenes[currentscene]->Update(dtime->getDeltatime());
    resourcemanager->updateShaders(shader, scenes[currentscene]->camera);
    for (int i = 0; i < scenes[currentscene]->meshes.size(); i++) {
      if (scenes[currentscene]->lights.size() > 0) {
         renderer->render(glfwGetTime(), shader, scenes[currentscene]->camera, scenes[currentscene]->meshes[i], scenes[currentscene]->lights[0]);
       } else {
         renderer->render(glfwGetTime(), shader, scenes[currentscene]->camera, scenes[currentscene]->meshes[i]);
       }
    }
    resourcemanager->updateShaders(shaderNormals, scenes[currentscene]->camera);
    for (int i = 0; i < scenes[currentscene]->meshes.size(); i++) {
      if (scenes[currentscene]->meshes[i]->showNormals) {
         renderer->render(glfwGetTime(), shaderNormals, scenes[currentscene]->camera, scenes[currentscene]->meshes[i]);
       }
    }

    //Get deltatime and fps
    dtime->update();
    //Update camera movement
    //TODO remove
    input->doMovement(dtime->getDeltatime());
    //Get the current screen
    glfwSwapBuffers(window);
    //Update glfw's input
    glfwPollEvents();
  } while (!glfwWindowShouldClose(window));

  //Destroy everything glfw has made.
  glfwDestroyWindow(window);
  glfwTerminate();
}

Display::~Display() {
  //Destroy everything for memory leaks
  delete input;
  delete renderer;
  delete shader;
  delete shaderNormals;
  delete shaderExplode;
  delete scene;
  delete scene0;
  delete dtime;
  delete window;
  delete resourcemanager;
}

void Display::initGlfw()
{
  //Initialize glfw
  if (!glfwInit())
  {
    std::cout << "glfw is not supported!" << std::endl;
  }
  //Set some window hints
  //See glfw's documentation for more info
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowinfo.majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowinfo.minorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  //Create the window
  window = glfwCreateWindow(windowinfo.windowWidth, windowinfo.windowHeight, windowinfo.windowName.c_str(), nullptr, nullptr);
  glfwGetFramebufferSize(window, &windowinfo.windowWidth, &windowinfo.windowHeight);

  //Check if there is a window
  if (!window)
  {
    std::cout << "glfw window failed to create" << std::endl;
    glfwTerminate();
  }

  //Say we want to render to this window
  glfwMakeContextCurrent(window);
  initGlew();

  //Set the callbacks to the Input() class
  glfwSetKeyCallback(window, input->keyCallBack);
  glfwSetCursorPosCallback(window, input->mouseCallBack);
  glfwSetMouseButtonCallback(window, input->mouseButtonCallback);
  //Lock the cursor
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Display::initGlew()
{
  glewExperimental = GL_TRUE;

  //Initialize GLEW
  if (glewInit() != GLEW_OK) {
      std::cout << "Failed to initialize GLEW" << std::endl;
  }
  //Enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  //Enable backface culling
  glEnable(GL_CULL_FACE);
}
