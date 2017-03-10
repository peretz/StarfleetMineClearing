# StarfleetMineClearing

What the project does?

This repository contains a C++ implementation of the Starfleet Mine Clearing Exercise. The description of this exercise is included in the Starfleet Mine Clearing Exercise.pdf.

How users can get started with the project?

This project has been compiled using Clang++ in a Mac system, so to get started you need to set up a Mac system with Clang++ installed in it.

Once you have your Mac setup and Clang++ installed, just proceed to run 'make' in the root directory of your repository. Running make creates an executable StarfleetMineClearing.out. This executable needs a script and a field file to run the simulation.

There are several examples provided in the fields and scripts directories which can be used as shown below:
./StarfleetMineClearing.out ./scripts/Exercise1.script ./fields/Exercise1.fields

What is the program architecture?

The program uses three classes, Field, Script and Simulation, and a main.cpp file. The three classes leverage most of the logic for this implementation. Below, I cover their responsibilities.

Field:
This class provides an interface to keep track of the status of the mines in the game. Part of the responsibilities of this class is loading the mines from the \*.field file, keeping track of the different coordinates of the mines, updating the state of the mines as the simulation runs and provide a method for the client code to "view" the field. The core technical decisions in this class is using a 2D array of integers to represent the field and using vector math to map the field's cartesian coordinates to the vessel's cartesian coordinates. 

Script:
This class provides an interface to access each line of instructions as well as parse this instructions into tokens. To achieve this, this class is responsible of loading the instructions from memory \*.script file, keep track of the active instruction line and parse the different individual instructions (tokens).

Simulation:
This class leverages the other two classes and adds the "game" logic to the program. This includes keeping track of the vessel location, the different move and shooting options and the scoring system. In addition, this class is in charge of displaying this information to the end user.

Can users help with your project?

If you are interested in helping improve this C++ implementation, please check the TODO.txt file. This file contains several improvements that can be done to the source code.

