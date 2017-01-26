#include "roboteam_utils/Draw.h"

namespace rtt {

Draw::Draw() {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    debugPub = n.advertise<roboteam_msgs::DebugLine>("view_debug_lines", 1000);
    debugPubPoint = n.advertise<roboteam_msgs::DebugPoint>("view_debug_points", 1000);
#endif
}

void Draw::DrawLine(std::string name, roboteam_utils::Vector2 start, roboteam_utils::Vector2 line) {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    roboteam_msgs::DebugLine Line;
    Line.name = name;
    Line.remove = false;
    roboteam_msgs::Vector2f startLine1;
    startLine1.x = start.x;
    startLine1.y = start.y;
    roboteam_msgs::Vector2f endLine1;
    endLine1.x = line.x + start.x;
    endLine1.y = line.y + start.y;
    Line.points.push_back(startLine1);
    Line.points.push_back(endLine1);
    Line.color = color;
    debugPub.publish(Line);
#endif
}

void Draw::RemoveLine(std::string name) {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    roboteam_msgs::DebugLine Line;
    Line.name = name;
    Line.remove = true;
    debugPub.publish(Line);
#endif
}

void Draw::DrawPoint(std::string name, roboteam_utils::Vector2 point) {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    roboteam_msgs::DebugPoint position;
    position.name = name;
    position.pos.x = point.x;
    position.pos.y = point.y;
    position.color = color;
    debugPubPoint.publish(position);
#endif
}

void Draw::RemovePoint(std::string name) {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    roboteam_msgs::DebugPoint position;
    position.name = name;
    position.remove = true;
    debugPubPoint.publish(position);
#endif
}

void Draw::SetColor(int r, int g, int b) {
#ifdef RTT_ENABLE_DEBUG_GRAPHICS
    color.r = r;
    color.g = g;
    color.b = b;
#endif
}

} // rtt