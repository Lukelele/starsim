To compile and run the project, navigate to the StarSim directory and run the bash command below


For Linux (Make sure GLFW is pre-installed using "sudo apt-get install libglfw3 libglfw3-dev"):

g++ *.cpp dependencies/include/imgui/imgui.cpp dependencies/include/imgui/imgui_draw.cpp dependencies/include/imgui/imgui_impl_glfw.cpp dependencies/include/imgui/imgui_impl_opengl3.cpp dependencies/include/imgui/imgui_tables.cpp dependencies/include/imgui/imgui_widgets.cpp glad.c -I dependencies/include -lglfw -o bin/app


For MacOS:

g++ *.cpp dependencies/include/imgui/imgui.cpp dependencies/include/imgui/imgui_draw.cpp dependencies/include/imgui/imgui_impl_glfw.cpp dependencies/include/imgui/imgui_impl_opengl3.cpp dependencies/include/imgui/imgui_tables.cpp dependencies/include/imgui/imgui_widgets.cpp glad.c -I dependencies/include dependencies/library/libglfw.3.3.dylib -o bin/app
