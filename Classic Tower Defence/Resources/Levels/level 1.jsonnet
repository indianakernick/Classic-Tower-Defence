local getSprite = import "get sprite.libsonnet";
local BaseWave = import "base wave.libsonnet";

{
  map: 1,
  sprite: getSprite("map 0"),
  gold: 250,
  health: 10,
  spawntime: 1,
  waves: [
    BaseWave(25, "homie", "robot", {
      health: 250,
      armour: 100,
      gold: 5
    }),
    BaseWave(10, "bruh", "robot", {
      health: 250,
      armour: 250,
      healthRegen: 10,
      dodge: 0.1,
      gold: 10
    }),
    BaseWave(30, "sam", "tank", {
      health: 100,
      armour: 100,
      healthRegen: 25,
      armourRegen: 25,
      dodge: 0.2,
      gold: 10
    }),
    BaseWave(30, "meaningless name", "big robot", {
      health: 200,
      armour: 200,
      healthRegen: 15,
      dodge: 0.3,
      gold: 10
    }),
    BaseWave(5, "~!@#$%^&*()_+", "robot", {
      health: 100,
      armour: 100,
      dodge: 0.9,
      healthRege: 5,
      gold: 20
    }),
    BaseWave(50, "blue blazers", "tank", {
      health: 1000,
      armour: 500,
      healthRegen: 10,
      armourRegen: 10,
      gold: 5
    })
  ]
}
