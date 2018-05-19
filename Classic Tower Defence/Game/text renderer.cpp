//
//  text renderer.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "text renderer.hpp"

void TextRenderer::centerAlign(const std::string_view text) {
  beginning = pos;
  pos.x -= (width(text) - (advance.x - size.x) * scale) / 2.0f;
}

void TextRenderer::rightAlign(const std::string_view text) {
  beginning = pos;
  pos.x -= width(text);
}

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
  pos.x += tabSize(pos.x - beginning.x);
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

float TextRenderer::tabSize(const float posx) const {
  const float scaledAdvance = scale * advance.x;
  const int chars = std::nearbyint(posx / scaledAdvance);
  return scaledAdvance * (8 - chars % 8);
}

namespace {
  inline void maxReset(float &max, float &curr) {
    if (max < curr) {
      max = curr;
    }
    curr = 0.0f;
  }
}

float TextRenderer::width(const std::string_view text) const {
  const float advanceX = advance.x * scale;
  float maxWidth = 0.0f;
  float currWidth = 0.0f;
  
  for (const char c : text) {
    switch (c) {
      case '\n':
        maxReset(maxWidth, currWidth);
        break;
      case ' ':
        currWidth += advanceX;
        break;
      case '\b':
        currWidth -= advanceX;
        break;
      case '\t': {
        currWidth += tabSize(currWidth);
        break;
      }
      case '\r':
        maxReset(maxWidth, currWidth);
        break;
      default:
        if (std::isprint(c)) {
          currWidth += advanceX;
        }
    }
  }
  
  maxReset(maxWidth, currWidth);
  
  return maxWidth;
}

float TextRenderer::height(const std::string_view text) const {
  if (text.empty()) {
    return 0.0f;
  }
  const float advanceY = advance.y * scale;
  float maxHeight = advanceY;
  
  for (const char c : text) {
    if (c == '\n' || c == '\v') {
      maxHeight += advanceY;
    }
  }
  
  return maxHeight;
}
