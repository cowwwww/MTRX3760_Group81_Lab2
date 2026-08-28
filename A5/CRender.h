//-----------------------------------------------------------------------------
// CRender.h
//
// Small C++ interface around raylib for MTRX3760 Lab 2. The rest of the
// simulator uses only this class and does not call raylib directly.
//-----------------------------------------------------------------------------

#ifndef CRENDER_H
#define CRENDER_H

// A simple 2D point used throughout the simulator.
struct Vec2D
{
    float x;
    float y;
};

class CRender
{
    public:
        // Drawing styles keep raylib colours inside CRender.
        enum EStyle
        {
            WALL,
            FLOOR_LINE,
            WALL_ROBOT,
            LINE_ROBOT,
            WALL_TRAIL,
            LINE_TRAIL,
            SENSOR
        };

        CRender();

        bool WindowShouldClose();
        void CloseWindow();

        void BeginDrawing();
        void EndDrawing();

        void DrawCircle( Vec2D aPosition, int aRadius, EStyle aStyle );
        void DrawLine( Vec2D aStart, Vec2D aEnd, float aThickness, EStyle aStyle );

        int GetScreenWidth() const;
        int GetScreenHeight() const;

    private:
        const int mScreenWidth;
        const int mScreenHeight;
};

#endif
