//#include <Fepic/DofHandler>
#include <Fepic/Mesh>
//#include <tr1/memory>

using namespace std;
//using namespace Eigen;

void printMesh(Mesh *mesh);


class IteratorTest
{
public:

  virtual ~IteratorTest() {delete mesh;}
  
  virtual void SetUp() {
    
    //Mesh *mesh;
    
    ECellType cell_t     = TRIANGLE3;
    const char* mesh_in  = "tests/meshes/iter_tri3.msh";
    
    //mesh = Mesh::create(cell_t);
    mesh = new SMesh<Triangle3,2>;

    mesh->numNodes();
    //
    mesh->qBuildAdjacency(false);
    //
    Mesh const*const mesh2 = mesh;
    Mesh *const mesh3 = mesh;
    cout << "a) mesh==mesh2 : " << (mesh==mesh2) << "; " << mesh2 << " " << mesh<< endl;
    msh_reader.readFileMsh(mesh_in, mesh3);
    cout << "b) mesh==mesh2 : " << (mesh==mesh2) << "; " << mesh2 << " " << mesh<< endl;
    //
    mesh->numNodes();

  };

  virtual void TearDown()
  {
    delete mesh;
  }

protected:
  MeshIoMsh msh_reader;
  //  //MeshIoVtk vtk_printer;
  Mesh *mesh;
  
};



int main()
{

  IteratorTest t;
  
  t.SetUp();
  
  
  
  //VarDofs vvv;
  
  //const char* mesh_name = "malha/tri1.msh";
  //Hexahedron8   hex1;
  //Hexahedron20  hex2;
  //Hexahedron27  hex3;
  //Tetrahedron4  tet1;
  //Tetrahedron10 tet2;
  //Triangle3     tri1;
  //Triangle6     tri2;
  //Quadrangle4   qua1;
  //Quadrangle8   qua2;
  //Quadrangle9   qua3;
  //Facet         f[DIM];

  

  ////std::tr1::shared_ptr<Mesh> mesh(new SMesh<Triangle3>);
  //std::tr1::shared_ptr<Mesh> mesh(Mesh::create(TRIANGLE3));
  ////Mesh * mesh = Mesh::create(TRIANGLE3,-1);
  
  //MeshIoMsh Writer;
  //MeshIoVtk vtk_printer(mesh.get());

  //Writer.readFileMsh(mesh_name, mesh.get());
  
  //mesh->printInfo();
  
  //vtk_printer.setOutputFileName(mesh_name);
  //vtk_printer.writeVtk();
  
  //printMesh(mesh.get());
  

  return 0;
}
//////sed -i '/__/d' log



//void printMesh(Mesh *mesh)
//{
  //printf("NODES \n");
  //for (int i = 0; i < mesh->numNodes(); ++i)
  //{
    //double x[2];
    //mesh->getNode(i)->getCoord(x);
    //printf("%lf %lf\n", *x, x[1]);
  //}
  //printf("\n");
  
  //printf("CELLS\n");
  //for (int i = 0; i < mesh->numCells(); ++i)
  //{
    //int nds[3];
    //mesh->getCell(i)->getNodesId(nds);
    //printf("%d %d %d\n", *nds, nds[1], nds[2]);
  //}
  //printf("\n");
  
//}

