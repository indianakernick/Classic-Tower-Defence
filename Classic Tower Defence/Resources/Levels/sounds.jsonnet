local soundNames = [
  "blaster", "blaster 1", "cannon", "robot destroyed", "plasma", "fire ball shooting"
];

{
  names: {
    [soundNames[index]]: index
    for index in std.makeArray(std.length(soundNames), function(x)x)
  },
  files: [
    name + ".wav" for name in soundNames
  ]
}
