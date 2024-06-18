#include "Transform.h"
#include <cmath>

namespace Transform {

    Vertex MoveVertex(Vertex point, Vector meter) {
        point.x += meter.x_meter;
        point.y += meter.y_meter;
        return point;
    }

    Vertex RotateVertex(Vertex point, float angle_degree) {
        float angle_rad = angle_degree * (3.14159265358979323846 / 180.0f); // Convert degree to radian
        float cos_theta = std::cos(angle_rad);
        float sin_theta = std::sin(angle_rad);

        float new_x = point.x * cos_theta - point.y * sin_theta;
        float new_y = point.x * sin_theta + point.y * cos_theta;

        point.x = new_x;
        point.y = new_y;

        return point;
    }

    Vertex ScaleVertex(Vertex point, Vector meter) {
        point.x *= meter.x_meter;
        point.y *= meter.y_meter;
        return point;
    }

} // namespace Transform
