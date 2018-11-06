// SplineMesh2D.cpp - implementation of SplineMesh2D class
//
// Developed by: Mike Childs
//      Started: 2/19/98

#include "SplineMesh2D.h"
#include "ProjectionLib/Projection.h"
#include <math.h>

// Constructor
SplineMesh2D::SplineMesh2D()
: d_top(0.0), d_left(0.0), 
  d_sourceWidth(0.0), d_sourceHeight(0.0),
  d_horizMeshSpacing(0.0), d_vertMeshSpacing(0.0),
  d_meshWidth(0), d_meshHeight(0), d_pNodes(0)
{
}

// Destructor
SplineMesh2D::~SplineMesh2D()
{
    delete[] d_pNodes;
}

// MeshNode Constructor
SplineMesh2D::MeshNode::MeshNode()
: d_x(0.0), d_y(0.0), d_bValid(false)
{
}

void 
SplineMesh2D::setSourceMeshBounds( double left, double bottom, double right, double top )
{
    d_left = left;
    d_top = top;
    d_sourceWidth = right - left;
    d_sourceHeight = top - bottom;

    // Compute the horizontal mesh spacing
    if ( 0.0 != d_meshWidth )
    {
        d_horizMeshSpacing = d_sourceWidth / ( d_meshWidth - 1 );
    }

    // Computer the vertical mesh spacing
    if ( 0.0 != d_meshHeight )
    {
        d_vertMeshSpacing = d_sourceHeight / ( d_meshHeight - 1 );
    }
}

void 
SplineMesh2D::setMeshSize( long width, long height )
{
    d_meshWidth = width;
    d_meshHeight = height;

    // Make sure the mesh sizes are at least 3
    if ( d_meshWidth < 3 )
    {
        d_meshWidth = 3;
    }

    if ( d_meshHeight < 3 )
    {
        d_meshHeight = 3;
    }

    // Allocate the mesh
    delete d_pNodes;
    d_pNodes = new MeshNode[width * height];

    // Compute the horizontal mesh spacing
    if ( 0.0 != d_meshWidth )
    {
        d_horizMeshSpacing = d_sourceWidth / ( d_meshWidth - 1 );
    }

    // Computer the vertical mesh spacing
    if ( 0.0 != d_meshHeight )
    {
        d_vertMeshSpacing = d_sourceHeight / ( d_meshHeight - 1 );
    }
}

// Projection function
bool
SplineMesh2D::projectPoint( double& x, double& y ) const
{
    // Determine which mesh grid the point is in
    float col = ( x - d_left ) / d_horizMeshSpacing;
    float row = ( d_top - y  ) / d_vertMeshSpacing;

    // Determine which mesh nodes to get
    long leftCol   = static_cast<long>( col );
    long rightCol  = leftCol + 1;
    long topRow    = static_cast<long>( row );
    long bottomRow = topRow + 1;

    // Make sure the point is in the mesh
    if ( leftCol < 0 || rightCol  > d_meshWidth ||
         topRow  < 0 || bottomRow > d_meshHeight )
    {
        return false;
    }

    // Make sure we didn't go off the edge with nodes
    if ( rightCol == d_meshWidth )
    {
        rightCol = leftCol;
    }

    if ( bottomRow == d_meshHeight )
    {
        bottomRow = topRow;
    }
 
    // Get the needed mesh nodes
    MeshNode* pULNode = getMeshNode( leftCol, topRow );
    MeshNode* pURNode = getMeshNode( rightCol, topRow );
    MeshNode* pLLNode = getMeshNode( leftCol, bottomRow );
    MeshNode* pLRNode = getMeshNode( rightCol, bottomRow );

    // Fail if any of the surrounding nodes are invalid
    if ( !pULNode->isValid() || !pURNode->isValid() ||
         !pLLNode->isValid() || !pLRNode->isValid() )
    {
        return false;
    }

    // Calculate the source coordinates of the node at <col>, <row>
    double sourceX = d_left + leftCol * d_horizMeshSpacing;
    double sourceY = d_top  - topRow  * d_vertMeshSpacing;

    // Calculate the parametric u and v
    double u = ( x - sourceX ) / d_horizMeshSpacing;
    double v = ( sourceY - y ) / d_vertMeshSpacing;

    // Do a bilinear interpolation to get the results
    double x0, y0, x1, y1, x2, y2, x3, y3;
    x0 = pULNode->getX();
    y0 = pULNode->getY();
    x1 = pURNode->getX();
    y1 = pURNode->getY();
    x2 = pLRNode->getX();
    y2 = pLRNode->getY();
    x3 = pLLNode->getX();
    y3 = pLLNode->getY();

    double xL0, yL0, xL1, yL1, xL2, yL2, xL3, yL3;
    xL0 = x0 + u * ( x1 - x0 );
    yL0 = y0 + u * ( y1 - y0 );
    xL1 = x1 + v * ( x2 - x1 );
    yL1 = y1 + v * ( y2 - y1 );
    xL2 = x3 + u * ( x2 - x3 );
    yL2 = y3 + u * ( y2 - y3 );
    xL3 = x0 + v * ( x3 - x0 );
    yL3 = y0 + v * ( y3 - y0 );

    if ( xL1 == xL3 )
    {
        x = xL1;
        y = yL3;
    }
    else if ( xL2 == xL0 )
    {
        x = xL2;
        y = yL3 + v * ( yL1 - yL3 );
    }
    else
    {
        double m13, m02;
        m13 = ( yL1 - yL3 ) / ( xL1 - xL3 );
        m02 = ( yL2 - yL0 ) / ( xL2 - xL0 );

        x = ( m13 * xL3 - yL3 - m02 * xL0 + yL0 ) / ( m13 - m02 );
        y = m13 * ( x - xL3 ) + yL3;
    }

    return true;
}

void
SplineMesh2D::validateNodes()
{
    MeshNode* pTopNode;
    MeshNode* pLeftNode;
    MeshNode* pRightNode;
    MeshNode* pBottomNode;
    MeshNode* pCenterNode;

    for ( int row = 0; row < d_meshHeight; row++ )
    {
        for ( int col = 0; col < d_meshWidth; col++ )
        {
            pCenterNode = getMeshNode( col, row );

            // Don't check this node if it's already been marked invalid
            if ( !pCenterNode->isValid() )
            {
                continue;
            }

            // Handle top row case
            if ( 0 == row )
            {
                pTopNode = pCenterNode;
                pBottomNode = getMeshNode( col, row + 1 );
            }
            // Handle bottom row case
            else if ( ( d_meshHeight - 1 ) == row )
            {
                pTopNode = getMeshNode( col, row - 1 );
                pBottomNode = pCenterNode;
            }
            else
            {
                pTopNode = getMeshNode( col, row - 1 );
                pBottomNode = getMeshNode( col, row + 1 );
            }

            // Handle left column case
            if ( 0 == col )
            {
                pLeftNode = pCenterNode;
                pRightNode = getMeshNode( col + 1, row );
            }
            // Handle right column case
            else if ( ( d_meshWidth - 1 ) == col )
            {
                pLeftNode = getMeshNode( col - 1, row );
                pRightNode = pCenterNode;
            }
            else
            {
                pLeftNode = getMeshNode( col - 1, row );
                pRightNode = getMeshNode( col + 1, row );
            }

            // Determine the validity of the node
            double centerX = pCenterNode->getX();
            double centerY = pCenterNode->getY();
            if ( ( ( pRightNode->getX() - centerX ) * ( centerX - pLeftNode->getX() ) < 0.0 ) ||
                 ( ( pTopNode->getY() - centerY ) * ( centerY - pBottomNode->getY() ) < 0.0 ) )
            {
                pCenterNode->setValid( false );
            }
            else
            {
                pCenterNode->setValid( true );
            }
        }
    }
}

void 
SplineMesh2D::getProjectedBoundingRect( double& left, double& bottom,
                                        double& right, double& top ) const
{
    double x, y;
    bool bFirstPoint = true;
    for ( long row = 0; row < getMeshHeight(); row++ )
    {
        for ( long col = 0; col < getMeshWidth(); col++ )
        {
            // Get the projected point at this position
            if ( getProjectedCoordinate( col, row, x, y ) )
            {
                // Init the bounds if this is the first point
                if ( bFirstPoint )
                {
                    left = right = x;
                    top = bottom = y;
                    bFirstPoint = false;
                }
                else
                {
                    left   = ( left < x ) ? left : x;
                    right  = ( right > x ) ? right : x;
                    top    = ( top > y ) ? top : y;
                    bottom = ( bottom < y ) ? bottom : y;
                }
            }
        }
    }
}

void 
SplineMesh2D::calculateMesh( const Projection& sourceProj, const Projection& destProj )
{
    // Set all the points in the mesh grid
    double x, y;
    for ( long row = 0; row < getMeshHeight(); row++ )
    {
        for ( long col = 0; col < getMeshWidth(); col++ )
        {
            // Get the grs point at this position
            getSourceCoordinate( col, row, x, y );

            // Convert the coordinate to geographic
            if ( sourceProj.projectToGeo( x, y, y, x ) )
            {
                // Convert from geographic to the destination coordinates
                if ( destProj.projectFromGeo( y, x, x, y ) )
                {
                    // Set the projected coordinates in the mesh
                    setMeshPoint( col, row, x, y );
                }
            }
        }
    }

    // Validate the projection mesh
    validateNodes();
}
