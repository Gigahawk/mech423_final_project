# LitePog Firmware

## Config Constants

Hardware specific configuration should go inside `config.h`.

## Building

Ensure you are building for the correct target platform:
Right click project > `Build Configurations` > `Set Active` > your platform.

## Design Spec

### Terminology

- `Button 1`: The button connected to the logic PCB
- `Button 2`: The button connected to the power PCB
- `Handle 1`: The handle containing the logic PCB
- `Handle 2`: The handle containing the power PCB
- `Ball`: Single pixel of light that players must keep from reaching their handle
- `Return Zone`: Area that the ball must be in for a player to interact with the ball (in certain game modes)

### Revision 2

The following notes are for the specification designed below, implemented as of [firmware_rev2](https://github.com/Gigahawk/mech423_final_project/tree/firmware_rev2/firmware) (commit hash 8e8a770)

#### Playtest Notes

- Game Select Mode
    - Works well, reasonably intuitive given the lack of buttons
- Play Mode
    - Return zone should not be pure blue, probably best to make the hue slightly different to improve contrast
    - **Pong**
        - Works much better than Rev 1
        - Better anti-spam may be required
            - Cooldown between button presses to penalize double presses
    - **Ping Pong**
        - Works as expected
        - Anti-spam works fine
    - **Tug o' War**
        - May be better to experiment with how exactly the button interacts with the ball
            - Buttons should probably change the velocity of the ball instead of position directly
                - In this case there should be some natural decay of the ball speed towards 0 so that it doesn't move if nothing is pressed.
            - Should investigate benefits of punishing/helping losing player (when ball is near their handle)

#### Specification
The following will outline the expected behavior of LitePog.

##### Game Select Mode

1. User powers up LitePog while holding down Button 2
2. LitePog displays the demo animation of the currently selected game, as well as a rainbow pattern near Handle 2
3. User(s) can choose the next or previous games by pressing Button 1 or Button 2
4. The selection is saved to FRAM when the device is turned off

##### Play Mode

1. User powers up LitePog with no buttons held down.
2. LitePog displays the demo animation of the currently selected game
    - LitePog leaves idle animation when both buttons are held
3. Game count down starts
    - One or two red pixels in the middle light up, and grows outwards at regular interval
    - Once the countdown ends, all red pixels turn green
    - If either player releases their button at this point, return to the demo animation
4. Game is active
    - See below for game types
5. Display game end animation
    - Winner side blinks green, loser side blinks red
    - Return to idle animation after a few seconds

##### Pong

1. The first player to release their button spawns the ball in the middle, the ball starts travelling away from this player
2. Once the ball reaches the return zone of a player, (indicated by their button lighting up), they must press their button to return the ball
    - The return zone should be a few pixels in width
    - If the player fails to return the ball, the game ends

##### Ping Pong

1. The first player to release their button spawns the ball in the middle, the ball starts travelling away from this player
2. Once the ball reaches the return zone of a player, (indicated by their button lighting up), they must press their button to return the ball
    - The return zone should take up half of the light strip
    - If the player fails to return the ball, the game ends
    - If a player presses their button while the ball is not in their return zone and travelling towards them, the game ends

##### Tug o' War

1. The first player to release their button spawns the ball in the middle, the ball starts travelling away from this player
2. Each time the players press a button, the ball moves one pixel away from them
3. If the ball reaches a player's handle, the game ends

### Revision 1

The following notes are for the specification designed below, implemented as of [firmware_rev1](https://github.com/Gigahawk/mech423_final_project/tree/firmware_rev1/firmware) (commit hash 97b537f)

#### Playtest Notes

- Timing is both too slow and too fast
    - Movement of ball between handles takes too long, but the window to return a ball is too small, no good middle ground exists
        - Solution(s):
            - Player should be able to return the ball when the ball reaches a few LEDs prior to the last one (button should light up a few LEDs earlier)
                - This gives greater flexibility to find timing values that are both fun and challenging to play with.
            - Implement the game as shown in the promo video (see below)
- No speaker
    - No solution, the commercial product has more room due to injection molded parts, and more freedom with PCB sizing.
- Only one game mode
    - The commercial product appears to have extra buttons for game selection
        - Solution: Game select mode is handled by holding down the power handle button while flicking the switch, then the two buttons can be used to scroll through the game types.
        The selected game type is stored in FRAM, then the user power cycles the unit, and a demo animation unique to the game starts playing
    - Game Types from [promo video](https://www.youtube.com/watch?v=iOcHVvs48tQ):
        - Ping Pong:
            - Similar to current game, but player can press button to return the ball any time as soon as it passes the middle point.
            - Player loses if they push the button while it's on the other player's side
                - There is also supposedly anti-spam code, although this seems redundant
                - It may be fun to have a mechanic to incentivize waiting for longer before returning the ball (risks losing the game if player waits too long and the ball reaches their end) some potential examples:
                    - Ball returns faster depending on how close it is to the player
                    - Opponents reigion to return the ball gets smaller
        - Rev & Release:
            - This appears to be a single player game where you hold the button to shoot the ball down the tube, then release at a certain point.
                - Single player games don't look very fun, and will not be implemented
        - Tug o' War:
            - Each player button mashes to move the ball closer to the opponent side (think [egg blowing game](https://www.youtube.com/watch?v=yyNyL65NAKE) but less gross)
                - The commercial game uses buttons that are much nicer to spam with, this may cause pain on our buttons
        - Cyclone:
            - I have no idea how this is supposed to work, but this also appears to be a single player game.
                - Single player games don't look very fun, and will not be implemented

#### Specification
The following will outline the expected behavior of LitePog.

1. User powers up LitePog
2. LitePog displays its idle animation
    - LED strip displays either a rainbow cycling effect (power source permitting), or a simple dot moving back and forth.
    - Buttons light up when pressed
    - LitePog leaves idle animation when both buttons are held
3. Game count down starts
    - One or two red pixels in the middle light up, and grows outwards at regular interval
    - Once the countdown ends, all red pixels turn green
    - If either player releases their button at this point, return to the idle animation
4. Game is active
    - The first player to release their button spawns the ball in the middle, the ball starts travelling away from this player
5. Ball reaches player
    - The player must press the button when the ball reaches their side (indicated by the button lighting up) to continue the rally
    - If the player fails to return the ball, the game ends
6. Display game end animation
    - Winner side blinks green, loser side blinks red
    - Return to idle animation after a few seconds

