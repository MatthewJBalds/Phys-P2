#include <iostream>
#include <string>
#include <chrono>
#include <limits>
#include <vector>
#include <iomanip>
#include <cmath>
#include "GameObject.h"


//#include "p6/bungee/bungee.h"
#include "p6/Chain/Chain.h"

//#include "p6/Links/Rod.h"

#include "p6/PhysicsWorld.h"
//#include "p6/P6Particle.h"
#include "p6/RenderParticle.h"
#include "p6/RenderLine.h"
#include "p6/ParticleContact.h"

#include "Camera/OrthoCamera.h"
#include "Camera/PerspectiveCamera.h"





using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

enum class CameraMode {
    Orthographic,
    Perspective
};

int main(void)
{

    GLFWwindow* window;
    float window_width = 800;
    float window_height = 800;

    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);


    float cableLength;
    float particleGap, particleRad;
    float gravityStrength;
    float forceX, forceY, forceZ;

    //For User Inputs
    std::cout << "Cable Length: "; std::cin >> cableLength;
    std::cout << "Particle Gap: "; std::cin >> particleGap;
    std::cout << "Particle Radius: "; std::cin >> particleRad;
    std::cout << "Gravity Strength: "; std::cin >> gravityStrength;
    std::cout << "Apply Force: " << std::endl;
    std::cout << "x: "; std::cin >> forceX;
    std::cout << "y: "; std::cin >> forceY;
    std::cout << "z: "; std::cin >> forceZ;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(window_width, window_height, "Group 5 Phase 2: Baldonado - Macaraeg", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    auto ortho_camera = new OrthoCamera();
    ortho_camera->setCameraPosition(glm::vec3(0.0f, 0.0f, 400.0f));
    auto pers_camera = new PerspectiveCamera();
    pers_camera->setCameraPosition(glm::vec3(0, 0.f, 550.f));
    auto pWorld = physics::PhysicsWorld(MyVector(0, gravityStrength, 0));
    auto sphere = GameObject("3D/sphere.obj", "Shaders/sample.vert", "Shaders/sample.frag");

    glViewport(0, 0, 800, 800);
    std::list<RenderParticle*> RenderParticles;

    float fThreshHold = 0.2f;
    float fTicks = 0.0f;

    CameraMode currentCameraMode = CameraMode::Orthographic;

    glm::mat4 identity_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
    bool paused = false;
    bool pressed = false;


    //Create Particles 
 
  

    physics::PhysicsParticle p3 = physics::PhysicsParticle();
    p3.Position = physics::MyVector(0, 100, 0);
    p3.mass = 50;
    p3.radius = particleRad;
    pWorld.AddParticle(&p3);

    physics::PhysicsParticle p2 = physics::PhysicsParticle();
    p2.Position = physics::MyVector(p3.Position.x - particleGap, 100, 0);
    p2.mass = 50;
    p2.radius = particleRad;
    pWorld.AddParticle(&p2);

    physics::PhysicsParticle p1 = physics::PhysicsParticle();
    p1.Position = physics::MyVector(p2.Position.x - particleGap, 100, 0);
    p1.mass = 50;
    p1.radius = particleRad;
    pWorld.AddParticle(&p1);

    physics::PhysicsParticle p4 = physics::PhysicsParticle();
    p4.Position = physics::MyVector(p3.Position.x + particleGap, 100, 0);
    p4.mass = 50;
    p4.radius = particleRad;
    pWorld.AddParticle(&p4);

    physics::PhysicsParticle p5 = physics::PhysicsParticle();
    p5.Position = physics::MyVector(p4.Position.x + particleGap, 100, 0);
    p5.mass = 50;
    p5.radius = particleRad;
    pWorld.AddParticle(&p5);

    //springs for force registry
    physics::MyVector springPos3 = physics::MyVector(0, 150, 0);
    physics::Chain chainSpring3 = Chain(springPos3, 0, cableLength);
    pWorld.forceRegistry.Add(&p3, &chainSpring3);

    physics::MyVector springPos2 = physics::MyVector(springPos3.x - particleGap, 150, 0);
    physics::Chain chainSpring2 = Chain(springPos2, 0, cableLength);
    pWorld.forceRegistry.Add(&p2, &chainSpring2);

    physics::MyVector springPos1 = physics::MyVector(springPos2.x - particleGap, 150, 0);
    physics::Chain chainSpring1 = Chain(springPos1, 0, cableLength);
    pWorld.forceRegistry.Add(&p1, &chainSpring1);

    physics::MyVector springPos4 = physics::MyVector(springPos3.x + particleGap, 150, 0);
    physics::Chain chainSpring4 = Chain(springPos4, 0, cableLength);
    pWorld.forceRegistry.Add(&p4, &chainSpring4);

    physics::MyVector springPos5 = physics::MyVector(springPos4.x + particleGap, 150, 0);
    physics::Chain chainSpring5 = Chain(springPos5, 0, cableLength);
    pWorld.forceRegistry.Add(&p5, &chainSpring5);

    //Render Particles
    RenderParticle rp1 = RenderParticle(&p1, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p1.radius);
    RenderParticles.push_back(&rp1);

    RenderParticle rp2 = RenderParticle(&p2, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p2.radius);
    RenderParticles.push_back(&rp2);

    RenderParticle rp3 = RenderParticle(&p3, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p3.radius);
    RenderParticles.push_back(&rp3);

    RenderParticle rp4 = RenderParticle(&p4, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p4.radius);
    RenderParticles.push_back(&rp4);

    RenderParticle rp5 = RenderParticle(&p5, &sphere, glm::vec4(0.4f, 0, 0, 0.f), p5.radius);
    RenderParticles.push_back(&rp5);

    RenderLine p1Line = RenderLine(springPos1, p1.Position, glm::vec4(1, 1, 1, 1));
    RenderLine p2Line = RenderLine(springPos2, p2.Position, glm::vec4(1, 1, 1, 1));
    RenderLine p3Line = RenderLine(springPos3, p3.Position, glm::vec4(1, 1, 1, 1));
    RenderLine p4Line = RenderLine(springPos4, p4.Position, glm::vec4(1, 1, 1, 1));
    RenderLine p5Line = RenderLine(springPos5, p5.Position, glm::vec4(1, 1, 1, 1));



    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;

        curr_ns += dur;


        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            curr_ns -= curr_ns;

            if (glfwGetKey(window, GLFW_KEY_1))
            {
                std::cout << "Switching to Orthographic Camera" << std::endl;
                currentCameraMode = CameraMode::Orthographic;
            }
            if (glfwGetKey(window, GLFW_KEY_2))
            {
                std::cout << "Switching to Perspective Camera" << std::endl;
                currentCameraMode = CameraMode::Perspective;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed)
            {
                p1.AddForce(physics::MyVector(forceX, forceY, forceZ));
                std::cout << (paused ? "Paused" : "Resumed") << std::endl;
                paused = true;
                pressed = true;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
            {
                paused = false;
                pressed = false;
            }

            if (currentCameraMode == CameraMode::Orthographic) {
                projection_matrix = ortho_camera->getViewProjection();
                ortho_camera->Update(window, (float)ms.count() / 1000);
                view_matrix = ortho_camera->GetViewMatrix();
            }
            else if (currentCameraMode == CameraMode::Perspective) {
                projection_matrix = pers_camera->getViewProjection();
                pers_camera->Update(window, (float)ms.count() / 1000);
                view_matrix = pers_camera->GetViewMatrix();
            }

            if (!paused) {
                pWorld.Update((float)ms.count() / 1000);
            }
        }

        //render particles
        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin(); i != RenderParticles.end(); i++) {
            (*i)->Draw(identity_matrix, projection_matrix, view_matrix);
        }

        //for lines
        p1Line.Update(springPos1, p1.Position, projection_matrix, view_matrix);
        p1Line.Draw();

        p2Line.Update(springPos2, p2.Position, projection_matrix, view_matrix);
        p2Line.Draw();

        p3Line.Update(springPos3, p3.Position, projection_matrix, view_matrix);
        p3Line.Draw();

        p4Line.Update(springPos4, p4.Position, projection_matrix, view_matrix);
        p4Line.Draw();

        p5Line.Update(springPos5, p5.Position, projection_matrix, view_matrix);
        p5Line.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}