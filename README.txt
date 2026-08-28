MTRX3760 Lab 2 - Complete Code Draft

Folders:
  A1  Wall follower, full standalone program
  A2  Full A1/A2 program with wall follower and line follower together
  A4  ROS 2 Jazzy Pluginlib House extension and supporting test files
  A5  Optional noise bonus, copied from A2 and augmented
  ExampleCode  Original supplied example files, unchanged

Important:
- A1 and A2 are intentionally complete copies, as required by the handout.
- A3 has no code; it is the report post-mortem section.
- Run A1/A2 on your own raylib setup and verify the final screenshot and
  console output before submission.
- Run A4 inside the ROS 2 Jazzy tutorial workspace after completing the
  required tutorials.
- Submit code only, no compiled binaries or build folders.

Validation completed before packaging:
- A1/A2/A5 compile cleanly under C++11 with the lecture warning flags using a
  local raylib interface stub for static checking.
- Headless A1 logic test: lap completed in 847 updates with 0 collisions.
- Headless A2 logic test: wall follower completed in 847 updates with 0
  collisions; line follower completed in 863 updates with 0 collisions.
- Headless A5 test using the fixed seed: 40/40 robots completed a lap.
- A4 polygon_plugins.cpp passed C++ syntax checking against a small interface
  stub and plugins.xml was parsed as valid XML.

You still need to run A1/A2 with real raylib and A4 with real ROS 2 Jazzy on
your own setup before submitting, because those external libraries are not
available in this packaging environment.
