//-----------------------------------------------------------------------------
// TestLoopReader.cpp
//
// A small demonstration that loads a loop file with CLoopReader and draws the
// loop it describes on screen with CRender. It is a worked example of using
// the two classes together, not a starting template for the lab.
//
// Build it the same way as TestRender.cpp (see the top of TestRender.cpp for the two
// install variants). For example, with raylib installed via apt:
//
//     g++ -Wall -Wextra TestLoopReader.cpp CLoopReader.cpp CRender.cpp -lraylib -o TestLoopReader
//
// Run it, optionally naming a file to view. With no argument it opens
// SimpleWalls.map:
//
//     ./TestLoopReader
//     ./TestLoopReader SimpleLine.map
//-----------------------------------------------------------------------------

#include "CLoopReader.h"
#include "CRender.h"

#include <iostream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// Draw a loop as a closed outline: an edge between each vertex and the next,
// with the last vertex joining back to the first.
//-----------------------------------------------------------------------------
void DrawLoop( CRender& aRender, const CLoopReader& aLoop )
{
    const float EdgeThickness = 2.0f;

    const std::vector<Vec2D>& Vertices = aLoop.GetVertices();
    if( !Vertices.empty() )
    {
        // Start from the last vertex so the first edge drawn closes the loop.
        Vec2D Previous = Vertices.back();
        for( const Vec2D& Vertex : Vertices )
        {
            aRender.DrawLine( Previous, Vertex, EdgeThickness, RAYWHITE );
            Previous = Vertex;
        }
    }
}

//-----------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    // View the file named on the command line, or a default if none is given.
    std::string Filename = "SimpleWalls.map";
    if( argc > 1 )
    {
        Filename = argv[1];
    }

    CLoopReader Loop;
    bool ReadSuccess = Loop.ReadFile( Filename );
    std::cout << "Read " << (ReadSuccess ? "successful":"unsuccessful") << std::endl;

    CRender Render;

    while( !Render.WindowShouldClose() )
    {
        Render.BeginDrawing();
        DrawLoop( Render, Loop );
        Render.EndDrawing();
    }

    Render.CloseWindow();

    return 0;
}
