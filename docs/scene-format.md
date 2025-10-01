# Scene Format

Scenes are stored as JSON documents describing packets, static colliders, gates, and emitters. Fields are intentionally concise so the same description can be used by tooling or hand-authored.

```json
{
  "packets": [
    {"pos": [-1.0, 0.0], "vel": [1.0, 0.0], "radius": 0.05, "mass": 1.0, "state": 1}
  ],
  "colliders": [
    {"id": 10, "type": "segment", "a": [-2.0, -1.0], "b": [2.0, -1.0]}
  ],
  "gates": [
    {
      "id": 100,
      "name": "NAND",
      "ports": [
        {"id": 200, "name": "A", "pos": [0.0, 0.2], "dir": [1.0, 0.0], "radius": 0.06},
        {"id": 201, "name": "B", "pos": [0.0, -0.2], "dir": [1.0, 0.0], "radius": 0.06},
        {"id": 202, "name": "OUT", "pos": [0.6, 0.0], "dir": [1.0, 0.0], "radius": 0.06}
      ],
      "rule": {
        "table": [
          {"in": [0, 0], "outs": [{"port": "OUT", "state": 1, "speed": 1.4}]},
          {"in": [0, 1], "outs": [{"port": "OUT", "state": 1, "speed": 1.4}]},
          {"in": [1, 0], "outs": [{"port": "OUT", "state": 1, "speed": 1.4}]},
          {"in": [1, 1], "outs": [{"port": "OUT", "state": 0, "speed": 1.4}]}
        ]
      }
    }
  ],
  "emitters": [
    {"id": 300, "port": 200, "period": 0.5, "state": 1, "speed": 1.0}
  ]
}
```

Only the fields used by the current simulator are mandatory. Future iterations can extend the schema with additional gate types or collision primitives without breaking compatibility because unknown keys are ignored.
