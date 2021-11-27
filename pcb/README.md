# LitePog PCB

PCB files for LitePog

## Rev 1 Bring-Up Notes

The following notes refer to [pcb_rev1](https://github.com/Gigahawk/mech423_final_project/tree/pcb_rev1/pcb) (commit hash f791dd6).

### Logic Handle (assembled 2021-11-17)
Logic handle was assembled and tested over multiple days:
- 2021-11-17: Initial bring up and testing of all components
- 2021-11-24:
    - Validate Neopixel function with 3.3V logic level
    - Fix transistor connection for button LED

Notes:
- MCU appears to work fine
    - Can be programmed as expected
    - Resonator `Y1` not populated for now, likely not necessary
        - Firmware can rely entirely on DCO
- Power supply works fine
    - Produces 3.3V as expected
- Level shifter doesn't work
    - Level shifter U2 is designed to be connected between open-drain (or push-pull) pins, not to be connected directly to buttons or LEDs.
    - Solutions:
        - Remove/bypass the shifter (**Current solution as of 2021-11-17**)
            - The only strictly 5V level interface is the Neopixel strip, although it is fairly likely to work at 3.3V
            - All other IO is OK to run at 3.3V
            - *EDIT 2021-11-24: Neopixel strip works fine with 3.3V logic signals, level shifter has been removed, and all bypass jumpers set*
        - Use shifters with explicit transfer directions
            - Will need multiple chips, but this will allow all IO to be 5V
        - Only shift the Neopixel data line
            - Minimizes chips, ideal solution for next revision
- LED transistor `Q1` is wired incorrectly
    - Current always flows through body diode regardless of input
    - Solutions:
        - Short `LED-` and `LED1` (*Solution from 2021-11-17*):
            - This inverses the LED on polarity (Set `LED1` to let current flow, high to stop)
            - This sinks 20 mA into the GPIO pin, not ideal.
            - This may cause problems/uneven lighting across the interconnect due to voltage drop.
                - The transistor on the power PCB appears to be correct
        - Flip transistor on PCB (**Current solution as of 2021-11-24**)
            - Pins 1 and 2 need to be swapped (pins on same side of IC), which means pin 3 will be facing the other way. It just so happens that there is a ground pad at approximately the right distance away from the actual transistor footprint that would make this work (or some of the silkscreen can be scratched away)
            - *CORRECTION 2021-11-24: pins 2 and 3 need to be swapped, this was done by rotating IC 180 degrees.*
            *Pin 1 was left floating, which was connected back to R8 with a bodge wire.*
        - Fix transistor configuration in schematic(swap drain and source)
            - ideal solution for next revision

### Power Handle
Power handle was assembled over multiple days:
- 2021-11-26: bring up and testing of critical components (boost, charging, protection, in that order)

Notes:
- Boost circuit works as designed, capable of producing high current (> 1A continuous for 10 seconds)
- Boost circuit can not be turned off
    - The datasheet for PAM2423 indicates that setting the `EN` pin low only disables the IC's boosting function, it does not turn off the output since there is a direct path from input to output via the inductor and diode.
    - Solutions:
        - Use switch to cut off input current (**Current solution as of 2021-11-26**)
            - Done by cutting the traces going to the input, and running wires to `SW1`.
                - `SW1` is already connected to `BATT+` to drive the `EN` pin, add an extra wire to allow high current flow
            - The EG1224 is only rated for 0.5A, finding higher current switches in this form factor is hard
                - EG2219 is a DPDT switch rated for 0.5A per pole, which can theoretically be combined for 1A total current, but this is still impractical because the input must provide more than 1A current at peak loads
                - Testing at 1A output current (~ 2A input current) seems to be fine (tested for ~10 seconds)
            - This is the simplest solution for this revision, since it does not require `EN` to be rewired, nor does it allow the boost converter to continually drain the battery from quiescent current.
            - There is a risk of arcing if switch is disconnected during high load, although this has not been observed, and should never happen in normal operation
        - Use switch to cut off output current
            - Similar issues to cutting off input current, although current requirements on the output are lower
            - Boost converter will be constantly on, and drawing quiescent current from battery
            - There is a risk of arcing if switch is disconnected during high load, although this has not been observed, and should never happen in normal operation
        - Use MOSFET to switch input current
            - Switch input from high side using a PMOS
            - Ideal solution for next revision
- Charging circuit appears to work as expected
    - LED comes on when plugged in and battery is below max voltage
    - LED turns off when max voltage is reached
- Protection circuit appears to work as expected
    - Datasheet for BQ2970 indicates that it must be bootstrapped the first time by connecting a charger to the battery, which was observed
    - *Note: protection features are largely untested*
        - Over discharge current protection is set high enough that it cannot trip
            - This is intentional, we want to allow the battery to provide as much current as necessary for the boost converter
            - A battery capable of providing the necessary current without overheating is being used
        - Short circuit protection is untested
            - This would involve shorting `BATT+` to ground, which is unlikely to happen in regular operation
            - This safety feature is typically intended for standalone battery protection boards that provide user accessible output terminals that could be accidentally shorted
        - Under voltage protection is untested
            - It is time-consuming to wait for the battery to completely drain while monitoring the voltage to ensure that the cutoff protection works.
            - Periodic checking of the battery voltage during firmware development should take place to ensure the battery voltage is within safe levels
        - Over voltage protection is untested
            - The charging circuit stops charging the battery prior to the over voltage protection threshold
        - Over charge current protection is untested
            - The charge current of the charging circuit is fixed at 500mA, and should never be high enough to trigger over charge current protection
- Bypass diode `D2` is left unpopulated
    - Theoretically it should be safe to populate, however it is unknown if this will cause adverse behavior with the boost circuit.
    - Populating this diode will prevent the output from being turned off with the switch when `VBUS` is present
- Aluminum capacitors `C10` and `C1` are not structurally sound
    - Should be reinforced with hot glue

### Button harness (Assembled 2021-11-24)
- Works as expected

### Neopixel strip (Assembled 2021-11-24)
- Removing provided connectors is rather hard
    - Nearly damaged the pads while removing old joints
    - Simpler solution for next revision is to order more LEDs than required and cut off first one to access unsoldered pads

### Interconnect harness (Assembled 2021-11-24)
- Works as expected
- Very time-consuming to assemble, set aside more time to do this next revision