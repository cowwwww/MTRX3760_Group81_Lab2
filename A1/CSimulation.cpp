//-----------------------------------------------------------------------------
// CSimulation.cpp
//-----------------------------------------------------------------------------

#include "CSimulation.h"

#include <iostream>

// Set up the simulation.
CSimulation::CSimulation()
    : mWallMap( "SimpleWalls.map" ),
      mRender(),
      mWallFollower( mWallMap ),
      mSummaryPrinted( false )
{
}

// Run the simulation.
void CSimulation::Run()
{
    if( !mWallMap.IsReady() )
    {
        std::cout << "Could not load map." << std::endl;
    }
    else
    {
        while( !mRender.WindowShouldClose() )
        {
            if( !AllRobotsStopped() )
            {
                UpdateRobots();
            }
            else if( !mSummaryPrinted )
            {
                PrintSummary();
            }

            Draw();
        }
    }

    mRender.CloseWindow();
}

// Update the robot.
void CSimulation::UpdateRobots()
{
    const int updatesPerFrame = 4;
    const int maximumUpdates = 2000;

    for( int i = 0; i < updatesPerFrame; ++i )
    {
        if( !mWallFollower.HasCompletedLap() &&
            mWallFollower.GetUpdateCount() < maximumUpdates )
        {
            mWallFollower.Update();
        }
    }
}

// Draw the simulation.
void CSimulation::Draw()
{
    mRender.BeginDrawing();

    mWallMap.Draw( mRender );
    mWallFollower.Draw( mRender );

    mRender.EndDrawing();
}

// Check if the robot should stop.
bool CSimulation::AllRobotsStopped() const
{
    const int maximumUpdates = 2000;

    return mWallFollower.HasCompletedLap() ||
           mWallFollower.GetUpdateCount() >= maximumUpdates;
}

// Print the final result.
void CSimulation::PrintSummary()
{
    std::cout << std::endl;
    std::cout << "A1 simulation summary" << std::endl;

    mWallFollower.ReportSummary();

    mSummaryPrinted = true;
}