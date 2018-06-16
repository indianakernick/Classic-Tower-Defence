local getSprite = import "get sprite.libsonnet";
local BaseWave = import "base wave.libsonnet";

{
  map: 4,
  sprite: getSprite("map 0"),
  gold: 1000,
  health: 10,
  spawntime: 0.75,
  waves: [
    BaseWave(100, "warm UP", "tank", {
      health: 250,
      armour: 250,
      gold: 2
    }),
    BaseWave(50, "heavens ABOVE", "big robot", {
      health: 500,
      armour: 400,
      dodge: 0.2,
      armourRegen: 5,
      gold: 5
    }),
    BaseWave(30, "around THE WORLD", "robot", {
      health: 200,
      armour: 100,
      dodge: 0.75,
      healthRegen: 20,
      armourRegen: 20,
      gold: 10
    }),
    BaseWave(20, "space is SO HIGH", "big robot", {
      health: 1000,
      armour: 500,
      healthRegen: 10,
      armourRegen: 10,
      dodge: 0.1,
      gold: 20
    }),
    BaseWave(1, "LIKE A BOSS", "tank", {
      health: 50000,
      armour: 50000,
      healthRegen: 10,
      armourRegen: 10,
      gold: 1000,
      moveSpeed: 1.25 / 2
    }),
    BaseWave(50, "we're IN THE SKY", "robot", {
      health: 500,
      armour: 500,
      healthRegen: 100,
      armourRegen: 100,
      gold: 1
    })
  ]
}

