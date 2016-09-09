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
-libsdl2-dev 
-libsdl2-image-dev 
-libsdl2-mixer 
 
#### Installation
1: Clone from git repository type in: 
git clone git@github.com:thelloin/project_Twisc.git 

2: 
 To compile using make in terminal.
 	Go into the twisc folder and type the following command: make
 		The game should now be compiled. 
 To clean the folder(Only do this if you want to remove all .o files).
 	Go into the twisc folder and tyoe the following command: make clean

 To compile the game using Eclipse:
  First Step:
  	 Project -> Properties -> c/c++ Build -> Settings -> GCC C++ Compiler -> Dialect
  	 Change the language standard to ISO C++11.
  
  Second Step:
   	Project -> Properties -> c/c++ Build -> Settings -> GCC C++ Linker -> Libraries
   	Click the "+" button(add) to add the following libraries
   		*SDL2
   		*SDL2_image
   		*SDL2_mixer
   	
  Third Step:
  	Project -> Properties -> c/c++ Build
  		Make sure that "Generate makefile automaticly" is checked.
   	
  Now you should be able to compile and run the game.


#### Disclaimers

Background music created by TeknoAXE: http://teknoaxe.com/Link_Code_2.php?q=696

Character animation created by larsiusprime, the spritesheet were slightly changed to match our needs : http://opengameart.org/content/super-miyamoto

Sound effect creates with bfxr: http://www.bfxr.net/
