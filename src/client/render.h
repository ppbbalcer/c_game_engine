#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>
#include "scene.h"

bool render_start();
bool render_stop();
bool render_do();
struct positionf *render_camera();

#define CAM_X(_x)\
((_x) + render_camera()->x)

#define CAM_Y(_y)\
((_y) + render_camera()->y)

#endif /* RENDER_H */
