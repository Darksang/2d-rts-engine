#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "Box2D/Box2D.h"

#include "engine/camera2d.h"
#include "engine/shader.h"

struct RenderPoints;
struct RenderLines;
struct RenderTriangles;

class DebugDraw : public b2Draw {
    public:
        DebugDraw();
        ~DebugDraw();

        void Initialize(Camera2D * Camera);
        void Destroy();

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

        void DrawSegment(const glm::vec2 & P1, const glm::vec2 & P2, const glm::vec3 & Color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

        void DrawTransform(const b2Transform& xf) override;

        void DrawPoint(const glm::vec2 & P, const glm::vec3 & Color, float Size);
        void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
    
        void Render();

    private:
        Camera2D * Camera;

        RenderPoints * Points;
        RenderLines * Lines;
};

#endif