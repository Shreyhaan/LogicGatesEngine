# Logic-Matter Engine Design Notes

This repository implements a toy “logic-gate matter” simulator where individual signal packets behave like rigid disks that carry discrete bit states. Collisions between packets are processed with continuous collision detection (CCD) so that the scheduling of logic operations is deterministic.

The design intentionally mirrors a logic circuit:

- **Packets** are the moving operands. Each packet stores a compact bitfield along with kinematic data.
- **Gates** are static colliders enriched with truth tables. When a packet strikes a port the truth table can emit new packets or mutate the state of the incident packet.
- **Emitters** act like clocked wires that periodically introduce packets into the world.

Events are processed strictly in chronological order via a deterministic priority queue. The CCD solver computes times of impact for moving disks so the simulation can “jump” directly to interesting interactions without missing collisions. After each event the engine reschedules collisions so the queue always contains the next candidate interactions.

Although the viewer in this commit is textual, the architecture is deliberately modular so a graphical renderer (e.g., SDL or ImGui) can be dropped in later without changing the simulation core.
