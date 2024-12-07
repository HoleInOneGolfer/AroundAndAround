#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>
#include <raymath.h>

void CreateCamera(Camera2D *camera, int width, int height);
void UpdateCameraTarget(Camera2D *camera, Vector2 target, float follow_speed);

#endif // CAMERA_H
