//
//  text renderer.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 2/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef text_renderer_hpp
#define text_renderer_hpp

#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

//@SIMPLETON

class TextRenderer {
public:
  TextRenderer() = default;
  
  void setGlyphSize(glm::vec2);
  void setAdvance(glm::vec2);
  
  /// Change the position of the cursor. The x-coordinate of this position
  /// becomes the start of the line.
  void setCursor(glm::vec2);
  /// Return the cursor to the last place that it was set
  void resetCursor();
  /// Set the cursor such that the given text is center aligned about the given
  /// position
  void centerAlign(glm::vec2, std::string_view);
  /// Set the cursor such that the given text is right aligned about the given
  /// position
  void rightAlign(glm::vec2, std::string_view);
  
  /// Set the glyph scale (screen_size = glyph_scale * tex_size)
  void setScale(float);
  /// Set the depth of the quads
  void setDepth(float);
  
  /// Move the cursor down to the next line and to the start of the line
  void newline();
  /// Move the cursor right to the next character
  void space();
  /// Move the cursor left to the previous character.
  void backspace();
  /// Move the cursor to the next position that is an integer multiple of 8
  /// times the horizontal advance
  void tab();
  /// Move the cursor down to the next line without moving horizontally
  void vertTab();
  /// Move the cursor to the first character of the current line
  void carriageReturn();
  
  /// Take a whitespace character ('\n' ' ' '\b' '\t' '\v' '\r') and move the
  /// cursor appropriately. Return true if the character was handled.
  bool whitespace(char);
  
  /// Render a single character. Only renders printable characters.
  /// Whitespace characters ('\n' ' ' '\t' '\v' '\r') are handled appropriately
  template <G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_UP>
  void pushChar(
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
    writer.tileTex<PLUS_XY>(sheet.getSprite(c - '!'));
    
    space();
  }
  /// Render a string of characters. Calls pushChar for each character.
  template <G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_UP>
  void pushText(
    G2D::QuadWriter &writer,
    const Sprite::Sheet &sheet,
    const std::string_view text
  ) {
    writer.sectionSize(text.size());
    for (const char c : text) {
      pushChar<PLUS_XY>(writer, sheet, c);
    }
  }
  
private:
  // the last position that was set with a call to setCursor
  glm::vec2 beginning {0.0f};
  // the position where the next character will be drawn
  glm::vec2 pos {0.0f};
  glm::vec2 size {1.0f, 1.0f};
  glm::vec2 advance {1.0f, 1.0f};
  // a scale of one will mean that one pixel on the texture will coorespond
  // to one pixel on the monitor
  float scale = 1.0f;
  float depth = 0.0f;
  
  float tabSize(float) const;
  float width(std::string_view) const;
  float height(std::string_view) const;
};

#endif
