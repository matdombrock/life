A Cellular Automaton simulator in C++.

Outputs GIFs and CSV analysis of the simulation results. 

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

Note: Lines beginning with `#` or `-` are ignored. So are empty lines.

## Rules
There are 4 conditions for which we must specify a "rule". A rule is a combination of a condition and an "action". 

Each condition relates to the amount of "neighbors" a cell has. A cell is considered to have a neighbor if another living cell is touching it on its sides or corners.

In this example the cell "C" has 3 neighbors.
```
100
0C1
100
```

The conditions are as follows:

1. Neighbors < 2
2. Neighbors = 2
3. Neighbors = 3
4. Neighbors > 3

When one of these conditions is met, we need to take an "action". 

There are 3 possible actions that can be taken:

1. Survive: A living cell continues to live.
2. Thrive: A living cell continues to live. If the position is unoccupied (no living cell lives here) then a new cell is born at this position.
3. Die: A living cell will die.

Note: There is no functional difference between a dead cell and an empty cell. 

We can also call these rules by the first character of their name:

```
s = Survive
t = Thrive
d = Die
```

Considering that we always need to define exactly 4 rules, we can think of a rule set as being any string with a length of 4 characters that contains only the characters "s", "t" and "d". 

For example, the rules for Conway's Game of Life would be:

```
dstd
```

This would translate to:
1. Neighbors < 2 -> Die
2. Neighbors = 2 -> Survive
3. Neighbors = 3 -> Thrive
4. Neighbors > 3 -> Die

We can use this method to define any possible rule set. However, it is important to note that each condition can only have 1 rule and each rule set must have exactly 4 rules.

An interesting alternative to Conway's rule set is:
```
dttd
```

# The `.sorg` File Type

## Specifications
- Lines beginning with `#` are comments and are ignored.
- Spaces are removed from lines before the are read or counted
- Each character represents one cell
- The following characters represent a cell which is off `0`,`O`,`o`
- Any other character aside from `#` is considered to be on
- A line that contains # but does not start with # is an error and the file will be rejected  
- Width is determined by counting the (string) size of the first row
- Any row with a size greater than the first row is an error and the file will be rejected
- Height is determined by counting the number of rows 

Note: comments are really only intended to be used at the top of the file. 

## Example
An example `.sorg` file might look like this:

```
# A simple oscillator
1100
1100
0011
0011
```

This file would be calculated to have a `width` of 4 and a `height` of 4.

# Analysis Files

## Graphing Tool
http://www.graphreader.com/plotter

## Analysis Example
```
generations: 128

avg_age: 19.091869

avg_neighbors: 2.686716

avg_births: 32.625000

avg_deaths: 19.093750

final_alive: 6682

births: 4176

deaths: 2444

------- 

age_vector: 

1.500000, 1.777778, 1.833333, 2.000000, 1.250000, 2.111111, 2.727273, 2.700000, 2.928571, 3.583333, 3.263158, 3.000000, 2.076923, 1.866667, 2.454545, 2.250000, 2.500000, 3.250000, 2.857143, 1.500000, 1.500000, 1.750000, 1.500000, 2.000000, 1.666667, 2.111111, 2.500000, 2.428571, 2.777778, 4.000000, 3.714286, 3.777778, 5.500000, 5.000000, 4.777778, 7.000000, 6.285714, 5.777778, 8.500000, 7.571429, 6.777778, 10.000000, 8.857143, 7.777778, 11.500000, 10.142857, 8.777778, 13.000000, 11.428571, 9.777778, 14.500000, 12.714286, 10.777778, 16.000000, 14.000000, 11.777778, 17.500000, 15.285714, 12.777778, 19.000000, 16.571429, 13.777778, 20.500000, 17.857143, 14.777778, 22.000000, 19.142857, 15.777778, 23.500000, 20.428571, 16.777778, 25.000000, 21.714286, 17.777778, 26.500000, 23.000000, 18.777778, 28.000000, 24.285714, 19.777778, 29.500000, 25.571429, 20.777778, 31.000000, 26.857143, 21.777778, 32.500000, 28.142857, 22.777778, 34.000000, 29.428571, 23.777778, 35.500000, 30.714286, 24.777778, 37.000000, 32.000000, 25.777778, 38.500000, 33.285714, 26.777778, 40.000000, 34.571429, 27.777778, 41.500000, 35.857143, 28.777778, 43.000000, 37.142857, 29.777778, 44.500000, 38.428571, 30.777778, 46.000000, 39.714286, 31.777778, 47.500000, 41.000000, 32.777778, 49.000000, 42.285714, 33.777778, 50.500000, 43.571429, 34.777778, 52.000000, 44.857143, 35.777778

neighbors_vector: 

3.000000, 2.666667, 2.833333, 2.625000, 3.000000, 2.111111, 2.545455, 2.500000, 2.285714, 3.000000, 2.368421, 3.000000, 2.692308, 2.666667, 2.545455, 2.750000, 2.916667, 2.500000, 2.714286, 3.000000, 2.666667, 2.750000, 2.500000, 2.333333, 3.000000, 2.333333, 3.000000, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667, 2.833333, 2.571429, 2.666667

births_vector:

6.000000, 10.000000, 6.000000, 6.000000, 4.000000, 16.000000, 18.000000, 14.000000, 20.000000, 16.000000, 24.000000, 12.000000, 8.000000, 14.000000, 14.000000, 6.000000, 6.000000, 12.000000, 16.000000, 12.000000, 8.000000, 16.000000, 16.000000, 32.000000, 16.000000, 48.000000, 32.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000, 40.000000, 24.000000, 48.000000

deaths_vector:

4.000000, 2.000000, 12.000000, 6.000000, 12.000000, 0.000000, 0.000000, 8.000000, 0.000000, 12.000000, 0.000000, 26.000000, 16.000000, 12.000000, 16.000000, 16.000000, 18.000000, 12.000000, 0.000000, 16.000000, 16.000000, 8.000000, 16.000000, 0.000000, 32.000000, 0.000000, 40.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000, 32.000000, 24.000000, 8.000000

alive_vector:

12, 18, 12, 16, 16, 18, 22, 20, 28, 24, 38, 24, 26, 30, 22, 24, 24, 16, 28, 24, 24, 32, 32, 48, 48, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72, 48, 56, 72

```

More info coming soon.