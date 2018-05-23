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
public:
  
  // a pointer to these is stored internally so watch your lifetimes!
  void writer(G2D::QuadWriter &);
  void sheet(const Sprite::Sheet &);
  void glyphSize(glm::vec2);
  void advance(glm::vec2);
  void scale(float);
  void depth(float);
  
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN>
  glm::vec2 write(glm::vec2, std::string_view);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN>
  glm::vec2 write(glm::vec2, const std::string &);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN, size_t SIZE>
  glm::vec2 write(glm::vec2, const char (&)[SIZE]);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN>
  glm::vec2 write(glm::vec2, char);
  template <Align ALIGN = Align::LEFT, G2D::PlusXY PLUS_XY = G2D::PlusXY::RIGHT_DOWN, typename T>
  glm::vec2 write(glm::vec2, const T &);
  
private:
  G2D::QuadWriter *writer_ = nullptr;
  const Sprite::Sheet *sheet_ = nullptr;
  glm::vec2 glyphSize_;
  glm::vec2 advance_;
  float scale_;
  float depth_;

  template <G2D::PlusXY PLUS_XY>
  glm::vec2 writeLeft(glm::vec2, std::string_view);
};

#include "text renderer.inl"

#endif
