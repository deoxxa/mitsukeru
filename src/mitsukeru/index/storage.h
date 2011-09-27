#ifndef __MITSUKERU_INDEX_STORAGE_H
#define __MITSUKERU_INDEX_STORAGE_H

namespace Mitsukeru
{
  template <class Term_T, class Data_T>
  class Index_Storage
  {
  public:
    virtual void add(Term_T term, Data_T data) = 0;
    virtual std::vector< Data_T >* search(Term_T term) = 0;
  };
}

#endif
