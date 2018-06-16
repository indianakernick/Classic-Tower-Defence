local getSprite = import "get sprite.libsonnet";

{
  map: 5,
  sprite: getSprite("map 0"),
  gold: 0,
  health: 0,
  spawntime: 1,
  waves: []
}
