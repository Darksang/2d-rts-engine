#include "engine/debug_draw.h"

struct RenderPoints {

    RenderPoints() { }

    void Initialize(Camera2D * Camera) {
        PointShader = Shader("resources/shaders/vertex/point.glsl", "resources/shaders/fragment/point.glsl");

        this->Camera = Camera;
        PointShader.Use();
        PointShader.SetMat4("ProjectionMatrix", this->Camera->GetProjectionMatrix());

        glGenVertexArrays(1, &VAO);
        glGenBuffers(3, VBO);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Sizes), Sizes, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        Count = 0;
    }

    void Destroy() {
        if (VAO) {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(3, VBO);
            VAO = 0;
        }
    }

    void Vertex(const b2Vec2 & v, const b2Color & c, float32 size) {
        if (Count == MaxVertices)
            Flush();

        Vertices[Count] = v;
        Colors[Count] = c;
        Sizes[Count] = size;
        Count++;
    }

    void Flush() {
        if (Count == 0)
            return;

        PointShader.Use();
        PointShader.SetMat4("ViewMatrix", this->Camera->GetViewMatrix());

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(b2Vec2), Vertices);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(b2Color), Colors);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(float), Sizes);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glDrawArrays(GL_POINTS, 0, Count);
        glDisable(GL_PROGRAM_POINT_SIZE);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        Count = 0;
    }

    Shader PointShader;

    Camera2D * Camera;

    enum { MaxVertices = 512 };
    b2Vec2 Vertices[MaxVertices];
    b2Color Colors[MaxVertices];
    float32 Sizes[MaxVertices];

    int32 Count;

    GLuint VAO;
    GLuint VBO[3];
};

struct RenderLines {

    RenderLines() { }

    void Initialize(Camera2D * Camera) {
        LineShader = Shader("resources/shaders/vertex/line.glsl", "resources/shaders/fragment/line.glsl");

        this->Camera = Camera;
        LineShader.Use();
        LineShader.SetMat4("ProjectionMatrix", Camera->GetProjectionMatrix());

        glGenVertexArrays(1, &VAO);
        glGenBuffers(2, VBO);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        Count = 0;
    }

    void Destroy() {
        if (VAO) {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(2, VBO);
            VAO = 0;
        }
    }

    void Vertex(const b2Vec2 & v, const b2Color & c) {
        if (Count == MaxVertices)
            Flush();

        Vertices[Count] = v;
        Colors[Count] = c;
        Count++;
    }

    void Flush() {
        if (Count == 0)
            return;

        LineShader.Use();
        LineShader.SetMat4("ViewMatrix", Camera->GetViewMatrix());

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(b2Vec2), Vertices);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, Count * sizeof(b2Color), Colors);

        glDrawArrays(GL_LINES, 0, Count);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        Count = 0;
    }

    Shader LineShader;

    Camera2D * Camera;

    enum { MaxVertices = 512 * 2 };
    b2Vec2 Vertices[MaxVertices];
    b2Color Colors[MaxVertices];

    int32 Count;

    GLuint VAO;
    GLuint VBO[2];
};

DebugDraw::DebugDraw() {
    Points = 0;
    Lines = 0;
}

DebugDraw::~DebugDraw() {
    b2Assert(Points == 0);
    b2Assert(Lines == 0);
}

void DebugDraw::Initialize(Camera2D * Camera) {
    this->Camera = Camera;

    Points = new RenderPoints();
    Points->Initialize(Camera);

    Lines = new RenderLines();
    Lines->Initialize(Camera);
}

void DebugDraw::Destroy() {
    Camera = 0;

    Points->Destroy();
    delete Points;
    Points = 0;

    Lines->Destroy();
    delete Lines;
    Lines = 0;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {

}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {

}

void DebugDraw::DrawSegment(const glm::vec2 & P1, const glm::vec2 & P2, const glm::vec3 & Color) {
    DrawSegment(b2Vec2(P1.x, P1.y), b2Vec2(P2.x, P2.y), b2Color(Color.x, Color.y, Color.z));
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    Lines->Vertex(p1, color);
    Lines->Vertex(p2, color);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {

}

void DebugDraw::DrawPoint(const glm::vec2 & P, const glm::vec3 & Color, float Size) {
    DrawPoint(b2Vec2(P.x, P.y), Size, b2Color(Color.x, Color.y, Color.z));
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {
    Points->Vertex(p, color, size);
}

void DebugDraw::Render() {
    Points->Flush();
    Lines->Flush();
}