#pragma once
#include "../pch.h"

#include "../shader/shader_util.h"

namespace nelems
{
  class Element
  {
  public:
    virtual void update(nshaders::Shader* shader) = 0;
  };
}

