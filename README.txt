Taylor Seale - tseale
Computer Graphics - CSE 40166
September 13, 2012
Homework #6 - Grand Theft Hotwheels: Carpet City

In GTHW: Carpet City, you play as a criminal roaming around Carpet City picking up packages (containing money I assume) while avoiding cops. The game gets progressively more difficult as it goes along and as the player passes stages.

CONTROLS:
	'w' - move forward
	's' - move backwards
	'a' - turn left
	'd' - turn right
	'esc' - exit

OBJECTIVES:
	-Collect as many packages as possible
	-Avoid the cops
	-Don't fall off the edge

POLICE AI:
	-Police will spawn from packages at the beginning of each stage
	-If police are "in pursuit" they will chase you
		-Police go out of pursuit if they collide with another police car
			-If a police car is out of pursuit & it was spawned in the current stage
				-It will patrol around the map, turning around at the border
			-If a police car is out of pursuit & it was spawned in a previous stage
				-It will patrol around the map, but if it encounters the border it will fall off
		-If you get to close to a police car that is out of pursuit
			-It will pursue you again!

FUTURE DEVELOPMENT:
	-GTHW: Carpet City could use a lot more
		-Better police AI (flocking, etc.)
		-Sound
		-Powerups
		-Guns
		-Better texturing
		-Multiple texturing
		-Shaders
		-Lights
		-Materials
		-Etc.
	-Possibly a candidate for my final project

KNOWN BUGS:
	-Police headings are a little wonky
	-Collision detection could use some more work