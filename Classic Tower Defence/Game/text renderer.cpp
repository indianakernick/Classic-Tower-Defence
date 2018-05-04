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

void TextRenderer::newline() {
  carriageReturn();
  vertTab();
}

void TextRenderer::space() {
  pos.x += advance.x * scale;
}

void TextRenderer::backspace() {
  pos.x = std::max(beginning.x, pos.x - advance.x * scale);
}

void TextRenderer::tab() {
  const float scaledAdvance = scale * advance.x;
  const int chars = std::nearbyint(pos.x / scaledAdvance);
  pos.x += scaledAdvance * (8 - chars % 8);
}

void TextRenderer::vertTab() {
  pos.y += advance.y * scale;
}

void TextRenderer::carriageReturn() {
  pos.x = beginning.x;
}

bool TextRenderer::whitespace(const char c) {
  switch (c) {
    case '\n':
      newline();
      return true;
    case ' ':
      space();
      return true;
    case '\b':
      backspace();
      return true;
    case '\t':
      tab();
      return true;
    case '\v':
      vertTab();
      return true;
    case '\r':
      carriageReturn();
      return true;
  }
  return false;
}

void TextRenderer::pushChar(
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet,
  const char c
) {
  if (whitespace(c) || !std::isprint(c)) {
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
  
  space();
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
