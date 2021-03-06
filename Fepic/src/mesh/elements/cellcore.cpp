#include "cellcore.hpp"
#include "elements.hpp"
#include "../../util/misc2.hpp"
#include <tr1/array>

#if !defined(THIS) && !defined(CONST_THIS)
  #define THIS static_cast<CellT*>(this)
  #define CONST_THIS static_cast<const CellT*>(this)
#endif

Cell::~Cell() {} //definition of a pure virtual destructor; should always be empty

/** Get nodes of a corner
 * @param[in] f the corner local id.
 * @param[out] corner_nds where to put the nodes.
 * @note the vector corner_nds must have enough space allocated (num nodes per corner).
 */
template<typename CellT>
void iCellCore<CellT>::getCornerNodesId(int f, int *corner_nds) const
{
  FEPIC_CHECK(f < CellT::n_corners, "invalid index", std::out_of_range);

  if (CellT::dim==3)
    for (int i = 0; i < CellT::n_nodes_per_corner; ++i)
    {
      *corner_nds++ = CONST_THIS->m_nodes[CellT::m_table_bC_x_nC[f][i]];
    }
  else
    *corner_nds = CONST_THIS->m_nodes[f];
}

/** Get vertices of a corner
  * @param[in] f the corner local id.
  * @param[out] vtcs where to put the vertices.
  * @note the vector vtcs must have enough space allocated (num vertices per corner).
  */
template<typename CellT>
void iCellCore<CellT>::getCornerVerticesId(int f, int *corner_vtcs) const
{
  FEPIC_CHECK(f < CellT::n_corners, "invalid index", std::out_of_range);

  if (CellT::dim==3)
    for (int i = 0; i < CellT::n_vertices_per_corner; ++i)
    {
      *corner_vtcs++ = CONST_THIS->m_nodes[CellT::m_table_bC_x_vC[f][i]];
    }
  else
    *corner_vtcs = CONST_THIS->m_nodes[f];

}

/** Get nodes of a facet
  * @param[in] f the facet local id.
  * @param[out] facet_nds where to put the nodes.
  * @note the vector facet_nds must have enough space allocated (num nodes per facet).
  */
template<typename CellT>
void iCellCore<CellT>::getFacetNodesId(int f, int * facet_nds) const
{
  FEPIC_CHECK(f < CellT::n_facets, "invalid index", std::out_of_range);

  for (int i = 0; i < CellT::n_nodes_per_facet; ++i)
  {
    *facet_nds++ = CONST_THIS->m_nodes[CellT::m_table_fC_x_nC[f][i]];
  }

}

/** Get vertices of a facet
  * @param[in] f the facet local id.
  * @param[out] vtcs where to put the vertices.
  * @note the vector vtcs must have enough space allocated (num vertices per facet).
  */
template<typename CellT>
void iCellCore<CellT>::getFacetVerticesId(int f, int * facet_vtcs) const
{
  FEPIC_CHECK(f < CellT::n_facets, "invalid index", std::out_of_range);

  for (int i = 0; i < CellT::n_vertices_per_facet; ++i)
  {
    *facet_vtcs++ = CONST_THIS->m_nodes[CellT::m_table_fC_x_vC[f][i]];
  }

}

template<typename CellT>
void iCellCore<CellT>::getFacetCornersId(int f, int * corns) const
{
  FEPIC_CHECK(f < CellT::n_facets, "invalid index", std::out_of_range);

  // TODO: implement for CellT::dim==2 version

  if (CellT::dim ==3)
    // note: n_corners_per_facet = CellT::n_vertices_per_facet
    for (int i = 0; i < CellT::n_vertices_per_facet; ++i)
    {
      *corns++ = CONST_THIS->m_corners[ CellT::m_table_fC_x_bC[f][i] ];
    }
  else
    getFacetVerticesId(f, corns);
}

template<typename CellT>
bool iCellCore<CellT>::isCorner(int const* vtcs, int &f) const
{
  int corner_vtcs[CellT::n_vertices_per_corner + (CellT::dim==1)];

  if (CellT::dim==3)
  {
    for (f = 0; f < CellT::n_corners; ++f)
    {
      this->getCornerVerticesId(f, corner_vtcs);
      if (  (corner_vtcs[0]==vtcs[0]) && (corner_vtcs[1]==vtcs[1])  )
        return true;
      if (  (corner_vtcs[0]==vtcs[1]) && (corner_vtcs[1]==vtcs[0])  )
      {
        f = -f;
        return true;
      }
    }
  }
  else if(CellT::dim==2)
  {
    for (f = 0; f < CellT::n_corners; ++f)
    {
      this->getCornerVerticesId(f, corner_vtcs);
      if (corner_vtcs[0]==vtcs[0])
        return true;
    }
  }

  return false;
}


template<typename CellT>
bool iCellCore<CellT>::isFacet(int const* vtcs, int *ff, int *anchor) const
{
  int  facet_vtcs[CellT::n_vertices_per_facet];
  int* facet_vtcs_end = facet_vtcs + CellT::n_vertices_per_facet;
  int  f, a;

  for (f = 0; f < CellT::n_facets; ++f)
  {
    this->getFacetVerticesId(f, facet_vtcs);
    a = 0;
    
    for (int i = 0; i < CellT::n_vertices_per_facet; ++i)
    {
      if (std::equal(facet_vtcs, facet_vtcs_end, vtcs) )
      {
        if (anchor)
          *anchor = a;
        if (ff)
          *ff = f;
        return true;
      }
      else
      {
        std::rotate(facet_vtcs, facet_vtcs+1, facet_vtcs_end);
        ++a;
      }
    }

    std::reverse(facet_vtcs, facet_vtcs_end);
    a = 0;
  
    for (int i = 0; i < CellT::n_vertices_per_facet; ++i)
    {
      if (std::equal(facet_vtcs, facet_vtcs_end, vtcs) )
      {
        if (anchor)
          *anchor = a;
        if (ff)
          *ff = -f;
        return true;
      }
      else
      {
        std::rotate(facet_vtcs, facet_vtcs+1, facet_vtcs_end);
        ++a;
      }
    }    

  } // end facets
  
  return false;
}

/** @brief returns that if the cell has one or more facets in the boundary.
 */
template<typename CellT>
bool iCellCore<CellT>::inBoundary() const
{
  for (int i = 0; i < CellT::n_facets; ++i)
  {
    if (CONST_THIS->m_icells[i]<0)
      return true;
  }
  return false;
}


#undef THIS
#undef CONST_THIS



#define FEPIC_INSTANTIATE_MEMBERS_FUN(CellT)                            \
                                                                        \
template  void iCellCore<CellT>::getCornerNodesId(int, int *) const;    \
template  void iCellCore<CellT>::getCornerVerticesId(int, int *) const; \
template  void iCellCore<CellT>::getFacetNodesId(int, int *) const;     \
template  void iCellCore<CellT>::getFacetVerticesId(int, int *) const;  \
template  int  iCellCore<CellT>::isCorner(int const*) const;            \
template  int  iCellCore<CellT>::isFacet(int const*) const;             \
template  bool iCellCore<CellT>::inBoundary() const;

//FEPIC_INSTANTIATE_MEMBERS_FUN(Edge2)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Edge3)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Triangle3)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Triangle6)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Quadrangle4)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Quadrangle8)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Quadrangle9)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Tetrahedron4)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Tetrahedron10)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Hexahedron8)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Hexahedron20)
//FEPIC_INSTANTIATE_MEMBERS_FUN(Hexahedron27)

#undef FEPIC_INSTANTIATE_MEMBERS_FUN

namespace fi_CellStaticTablesInitializers
{
  typedef Cell::CreatorMemFunPtr MemFunPtr;

  std::tr1::array<MemFunPtr, N_CELL_TYPES> creators_tab()
  {
    std::tr1::array<MemFunPtr, N_CELL_TYPES> tab;

    tab[log2_i32(EDGE2        ) ] = &Cell::create<Edge2>;
    tab[log2_i32(EDGE3        ) ] = &Cell::create<Edge3>;
    tab[log2_i32(TRIANGLE3    ) ] = &Cell::create<Triangle3>;
    tab[log2_i32(TRIANGLE6    ) ] = &Cell::create<Triangle6>;
    tab[log2_i32(QUADRANGLE4  ) ] = &Cell::create<Quadrangle4>;
    tab[log2_i32(QUADRANGLE8  ) ] = &Cell::create<Quadrangle8>;
    tab[log2_i32(QUADRANGLE9  ) ] = &Cell::create<Quadrangle9>;
    tab[log2_i32(TETRAHEDRON4 ) ] = &Cell::create<Tetrahedron4>;
    tab[log2_i32(TETRAHEDRON10) ] = &Cell::create<Tetrahedron10>;
    tab[log2_i32(HEXAHEDRON8  ) ] = &Cell::create<Hexahedron8>;
    tab[log2_i32(HEXAHEDRON20 ) ] = &Cell::create<Hexahedron20>;
    tab[log2_i32(HEXAHEDRON27 ) ] = &Cell::create<Hexahedron27>;

    return tab;
  }

}

Cell* Cell::create(ECellType type)
{
  static const
  std::tr1::array<CreatorMemFunPtr, N_CELL_TYPES> creators = fi_CellStaticTablesInitializers::creators_tab();

  unsigned idx = log2_i32(type);
  if (idx >= N_CELL_TYPES)
  {
    FEPIC_CHECK(false, "invalid or not supported cell type", std::invalid_argument);
    return NULL;
  }
  else
    return (*(creators[idx]))();
  //{
  //  switch (type)
  //  {
  //    case EDGE2        : return new Edge2;
  //    case EDGE3        : return new Edge3;
  //    case TRIANGLE3    : return new Triangle3;
  //    case TRIANGLE6    : return new Triangle6;
  //    case QUADRANGLE4  : return new Quadrangle4;
  //    case QUADRANGLE8  : return new Quadrangle8;
  //    case QUADRANGLE9  : return new Quadrangle9;
  //    case TETRAHEDRON4 : return new Tetrahedron4;
  //    case TETRAHEDRON10: return new Tetrahedron10;
  //    case HEXAHEDRON8  : return new Hexahedron8;
  //    case HEXAHEDRON20 : return new Hexahedron20;
  //    case HEXAHEDRON27 : return new Hexahedron27;
  //    default : return NULL;
  //  }
  //  
  //}

}





