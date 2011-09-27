#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include <mitsukeru/index.h>

void Mitsukeru::Index::add(uint32_t id, const std::string term)
{
  terms[term].push_back(id);
}

std::vector< uint32_t >* Mitsukeru::Index::search(std::vector< std::string > _terms)
{
  std::vector< uint32_t >* result = new std::vector< uint32_t >;

  for (std::vector< std::string >::iterator it_a=_terms.begin();it_a!=_terms.end();++it_a) {
    if (terms.find(*it_a) != terms.end()) {
      for (std::vector< uint32_t >::iterator it_b=terms[*it_a].begin();it_b!=terms[*it_a].end();++it_b) {
        result->push_back(*it_b);
      }
    }
  }

  return result;
}
