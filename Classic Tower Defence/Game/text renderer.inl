//
//  text renderer.inl
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include <sstream>

inline void TextRenderer::writer(G2D::QuadWriter &newWriter) {
  writer_ = &newWriter;
}

inline void TextRenderer::sheet(const Sprite::Sheet &newSheet) {
  sheet_ = &newSheet;
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
  /// Advances the position by the character. Returns true if the given character
  /// is printable
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
        if (std::isprint(c)) {
          pos.x += advance.x;
        }
    }
    return false;
  }

  template <Align ALIGN>
  constexpr float getAlign() {
    if constexpr (ALIGN == Align::CENTER) {
      return 0.5f;
    } else if constexpr (ALIGN == Align::RIGHT) {
      return 1.0f;
    } else {
      assert(false);
    }
  }
}

template <Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::write(const glm::vec2 originPos, const std::string_view str) {
  if constexpr (ALIGN == Align::LEFT) {
    return writeLeft<PLUS_XY>(originPos, str);
  }
  
  glm::vec2 beginPos = {0.0f, 0.0f};
  glm::vec2 endPos = beginPos;
  glm::vec2 alignedStartPos;
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
      
    alignedStartPos = {
      originPos.x - (width - scaledAdv.x + scaledSize.x) * detail::getAlign<ALIGN>(),
      originPos.y
    };

    for (; rowBegin != rowEnd; ++rowBegin) {
      const char c = *rowBegin;
      
      if (std::isprint(c) && c != ' ') {
        writer_->quad();
        writer_->depth(depth_);
        writer_->tilePos(alignedStartPos + beginPos, scaledSize);
        writer_->tileTex<PLUS_XY>(sheet_->getSprite(c - '!'));
      }
      
      detail::advanceChar(beginPos, scaledAdv, c);
    }
    ++rowBegin;
    beginPos = endPos;
  }
  
  return alignedStartPos + endPos;
}

template <Align ALIGN, G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::write(const glm::vec2 originPos, const std::string &str) {
  return write<ALIGN, PLUS_XY>(originPos, std::string_view(str));
}

template <Align ALIGN, G2D::PlusXY PLUS_XY, size_t SIZE>
glm::vec2 TextRenderer::write(const glm::vec2 originPos, const char (&str)[SIZE]) {
  return write<ALIGN, PLUS_XY>(originPos, std::string_view(str, SIZE));
}

template <Align ALIGN, G2D::PlusXY PLUS_XY, typename T>
glm::vec2 TextRenderer::write(
  const glm::vec2 pos,
  const T &thing
) {
  // @TODO maybe a custom stream_buf?
  std::stringstream stream;
  stream << thing;
  if (stream.good()) {
    return write<ALIGN, PLUS_XY>(pos, stream.str());
  } else {
    return pos;
  }
}

template <G2D::PlusXY PLUS_XY>
glm::vec2 TextRenderer::writeLeft(const glm::vec2 originPos, const std::string_view str) {
  glm::vec2 pos = {0.0f, 0.0f};
  const glm::vec2 scaledSize = scale_ * glyphSize_;
  const glm::vec2 scaleAdv = scale_ * advance_;
  
  for (const char c : str) {
    if (std::isprint(c) && c != ' ') {
      writer_->quad();
      writer_->depth(depth_);
      writer_->tilePos(originPos + pos, scaledSize);
      writer_->tileTex<PLUS_XY>(sheet_->getSprite(c - '!'));
    }

    detail::advanceChar(pos, scaleAdv, c);
  }

  return originPos + pos;
}
