#include "Camera.hpp"

namespace game
{
    
    Camera::Camera(glm::vec3 position) : position(position) {}

    void Camera::LookAt(glm::vec3 target)
    {

        front = glm::normalize(target - position);
        right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::mat4 Camera::GetView()
    {
        LookAt(position + front);
        //local-x = right, local-y = up, local-z = back

        return glm::mat4
        {
            right.x, up.x, -front.x, 0.0f,
            right.y, up.y, -front.y, 0.0f,
            right.z, up.z, -front.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        } * glm::mat4
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -position.x, -position.y, -position.z, 1.0f
        };
    };
}