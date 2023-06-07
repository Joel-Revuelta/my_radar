# My_radar

## Description

my_radar is an air traffic graphical simulation.
Planes fly from a control tower to another, and reset when they reach their
destination or collide with one another.
Two planes colliding within a tower control area are not destroyed and can
continue on their way.

## Usage

```
./my_radar -h

    Air traffic simulation panel

    USAGE
            ./my_radar [OPTIONS] path_to_script
            path_to_script  The path to the script file.

    OPTIONS
            -h              print the usage and quit.

    USAGE INTERACTIONS
            'L' key         enable/disable hitboxes and areas.
            'S' key         enable/disable sprites.
```

A script file determines the positions of the towers, the starting towers of
each plane, aswell as its speed and delay before take off.
There are scripts to test the program under the scripts directory.
