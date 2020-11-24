# csc315_fall2020_graphclients

A visualization of different graph algorithms and pathfinding.

### Compile Instructions

To compile/clean the project respectively, run the following commands:
```bash
make
make clean
```

For more information run:
```bash
make help
```

### Example Usage
The program allows for custom graphs to be used using .dat files. For example,
a graph file would look like this:
```
3 3
1 1 1
1 -1 1
1 1 1
```
Where -1s represent walls and 1s represent traversable tiles.

To use a custom file, run the program as so:
```bash
./driver CUSTOM_MAP_FILE.dat
```
