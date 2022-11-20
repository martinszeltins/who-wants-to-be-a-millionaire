<div style="display: flex; justify-content: center;"><img src="https://raw.githubusercontent.com/martinszeltins/who-wants-to-be-a-millionaire/master/data/icons/hicolor/scalable/apps/lv.martinsz.millionaire.svg" width="100px" /></div> <h1 style="text-align: center;">Who Wants To Be a Millionaire</h1>

I am open to pull requests if anyone wants to improve on this game.

This is a simple version of the popular game made using C / GTK 4 / Libadwaita. There are only 10 hard-coded questions and they are not in a random order. There also is no time limit.

The codebase could be much improved by moving the main game logic into its own GObject class - a millionaire-gameplay an object that represents the game state, and give millionaire-window a property of type MillionaireGameplay making it into a model/view split, where Gameplay is responsible only for the game logic and Window is responsible only for displaying the game state in the UI. As a bonus, it gives the ability to use property bindings, like label: bind gameplay.money.

The game also uses GTK Fixed widget and a fixed window size. This could also be improved by moving to a more responsive layout like GTK Grid.

**Screenshot**:
<img src="https://raw.githubusercontent.com/martinszeltins/who-wants-to-be-a-millionaire/master/screenshot.jpg" />
