
#include "raylib.h"
#include "resource_dir.h"
#include <cmath>
#include <limits.h>
#include <limits>
#include <raymath.h>
#include "raylibVectorsWrapper.hpp"

//#define debug

class point
{
public:
    Vector2 pos;
    int deg = 0;
    int degPrev = 180;
    point *next;

    point(int initX, int initY, point *initNext = nullptr)
    {
        pos = { (float)initX, (float)initY };
        next = initNext;
    };

    point(Vector2 initPos, point *initNext = nullptr)
    {
        pos = initPos;
        next = initNext;
    };
};

void renderPoints(point* head);
point *calcClosestPoint(point* head, Vector2 mousePos);
Vector2 calcIntersect(const Vector2& v1start, const Vector2& v1end, const Vector2& v2start, const Vector2& v2end);
void renderStuff(point *head);
void drawBezier(Vector2 start, Vector2 end, Vector2 center);

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "Bezier Curve");
    SearchAndSetResourceDir("resources");

    point *head = nullptr;

    Vector2 mousePos;
    point* closest_hightligted_point = nullptr;

    while (!WindowShouldClose()) {
        mousePos = GetMousePosition();

        point* candidate = calcClosestPoint(head, mousePos);
        if (candidate != nullptr) {
            int dist = Vector2Distance(candidate->pos, mousePos);
            if (dist < 10) {
                closest_hightligted_point = candidate;
            } else {
                closest_hightligted_point = nullptr;
            }
        }

        int scrollSpeed = 1;
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            scrollSpeed *= 5;
        }

        if (closest_hightligted_point != nullptr) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                closest_hightligted_point->pos = mousePos;
            }

            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                closest_hightligted_point->degPrev -= GetMouseWheelMove() * scrollSpeed;
            } else {
                closest_hightligted_point->deg -= GetMouseWheelMove() * scrollSpeed;
            }
        }


        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            head = new point(mousePos, head);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            renderPoints(head);

            #ifdef debug
            if (closest_hightligted_point != nullptr) {
                DrawCircle(closest_hightligted_point->pos, 4.0f, BLUE);
            }
            #endif
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void renderPoints(point* head)
{
    while (head != nullptr)
    {

        renderStuff(head);
        DrawCircleLines(head->pos, 3.0f, WHITE);

        head = head->next;
    }
}

point *calcClosestPoint(point* head, Vector2 mousePos)
{
    point *closest = nullptr;
    int closestDist = INT_MAX;
    while (head != nullptr)
    {
        int dist = Vector2Distance(head->pos, mousePos);
        if (dist < closestDist) {
            closestDist = dist;
            closest = head;
        }
        head = head->next;
    }
    return closest;
}

Vector2 calcIntersect(const Vector2& v1start, const Vector2& v1end, const Vector2& v2start, const Vector2& v2end)
{
    float x1 = v1start.x, y1 = v1start.y;
    float x2 = v1end.x, y2 = v1end.y;
    float x3 = v2start.x, y3 = v2start.y;
    float x4 = v2end.x, y4 = v2end.y;

    float den = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    if (std::abs(den) < 1e-6f)
        return Vector2{std::numeric_limits<float>::quiet_NaN()};

    float px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / den;
    float py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / den;

    Vector2 intersection{px, py};

    Vector2 d1 = Vector2Subtract(v1end, v1start);
    Vector2 d2 = Vector2Subtract(v2end, v2start);

    Vector2 r1 = intersection - v1start;
    Vector2 r2 = intersection - v2start;

    if ((d1.x * r1.x + d1.y * r1.y) < 0 || (d2.x * r2.x + d2.y * r2.y) < 0)
        return Vector2{std::numeric_limits<float>::quiet_NaN()};

    return intersection;
}


void renderStuff(point *head)
{
    float length = 50.0f;

    float angleRad1 = head->deg * PI / 180.0f;
    Vector2 v1end = {
        head->pos.x + length * cos(angleRad1),
        head->pos.y + length * sin(angleRad1)
    };

    float angleRadPrev1 = head->degPrev * PI / 180.0f;
    Vector2 v1prevEnd = {
        head->pos.x + length * cos(angleRadPrev1),
        head->pos.y + length * sin(angleRadPrev1)
    };

    DrawLine(head->pos, v1end, PURPLE);
    DrawLine(head->pos, v1prevEnd, BLUE);

    if (head->next != nullptr)
    {
        point *nextHead = head->next;
        #ifdef debug
        DrawLine(head->pos, nextHead->pos, WHITE);
        #endif

        float angleRad2 = nextHead->degPrev * PI / 180.0f;
        Vector2 v2prevEnd = {
            nextHead->pos.x + length * cos(angleRad2),
            nextHead->pos.y + length * sin(angleRad2)
        };

        Vector2 intersection = calcIntersect(head->pos, v1end, nextHead->pos, v2prevEnd);
        if (!std::isnan(intersection.x)) {
            #ifdef debug
            DrawCircle(intersection, 4.0f, GREEN);
            #endif
            drawBezier(head->pos, nextHead->pos, intersection);
        }
        
    }
}

void drawBezier(Vector2 start, Vector2 end, Vector2 center)
{
    const int segments = 100;
    const float steps = 1.0f / segments;
    float amount = 0.0f;

    Vector2 prev = start;

    Vector2 drawPoint;
    while (amount < 1.0f) {
        Vector2 point1 = Vector2Lerp(start, center, amount);
        Vector2 point2 = Vector2Lerp(center, end, amount);
        drawPoint = Vector2Lerp(point1, point2, amount);
        DrawLine(prev, drawPoint, WHITE);
        prev = drawPoint;
        amount += steps;
    };
    DrawLine(drawPoint, end, WHITE);
}