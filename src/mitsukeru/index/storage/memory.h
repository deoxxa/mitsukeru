#include <string>
#include <map>
#include <vector>

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
    void add(Term_T term, Data_T data)
    {
      terms[term].push_back(data);
    }

    std::vector< Data_T >* search(Term_T term)
    {
      std::vector< Data_T >* result = new std::vector< Data_T >;

      if (terms.find(term) != terms.end()) {
        for (typename std::vector< Data_T >::iterator it=terms[term].begin();it!=terms[term].end();++it) {
          result->push_back(*it);
        }
      }

      return result;
    }
  };
}

#endif
