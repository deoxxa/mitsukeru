#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#ifndef __MITSUKERU_INDEX_H
#define __MITSUKERU_INDEX_H

namespace Mitsukeru
{
  struct Index
  {
  protected:
    std::map< std::string, std::vector< uint32_t > > terms;
  public:
    void add(uint32_t, std::string);
    std::vector< uint32_t >* search(std::vector< std::string >);
  };
}

#endif
