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
      quantity: 100,
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
        UnitSprite: {
          sprite: getSprite("tank 0 0"),
          frames: getSprite("tank 1 0") - getSprite("tank 0 0"),
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
        UnitPath: {},
        UnitMoveDistance: {}
      }
    }
  ]
}
