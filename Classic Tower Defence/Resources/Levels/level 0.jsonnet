local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

local unitSprites(name) = {
  walk: {
    sprite: getSprite(name + " 0 0"),
    frames: getSprite(name + " 1 0") - self.sprite
  },
  death: {
    sprite: getSprite("explosion 0"),
    frames: 4
  }
};

{
  map: 0,
  sprite: getSprite("map 0"),
  gold: 1400,
  health: 100,
  spawntime: 1.5,
  waves: [
    {
      quantity: 10,
      proto: {
        UnitStats: {
          health: 2000,
          armour: 2000,
          healthRegen: 100,
          armourRegen: 100,
          dodge: 0.1,

          // frames per tile = pixels per tile / pixels per frame
          // tiles per second = frames per second / frames per tile
          // frames per tile = 16 / 1 = 16
          // tiles per second = 20 / 16 = 5 / 4 = 1.25

          moveSpeed: 1.25,
          gold: 10
        },
        UnitSprite: unitSprites("robot"),
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {},
        Name: "LIL BOT"
      }
    },
    {
      quantity: 10,
      proto: {
        UnitStats: {
          health: 2000,
          armour: 2000,
          healthRegen: 100,
          armourRegen: 100,
          dodge: 0.1,

          // frames per tile = pixels per tile / pixels per frame
          // tiles per second = frames per second / frames per tile
          // frames per tile = 16 / 1 = 16
          // tiles per second = 20 / 16 = 5 / 4 = 1.25

          moveSpeed: 1.25,
          gold: 10
        },
        UnitSprite: unitSprites("big robot"),
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {},
        Name: "BIG BOT"
      }
    },
    {
      quantity: 10,
      proto: {
        UnitStats: {
          health: 2000,
          armour: 2000,
          healthRegen: 100,
          armourRegen: 100,
          dodge: 0.1,

          // frames per tile = pixels per tile / pixels per frame
          // tiles per second = frames per second / frames per tile
          // frames per tile = 16 / 1 = 16
          // tiles per second = 20 / 16 = 5 / 4 = 1.25

          moveSpeed: 1.25,
          gold: 10
        },
        UnitSprite: unitSprites("tank"),
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {},
        Name: "FAT BOT"
      }
    }
  ]
}
