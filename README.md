### Who Wants To Be a Millionaire

I am open to pull requests if anyone wants to improve on this game.

This is a simple version of the popular game made using C / GTK 4 / Libadwaita. The answers are hard-coded and not in a random order. There also is no time limit.

The codebase could be much improved by moving the main game logic into its own GObject class - a millionaire-gameplay an object that represents the game state, and give millionaire-window a property of type MillionaireGameplay making it into a model/view split, where Gameplay is responsible only for the game logic and Window is responsible only for displaying the game state in the UI. As a bonus, it gives the ability to use property bindings, like label: bind gameplay.money.


