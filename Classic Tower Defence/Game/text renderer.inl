//
//  text renderer.inl
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <sstream>

inline void TextRenderer::section(G2D::Section &section) {
  section_ = &section;
}

inline G2D::Section &TextRenderer::section() const {
  return *section_;
}

inline void TextRenderer::glyphSize(const glm::vec2 newSize) {
  glyphSize_ = newSize;
}

inline void TextRenderer::advance(const glm::vec2 newAdvance) {
  advance_ = newAdvance;
}

inline void TextRenderer::scale(const float newScale) {
  scale_ = newScale;
}

inline void TextRenderer::depth(const float newDepth) {
  depth_ = newDepth;
}

namespace detail {
  /// Advances the position by the character. Returns true if a new section
  /// should be started (only useful when ALIGN != Align::LEFT)
  inline bool advanceChar(glm::vec2 &pos, const glm::vec2 advance, const char c) {
    switch (c) {
      case '\n':
        pos.x = 0.0f;
        pos.y += advance.y;
        return true;
      case ' ':
        pos.x += advance.x;
        break;
      case '\b':
        pos.x -= advance.x;
        break;
      case '\t': {
        const int chars = std::nearbyint(pos.x / advance.x);
        pos.x += advance.x * (8 - chars % 8);
        break;
      }
      case '\v':
        pos.y += advance.y;
        break;
      case '\r':
        pos.x = 0.0f;
        return true;
      default:
        if (' ' <= c && c <= '~') {
          pos.x += advance.x;
        }
    }
    return false;
  }

  template <Align ALIGN>
  constexpr float getAlign() {
    if constexpr (ALIGN == Align::LEFT) {
      return 0.0f;
    } else if constexpr (ALIGN == Align::CENTER) {
      return 0.5f;
    } else if constexpr (ALIGN == Align::RIGHT) {
      return 1.0f;
    }
  }
}

template <Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::write(const glm::vec2 origin, const std::string_view str) {
  if constexpr (ALIGN == Align::LEFT) {
    return writeLeft<PLUS_XY>(origin, str);
  }
  
  glm::vec2 beginPos = {0.0f, 0.0f};
  glm::vec2 endPos = beginPos;
  glm::vec2 alignedOrigin;
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 scaledAdv = scale_ * advance_;
  const char *const endChar = str.data() + str.size();
  const char *rowBegin = str.data();
  const char *rowEnd = rowBegin;

  for ( ; rowEnd != str.data() + str.size() + 1; ++rowEnd) {
    const float width = endPos.x;    
    if (rowEnd != endChar && !detail::advanceChar(endPos, scaledAdv, *rowEnd)) {
      continue;
    }
      
    alignedOrigin = {
      origin.x - (width - scaledAdv.x + scaledSize.x) * detail::getAlign<ALIGN>(),
      origin.y
    };

    for (; rowBegin != rowEnd; ++rowBegin) {
      const char c = *rowBegin;
      writeChar<PLUS_XY>(alignedOrigin + beginPos, scaledSize, c);
      detail::advanceChar(beginPos, scaledAdv, c);
    }
    ++rowBegin;
    beginPos = endPos;
  }
  
  return alignedOrigin + endPos;
}

template <Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::write(const glm::vec2 origin, const char c) {
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 alignedOrigin = {
    origin.x - scaledSize.x * detail::getAlign<ALIGN>(),
    origin.y
  };
  writeChar<PLUS_XY>(alignedOrigin, scaledSize, c);
  glm::vec2 pos = {0.0f, 0.0f};
  detail::advanceChar(pos, scale_ * advance_, c);
  return alignedOrigin + pos;
}

template <Align ALIGN, G2D::PlusXY PLUS_XY, typename T>
TextRenderer::EnableNotStr<T, glm::vec2> TextRenderer::write(
  const glm::vec2 origin,
  const T &thing
) {
  // @TODO maybe a custom stream_buf?
  std::stringstream stream;
  stream << thing;
  if (stream.good()) {
    return write<ALIGN, PLUS_XY>(origin, stream.str());
  } else {
    return origin;
  }
}

template <G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::writeLeft(const glm::vec2 origin, const std::string_view str) {
  glm::vec2 pos = {0.0f, 0.0f};
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 scaleAdv = scale_ * advance_;
  
  for (const char c : str) {
    writeChar<PLUS_XY>(origin + pos, scaledSize, c);
    detail::advanceChar(pos, scaleAdv, c);
  }

  return origin + pos;
}

template <G2D::PlusXY PLUS_XY>
void TextRenderer::writeChar(const glm::vec2 pos, const glm::vec2 size, const char c) {
  if ('!' <= c && c <= '~') {
    section_->quad();
    section_->depth(depth_);
    section_->tilePos(pos, size);
    section_->tileTex<PLUS_XY>(Sprite::ID(c - '!'));
  }
}
