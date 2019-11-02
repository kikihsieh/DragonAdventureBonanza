# Dragon Adventure Bonanza

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
