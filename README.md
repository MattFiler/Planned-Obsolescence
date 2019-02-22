<img align="right" src="https://i.imgur.com/Udt8hGy.jpg" width="100%" alt="Planned Obsolescence">

This was a group project to create a game with a tangential link to the film Ex Machina. 

Using OpenGL and the engine framework ASGE we created Planned Obsolescence - a game where you play TIM, the Totally Intelligent Machine. TIM oversees a research lab which has just started working on a project to supersede TIM. The goal of the game is to disrupt their work on the project so that TIM can stay in control of the lab and not be replaced.

<img align="right" src="https://i.imgur.com/Q0MhRLJ.png" width="50%">

### Gameplay

In order to disrupt project work you can interact with a number of locations around the map - for example, corrupting a computer system or closing a door. Doing so will decrease worker's productivity which will affect the progression speed of the project.

Interactions with points around the map cost energy, which you slowly gain over time. If you don't have enough energy you will be unable to interact with a point - so don't spend it too casually!

You must watch out for guards when interacting with points in the map, as being spotted by a guard will raise their suspicion of your actions. If one of the guard's suspicion gauges reaches 100%, it's game over and you're shut down.

Any points in the map that you damage will be repaired by the lab technicians after the workers report the fault, so keep an eye out for them and try to delay their access to fix points as long as possible!

To win, you must make the workers unproductive to the point that they are unable to finish the project before their deadline. If the replacement project isn't completed, TIM is kept in control of the lab and continues to see another day.

If the workers finish the project before the deadline however, TIM is replaced and it's game over.

### Extra Stuff

This project includes an editor tool to allow easy configuration modifications. It also allows the ability to produce custom maps through tileset and room definitions, and features a smart keybind manager that ties to the game launcher - allowing remapping of key inputs.

Not all configurations can be changed through the editor as this project was quite time limited so the focus was on finishing game features towards the end rather than having a fully working toolset. Some things like character data (sprites, sizes, etc) can be modified in the game's JSON files, but not through the tool's GUI.

The game also supports multiple languages (English/Spanish/French) and resolutions, able to be selected in the launcher on startup.

### Team

This project was put together by:

- [Matt Filer](http://www.mattfiler.co.uk) (tools programmer, systems programmer, designer)
- [Toby Jones](https://github.com/Halichoerus) (AI programmer, systems programmer)
- [Szymon Wlodarczyk](https://github.com/SzymonTheWlod) (tile sprite design)