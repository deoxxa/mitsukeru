#include <vector>

#include <mitsukeru/index.h>

template < class Term_T, class Data_T >
void Mitsukeru::Index< Term_T, Data_T >::add(Term_T term, Data_T data)
{
  storage.add(term, data);
}

template < class Term_T, class Data_T >
std::vector< Data_T >* Mitsukeru::Index< Term_T, Data_T >::search(Term_T term)
{
  return storage.search(term);
}
