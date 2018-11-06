// ProjectionMesh.h - interface for ProjectionMesh class
//
// Developed by: Mike Childs
//      Started: 2/19/98

#ifndef _PROJECTIONMESH_H_
#define _PROJECTIONMESH_H_

class Projection; // forward declaration

class ProjectionMesh
{
public:
  // Construction
  ProjectionMesh();

  // Destruction
  ~ProjectionMesh();

  // Projection function
  bool projectPoint( double& x, double& y ) const;
  /* Projects the point ( <x>, <y> ) from source mesh coordinate space to
     the target mesh coordinate space using the calculated spline 
     coefficients */

  // Modifiers
  void setSourceMeshBounds( double left, double bottom,
                            double right, double top );
  /* Set the bounding rectangle of the source mesh */

  void setMeshSize( long width, long height );
  /* Set the number of points to place in the mesh */

  void calculateMesh( const Projection& sourceProj, 
                      const Projection& destProj );
  /* Projects each source coordinate in the mesh from <sourceProj> to
     <destProj> and validates all the nodes when it's done */

  // Accessors
  double getSourceMeshLeft() const;
  double getSourceMeshRight() const;
  double getSourceMeshBottom() const;
  double getSourceMeshTop() const;
  /* Gets a bounding value from the source mesh */

  long getMeshWidth() const;
  long getMeshHeight() const;
  /* Returns either the height or width in mesh points of the mesh */

  void getSourceCoordinate( long col, long row, double& x, double& y ) const;
  /* Gets the source mesh coordinate for the grid coordinate <col>, <row> */

  bool getProjectedCoordinate( long col, long row,
                               double& x, double& y ) const;
  /* Gets the projected coordinate for the grid coordinate <col>, <row>.
     Returns <true> if the projected mesh point was valid, <false> if it
     was invalid */

  void getProjectedBoundingRect( double& left, double& bottom,
                                 double& right, double& top ) const;
  /* Iterates through every valid point in the grid and determines the
     minimum bounding rectangle of the projected coordinates */

private:    
  // MeshNode internal class
  class MeshNode
  {
  public:
    // Construction
    MeshNode();

    // Accessors
    double getX() const;
    double getY() const;
    bool   isValid() const;

    // Modifiers
    void setValid( bool bValid );
    void setXY( double x, double y );

  private:
    // Data members
    double d_x, d_y; // Projected coordinates
    bool   d_bValid;
  };

  // Helper functions
  MeshNode* getMeshNode( long col, long row ) const;

  void validateNodes();
  /* Determines the validity of each node in the mesh.  This should be
     called after setMeshPoint has been called for each point in the mesh */

  void setMeshPoint( long col, long row,
                     double projectedX, double projectedY );

  // Data members
  double    d_left, d_top;
  double    d_sourceWidth, d_sourceHeight;
  double    d_horizMeshSpacing, d_vertMeshSpacing;
  long      d_meshWidth, d_meshHeight;
  MeshNode* d_pNodes;
  Projection* d_pFromProj;
  Projection* d_pToProj;
};

inline void 
ProjectionMesh::setMeshPoint( long col, long row,
                              double projectedX, double projectedY )
{
  d_pNodes[ row * d_meshWidth + col ].setXY( projectedX, projectedY );
  d_pNodes[ row * d_meshWidth + col ].setValid( true );
}

inline double 
ProjectionMesh::getSourceMeshLeft() const
{
  return d_left;
}

inline double 
ProjectionMesh::getSourceMeshRight() const
{
  return ( d_left + d_sourceWidth );
}

inline double 
ProjectionMesh::getSourceMeshBottom() const
{
  return ( d_top - d_sourceHeight );
}

inline double 
ProjectionMesh::getSourceMeshTop() const
{
  return d_top;
}

inline long 
ProjectionMesh::getMeshWidth() const
{
  return d_meshWidth;
}

inline long 
ProjectionMesh::getMeshHeight() const
{
  return d_meshHeight;
}

inline void 
ProjectionMesh::getSourceCoordinate( long col, long row,
                                     double& x, double& y ) const
{
  x = d_left + col * d_horizMeshSpacing;
  y = d_top  - row * d_vertMeshSpacing;
}

inline bool
ProjectionMesh::getProjectedCoordinate( long col, long row,
                                        double& x, double& y ) const
{
  MeshNode node = d_pNodes[ row * d_meshWidth + col ];
  x = node.getX();
  y = node.getY();
  return node.isValid();
}

inline ProjectionMesh::MeshNode*
ProjectionMesh::getMeshNode( long col, long row ) const
{
  return &d_pNodes[ row * d_meshWidth + col ];
}

inline double 
ProjectionMesh::MeshNode::getX() const
{
  return d_x;
}

inline double 
ProjectionMesh::MeshNode::getY() const
{
  return d_y;
}

inline bool
ProjectionMesh::MeshNode::isValid() const
{
  return d_bValid;
}

inline void
ProjectionMesh::MeshNode::setValid( bool bValid )
{
  d_bValid = bValid;
}

inline void 
ProjectionMesh::MeshNode::setXY( double x, double y )
{
  d_x = x;
  d_y = y;
}

#endif