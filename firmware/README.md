# LitePog Firmware

## Config Constants

Hardware specific configuration should go inside `config.h`.

## Building

Ensure you are building for the correct target platform:
Right click project > `Build Configurations` > `Set Active` > your platform.

## Design Spec

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
    - The first player to release their button spawns the "ball" in the middle, the ball starts travelling away from this player
5. Ball reaches player
    - The player must press the button when the ball reaches their side (indicated by the button lighting up) to continue the rally
    - If the player fails to return the ball, the game ends
6. Display game end animation
    - Winner side blinks green, loser side blinks red
    - Return to idle animation after a few seconds

