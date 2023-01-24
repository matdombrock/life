A Cellular Automaton implementation in C++ that outputs GIFs of the simulation results. 

![example](examples/example.gif)
![example](examples/example2.gif)
![example](examples/example3.gif)

# Configuration

The program will look for a cfg.txt file in the working directory. 

The file might look something like this:

```
# Example config
# Comments are ignored
file = life
delay = 16
frames = 128
pre = 0
width = 64
height = 64
scale = 8
pallet = white
copy_cfg = 1
rules = dstd
---
# .sorg settings
---
sorg = rune1
#sorg_center = 0
#sorg_x = 1
#sorg_y = 1
```


