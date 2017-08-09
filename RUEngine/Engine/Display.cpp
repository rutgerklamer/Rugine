
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
  input->setWindow(window);
  //Make a renderer
  renderer = new Renderer();
  //Make a shader after initializing glew
  shader = new Shader("Shaders/3D/shader.vert", "Shaders/3D/shader.frag","","","");
  shaderNormals = new Shader("Shaders/Normals/shader.vert", "Shaders/Normals/shader.frag","","","Shaders/Normals/shader.geom");
  shaderExplode = new Shader("Shaders/Explode/shader.vert", "Shaders/Explode/shader.frag","","","Shaders/Explode/shader.geom");
  shaderSkybox = new Shader("Shaders/SkyboxShaders/shader.vert", "Shaders/SkyboxShaders/shader.frag","","","");
  shaderReflection = new Shader("Shaders/StrongReflection/shader.vert", "Shaders/StrongReflection/shader.frag","","","");
  shaderTransparent = new Shader("Shaders/Transparent/shader.vert", "Shaders/Transparent/shader.frag","","","");
  waterShader = new Shader("Shaders/Water/shader.vert", "Shaders/Water/shader.frag","","","");
  dtime = new Time();
  scenemanager = new SceneManager(input);
  raycaster = new Raycast(&camera, input);
  std::cout << "Display initialized" << std::endl;
  //We want to run this atleast once.
  //Get the projection matrix
}

void Display::addScene(Superscene* scene)
{
  scenemanager->scenes.push_back(scene);
}

void Display::whatToRender(glm::vec4 waterPlane)
{
  for (int i = 0; i < scenemanager->scenes[currentscene]->entities.size(); i++) {
    if (scenemanager->scenes[currentscene]->entities[i] != nullptr) {
  //    raycaster->checkCollision(scenemanager->scenes[currentscene]->entities[i]);
    }
      if (scenemanager->scenes[currentscene]->lights.size() > 0 && scenemanager->scenes[currentscene]->entities[i]->enabled && !scenemanager->scenes[currentscene]->entities[i]->reflective && !scenemanager->scenes[currentscene]->entities[i]->transparent) {
         renderer->render(glfwGetTime(), shader, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->entities[i], scenemanager->scenes[currentscene]->getSceneData(),waterPlane, &scenemanager->scenes[currentscene]->lights);

       } else if (scenemanager->scenes[currentscene]->entities[i]->enabled && !scenemanager->scenes[currentscene]->entities[i]->reflective && !scenemanager->scenes[currentscene]->entities[i]->transparent) {
         renderer->render(glfwGetTime(), shader, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->entities[i], scenemanager->scenes[currentscene]->getSceneData(), waterPlane);
       } else if (scenemanager->scenes[currentscene]->entities[i]->reflective  && !scenemanager->scenes[currentscene]->entities[i]->transparent)
       {
         renderer->renderSkybox(glfwGetTime(), shaderReflection, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->entities[i], scenemanager->scenes[currentscene]->getSceneData(), waterPlane, scenemanager->scenes[currentscene]->skybox->getTexture());
         shader->Use();
       } else if (scenemanager->scenes[currentscene]->entities[i]->transparent)
       {
         renderer->renderSkybox(glfwGetTime(), shaderTransparent, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->entities[i], scenemanager->scenes[currentscene]->getSceneData(), waterPlane, scenemanager->scenes[currentscene]->skybox->getTexture());
         shader->Use();
       }
       if (scenemanager->scenes[currentscene]->entities[i]->showNormals && scenemanager->scenes[currentscene]->entities[i]->enabled) {
          resourcemanager->updateShaders(shaderNormals, scenemanager->scenes[currentscene]->camera);
          renderer->render(glfwGetTime(), shaderNormals, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->entities[i], scenemanager->scenes[currentscene]->getSceneData(), waterPlane);
          shader->Use();
        }
  }
}


void Display::gameLoop()
{
  scenemanager->scenes[currentscene]->input->setCamera(scenemanager->scenes[currentscene]->camera);
  raycaster->setCamera(scenemanager->scenes[currentscene]->camera);
  resourcemanager->setProjectionMatrix(shaderNormals, scenemanager->scenes[currentscene]->camera);
  resourcemanager->setProjectionMatrix(shader, scenemanager->scenes[currentscene]->camera);
  resourcemanager->setProjectionMatrix(shaderSkybox, scenemanager->scenes[currentscene]->camera);
  resourcemanager->setProjectionMatrix(waterShader, scenemanager->scenes[currentscene]->camera);
  do {
    if (input->isDown(93) && currentscene < scenemanager->scenes.size() - 1) {
      currentscene++;
      input->setKey(93, false);
      scenemanager->scenes[currentscene]->input->setCamera(scenemanager->scenes[currentscene]->camera);
      raycaster->setCamera(scenemanager->scenes[currentscene]->camera);
      resourcemanager->removeLights(shader);
    }
    if (input->isDown(91) && currentscene > 0) {
      currentscene--;
      input->setKey(91, false);
      scenemanager->scenes[currentscene]->input->setCamera(scenemanager->scenes[currentscene]->camera);
      raycaster->setCamera(scenemanager->scenes[currentscene]->camera);
      resourcemanager->removeLights(shader);
    }
    scenemanager->scenes[currentscene]->Update(dtime->getDeltatime());
    resourcemanager->updateShaders(waterShader, scenemanager->scenes[currentscene]->camera);
    resourcemanager->updateShaders(shader, scenemanager->scenes[currentscene]->camera);

    if (scenemanager->scenes[currentscene]->water != nullptr) {
      glBindFramebuffer(GL_FRAMEBUFFER, scenemanager->scenes[currentscene]->water->top->fbo);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_CLIP_DISTANCE0);
      float dist = 2* (scenemanager->scenes[currentscene]->camera->getPosition().y - scenemanager->scenes[currentscene]->water->waterPosition.y);
      scenemanager->scenes[currentscene]->camera->setPosition(glm::vec3(scenemanager->scenes[currentscene]->camera->getPosition().x,scenemanager->scenes[currentscene]->camera->getPosition().y - dist,scenemanager->scenes[currentscene]->camera->getPosition().z));
      scenemanager->scenes[currentscene]->camera->invertPitch();
      resourcemanager->updateShaders(shader, scenemanager->scenes[currentscene]->camera);
      resourcemanager->updateShaders(shaderReflection, scenemanager->scenes[currentscene]->camera);
      renderer->renderSkybox(glfwGetTime(), shaderSkybox, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->skybox, scenemanager->scenes[currentscene]->getSceneData(), glm::vec4(0,0,0,0), scenemanager->scenes[currentscene]->skybox->getTexture());
      whatToRender(glm::vec4(0,1,0,scenemanager->scenes[currentscene]->water->waterPosition.y));

      glBindFramebuffer(GL_FRAMEBUFFER, scenemanager->scenes[currentscene]->water->bottom->fbo);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_CLIP_DISTANCE0);
      scenemanager->scenes[currentscene]->camera->setPosition(glm::vec3(scenemanager->scenes[currentscene]->camera->getPosition().x,scenemanager->scenes[currentscene]->camera->getPosition().y + dist,scenemanager->scenes[currentscene]->camera->getPosition().z));
      scenemanager->scenes[currentscene]->camera->invertPitch();
      resourcemanager->updateShaders(shader, scenemanager->scenes[currentscene]->camera);
      resourcemanager->updateShaders(shaderReflection, scenemanager->scenes[currentscene]->camera);
      renderer->renderSkybox(glfwGetTime(), shaderSkybox, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->skybox, scenemanager->scenes[currentscene]->getSceneData(), glm::vec4(0,0,0,0), scenemanager->scenes[currentscene]->skybox->getTexture());
      whatToRender(glm::vec4(0,-1,0,scenemanager->scenes[currentscene]->water->waterPosition.y));
    }
    if (scenemanager->scenes[currentscene]->framebuffer != nullptr) {
      glBindFramebuffer(GL_FRAMEBUFFER, scenemanager->scenes[currentscene]->framebuffer->fbo);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      //Clear window with a red-"ish" color
      glClearColor(0.3,0.3,0.3,1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    //raycaster->Update();
    if (scenemanager->scenes[currentscene]->skybox != NULL)
    {
      shaderSkybox->Use();
      resourcemanager->updateShaders(shaderSkybox, scenemanager->scenes[currentscene]->camera);
      renderer->renderSkybox(glfwGetTime(), shaderSkybox, scenemanager->scenes[currentscene]->camera, scenemanager->scenes[currentscene]->skybox, scenemanager->scenes[currentscene]->getSceneData(), glm::vec4(0,0,0,0), scenemanager->scenes[currentscene]->skybox->getTexture());
      shader->Use();
    }
    glDisable(GL_CLIP_DISTANCE0);
    whatToRender(glm::vec4(0,0,0,0));
    if (scenemanager->scenes[currentscene]->water != nullptr) {
    //  waterShader->Use();
    GLuint texture = scenemanager->scenes[currentscene]->water->top->framebufferTexture;
      renderer->renderWater(waterShader, texture, scenemanager->scenes[currentscene]->water->bottom->framebufferTexture, scenemanager->scenes[currentscene]->water->DUDVmap, scenemanager->scenes[currentscene]->water->normalMap, scenemanager->scenes[currentscene]->water->entity);
      //renderer->renderFramebuffer(scenemanager->scenes[currentscene]->water->top->shader, texture, input);
      shaderReflection->Use();
    }
    if (scenemanager->scenes[currentscene]->framebuffer != nullptr) {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glDisable(GL_DEPTH_TEST);
      renderer->renderFramebuffer(scenemanager->scenes[currentscene]->framebuffer->shader, scenemanager->scenes[currentscene]->framebuffer->framebufferTexture, input);
      glEnable(GL_DEPTH_TEST);
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
  delete waterShader;
  delete shaderSkybox;
  delete shaderTransparent;
  delete shaderReflection;
  delete dtime;
  delete window;
  delete resourcemanager;
  delete scenemanager;
  delete raycaster;
  for (unsigned int i = 0; i < scenes.size(); i++)
  {
    delete scenes[i];
  }
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
  glCullFace(GL_BACK);
}
