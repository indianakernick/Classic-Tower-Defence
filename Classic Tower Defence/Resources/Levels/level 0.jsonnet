local getSprite = import "get sprite.libsonnet";
local BaseWave = import "base wave.libsonnet";

{
  map: 3,
  sprite: getSprite("map 0"),
  gold: 100,
  health: 10,
  spawntime: 1.5,
  waves: [
    BaseWave(5, "quick cash", "robot", {
      health: 50,
      armour: 10,
      dodge: 0.25,
      gold: 10
    }),
    BaseWave(10, "dude", "big robot", {
      health: 150,
      armour: 100,
      gold: 10
    }),
    BaseWave(15, "boiii", "big robot", {
      health: 100,
      armour: 100,
      healthRegen: 10,
      armourRegen: 5,
      gold: 10
    }),
    BaseWave(15, "broomstick", "big robot", {
      health: 200,
      armour: 150,
      healthRegen: 5,
      armourRegen: 5,
      gold: 10
    }),
    BaseWave(10, "lad", "tank", {
      health: 250,
      armour: 250,
      healthRegen: 10,
      armourRegen: 5,
      gold: 10
    }),
    BaseWave(3, "sick lad", "tank", {
      health: 750,
      armour: 750,
      healthRegen: 20,
      armourRegen: 20,
      gold: 50
    }),
    BaseWave(100, "stream", "robot", {
      health: 50,
      armour: 50,
      gold: 2
    }),
  ]
}
