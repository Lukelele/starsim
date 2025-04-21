// #include "Renderer.h"
//
//
// using namespace std;
// using namespace glm;
//
//
//
// int main() {
//     Renderer renderer;
//     renderer.InitWindow(1200, 900, "Lukelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelelele");
//
//     Shader shader;
//     shader.AddShadersByFilepath("vertexShader.glsl", "fragmentShader.glsl");
//
//     Shape sphere("sphere.obj");
//
//     vector <Body*> planets;
//     planets.push_back(new Body(sphere));
//     planets.push_back(new Body(sphere));
//
//     System system;
//     system.Add(*planets[0]);
//     system.Add(*planets[1]);
//
//     planets[0]->SetPosition(vec3(-6, -1.8, -4));
//     planets[1]->SetPosition(vec3(6, -1.8, -4));
//     planets[0]->SetVelocity(vec3(0, 0, 0.015));
//     planets[1]->SetVelocity(vec3(0, 0, -0.015));
//     planets[0]->SetMass(1);
//     planets[1]->SetMass(1);
//    
////     Camera camera;
//
//     Panel panel;
//
//     ImVec4 clear_colour;
//     ImVec4 vertex_colour(1, 1, 1, 1);;
//     ImVec4 lightLocation(0,0,0,1);
//     float ambientLight = 0.05;
//
//     int counter = 0;
//
//     vec3 addPosition = vec3();
//     vec3 addVelocity = vec3();
//     float addMass = 1;
//     float addScale = 1;
//     bool lock = false;
//
//
//     while (!glfwWindowShouldClose(renderer.GetWindow()))
//     {
//         mat4 projectionMatrix = perspective(radians(90.0f), 4.0f / 3.0f, 0.1f, 1000000.0f);
//
//         shader.SendUniform("u_projectionMatrix", projectionMatrix);
//         shader.SendUniform("u_lightLocation", lightLocation.x, lightLocation.y, lightLocation.z);
//         shader.SendUniform("u_ambientLight", ambientLight);
//         shader.SendUniform("u_colour", vertex_colour.x, vertex_colour.y, vertex_colour.z, 1.0f);
//
//
//         ///////////////////////////////////////////////////////////////////////////////////////////////////////
//        
//    
//         if (panel.GetPaused() == true && system.GetPaused() == false) {
//             system.Pause();
//         }
//         else if (panel.GetPaused() == false && system.GetPaused() == true) {
//             system.Continue();
//         }
//
////         camera.Move(panel.GetCameraSpeed(), panel.GetSensitivity());
//
//         renderer.StartFrame();
//
//         panel.DrawGameMenu();
//
//
//         {
//             ImGui::Begin("World");
//
//             ImGui::Text("Add to Position");
//             ImGui::InputFloat3("       ", (float*)&addPosition);
//             ImGui::Text("Add with Velocity");
//             ImGui::InputFloat3("      ", (float*)&addVelocity);
//             ImGui::Text("Add with Mass");
//             ImGui::InputFloat("", &addMass);
//             ImGui::Text("Add with Scale");
//             ImGui::InputFloat("   ", &addScale);
//             ImGui::SameLine(0, 0);
//             if (ImGui::Button("Add", ImVec2(60, 20))) {
//                 planets.push_back(new Body(sphere));
//                 planets.back()->SetPosition(addPosition);
//                 if (addMass != 0) {
//                     planets.back()->SetMass(addMass);
//                 }
//                 planets.back()->SetVelocity(addVelocity);
//                 planets.back()->SetScale(addScale);
//                 system.Add(*planets.back());
//             }
//
//
//             ImGui::Text("");
//             ImGui::Text("System");
//             for (int i = 0; i < planets.size(); i++) {
//                 if (planets[i]->GetActive()) {
//                     if (ImGui::CollapsingHeader(planets[i]->GetName().c_str())) {
//                         ImGui::Text("           ");
//                         ImGui::SameLine(0, 4);
//                         if (ImGui::Button("Move To")) {
//                             //camera.SetPosition(planets[i]->GetPosition() - camera.GetRotation() * vec3(10 / panel.m_zoom));
////                             camera.LockOn(planets[i]->GetPosition(), 10 / panel.m_zoom);
//                         }
//                         ImGui::SameLine(0, 14);
//                         if (ImGui::Button("Toggle Lock")) {
//                             lock = !lock;
//                         }
//                         if (lock == true) {
//                         //    camera.SetPosition(planets[i]->GetPosition() - camera.GetRotation() * vec3(10 / panel.m_zoom));
////                             /*camera*/.LockOn(planets[i]->GetPosition(), 10 / panel.m_zoom);
//                         }
//
//                         ImGui::Text("Position");
//                         ImGui::SameLine(0, 25);
//                         ImGui::InputFloat3(" ", (float*)&planets[i]->m_position);
//
//                         ImGui::Text("Velocity");
//                         ImGui::SameLine(0, 25);
//                         ImGui::InputFloat3("  ", (float*)&planets[i]->m_velocity);
//
//                         ImGui::Text("Mass    ");
//                         ImGui::SameLine(0, 25);
//                         ImGui::InputFloat("     ", &planets[i]->m_mass);
//
//                         ImGui::Text("Scale   ");
//                         ImGui::SameLine(0, 25);
//                         ImGui::InputFloat("      ", &planets[i]->m_scale);
//
//                         ImGui::Text("Remove this body");
//                         ImGui::SameLine(0, 25);
//                         if (ImGui::Button("Remove", ImVec2(80, 30))) {
//                             planets[i]->Free();
//                         }
//                     }
//                 }
//             }
//             ImGui::End();
//         }
//        
//
//         system.ChangeSpeed(panel.GetGameSpeed());
//
//         system.Orbit();
//
//
//         ///////////////////////////////////////////////////////////////////////////////////////////////
//
//
//         renderer.Clear(clear_colour.x, clear_colour.y, clear_colour.z);
//
////         renderer.Render(system, shader, camera);
//
//         renderer.EndFrame(panel.GetFPSLimit());
//     }
//
//     for (int i = 0; i < planets.size(); i++) {
//         delete planets[i];
//     }
//
//     renderer.Terminate();
//
//     return 0;
// }


#define GL_SILENCE_DEPRECATION
#include "Renderer.h"


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
