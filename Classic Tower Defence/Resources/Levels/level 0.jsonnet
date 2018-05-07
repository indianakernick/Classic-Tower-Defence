local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

{
  map: 0,
  sprite: getSprite("map 0"),
  gold: 1000,
  health: 1000,
  spawntime: 1.5,
  waves: [
    {
      quantity: 20,
      proto: {
        UnitStats: {
          health: 200,
          armour: 100,
          healthRegen: 0.1,
          armourRegen: 0,
          dodge: 0.2,

          // frames per tile = pixels per tile / pixels per frame
          // tiles per second = frames per second / frames per tile
          // frames per tile = 16 / 1 = 16
          // tiles per second = 20 / 16 = 5 / 4 = 1.25

          moveSpeed: 1.25,
          gold: 10
        },
        UnitSprite: {
          sprite: getSprite("big robot 0 0"),
          frames: getSprite("big robot 1 0") - getSprite("big robot 0 0"),
          death: getSprite("explosion 0"),
          deathFrames: 4
        },
        local sprite = self.UnitSprite,
        UnitWalkAnim: {
          frames: sprite.frames,
          subframes: 1
        },
        Sound: {
          id: getSound("robot destroyed")
        },
        UnitPath: {}
      }
    }
  ]
}
