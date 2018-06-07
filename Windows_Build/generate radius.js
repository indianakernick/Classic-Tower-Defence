for (let i = 0; i != 32; ++i) {
    const r = i + 1;
    const size = 32*(0.5 + r);
    const halfsize = size / 2 - 1;
    let key = new Keyframe(size, size);
    key.clear();
    key.circle([halfsize, halfsize], halfsize, [255, 255, 255, 255], [255, 255, 255, 63], false);
  
    canvas.file.layerNames[i] = "Radius " + r;
    canvas.file.layerSizes[i] = [size, size];
    canvas.file.layers[i] = [key];
}
