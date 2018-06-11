local getSprite = import "getsprite.libsonnet";
local getSound = import "getsound.libsonnet";

local towerSprites(sprite) = {
  base: getSprite(sprite + " base"),
  projectile: getSprite(sprite + " projectile"),
  gun: {
    sprite: getSprite(sprite + " 0"),
    frames: $.base - self.sprite
  }
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
    upgrades: {
      next: 1
    },
    Sound: {
      id: getSound("blaster")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 2
    },
    Sound: {
      id: getSound("blaster 1")
    },
    TowerBeamAnim: {},
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 4
    },
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 5
    },
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 7
    },
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 8
    },
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "ICEBALL SHOOTER"
  },
  {
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
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    Sound: {
      id: getSound("blaster 1")
    },
    TowerBeamAnim: {
      frames: 4,
      scaleBeam: false
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
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
    upgrades: {
      next: 11
    },
    Sound: {
      id: getSound("fire ball shooting")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AimTower: {},
    Name: "FIREBALL SHOOTER"
  },
  {
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
    Sound: {
      id: getSound("cannon")
    },
    TowerShootTime: {
      fireTime: 1 / tower.CommonTowerStats.rof,
      startTime: self.fireTime - tower.TowerSprites.gun.frames / 20
    },
    TowerTarget: {},
    AuraTower: {},
    Name: "FIRE AURA"
  },
]
