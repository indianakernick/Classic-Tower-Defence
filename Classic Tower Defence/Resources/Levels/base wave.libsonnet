local getSound = import "get sound.libsonnet";
local getSprite = import "get sprite.libsonnet";

local BaseUnitStats = {
  healthRegen: 0,
  armourRegen: 0,
  dodge: 0,

  // frames per tile = pixels per tile / pixels per frame
  // tiles per second = frames per second / frames per tile
  // frames per tile = 16 / 1 = 16
  // tiles per second = 20 / 16 = 5 / 4 = 1.25

  moveSpeed: 1.25
};

local BaseUnit(name) = {
  Name: std.asciiUpper(name),
  UnitPath: {},
  UnitMoveDistance: {},
  Sound: getSound("robot destroyed")
};

local BaseUnitSprites(name) = {
  walk: {
    sprite: getSprite(name + " 0 0"),
    frames: getSprite(name + " 1 0") - self.sprite
  },
  death: {
    sprite: getSprite("explosion 0"),
    frames: 4
  }
};

function(count, name, sprite, stats) {
  quantity: count,
  proto: BaseUnit(name) + {
    UnitStats: BaseUnitStats + stats,
    UnitSprite: BaseUnitSprites(sprite)
  }
}
