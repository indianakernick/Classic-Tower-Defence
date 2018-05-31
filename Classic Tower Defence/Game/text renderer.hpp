//
//  text renderer.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef text_renderer_hpp
#define text_renderer_hpp

#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

//@SIMPLETON

enum class Align {
  LEFT,
  CENTER,
  RIGHT
};

class TextRenderer {
  
  template <typename T, typename Ret>
  using EnableNotStr = std::enable_if_t<
    !std::is_convertible_v<T, std::string_view>,
    Ret
  >;

public:
  
  // a pointer to these is stored internally so watch your lifetimes!
  void writer(G2D::QuadWriter &);
  void sheet(const Sprite::Sheet &);
  void glyphSize(glm::vec2);
  void advance(glm::vec2);
  void scale(float);
  void depth(float);
  
  G2D::QuadWriter &writer() const;
  const Sprite::Sheet &sheet() const;
  
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN>
  glm::vec2 write(glm::vec2, std::string_view);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN>
  glm::vec2 write(glm::vec2, char);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN, typename T>
  EnableNotStr<T, glm::vec2> write(glm::vec2, const T &);
  
private:
  G2D::QuadWriter *writer_ = nullptr;
  const Sprite::Sheet *sheet_ = nullptr;
  glm::vec2 glyphSize_;
  glm::vec2 advance_;
  float scale_;
  float depth_;

  template <G2D::PlusXY PLUS_XY>
  glm::vec2 writeLeft(glm::vec2, std::string_view);
  template <G2D::PlusXY PLUS_XY>
  void writeChar(glm::vec2, glm::vec2, char);
};

#include "text renderer.inl"

#endif
