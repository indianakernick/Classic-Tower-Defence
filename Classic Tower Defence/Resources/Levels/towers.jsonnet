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
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "BLASTER",
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
    },
    TowerBeamAnim: {},
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "LASER"
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
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "PLASMA CANNON"
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 6,
      damage: 60,
      rof: 1/2,
      armourPiercing: 0.5
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    TowerSprites: towerSprites("cannon"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "CANNON"
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
      aoe: 3
    },
    TowerEffect: {
      # is this necessary?
      PoisonEffect: {
        damageFactor: 0.0,
        duration: 0
      }
    },
    TowerSprites: towerSprites("explosive cannon"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "EXPLOSIVE CANNON"
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 4,
      damage: 20,
      rof: 1/4,
      armourPiercing: 0.6
    },
    TowerGold: {
      buy: 100,
      sell: 50
    },
    SplashTower: {
      aoe: 3
    },
    TowerEffect: {
      PoisonEffect: {
        damageFactor: 0.2,
        duration: 2
      }
    },
    TowerSprites: towerSprites("poison cannon"),
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "POISON CANNON"
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
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "SNOWBALL SHOOTER"
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
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "ICEBALL SHOOTER"
  },
  {
    local tower = self,
    ProjectileTower: {},
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
      gun: getSprite("ice aura base 0"),
      base: 0,
      firingFrames: 5,
      projectile: getSprite("ice aura 0")
    },
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AuraTower: {},
    Name: "ICE AURA"
  },
  {
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

      gun: getSprite(sprite + " 0"),
      base: getSprite(sprite + " base"),
      firingFrames: self.base - self.gun,
      projectile: getSprite("fire 0")
    },
    upgrades: {},
    Sound: {
      id: getSound("blaster 1")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerBeamAnim: {
      frames: 4,
      scaleBeam: false
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "FLAMETHROWER"
  },
  {
    local tower = self,
    ProjectileTower: {},
    CommonTowerStats: {
      range: 6,
      damage: 50,
      rof: 1,
      armourPiercing: 0.2
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
        duration: 1
      }
    },
    TowerSprites: towerSprites("fireball"),
    upgrades: {},
    Sound: {
      id: getSound("fire ball shooting")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "FIREBALL SHOOTER"
  },
  {
    local tower = self,
    ProjectileTower: {},
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
      gun: getSprite("fire aura base 0"),
      base: 0,
      firingFrames: 5,
      projectile: getSprite("fire aura 0")
    },
    upgrades: {},
    Sound: {
      id: getSound("cannon")
    },
    TowerFiringAnim: {
      frames: tower.TowerSprites.firingFrames
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.firingFrames / 20
    },
    TowerTarget: {},
    AuraTower: {},
    Name: "FIRE AURA"
  },
]
