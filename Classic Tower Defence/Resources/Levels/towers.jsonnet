local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

[
  {
    stats: {
      range: 10,
      damage: 20,
      rof: 1,
      armourPiercing: 0
    },
    sprites: {
      gun: getSprite("cannon gun 0"),
      base: getSprite("cannon base"),
      firingFrames: 9
    },
    upgrades: {},
    sound: {
      id: getSound("cannon")
    }
  }
]
