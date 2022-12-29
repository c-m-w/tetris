/// main.hpp

/******************************
*
* opengl
*
/******************************/

#define GLEW_STATIC

#pragma comment(lib, "gl3w.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/******************************
*
* other
*
/******************************/

#include <array>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

/******************************
*
* mine
*
/******************************/

#include "utils/utils.hpp"
#include "drawing/drawing.hpp"
