#pragma once
#include "raylib.h"

// 2D Circle and Ellipse Drawing
inline void DrawCircle(Vector2 pos, float radius, Color color) { DrawCircle(pos.x, pos.y, radius, color); }
inline void DrawCircleGradient(Vector2 center, float radius, Color inner, Color outer) { DrawCircleGradient(center.x, center.y, radius, inner, outer); }
inline void DrawCircleLines(Vector2 center, float radius, Color color) { DrawCircleLines(center.x, center.y, radius, color); }
inline void DrawEllipse(Vector2 center, float radiusH, float radiusV, Color color) { DrawEllipse(center.x, center.y, radiusH, radiusV, color); }
inline void DrawEllipseLines(Vector2 center, float radiusH, float radiusV, Color color) { DrawEllipseLines(center.x, center.y, radiusH, radiusV, color); }

// 2D Rectangle Drawing
inline void DrawRectangle(Vector2 position, Vector2 size, Color color) { DrawRectangle(position.x, position.y, size.x, size.y, color); }
inline void DrawRectangleGradientV(Vector2 position, Vector2 size, Color top, Color bottom) { DrawRectangleGradientV(position.x, position.y, size.x, size.y, top, bottom); }
inline void DrawRectangleGradientH(Vector2 position, Vector2 size, Color left, Color right) { DrawRectangleGradientH(position.x, position.y, size.x, size.y, left, right); }
inline void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4) { DrawRectangleGradientEx(rec, col1, col2, col3, col4); }
inline void DrawRectangleLines(Vector2 position, Vector2 size, Color color) { DrawRectangleLines(position.x, position.y, size.x, size.y, color); }
inline void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color) { DrawRectangleLinesEx(rec, lineThick, color); }
inline void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color) { DrawRectangleRounded(rec, roundness, segments, color); }
inline void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color) { DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color); }

// 2D Text Drawing
inline void DrawText(const char *text, Vector2 pos, int fontSize, Color color) { DrawText(text, pos.x, pos.y, fontSize, color); }

// 2D Lines and Pixels
inline void DrawLine(Vector2 start, Vector2 end, Color color) { DrawLine(start.x, start.y, end.x, end.y, color); }
inline void DrawPixel(Vector2 position, Color color) { DrawPixel(position.x, position.y, color); }

// Image Drawing
inline void ImageDrawPixel(Image *dst, Vector2 pos, Color color) { ImageDrawPixel(dst, pos.x, pos.y, color); }
inline void ImageDrawLine(Image *dst, Vector2 start, Vector2 end, Color color) { ImageDrawLine(dst, start.x, start.y, end.x, end.y, color); }
inline void ImageDrawCircle(Image *dst, Vector2 center, int radius, Color color) { ImageDrawCircle(dst, center.x, center.y, radius, color); }
inline void ImageDrawRectangle(Image *dst, Vector2 position, Vector2 size, Color color) { ImageDrawRectangle(dst, position.x, position.y, size.x, size.y, color); }
inline void ImageDrawText(Image *dst, const char *text, Vector2 position, int fontSize, Color color) { ImageDrawText(dst, text, position.x, position.y, fontSize, color); }
