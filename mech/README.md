# LitePog Mechanical CAD

Mechanical CAD files for LitePog

## Exporting for 3D Printing

To export parts for 3D printing, open them in SolidWorks and save as `.3MF`.

Some parts contain multiple bodies, when importing the `.3MF` files into a slicer, ensure each body is treated as a separate part.

All parts should be printable without supports.
> Note: bridges and overhangs may not print well, but they will not be visible from the outside nor cause interference issues.

The list of required parts is:
- `strip_holder.SLDPRT` x2
- `strip_collar.SLDPRT` x2
- `button_plate.SLDPRT` x2
- `button_spacer.SLDPRT` x2
- `button_collar.SLDPRT` x2
- `handle_core.SLDPRT`
    - `logic_handle` configuration x1
    - `power_handle` configuration x1


## Rev 1 Notes

The following notes refer to [mech_rev1](https://github.com/Gigahawk/mech423_final_project/tree/mech_rev1/mech) (commit hash a887341).

### Playtest Notes
- Button placement is uncomfortable
    - Solutions:
        - Make handle's more narrow
            - Handle size is largely constrained by PCB design, which needs to be cost-effective (within 10x10cm), and easy to assemble.
        - Place button on side
            - Will require major redesign
        - Use a bigger/protruding arcade style button
            - Ideal for a next revision, but arcade buttons can be expensive

### Assembly Notes
- Thread features work smoothly
- LED strip clamp could be better designed currently the clamping force is transmitted through hot glue covering the LED strip solder joints
- Wall thickness is insufficient in many areas
    - Some areas are unfixable, like screw holes
- Screw holes are unnecessary
    - Sandwich mount works fine with just the collars holding the pieces together