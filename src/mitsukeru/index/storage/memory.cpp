#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include <mitsukeru/index/storage/memory.h>

template < class Term_T, class Data_T >
void Mitsukeru::Index_Storage_Memory< Term_T, Data_T >::add(Term_T term, Data_T data)
{
  terms[term].push_back(data);
}

template < class Term_T, class Data_T >
std::vector< Data_T >* Mitsukeru::Index_Storage_Memory< Term_T, Data_T >::search(Term_T term)
{
  std::vector< Data_T >* result = new std::vector< Data_T >;

/*
  if (terms.find(term) != terms.end()) {
    for (std::vector< Data_T >::iterator it=terms[term].begin();it!=terms[term].end();++it) {
      result->push_back(*it);
    }
  }
*/

  return result;
}
