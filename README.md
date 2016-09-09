# A project done for the course [TDP005](https://www.ida.liu.se/~TDP005/)
Started 2014-11 and ended 2014-12  
Techniques used: C++, SDL2, Git  
IDE used: Eclipse  
 
## Twisc - The Wall is Coming


#### Player controls
A and D: Walk left or right  
W : Jump  
Space(while walking): Use the ability "Dash", kills enemies and bullets.  
	You die if you dash into walls, use it wisely.  
P : Paus the game  
ESC : Paus and open paus menu  
Up and Down arrow : Move in menu  
Enter : Execute selection in menu  
 
 
#### Requirements
Make sure you have following installed on your system.  
- -libsdl2-dev 
- -libsdl2-image-dev 
- -libsdl2-mixer 
 
#### Installation
To start the game from terminal:  
1. Clone from git repository type in: 
`git clone git@github.com:thelloin/project_Twisc.git`  
2. Go into the twisc folder and type the following command: `make`  
The game should now be compiled.  
3. Start the game by typing: `./Twisc`

To start the game using Eclipse:  
1. Go to: Project -> Properties -> c/c++ Build -> Settings -> GCC C++ Compiler -> Dialect and change the language standard to ISO C++11.  
2. Project -> Properties -> c/c++ Build -> Settings -> GCC C++ Linker -> Libraries and
click the "+" button(add) to add the following libraries
- SDL2
- SDL2_image
- SDL2_mixer
3. Project -> Properties -> c/c++ Build  
Make sure that "Generate makefile automaticly" is checked.
4. Start the game using the green start button.


#### Disclaimers

Background music created by TeknoAXE: http://teknoaxe.com/Link_Code_2.php?q=696

Character animation created by larsiusprime, the spritesheet were slightly changed to match our needs : http://opengameart.org/content/super-miyamoto

Sound effect creates with bfxr: http://www.bfxr.net/
