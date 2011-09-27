#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include <mitsukeru/index/storage.h>

#ifndef __MITSUKERU_INDEX_STORAGE_MEMORY_H
#define __MITSUKERU_INDEX_STORAGE_MEMORY_H

namespace Mitsukeru
{
  template <class Term_T, class Data_T>
  struct Index_Storage_Memory : public Mitsukeru::Index_Storage< Term_T, Data_T >
  {
  protected:
    std::map< Term_T, std::vector< Data_T > > terms;
  public:
    void add(Term_T term, Data_T data);
    std::vector< Data_T >* search(Term_T term);
  };
}

#endif
