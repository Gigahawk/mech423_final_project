# LitePog PCB

PCB files for LitePog

## Rev 1 Bring-Up Notes (2021-11-17)

The following notes refer to [pcb_rev1](https://github.com/Gigahawk/mech423_final_project/tree/pcb_rev1/pcb) (commit hash f791dd6).

### Logic Handle

- Level shifter doesn't work
    - Level shifter U2 is designed to be connected between open-drain (or push-pull) pins, not to be connected directly to buttons or LEDs.
    - Solutions:
        - Remove/bypass the shifter (**Current solution for this bring-up**)
            - The only strictly 5V level interface is the Neopixel strip, although it is fairly likely to work at 3.3V
            - All other IO is OK to run at 3.3V
        - Use shifters with explicit transfer directions
            - Will need multiple chips, but this will allow all IO to be 5V
        - Only shift the Neopixel data line
            - Minimizes chips, ideal solution for next revision
- LED transistor Q1 is wired incorrectly
    - Current always flows through body diode regardless of input
    - Solutions:
        - Short `LED-` and `LED1` (**Current solution for this bring-up**):
            - This inverses the LED on polarity (Set `LED1` to let current flow, high to stop)
            - This sinks 20 mA into the GPIO pin, not ideal.
            - This may cause problems/uneven lighting across the interconnect due to voltage drop.
                - The transistor on the power PCB appears to be correct
        - Flip transistor on PCB (**Ideal solution for this revision, should look into this**)
                - Pins 1 and 2 need to be swapped (pins on same side of IC), which means pin 3 will be facing the other way. It just so happens that there is a ground pad at approximately the right distance away from the actual transistor footprint that would make this work (or some of the silkscreen can be scratched away)
        - Fix transistor configuration in schematic(swap drain and source)
            - ideal solution for next revision
- Resonator Y1 not populated for now
    - Likely not necessary
