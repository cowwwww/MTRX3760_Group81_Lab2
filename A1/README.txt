A1 - Wall Follower

With raylib installed by apt:
  g++ -std=c++11 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic \
      main.cpp CSimulation.cpp CWallFollower.cpp CRobot.cpp CRangeSensor.cpp \
      CWallMap.cpp CLoopReader.cpp CRender.cpp -lraylib -o wall_follower
  ./wall_follower

On a lab machine with raylib in $HOME/raylib, add:
  -I$HOME/raylib/include -L$HOME/raylib/lib

The simulation stops updating after one lap and leaves the final drawing open
for the required screenshot. Close the window to exit.
