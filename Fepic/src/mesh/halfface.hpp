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

#ifndef FEPIC_HALFFACE_HPP
#define FEPIC_HALFFACE_HPP



template<class Traits>
class HalfFace : public _HalfCore<HalfFace<Traits>>
{
public:
  typedef typename Traits::MeshT MeshT;
  typedef typename Traits::CellT CellT;

  enum {cell_id_limit=134217727};
  enum {position_limit=6};
  enum {anchor_limit=3};
  
  friend class _HalfCore<HalfEdge<Traits>>;

  HalfFace(uint incid_cell, int position, int anchor) : _incid_cell(incid_cell), _position(position), _anchor(anchor)
  {
  
  }
  
  /** Construtor.
  */ 
  HalfFace() : _incid_cell(0), _position(0), _anchor(0)
  {
  }
  
  /** Imprime em um stream a composição do iD, i.e, imprime \n
  *  getIncidCell() << " " << getPosition() << " " << getAnchor()
  *  @param o o stream onde se vai escrever.
  */ 
  void printSelf(std::ostream& o) const
  {
    o << this->getIncidCell() << " " << this->getPosition() << " " << this->getAnchor();
  }
  
  /** @return uma string com o nome Half-Face.
  */ 
  static std::string getName()
  {
    return std::string("Half-Face");
  }
  
  /** Destrutor.
  */ 
  ~HalfFace() {}
protected:
  uint _incid_cell : 27;
  uint _position   : 3;
  uint _anchor     : 2;
};      







#endif