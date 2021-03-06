// This file is part of FEPiC++, a toolbox for finite element codes.
//
// FEPiC++ is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// FEPiC++ is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// FEPiC++. If not, see <http://www.gnu.org/licenses/>.

#ifndef FEPIC_FACET_HPP
#define FEPIC_FACET_HPP

#include "cell_element.hpp"
#include "../labelable.hpp"

class Facet : public CellElement
{
public:
  Facet(int ic,
         int pos,
         int tag,
         int flags,
         int bid=-1) : CellElement(ic,pos,tag,flags), m_bound_comp_id(bid)
  {}
  
  Facet() : m_bound_comp_id(-1) {}
  
  static Facet* create()
  {
    return new Facet();
  }
  
  void setBoundaryComponentId(int id)
  {
    m_bound_comp_id=id;
  }
  int getBoundaryComponentId() const
  {
    return m_bound_comp_id;
  }
  void setAllMembers(int const* ic, int const* pos, int const* tag, int const* flags, int const* bound_comp_id)
  {
    if (ic != NULL)
      setIncidCell(*ic);
    if (pos != NULL)
      setPosition(*pos);
    if (tag != NULL)
      setTag(*tag);
    if (flags != NULL)
      setFlags(*flags);
    if (bound_comp_id != NULL)
      setBoundaryComponentId(*bound_comp_id);
  }
  
private:
  int m_bound_comp_id;
};

#endif
