#include <string>
#include <vector>
#include <cstring> // for size_t

#ifndef __MITSUKERU_TOKENISER_H
#define __MITSUKERU_TOKENISER_H

namespace Mitsukeru
{
  class Tokeniser
  {
  public:
    std::vector< std::string >* tokenise(std::string data);
  };
}

#endif
