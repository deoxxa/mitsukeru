#include <vector>

#include <mitsukeru/index/storage.h>

#ifndef __MITSUKERU_INDEX_H
#define __MITSUKERU_INDEX_H

namespace Mitsukeru
{
  template < class Term_T, class Data_T >
  class Index
  {
  protected:
    Mitsukeru::Index_Storage< Term_T, Data_T >* storage;
  public:
    Index(Mitsukeru::Index_Storage< Term_T, Data_T>* _storage) : storage(_storage) {}
    ~Index() { delete storage; }

    void add(Term_T term, Data_T data)
    {
      storage->add(term, data);
    }

    std::vector< Data_T >* search(Term_T term)
    {
      return storage->search(term);
    }
  };
}

#endif
