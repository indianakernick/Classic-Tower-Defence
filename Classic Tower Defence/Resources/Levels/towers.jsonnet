local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

local towerSprites(sprite) = {
  gun: getSprite(sprite + " 0"),
  base: getSprite(sprite + " base"),
  firingFrames: $.base - $.gun,
  projectile: getSprite(sprite + " projectile")
};

[
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 6,
      damage: 10,
      rof: 3,
      armourPiercing: 0.1
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    TurretTower: {},
    TowerSprites: towerSprites("blaster"),
    upgrades: {},
    Sound: {
      id: getSound("blaster")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  },
  {
    local tower = self,
    BeamTower: {},
    TurretTower: {},
    CommonTowerStats: {
      range: 10,
      damage: 5,
      rof: 20,
      armourPiercing: 0.2
    },
    TowerGold: {
      buy: 150,
      sell: 100
    },
    TowerSprites: towerSprites("laser"),
    upgrades: {},
    Sound: {
      id: getSound("blaster 1")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 6,
      damage: 50,
      rof: 1/3,
      armourPiercing: 0.6
    },
    TowerGold: {
      buy: 150,
      sell: 100
    },
    TurretTower: {},
    TowerSprites: towerSprites("plasma"),
    upgrades: {},
    Sound: {
      id: getSound("plasma")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 4,
      damage: 50,
      rof: 1/2,
      armourPiercing: 0.6
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    SplashTower: {
      aoe: 10
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.0,
        duration: 5
      }
    },
    TowerSprites: towerSprites("explosive cannon"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 4,
      damage: 5,
      rof: 1/2,
      armourPiercing: 0.4
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    SplashTower: {
      aoe: 3
    },
    TowerEffect: {
      SlowEffect: {
        speedFactor: 0.5,
        duration: 4
      }
    },
    TowerSprites: towerSprites("snowball"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 4,
      damage: 5,
      rof: 1/8,
      armourPiercing: 0.4
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    SplashTower: {
      aoe: 3
    },
    TowerEffect: {
      SlowEffect: {
        speedFactor: 0,
        duration: 2
      }
    },
    TowerSprites: towerSprites("iceball"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    }
  }
]
