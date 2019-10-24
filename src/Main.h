
#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <list>
#include <vector>
#include <bitset>
#include <map>
#include <cmath>
#include <random>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;

#include "engine/math/BasicMath.h"
#include "engine/datatype/CFlag32.h"

#endif


#ifdef IMPORT_ENGINE
#include "game/Engine.h"
extern Engine engine;
#endif
