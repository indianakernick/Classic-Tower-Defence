local getSprite = import "get sprite.libsonnet";
local getSound = import "get sound.libsonnet";

local towerSprites(sprite) = {
  base: getSprite(sprite + " base"),
  projectile: getSprite(sprite + " projectile"),
  gun: {
    sprite: getSprite(sprite + " 0"),
    frames: $.base - self.sprite
  }
};

local BaseTower(index, name, sprite, sound, stats) = {
  local tower = self,

  Name: std.asciiUpper(name),
  CommonTowerStats: stats,
  TowerSprites: towerSprites(sprite),
  Sound: getSound(sound),
  TowerShootTime: {
    fireTime: 1 / tower.CommonTowerStats.rof,
    startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
  },
  upgrades: {
    [if index % 3 != 2 then "next"]: index + 1
  }
};

/*

must have ONE from ALL three groups

------------+-----------------------
 damage     |  turret   splash
------------+-----------------------
 animation  |  beam     projectile
------------+-----------------------
 gun        |  aim      aura
------------+-----------------------

*/

[
  BaseTower(0, "blaster", "blaster", "blaster", {
    range: 3,
    damage: 10,
    rof: 3,
    armourPiercing: 0.1
  }) + {
    TowerGold: {
      buy: 100,
      sell: 50
    },
    AimTower: {},
    TowerTarget: {},
    TurretTower: {},
    ProjectileTower: {},
  },
  BaseTower(1, "laser", "laser", "blaster 1", {
    range: 7,
    damage: 3,
    rof: 20,
    armourPiercing: 0.1
  }) + {
    TowerGold: {
      buy: 50,
      sell: 100
    },
    TowerTarget: {},
    AimTower: {},
    TowerBeamAnim: {},
    BeamTower: {},
    TurretTower: {},
  },
  BaseTower(2, "plasma cannon", "plasma", "plasma", {
    range: 5,
    damage: 150,
    rof: 1/2,
    armourPiercing: 0.6
  }) + {
    TowerGold: {
      buy: 150,
      sell: 200
    },
    ProjectileTower: {},
    TurretTower: {},
    TowerTarget: {},
    AimTower: {},
  },
  BaseTower(3, "cannon", "cannon", "cannon", {
    range: 4,
    damage: 60,
    rof: 1/2,
    armourPiercing: 0.5
  }) + {
    TowerGold: {
      buy: 100,
      sell: 50
    },
    ProjectileTower: {},
    TowerTarget: {},
    AimTower: {},
    TurretTower: {}
  },
  BaseTower(4, "explosive cannon", "explosive cannon", "cannon", {
    range: 4,
    damage: 40,
    rof: 1/2,
    armourPiercing: 0.4
  }) + {
    SplashTower: {
      aoe: 1
    },
    TowerGold: {
      buy: 100,
      sell: 100
    },
    ProjectileTower: {},
    TowerEffect: {},
    TowerTarget: {},
    AimTower: {}
  },
  BaseTower(5, "poison cannon", "poison cannon", "cannon", {
    range: 4,
    damage: 20,
    rof: 1/4,
    armourPiercing: 0.6
  }) + {
    SplashTower: {
      aoe: 1
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.1,
        duration: 2
      }
    },
    TowerGold: {
      buy: 200,
      sell: 150
    },
    ProjectileTower: {},
    TowerTarget: {},
    AimTower: {},
  },
  BaseTower(6, "snowball shooter", "snowball", "cannon", {
    range: 4,
    damage: 5,
    rof: 1/2,
    armourPiercing: 0.4
  }) + {
    SplashTower: {
      aoe: 3
    },
    TowerEffect: {
      SlowEffect: {
        speedFactor: 0.5,
        duration: 4
      }
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    ProjectileTower: {},
    TowerTarget: {},
    AimTower: {},
  },
  BaseTower(7, "iceball shooter", "iceball", "cannon", {
    range: 4,
    damage: 5,
    rof: 1/8,
    armourPiercing: 0.4
  }) + {
    SplashTower: {
      aoe: 3
    },
    TowerEffect: {
      SlowEffect: {
        speedFactor: 0,
        duration: 2
      }
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    ProjectileTower: {},
    TowerTarget: {},
    AimTower: {},
  },
  {
    # doesn't really work with the BaseTower because of custom TowerSprites
    Name: "ICE AURA",

    local tower = self,
    CommonTowerStats: {
      range: 4,
      damage: 5,
      rof: 1/4,
      armourPiercing: 0.4
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    TowerEffect: {
      SlowEffect: {
        speedFactor: 0,
        duration: 2
      }
    },
    TowerSprites: {
      gun: {
        sprite: getSprite("ice aura base 0"),
        frames: 5
      },
      base: 0,
      projectile: getSprite("ice aura 0")
    },
    upgrades: {},
    Sound: getSound("cannon"),
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AuraTower: {}
  },
  {
    # doesn't really work with the BaseTower because of custom TowerSprites
    Name: "FLAMETHROWER",

    local tower = self,
    BeamTower: {},
    CommonTowerStats: {
      range: 2,
      damage: 10,
      rof: 20,
      armourPiercing: 0.1
    },
    TowerGold: {
      buy: 150,
      sell: 100
    },
    SplashTower: {
      aoe: 2
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.1,
        duration: 2
      }
    },
    TowerSprites: {
      local sprite = "flamethrower",
      local this = self,

      gun: {
        sprite: getSprite(sprite + " 0"),
        frames: this.base - self.sprite
      },
      base: getSprite(sprite + " base"),
      projectile: getSprite("fire 0")
    },
    upgrades: {
      next: 10
    },
    Sound: getSound("blaster 1"),
    TowerBeamAnim: {
      frames: 4,
      scaleBeam: false
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AimTower: {}
  },
  BaseTower(10, "fireball shooter", "fireball", "fire ball shooting", {
    range: 6,
    damage: 50,
    rof: 1,
    armourPiercing: 0.2
  }) + {
    SplashTower: {
      aoe: 2
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.1,
        duration: 1
      }
    },
    TowerGold: {
      buy: 150,
      sell: 100
    },
    ProjectileTower: {},
    TowerTarget: {},
    AimTower: {},
  },
  {
    # doesn't really work with the BaseTower because of custom TowerSprites
    Name: "FIRE AURA",

    local tower = self,
    CommonTowerStats: {
      range: 2,
      damage: 100,
      rof: 1/3,
      armourPiercing: 0.6
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.2,
        duration: 1
      }
    },
    TowerSprites: {
      gun: {
        sprite: getSprite("fire aura base 0"),
        frames: 5
      },
      base: 0,
      projectile: getSprite("fire aura 0")
    },
    upgrades: {},
    Sound: getSound("cannon"),
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AuraTower: {}
  },
]
