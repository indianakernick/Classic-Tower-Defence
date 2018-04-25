local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

local towerSprites(sprite) = {
  gun: getSprite(sprite + " 0"),
  base: getSprite(sprite + " base"),
  firingFrames: $.base - $.gun
};

[
  {
    stats: {
      range: 6,
      damage: 10,
      rof: 3,
      armourPiercing: 0.1
    },
    sprites: towerSprites("blaster"),
    upgrades: {},
    sound: {
      id: getSound("blaster")
    }
  },
  {
    stats: {
      range: 4,
      damage: 30,
      rof: 1/2,
      armourPiercing: 0
    },
    sprites: towerSprites("cannon"),
    upgrades: {},
    sound: {
      id: getSound("cannon")
    }
  }
]
