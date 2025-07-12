#pragma once

#pragma once

#include <Eigen/Dense>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>

constexpr double PI = 3.14159265358979323846;

constexpr float degToRad(float deg) {
    return deg * PI / 180.0f;
}

class ArcBall {
private:
    Eigen::Vector3f TARGET_VECTOR, POSITION_VECTOR, UP_VECTOR;
    Eigen::Matrix4f PERSPECTIVE_MAT, VIEW_MAT;

    float YAW = -90.0f, PITCH = 0.0f;
    float DIST_FROM_TARGET = 2.0f;

    float FIELD_OF_VIEW;
    float a_sensitivity = 0.3f;
    float a_pan_speed = 0.4f;
    float a_scroll_sensitivity = 0.09f;

    // Freefly mode additions
    bool freeFlyMode = false;
    bool firstMouse = true;
    double lastMouseX = 0.0, lastMouseY = 0.0;

    float camSpeed = 3.0f;
    float lookSensitivity = 90.0f;

    void ProcMouseOrbit(float dx, float dy) {
        YAW += dx * a_sensitivity;
        PITCH -= dy * a_sensitivity;

        if (PITCH < -89.0f) PITCH = -89.0f;
        if (PITCH > 89.0f)  PITCH = 89.0f;

        RecalcPos();
    }

    void ProcMousePan(float dx, float dy) {
        Eigen::Vector3f forward = (TARGET_VECTOR - POSITION_VECTOR).normalized();
        Eigen::Vector3f right = (forward.cross(UP_VECTOR)).normalized();
        Eigen::Vector3f up = (right.cross(forward)).normalized();

        float panScale = DIST_FROM_TARGET * 0.002f;
        Eigen::Vector3f panOffset = (-right * dx + up * dy) * panScale;

        POSITION_VECTOR += panOffset;
        TARGET_VECTOR += panOffset;
    }

    void ProcMouseScroll(float dy) {
        DIST_FROM_TARGET = std::max(0.1f, DIST_FROM_TARGET - dy);
        RecalcPos();
    }

    void RecalcPos() {
        float radYaw = degToRad(YAW);
        float radPitch = degToRad(PITCH);
        Eigen::Vector3f direction = {
            cos(radPitch) * cos(radYaw),
            sin(radPitch),
            cos(radPitch) * sin(radYaw)
        };
        POSITION_VECTOR = TARGET_VECTOR - direction * DIST_FROM_TARGET;
    }

    Eigen::Matrix4f mine_lookAt(const Eigen::Vector3f& eye, const Eigen::Vector3f& center, const Eigen::Vector3f& up) {
        Eigen::Vector3f f = (center - eye).normalized();
        Eigen::Vector3f s = f.cross(up).normalized();
        Eigen::Vector3f u = s.cross(f);

        Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
        view.block<1, 3>(0, 0) = s.transpose();
        view.block<1, 3>(1, 0) = u.transpose();
        view.block<1, 3>(2, 0) = -f.transpose();
        view(0, 3) = -s.dot(eye);
        view(1, 3) = -u.dot(eye);
        view(2, 3) = f.dot(eye);

        return view;
    }

    Eigen::Matrix4f mine_perspective(float fovY, float aspect, float zNear, float zFar) {
        float tanHalfFovy = std::tan(fovY / 2.0f);

        Eigen::Matrix4f proj = Eigen::Matrix4f::Zero();
        proj(0, 0) = 1.0f / (aspect * tanHalfFovy);
        proj(1, 1) = 1.0f / (tanHalfFovy);
        proj(2, 2) = -(zFar + zNear) / (zFar - zNear);
        proj(2, 3) = -2.0f * zFar * zNear / (zFar - zNear);
        proj(3, 2) = -1.0f;

        return proj;
    }

public:
    ArcBall() = default;

    ArcBall(float fov, float near, float far, float aspect) :
        POSITION_VECTOR(Eigen::Vector3f::Zero()),
        TARGET_VECTOR(Eigen::Vector3f::Zero()),
        UP_VECTOR(Eigen::Vector3f(0.0, 1.0, 0.0)),
        FIELD_OF_VIEW(fov)
    {
        PERSPECTIVE_MAT = mine_perspective(FIELD_OF_VIEW, aspect, near, far);
        RecalcPos();
    }

    ~ArcBall() = default;

    void Update(GLFWwindow* window, float deltaTime) {
        // Toggle modes
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            freeFlyMode = true;
            firstMouse = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            freeFlyMode = false;
            firstMouse = true;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float dx = static_cast<float>(mouseX - lastMouseX);
        float dy = static_cast<float>(mouseY - lastMouseY);

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        if (freeFlyMode) {
            if (firstMouse) {
                firstMouse = false;
                return;
            }

            float offsetX = lookSensitivity * dx * deltaTime;
            float offsetY = lookSensitivity * dy * deltaTime;

            YAW += offsetX;
            PITCH -= offsetY;

            if (PITCH > 89.0f) PITCH = 89.0f;
            if (PITCH < -89.0f) PITCH = -89.0f;

            float yawRad = degToRad(YAW);
            float pitchRad = degToRad(PITCH);

            Eigen::Vector3f direction;
            direction.x() = cos(pitchRad) * cos(yawRad);
            direction.y() = sin(pitchRad);
            direction.z() = cos(pitchRad) * sin(yawRad);
            direction.normalize();

            Eigen::Vector3f forward = direction;
            Eigen::Vector3f right = forward.cross(UP_VECTOR).normalized();

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                POSITION_VECTOR += camSpeed * forward * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                POSITION_VECTOR -= camSpeed * forward * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                POSITION_VECTOR -= camSpeed * right * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                POSITION_VECTOR += camSpeed * right * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
                POSITION_VECTOR += camSpeed * UP_VECTOR * deltaTime;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                POSITION_VECTOR -= camSpeed * UP_VECTOR * deltaTime;

            TARGET_VECTOR = POSITION_VECTOR + forward;
        }
        else {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
                ProcMouseOrbit(dx, dy);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
                ProcMousePan(dx * a_pan_speed, dy * a_pan_speed);
        }
    }

    void setScrollDelta(float scrollY) {
        ProcMouseScroll(scrollY * a_scroll_sensitivity);
    }

    float* renderView() {
        VIEW_MAT = mine_lookAt(POSITION_VECTOR, TARGET_VECTOR, UP_VECTOR);
        return VIEW_MAT.data();  // Eigen uses column-major by default
    }

    float* getProjMatrix() {
        return PERSPECTIVE_MAT.data();
    }

    Eigen::Vector3f getCamPos() const {
        return POSITION_VECTOR;
    }

    bool isFreeFly() const {
        return freeFlyMode;
    }
};

