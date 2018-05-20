local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

local unitSprites(name) = {
  sprite: getSprite(name + " 0 0"),
  frames: getSprite(name + " 1 0") - self.sprite,
  death: getSprite("explosion 0"),
  deathFrames: 4
};

{
  map: 0,
  sprite: getSprite("map 0"),
  gold: 2000,
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
        local sprite = self.UnitSprite,
        UnitWalkAnim: {
          frames: sprite.frames
        },
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {}
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
        local sprite = self.UnitSprite,
        UnitWalkAnim: {
          frames: sprite.frames
        },
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {}
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
        local sprite = self.UnitSprite,
        UnitWalkAnim: {
          frames: sprite.frames
        },
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {},
        UnitMoveDistance: {}
      }
    }
  ]
}
