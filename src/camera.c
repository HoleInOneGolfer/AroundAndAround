#include "camera.h"

void CreateCamera(Camera2D *camera, int width, int height)
{
    camera->target = Vector2Zero();
    camera->offset = (Vector2){width / 2, height / 2};
    camera->rotation = 0;
    camera->zoom = 1;
}

void UpdateCameraTarget(Camera2D *camera, Vector2 target, float follow_speed)
{
    camera->target = Vector2Lerp(camera->target, target, follow_speed);
}
