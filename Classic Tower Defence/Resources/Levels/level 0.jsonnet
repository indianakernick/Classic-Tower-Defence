local getSprite = import "getsprite.libsonnet";

{
  "map": 0,
  "sprite": getSprite("placeholder map 0"),
  "waves": [
    {
      "quantity": 10,
      "stats": {
        "health": 100,
        "moveSpeed": 2
      },
      "sprite": {
        "sprite": getSprite("robot 0 0"),
        "frames": getSprite("robot 1 0") - getSprite("robot 0 0")
      }
    }
  ]
}
