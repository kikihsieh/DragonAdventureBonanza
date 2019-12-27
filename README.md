# Dragon Adventure Bonanza

#### Instructions for installing Freetype 

Mac users please run:
`brew install freetype
brew install glm`

#### Instructions for making the game easier for testing purposes
To unlock levels the cheater's way: 
* When the game is open, press "o" to manually generate a save file
* In the main directory, there should be a folder called saves
* Inside the saves folder, open the save_v3.txt file and change all the 0's to 1's
* Re-launch the game

To change the "goal" position that needs to be reached for a level change:
* Add the letter "G" to the location you want in the tile map (tile maps can be found in for example scenes/levels/forest_level.hpp)
* Alternatively, move "P" to whereever you want the player to be initialized to

To change the number of lives you start each level with:
* In ecs/entities/player.hpp change the line "health->health = 10;" to whatever number you want.
* To change the number of lives in the boss level, look in night_sky.cpp

#### Info
* The name of your game: Dragon Adventure Bonanza
* The names of your team members: Arden Allen, Dian (Desta) Chi, Karen Hong, Kiki Hsieh, Mayesha Kabir, Austin Kobayashi
* A short description of the game: A 2D platformer taking place in a fantasy world, you play as a baby dragon on a quest to find your long lost mother. Complete all three levels each with it's own unique player abilities, enemies and terrains and lastly, a final boss round!
* A still image of the game: still-image.png
* A link to trailer video: https://drive.google.com/file/d/1dbpmoPApd7OMlTD9pNeSt-WOubrNlLuY/view?usp=sharing

## Milestone 4: Final Game
### Features implemented this milestone
* UI/ UX
    * Updated help menu and main menu
    * Added credit modal
    * Added buttons on each level for navigation and help
    * Added exit button to main menu
    * Modal descriptions at the start of each level, storyline screen, victory scene
    * Added level select screen
    * Displays for # of torches to light in cave level
    * Displays for health status
    * Autosaving progress
    * Added a loading screen
    * Refresh/ restart a level when R is pressed 
* Gameplay
    * Level transitioning - level unlocking, ability unlocking
    * Added a tile properties system - collectibles, tiles with physical properties, torches, and goal tiles
    * Updated the design of all levels 
    * Added a final boss level with 4.5 phases
    * Adjusted player movement
    * Flashing feedback on damage
    * Light system for cave level and torch lighting
    * Created music and sound effects (total of 21 wav files)
    * New assets
    * Parallax scrolling
    * Removed the white lines around the player
    * Animated and created sprite sheets for the characters, torches, and hearts

### Stability
* Fixes from last milestone
    * **Runs decently but with significant memory usage increases over time**
        * Checked and fixed our memory leaks 
    * **Frame drops occasionally**
        * Made efficiency improvements to address this:
            * reduced the number of times we iterated through our entity list for collisions
            * fixed an issue with removing projectiles when they move off camera
            * stopped updating entities that are off screen and stopped calling render on them
        * we stopped at this point because it was good enough other things we considered doing include: 
            * rendering the tile map to texture once and just draw the texture
            * instance rendering
            * adding an entity manager system and storing components contiguously in memory
    * **White lines around the player** 
        *  Extra pixel in the spritesheet + changed some OpenGL flags
            
### Playability
* Game includes 3 distinct levels and a boss level 
* There is clear progression throughout the game
    * A new ability is unlocked at the end of every level 
        * Level 1 (forest): Player starts with the ability to shoot
        * Level 2 (cave): Player gains the ability to double jump
        * Level 3 (snow mountain): Player is able to air dash
        * Boss level: Player is able to fly
    * Each level gets progressively more difficult and has new challenges 
        * Level 1 (forest): Walking and shooting enemies
        * Level 2 (cave): This level is more maze-like and requires the user to explore and light torches before being allowed to complete the level. Adds flying enemies.
        * Level 3 (snow mountain): Faster shooting and walking speeds of enemies. Adds special ice tiles (that are slippery) and bouncy tiles. Requires the player to move upwards to goal.
        * Boss level: 4.5 different boss phases that the player needs to survive. Each phase has a different pattern of projectiles and flying enemy dragons. 
### User Experience
* Tutorial / game mechanics
    * Added a storyline to the game - at the start of each level, a modal describes the level and new abilities unlocked and how to use them
    * Help menu and main menu are easily accessible from all screens via buttons at the top right 
    * There is a button to exit the game from the main menu
    * Added a level select screen
* User testing: 
    * **The map is confusing!**
        * We addressed this point through our level design. Paths that we do not want the user to take have been blocked by physical barriers so there is no confusion as to which direction to go.
    *  **Visual feedback on collision would be nice**
        * Added flickering to the player when hit and audio feedback
    * **How much health do I have left?**
        * Added text that displays current health
    * **Controls are not crisp**
        *  Updated our friction calculations so that the player is able to make more precise movements 
    * **Ice physics are weiiiirrdd**
        * Re-did that with our friction calculations
    * **I don't like the key combination for controls**
        * There was not enough of a consensus on which controls are preferred in order to warrant a switch. Some people liked the current key mapping and fewer would like to see them switched so we kept our original key mapping.
    * **Being unable to see the ground when you're on higher platforms is super annoying**
        * Added sign posts for deadly drops and changed our level designs so that the floor below is visible
    * **The levels are too hard!**
        * Added collectible hearts throughout the level to regain health
    * **It's hard to hit stuff when I shoot**
       * Made the player projectiles bigger and its collision box bigger 
### External Integration 
* FreeType Library Integration - used for text rendering of player health (all levels), boss health (boss level) , and number of torches collected (level 2, cave level), Loading screen

### Advanced Graphics
* Parallax scrolling background for all three levels (forest, cave, snow) 
* Lighting system in level 2 (cave level) - added depth calculations
    * Darkened cave with a spotlight on the player 
    * Hit a torch with a fireball to see it light up
    * Allowed the torch to flicker to replicate real lit torches
    * Smooth blending light of adjacent torches
* More animations! - flying player sprite, boss, boss minions, hearts, cave spirits, torches, player projectiles etc.
### Advanced Gameplay
* Boss level with 4.5 different attack phases
    * Coordination between boss projectiles and minions to form different patterns 
    * New types of projectiles that bounce into different formations
    * Phases are boss health based 
    * Randomized safe spaces based on player position, player is able to reach a safe spot during each attack wave
* Tiles with physical properties - play level 3 (snow level) to see these
    * Sliding tiles - try walking on one
    * Bouncy tiles - try jumping on the top of these in the snow level
### Audio 
* **Background music:** Each level has a different soundtrack, victory soundtrack on game completion
* **Feedback:** We have sounds effects associated with the following actions; button clicks, the player getting hit, jumping, shooting, collecting a heart, lighting a torch, jumping on an enemy, shooting an enemy etc.

### Proposal Targets
* Optional advanced technical elements from the original pitch that were implemented
    *  Boss phases - varying attack patterns based on boss health
    *  Cutscenes - A storyline sequence using scenes and modals
* Changed targets from original pitch
    *  Moving platforms, disappearing platforms
        *   this just doesn't work well with our tile system so we opted to have tiles that are special in other ways such as slippery and bouncy ones
    *   Volcano level
        *   Decided that the player should be able to breath fire from the start and that it is unnecessary to have a separate level to unlock this ability. This was a decision made to save time and resources.
    *   Boss levels at the end of each level
        *   Changed to have one final boss level that is longer and more complex. This was a decision made to save time and resources. 

________________________________________________________________________________________________________________________
### Milestone 3: Playable Game

#### Rendering: 
* Added real sprite sheet animation
* More assests to create new levels

#### Gameplay:
* Enemies
   * Spline based flying enemies
   * Shooting enemies  
* Collisions with environment obstacles and enemies
   * Player is able to collide with platforms from all directions, the collisions are improved
* Systems
   * Health system (player and enemies are given health and can die)
   * Shooting System (player and enemies can shoot)
* UI
   * Escape/exit button
   * Clickable buttons
   * Help menu modals
* Features
   * Save game, return to old location when you fall
   * restart game when you lose all your lives
   * Pause

#### Creative Component: 
* Spline based flying enemies
* physics to make projectiles bounce
* three new and improved levels (forest, cave, mountain)
* extended camera to work vertically
* modals
* save (when player falls it restarts with its last location, if health is sufficient)

#### Robustness:
* No severe lag
* Resolution / ratio is consistent (1200 x 800) 
* No crashes

#### In progress: 
* Tile Map properties (bouncing, slipperry, damage tiles)
* final boss level
* story transitions


### Milestone 2: Minimal Playable Game

#### Rendering: 
* Added main dragon character sprite sheet.
* 12 different tile assets to create the level 

#### Gameplay:
* Architecture
   * Rewrote our code using ECS system and tile maps to generate levels
* Walking and jumping
   * The player is able to move forwards/backwards and jump based on keyboard controls
   * Physics System which includes Gravity, acceleration, velocity etc..  
   * The player is able to double jump
   * The player is able to airdash in its given direction while airborne
* Define our game space boundaries (boundary collision management)
   * Boundaries are now defined by our tile system
   * X boundaries are  by max number of columns
   * Y boundaries are by max number of rows
* Collisions with environment obstacles and enemies
   * Player is able to collide with platforms from all directions
* Collisions with enemies
   * Enemies move back and forth within a defined area
   * Enemies position is based on tile system
   * When it is on a tile it moves based on its surrounds
   * It knows when it's near the edge so it won't fall off and instead walk in the other direction
* UI
   * Provided basic main menu
   * Provided basic help menu
* Added level transitions between each level (currently pressing 1 switches to level 1, pressing 2 switches to level 2 etc)

#### Creative Component: 
* Air-dash physics
* Tile system to define the location of platforms, enemies and general level design.
* Main menu and button classes

#### Robustness:
* No severe lag
* Resolution / ratio is consistent (1200 x 800) 
* No crashes

#### Items missing from development plan: 
* Boss Level
   * Due to the migration of all our game mechanics into the ECS system, a lot of these mechanics needed to be refactored and improved. This was vital before starting any boss level
* Parallax scrolling
   * Similar reason. Migration to ECS was more vital, this will be moved to the next sprint

#### In progress: 
* Collisions 
   * With enemies, due to change into ECS, enemy collision lost functionality, it will continue to be worked on 
   * With tiles, is slightly buggy, logic needs to be tweaked
   * Clickable main menu


### Milestone 1: Skeletal Game

#### Rendering: 
* Main dragon character, multiple spiders, ground, and one platform is rendered in the correct drawing order
* 2D Transformations and key-frame/state interpolation of the dragon and spiders based on their movement

#### Gameplay: 
Walking and jumping
* The player is able to move forwards/backwards and jump based on keyboard controls
* Define our game space boundaries (boundary collision management)
    * Gamespace boundaries are defined in world.cpp
    * There are boundaries on the left, right, top, and bottom of the level
    * The player cannot move past the left, right, and top boundaries
    * Touching the bottom boundary kills the player
* Collisions with environment obstacles and enemies
    * Player is able to collide with platforms from all directions
    * No collisions with enemies (yet)
* Enemies move back and forth within a defined area
* Enemies position is randomized for now, once the tile system is introduced in, will be able to statically position enemies and platforms 

#### Creative Component: 
* Camera-follow: camera follows player as they move across the screen. The camera adapts to forward/backward movement and smoothly transitions between the two states
    * Camera does not stop at the correct position in relation to  world boundaries 
* Double jump: If the ability is unlocked, the player can jump a second time while in the air. Landing on the ground or a platform will reset the jumps.
* Gravity 

#### Robustness:
* No severe lag
* Resolution / ratio is consistent (1200 x 800) 
* No crashes

#### Items missing from development plan: 
We implemented features not mentioned in the development plan for this week in place of these items as we found that they were more vital to the basic game definition. These include the camera-follow, tile system, and gravity/ double jump. 
* ECS design: We focused on gameplay mechanics and will update to ECS design as we find common elements to combine
* Walking enemy AI (platform bound): we decided to change to a tile system for defining platforms before attempting to place enemies on them. We also plan to use the tile system to place the spiders. As this is an additional feature that we did not anticipate implementing, we did not have the time to implement platform bound enemies. 
* Collisions with enemies: collisions for platforms is working which can in turn be easily reused to provide collisions with enemies

#### In progress: 
* Tile system: we are currently working on a tile system to define the location of platforms and general level design. This is already working except collisions with platforms declared in this way are not yet implemented. (it’s on the tile_system branch)
* Collisions with enemies
* Enemies dropping in y-direction at random time
