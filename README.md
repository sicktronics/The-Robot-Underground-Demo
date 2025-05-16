# The Robot Underground
Jump into a world of wiring, coding, and testing robots as you unravel the disappearance of your coworker and friend Jefe. While it's too risky for you to waltz into a government research facility yourself, you and your partner Temp devise a plan to send a robot in to infiltrate instead. Gather information and find out what other secrets they've been hiding!

[Download and play the demo here! (COMING SOON)](./README.md "an itch.io link I assume?")

The game itself revolves around wiring and coding a robot to solve various challenges. You learn to wire your Arduino up to your motor drivers and make it move with the code you load onto it. The robots that you build in-game should behave identically to actual robots, so these skills can be directly transferred into building a real-life Speedy Luigi. 


<p float="center">
  <img src="READMEPics/Website_Graphix_2.png" width="32%" />
  <img src="READMEPics/Website_Graphix_3.png" width="32%" /> 
  <img src="READMEPics/Website_Graphix_6.png" width="32%" />
</p>

## System Requirements
- Compatible with: Windows x64
- Minimum Graphics Requirements: COMING SOON
- Minimum RAM Requirements: COMING SOON

## How to Build the Project in Unreal
1. Make sure you have Unreal Engine 5.4.4 installed, as well as an IDE such as VSCode, Visual Studio, or Rider
2. Clone this repository
3. Build the project in your IDE (steps vary depending on your specific IDE—for VSCode, use "Run and Debug" --> "Launch TRUDemoEditor (Development) (workspace)")
4. Unreal should compile the project files and then open the project (Yay!)
5. To test out the demo in the editor, run the PermaWorld map

## Socials
Follow us on [Instagram](https://www.instagram.com/therobotunderground/ "@therobotunderground"), [TikTok](https://www.instagram.com/therobotunderground/ "@therobotunderground"), or [YouTube](https://www.youtube.com/channel/UCGiVgfm5pshJ7L6ViB6xAog "The Robot Underground") or check out our [website](https://robotunderground.party/ "robotunderground.party") to keep up with our progress!

## About the Repository
ToDo
- (funny/sketchy) dev challenges lol

This project was built in Unreal Engine 5, meaning it's written in C++ and Blueprints (Unreal's visual programming language built on top of C++). We also plug in the [Arduino simulation library](https://github.com/sicktronics/avr8cpp "sim library") created by Parker as a static library. This needs to be compiled into a static `.lib` file separately and included into the project as an Unreal 3rd-Party Plugin.

This repository is laid out similarly to most other Unreal projects. The `Content` folder contains all Unreal-generated assets, including all imported images/textures, UI elements, Blueprint actors, data tables, and levels (maps). The `Config` folder contains some engine configurations, and the `Source` folder contains all C++ source files. 

In this game, the only map that you should load is `PermaWorld.umap`. All other levels are streamed into PermaWorld, and it also includes any global actors that need to be persisted across levels. Various singleton actors are loaded and used throughout the game to manage subsystems, such as the inventory or wiring managers. The entire game is managed by the `GameMaster`, who switches between levels, menus, and pawns (player-controlled actors). 

## About the Team
ToDo
- if there's some professional email for TRU, could link here too
- better/longer individual intros?
- if this repo is gonna be referenced after graduation, should probably switch to professional emails

This was Parker's project, created as a natural extension of work she and her sister had been doing to make robotics accessible to middle- and high-school students that would otherwize have had no access or exposure to robotics education. For the rest of us, it became our capstone project for a year, learning to build and ship a game while working with others towards a shared goal. It has become a source of pride (and stress) as we've dug into this project to make it happen. 

**Crystal Lee** (leecry@oregonstate.edu)  
Robot wiring and game loop

**Evelyn Nixon** (nixone@oregonstate.edu)  
Modelling and animation

**Him Shun Lee** (leehi@oregonstate.edu)  
Compilation pipeline

**Ian Dugo** (dugoi@oregonstate.edu)  
Level design and inventory

**Luke Williams** (williluk@oregonstate.edu)  
Robot simulation and texturing
 
**Parker Caywood Mayer** (mayerpa@oregonstate.edu)  
Robot simulation and gnomes


**Kirsten Winters**  
Team Mentor, Senior Instructor I, OSU College of Engineering
