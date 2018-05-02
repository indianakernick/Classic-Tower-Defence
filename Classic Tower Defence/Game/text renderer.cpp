//
//  text renderer.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "text renderer.hpp"

void TextRenderer::setGlyphSize(const glm::vec2 newSize) {
  size = newSize;
}

void TextRenderer::setAdvance(const glm::vec2 newAdvance) {
  advance = newAdvance;
}

void TextRenderer::setCursor(const glm::vec2 newPos) {
  beginning = newPos;
  pos = newPos;
}

void TextRenderer::resetCursor() {
  pos = beginning;
}

void TextRenderer::setScale(const float newScale) {
  scale = newScale;
}

void TextRenderer::setDepth(const float newDepth) {
  depth = newDepth;
}

void TextRenderer::startLine() {
  firstChar();
  nextLine();
}

void TextRenderer::nextLine() {
  pos.y += advance.y * scale;
}

void TextRenderer::nextChar() {
  pos.x += advance.x * scale;
}

void TextRenderer::firstChar() {
  pos.x = beginning.x;
}

void TextRenderer::pushChar(
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet,
  const char c
) {
  if (c == ' ') {
    return nextChar();
  }
  if (c == '\n') {
    return startLine();
  }
  if (!std::isprint(c)) {
    return;
  }
  
  writer.quad();
  writer.depth(depth);
  writer.tilePos(pos, scale * size);
  // the spritesheet is expected to hold all of the printable ascii characters.
  // std::isprint considers space a printable character but there's no point
  // in storing a blank space in a sprite sheet. So sheet.getSprite(0) should
  // return the rectangle for '!' (the character after space)
  writer.tileTex(sheet.getSprite(c - '!'));
  
  nextChar();
}

void TextRenderer::pushText(
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet,
  const std::string_view text
) {
  writer.sectionSize(text.size());
  for (const char c : text) {
    pushChar(writer, sheet, c);
  }
}
