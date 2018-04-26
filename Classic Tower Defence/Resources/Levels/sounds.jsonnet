local soundNames = [
  "blaster", "cannon", "robot destroyed"
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
