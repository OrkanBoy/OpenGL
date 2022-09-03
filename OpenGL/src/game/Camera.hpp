#pragma once

#include "Math/Rotations.hpp"
#include "Transform.hpp"
#include "Error.hpp"

namespace game
{
	class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3
            right = glm::vec3(1.0f, 0.0f, 0.0f),
            up = glm::vec3(0.0f, 1.0f, 0.0f),
            front = glm::vec3(0.0f, 0.0f, -1.0f);
        float yaw, pitch;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

        void LookAt(glm::vec3 target);

        glm::mat4 GetView();
    };
	
    class camera 
    {
    public:
        Transform transform;

        void LookAt(glm::vec3 target);

        glm::mat4 GetView();
    };
	
}