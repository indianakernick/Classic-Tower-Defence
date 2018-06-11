local getSprite = import "get sprite.libsonnet";
local BaseWave = import "base wave.libsonnet";

{
  map: 0,
  sprite: getSprite("map 0"),
  gold: 2000,
  health: 100,
  spawntime: 1.5,
  waves: [
    BaseWave(10, "LIL BOT", "robot", {
      health: 2000,
      armour: 2000,
      healthRegen: 100,
      armourRegen: 100,
      dodge: 0.1,
      gold: 10
    }),
    BaseWave(10, "BIG BOT", "big robot", {
      health: 2000,
      armour: 2000,
      healthRegen: 100,
      armourRegen: 100,
      dodge: 0.1,
      gold: 10
    }),
    BaseWave(10, "FAT BOT", "tank", {
      health: 2000,
      armour: 2000,
      healthRegen: 100,
      armourRegen: 100,
      dodge: 0.1,
      gold: 10
    })
  ]
}
