# Logic-Gate Matter Engine

This repository contains an experimental C++ physics playground where digital logic is simulated by literal collisions between moving particles. Each packet is a rigid disk that carries bit states; when two packets touch, a logic rule decides whether they bounce, merge, or spawn new packets.

## Features

- Continuous collision detection for disk–disk interactions.
- Deterministic event scheduler that processes impacts in strict chronological order.
- Truth-table driven gate definitions.
- JSON scene loader and a lightweight text-mode viewer for inspecting simulations.

## Building

```bash
cmake -S . -B build
cmake --build build
```

## Running the viewer

```bash
./build/viewer examples/nand_demo.json 5.0 5.0 0.1
```

The viewer prints the timeline of packet positions and states. Swap in different JSON scenes to explore new logic constructs.
