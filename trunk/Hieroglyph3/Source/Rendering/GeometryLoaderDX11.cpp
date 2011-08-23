//--------------------------------------------------------------------------------
// This file is a portion of the Hieroglyph 3 Rendering Engine.  It is distributed
// under the MIT License, available in the root of this distribution and 
// at the following URL:
//
// http://www.opensource.org/licenses/mit-license.php
//
// Copyright (c) 2003-2010 Jason Zink 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
#include "PCH.h"
#include "GeometryLoaderDX11.h"
#include "GeometryDX11.h"
#include "VertexElementDX11.h"
#include "ms3dspec.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Log.h"
#include "GlyphString.h"
#include "MaterialGeneratorDX11.h"
#include <sstream>

//--------------------------------------------------------------------------------
using namespace Glyph3;
//--------------------------------------------------------------------------------
GeometryLoaderDX11::GeometryLoaderDX11( )
{
}
//--------------------------------------------------------------------------------
//CGeometryDX9* CGeometryLoaderDX9::loadPlyFile( std::wstring filename )
//{
//
//	std::wstring nextLine;
//	std::ifstream iFile( filename.c_str() );
//	std::wstring command;
//	std::wstring subcommand;
//
//	int iNumVertices;
//	int iNumFaces;
//	
//	CVertexElementDX9* pPositions = NULL;
//	Vector3f* pPos = NULL;
//
//	getline( iFile, nextLine, '\n' );
//
//	std::istringstream In(nextLine);
//
//	while ( command != "end_header" )
//	{
//		getline( iFile, nextLine, '\n' );
//		std::istringstream thisline(nextLine);
//		thisline >> command;
//
//		if ( command == "element" )
//		{
//			while ( thisline )
//			{
//				std::wstring test;
//				thisline >> test;
//				removeWhiteSpace( test );
//
//				if ( test.length() > 0 )
//				{
//					std::istringstream subcommandstream(test);
//					subcommandstream >> subcommand;
//
//					if ( subcommand == "vertex" )
//					{
//						thisline >> test;
//						removeWhiteSpace( test );
//						
//						if ( test.length() > 0 )
//						{
//							std::istringstream final( test );
//							final >> iNumVertices;
//
//							pPositions = new CVertexElementDX9( 3, iNumVertices );
//							pPositions->m_Name = "POSITION";
//							pPositions->m_Type = FLOAT3;
//							pPositions->m_Method = DEFAULT;
//							pPositions->m_Usage = POSITION;
//							pPositions->m_UsageIndex = 0;
//							pPos = (Vector3f*)((*pPositions)[0]);
//						}
//					}
//					if ( subcommand == "face" )
//					{
//						thisline >> test;
//						removeWhiteSpace( test );
//
//						if ( test.length() > 0 )
//						{
//							std::istringstream final( test );
//							final >> iNumFaces;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	for ( int i = 0; i < iNumVertices; i++ )
//	{
//		getline( iFile, nextLine, '\n' );
//		std::istringstream vertexData(nextLine);
//		vertexData >> pPos[i].x() >> pPos[i].y() >> pPos[i].z();
//	}
//
//	CGeometryDX9* pMesh = new CGeometryDX9();
//	pMesh->AddElement( pPositions );
//
//	for ( int i = 0; i < iNumFaces; i++ )
//	{
//		getline( iFile, nextLine, '\n' );
//		std::istringstream faceData(nextLine);
//		
//		int indexCount;
//		faceData >> indexCount;
//
//		TriangleIndices face;
//		faceData >> face.P1() >> face.P2() >> face.P3();
//
//		pMesh->AddFace( face );
//	}
//
//	iFile.close();
//
//	return pMesh;
//}
//--------------------------------------------------------------------------------
//GeometryDX11* GeometryLoaderDX11::loadMS3DFile( std::wstring filename )
//{
//	// Temporary Milkshape structures
//	unsigned short usVertexCount = 0;
//	unsigned short usTriangleCount = 0;
//	unsigned short usGroupCount = 0;
//	unsigned short usMaterialCount = 0;
//	MS3DVertex* pMS3DVertices = NULL;
//	MS3DTriangle* pMS3DTriangles = NULL;
//	MS3DGroup* pMS3DGroups = NULL;
//	MS3DMaterial* pMS3DMaterials = NULL;
//
//	int i;
//	std::ifstream fin;
//	MS3DHeader header;
//
//	// Open the file and read the MS3D header data
//	fin.open( filename.c_str(),std::ios::binary );
//	fin.read((char*)(&(header.id)), sizeof(header.id));
//	fin.read((char*)(&(header.version)), sizeof(header.version));
//	if (header.version!=3 && header.version!=4)
//		return NULL;
//
//	// Load all the vertices
//	fin.read((char*)(&usVertexCount), sizeof(unsigned short));
//	pMS3DVertices = new MS3DVertex[usVertexCount];
//	for (i=0; i < usVertexCount; i++)
//	{
//		fin.read((char*)&(pMS3DVertices[i].flags), sizeof(unsigned char));
//		fin.read((char*)&(pMS3DVertices[i].vertex[0]), sizeof(float));
//		fin.read((char*)&(pMS3DVertices[i].vertex[1]), sizeof(float));
//		fin.read((char*)&(pMS3DVertices[i].vertex[2]), sizeof(float));
//		fin.read((char*)&(pMS3DVertices[i].boneId), sizeof(char));
//		fin.read((char*)&(pMS3DVertices[i].referenceCount), sizeof(unsigned char));
//	}
//
//	// Load all the triangle indices
//	fin.read((char*)(&usTriangleCount), sizeof(unsigned short));
//	pMS3DTriangles = new MS3DTriangle[usTriangleCount];
//	for (i=0; i < usTriangleCount; i++)
//	{
//		fin.read((char*)&(pMS3DTriangles[i].flags),sizeof(unsigned short));
//		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[0]), sizeof(unsigned short)); //3*sizeof(unsigned short));
//		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[1]), sizeof(unsigned short)); //3*sizeof(unsigned short));
//		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[2]), sizeof(unsigned short)); //3*sizeof(unsigned short));
//		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[0]), 3*sizeof(float));
//		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[1]), 3*sizeof(float));
//		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[2]), 3*sizeof(float));
//		fin.read((char*)&(pMS3DTriangles[i].s), 3*sizeof(float));
//		fin.read((char*)&(pMS3DTriangles[i].t), 3*sizeof(float));
//		fin.read((char*)&(pMS3DTriangles[i].smoothingGroup), sizeof(unsigned char));
//		fin.read((char*)&(pMS3DTriangles[i].groupIndex), sizeof(unsigned char));
//	}
//
//	// Load all the group information
//	fin.read((char*)(&usGroupCount), sizeof(unsigned short));
//	pMS3DGroups = new MS3DGroup[usGroupCount];
//	for (i=0; i < usGroupCount; i++)
//	{
//		fin.read((char*)&(pMS3DGroups[i].flags), sizeof(unsigned char));
//		fin.read((char*)&(pMS3DGroups[i].name), sizeof(char[32]));
//		fin.read((char*)&(pMS3DGroups[i].numtriangles), sizeof(unsigned short));
//		unsigned short triCount = pMS3DGroups[i].numtriangles;
//		pMS3DGroups[i].triangleIndices = new unsigned short[triCount];
//		fin.read((char*)(pMS3DGroups[i].triangleIndices), sizeof(unsigned short) * triCount);
//		fin.read((char*)&(pMS3DGroups[i].materialIndex), sizeof(char));
//	}
//
//	// Load all the material information
//	fin.read((char*)(&usMaterialCount),sizeof(unsigned short));
//	pMS3DMaterials = new MS3DMaterial[usMaterialCount];
//	for (i=0; i < usMaterialCount; i++)
//	{
//		fin.read((char*)&(pMS3DMaterials[i].name), sizeof(char[32]));
//		fin.read((char*)&(pMS3DMaterials[i].ambient), 4 * sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].diffuse), 4 * sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].specular), 4 * sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].emissive), 4 * sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].shininess), sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].transparency), sizeof(float));
//		fin.read((char*)&(pMS3DMaterials[i].mode), sizeof(char));
//		fin.read((char*)&(pMS3DMaterials[i].texture), sizeof(char[128]));
//		fin.read((char*)&(pMS3DMaterials[i].alphamap), sizeof(char[128]));
//	}
//
//	// Close the file (remaining file data unused)
//	fin.close();
//
//
//	// create the vertex element streams
//	CVertexElementDX9* pPositions = new CVertexElementDX9( 3, usVertexCount );
//	pPositions->m_Name = "POSITION";
//	pPositions->m_Type = FLOAT3;
//	pPositions->m_Method = DEFAULT;
//	pPositions->m_Usage = POSITION;
//	pPositions->m_UsageIndex = 0;
//
//	CVertexElementDX9* pTexcoords = new CVertexElementDX9( 2, usVertexCount );
//	pTexcoords->m_Name = "TEXCOORDS0";
//	pTexcoords->m_Type = FLOAT2;
//	pTexcoords->m_Method = DEFAULT;
//	pTexcoords->m_Usage = TEXCOORD;
//	pTexcoords->m_UsageIndex = 0;
//
//	CVertexElementDX9* pNormals = new CVertexElementDX9( 3, pPositions->Count() );
//	pNormals->m_Name = "NORMAL";
//	pNormals->m_Type = FLOAT3;
//	pNormals->m_Method = DEFAULT;
//	pNormals->m_Usage = NORMAL;
//	pNormals->m_UsageIndex = 0;
//
//	Vector3f* pPos = (Vector3f*)((*pPositions)[0]);
//	Vector3f* pNrm = (Vector3f*)((*pNormals)[0]);
//	Vector2f* pTex = (Vector2f*)((*pTexcoords)[0]);
//
//	CGeometryDX9* pMesh = new CGeometryDX9();
//
//	for ( int i = 0; i < usVertexCount; i++ )
//	{
//		pPos[i].x() = pMS3DVertices[i].vertex[0];
//		pPos[i].y() = pMS3DVertices[i].vertex[1];
//		pPos[i].z() = -pMS3DVertices[i].vertex[2];
//		pNrm[i].MakeZero();
//	}
//
//	TriangleIndices face;
//
//	for ( int i = 0; i < usTriangleCount; i++ )
//	{
//		face.P1() = pMS3DTriangles[i].vertexIndices[0];
//		face.P2() = pMS3DTriangles[i].vertexIndices[1];
//		face.P3() = pMS3DTriangles[i].vertexIndices[2];
//
//		pNrm[face.P1()].x() += pMS3DTriangles[i].vertexNormals[0][0];
//		pNrm[face.P1()].y() += pMS3DTriangles[i].vertexNormals[0][1];
//		pNrm[face.P1()].z() += pMS3DTriangles[i].vertexNormals[0][2];
//
//		pNrm[face.P2()].x() += pMS3DTriangles[i].vertexNormals[1][0];
//		pNrm[face.P2()].y() += pMS3DTriangles[i].vertexNormals[1][1];
//		pNrm[face.P2()].z() += pMS3DTriangles[i].vertexNormals[1][2];
//
//		pNrm[face.P3()].x() += pMS3DTriangles[i].vertexNormals[2][0];
//		pNrm[face.P3()].y() += pMS3DTriangles[i].vertexNormals[2][1];
//		pNrm[face.P3()].z() += pMS3DTriangles[i].vertexNormals[2][2];
//
//		pTex[face.P1()].x() = pMS3DTriangles[i].s[0];
//		pTex[face.P1()].y() = pMS3DTriangles[i].t[0];
//		pTex[face.P2()].x() = pMS3DTriangles[i].s[1];
//		pTex[face.P2()].y() = pMS3DTriangles[i].t[1];
//		pTex[face.P3()].x() = pMS3DTriangles[i].s[2];
//		pTex[face.P3()].y() = pMS3DTriangles[i].t[2];
//
//		pMesh->AddFace( face );
//	}
//
//	for ( int i = 0; i < usVertexCount; i++ )
//	{
//		pNrm[i].Normalize();
//		pNrm[i] *= -1.0f;
//	}
//
//	pMesh->AddElement( pPositions );
//	pMesh->AddElement( pTexcoords );
//	pMesh->AddElement( pNormals );
//
//	// Delete temporary materials
//	if (pMS3DMaterials != NULL)
//	{
//		delete[] pMS3DMaterials;
//		pMS3DMaterials = NULL;
//	}
//
//	// Delete temporary groups and their indices
//	if (pMS3DGroups != NULL)
//	{
//		for (i = 0; i < usGroupCount; i++)
//		{
//			if (pMS3DGroups[i].triangleIndices != NULL)
//			{
//				delete[] pMS3DGroups[i].triangleIndices;
//				pMS3DGroups[i].triangleIndices = NULL;
//			}
//		}
//		delete[] pMS3DGroups;
//		pMS3DGroups = NULL;
//	}
//
//	// Delete temporary triangles
//	if (pMS3DTriangles != NULL)
//	{
//		delete[] pMS3DTriangles;
//		pMS3DTriangles = NULL;
//	}
//
//	// Delete temporary vertices
//	if (pMS3DVertices != NULL)
//	{
//        delete[] pMS3DVertices;
//		pMS3DVertices = NULL;
//	}
//
//	pMesh->GenerateVertexDeclaration();
//	pMesh->LoadToBuffers();
//
//	return pMesh;
//}
//--------------------------------------------------------------------------------
GeometryDX11* GeometryLoaderDX11::loadMS3DFile2( std::wstring filename )
{
	// Temporary Milkshape structures
	unsigned short usVertexCount = 0;
	unsigned short usTriangleCount = 0;
	unsigned short usGroupCount = 0;
	unsigned short usMaterialCount = 0;
	MS3DVertex* pMS3DVertices = NULL;
	MS3DTriangle* pMS3DTriangles = NULL;
	MS3DGroup* pMS3DGroups = NULL;
	MS3DMaterial* pMS3DMaterials = NULL;

	int i;
	std::ifstream fin;
	MS3DHeader header;

	// Open the file and read the MS3D header data
	fin.open( filename.c_str(),std::ios::binary );
	fin.read((char*)(&(header.id)), sizeof(header.id));
	fin.read((char*)(&(header.version)), sizeof(header.version));
	if (header.version!=3 && header.version!=4)
		return NULL;

	// Load all the vertices
	fin.read((char*)(&usVertexCount), sizeof(unsigned short));
	pMS3DVertices = new MS3DVertex[usVertexCount];
	for (i=0; i < usVertexCount; i++)
	{
		fin.read((char*)&(pMS3DVertices[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DVertices[i].vertex[0]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[1]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[2]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].boneId), sizeof(char));
		fin.read((char*)&(pMS3DVertices[i].referenceCount), sizeof(unsigned char));
	}

	// Load all the triangle indices
	fin.read((char*)(&usTriangleCount), sizeof(unsigned short));
	pMS3DTriangles = new MS3DTriangle[usTriangleCount];
	for (i=0; i < usTriangleCount; i++)
	{
		fin.read((char*)&(pMS3DTriangles[i].flags),sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[0]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[1]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[2]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[0]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[1]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[2]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].s), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].t), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].smoothingGroup), sizeof(unsigned char));
		fin.read((char*)&(pMS3DTriangles[i].groupIndex), sizeof(unsigned char));
	}

	// Load all the group information
	fin.read((char*)(&usGroupCount), sizeof(unsigned short));
	pMS3DGroups = new MS3DGroup[usGroupCount];
	for (i=0; i < usGroupCount; i++)
	{
		fin.read((char*)&(pMS3DGroups[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DGroups[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DGroups[i].numtriangles), sizeof(unsigned short));
		unsigned short triCount = pMS3DGroups[i].numtriangles;
		pMS3DGroups[i].triangleIndices = new unsigned short[triCount];
		fin.read((char*)(pMS3DGroups[i].triangleIndices), sizeof(unsigned short) * triCount);
		fin.read((char*)&(pMS3DGroups[i].materialIndex), sizeof(char));
	}

	// Load all the material information
	fin.read((char*)(&usMaterialCount),sizeof(unsigned short));
	pMS3DMaterials = new MS3DMaterial[usMaterialCount];
	for (i=0; i < usMaterialCount; i++)
	{
		fin.read((char*)&(pMS3DMaterials[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DMaterials[i].ambient), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].diffuse), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].specular), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].emissive), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].shininess), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].transparency), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].mode), sizeof(char));
		fin.read((char*)&(pMS3DMaterials[i].texture), sizeof(char[128]));
		fin.read((char*)&(pMS3DMaterials[i].alphamap), sizeof(char[128]));
	}

	// Close the file (remaining file data unused)
	fin.close();


	// create the vertex element streams
	VertexElementDX11* pPositions = new VertexElementDX11( 3, usTriangleCount*3 );
    pPositions->m_SemanticName = VertexElementDX11::PositionSemantic;
	pPositions->m_uiSemanticIndex = 0;
	pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPositions->m_uiInputSlot = 0;
	pPositions->m_uiAlignedByteOffset = 0;
	pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPositions->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pTexcoords = new VertexElementDX11( 2, usTriangleCount*3 );
	pTexcoords->m_SemanticName = VertexElementDX11::TexCoordSemantic;
	pTexcoords->m_uiSemanticIndex = 0;
	pTexcoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexcoords->m_uiInputSlot = 0;
	pTexcoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexcoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexcoords->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pNormals = new VertexElementDX11( 3, usTriangleCount*3 );
	pNormals->m_SemanticName = VertexElementDX11::NormalSemantic;
	pNormals->m_uiSemanticIndex = 0;
	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pNormals->m_uiInputSlot = 0;
	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pNormals->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = (Vector3f*)((*pPositions)[0]);
	Vector3f* pNrm = (Vector3f*)((*pNormals)[0]);
	Vector2f* pTex = (Vector2f*)((*pTexcoords)[0]);

	GeometryDX11* pMesh = new GeometryDX11();

	//for ( int i = 0; i < usVertexCount; i++ )
	//{
	//	pPos[i].x() = pMS3DVertices[i].vertex[0];
	//	pPos[i].y() = pMS3DVertices[i].vertex[1];
	//	pPos[i].z() = -pMS3DVertices[i].vertex[2];
	//	pNrm[i].MakeZero();
	//}

	TriangleIndices face;

	for ( int i = 0; i < usTriangleCount; i++ )
	{

		face.P1() = 3*i+0;
		face.P2() = 3*i+2;
		face.P3() = 3*i+1;

		pPos[3*i+0].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[0];
		pPos[3*i+0].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[1];
		pPos[3*i+0].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[2];
		pPos[3*i+1].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[0];
		pPos[3*i+1].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[1];
		pPos[3*i+1].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[2];
		pPos[3*i+2].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[0];
		pPos[3*i+2].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[1];
		pPos[3*i+2].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[2];

		pNrm[3*i+0].x = pMS3DTriangles[i].vertexNormals[0][0];
		pNrm[3*i+0].y = pMS3DTriangles[i].vertexNormals[0][1];
		pNrm[3*i+0].z = -pMS3DTriangles[i].vertexNormals[0][2];
		pNrm[3*i+1].x = pMS3DTriangles[i].vertexNormals[1][0];
		pNrm[3*i+1].y = pMS3DTriangles[i].vertexNormals[1][1];
		pNrm[3*i+1].z = -pMS3DTriangles[i].vertexNormals[1][2];
		pNrm[3*i+2].x = pMS3DTriangles[i].vertexNormals[2][0];
		pNrm[3*i+2].y = pMS3DTriangles[i].vertexNormals[2][1];
		pNrm[3*i+2].z = -pMS3DTriangles[i].vertexNormals[2][2];

		pTex[3*i+0].x = pMS3DTriangles[i].s[0];
		pTex[3*i+0].y = pMS3DTriangles[i].t[0];
		pTex[3*i+1].x = pMS3DTriangles[i].s[1];
		pTex[3*i+1].y = pMS3DTriangles[i].t[1];
		pTex[3*i+2].x = pMS3DTriangles[i].s[2];
		pTex[3*i+2].y = pMS3DTriangles[i].t[2];

		pMesh->AddFace( face );
	}

	for ( int i = 0; i < usVertexCount; i++ )
	{
		pNrm[i].Normalize();
	}

	pMesh->AddElement( pPositions );
	pMesh->AddElement( pTexcoords );
	pMesh->AddElement( pNormals );

	// Delete temporary materials
	if (pMS3DMaterials != NULL)
	{
		delete[] pMS3DMaterials;
		pMS3DMaterials = NULL;
	}

	// Delete temporary groups and their indices
	if (pMS3DGroups != NULL)
	{
		for (i = 0; i < usGroupCount; i++)
		{
			if (pMS3DGroups[i].triangleIndices != NULL)
			{
				delete[] pMS3DGroups[i].triangleIndices;
				pMS3DGroups[i].triangleIndices = NULL;
			}
		}
		delete[] pMS3DGroups;
		pMS3DGroups = NULL;
	}

	// Delete temporary triangles
	if (pMS3DTriangles != NULL)
	{
		delete[] pMS3DTriangles;
		pMS3DTriangles = NULL;
	}

	// Delete temporary vertices
	if (pMS3DVertices != NULL)
	{
        delete[] pMS3DVertices;
		pMS3DVertices = NULL;
	}

	//pMesh->GenerateVertexDeclaration();
	//pMesh->LoadToBuffers();

	return( pMesh );
}
//--------------------------------------------------------------------------------
GeometryDX11* GeometryLoaderDX11::loadMS3DFileWithAnimation( std::wstring filename, SkinnedActor* pActor )
{
	// Temporary Milkshape structures
	unsigned short usVertexCount = 0;
	unsigned short usTriangleCount = 0;
	unsigned short usGroupCount = 0;
	unsigned short usMaterialCount = 0;
	MS3DVertex* pMS3DVertices = NULL;
	MS3DTriangle* pMS3DTriangles = NULL;
	MS3DGroup* pMS3DGroups = NULL;
	MS3DMaterial* pMS3DMaterials = NULL;

	int i;
	std::ifstream fin;
	MS3DHeader header;

	// Open the file and read the MS3D header data
	fin.open( filename.c_str(),std::ios::binary );
	fin.read((char*)(&(header.id)), sizeof(header.id));
	fin.read((char*)(&(header.version)), sizeof(header.version));
	if (header.version!=3 && header.version!=4)
		return NULL;

	// Load all the vertices
	fin.read((char*)(&usVertexCount), sizeof(unsigned short));
	pMS3DVertices = new MS3DVertex[usVertexCount];
	for (i=0; i < usVertexCount; i++)
	{
		fin.read((char*)&(pMS3DVertices[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DVertices[i].vertex[0]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[1]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].vertex[2]), sizeof(float));
		fin.read((char*)&(pMS3DVertices[i].boneId), sizeof(char));
		fin.read((char*)&(pMS3DVertices[i].referenceCount), sizeof(unsigned char));
	}

	// Load all the triangle indices
	fin.read((char*)(&usTriangleCount), sizeof(unsigned short));
	pMS3DTriangles = new MS3DTriangle[usTriangleCount];
	for (i=0; i < usTriangleCount; i++)
	{
		fin.read((char*)&(pMS3DTriangles[i].flags),sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[0]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[1]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexIndices[2]), sizeof(unsigned short)); //3*sizeof(unsigned short));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[0]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[1]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].vertexNormals[2]), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].s), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].t), 3*sizeof(float));
		fin.read((char*)&(pMS3DTriangles[i].smoothingGroup), sizeof(unsigned char));
		fin.read((char*)&(pMS3DTriangles[i].groupIndex), sizeof(unsigned char));
	}

	// Load all the group information
	fin.read((char*)(&usGroupCount), sizeof(unsigned short));
	pMS3DGroups = new MS3DGroup[usGroupCount];
	for (i=0; i < usGroupCount; i++)
	{
		fin.read((char*)&(pMS3DGroups[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DGroups[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DGroups[i].numtriangles), sizeof(unsigned short));
		unsigned short triCount = pMS3DGroups[i].numtriangles;
		pMS3DGroups[i].triangleIndices = new unsigned short[triCount];
		fin.read((char*)(pMS3DGroups[i].triangleIndices), sizeof(unsigned short) * triCount);
		fin.read((char*)&(pMS3DGroups[i].materialIndex), sizeof(char));
	}

	// Load all the material information
	fin.read((char*)(&usMaterialCount),sizeof(unsigned short));
	pMS3DMaterials = new MS3DMaterial[usMaterialCount];
	for (i=0; i < usMaterialCount; i++)
	{
		fin.read((char*)&(pMS3DMaterials[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DMaterials[i].ambient), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].diffuse), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].specular), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].emissive), 4 * sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].shininess), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].transparency), sizeof(float));
		fin.read((char*)&(pMS3DMaterials[i].mode), sizeof(char));
		fin.read((char*)&(pMS3DMaterials[i].texture), sizeof(char[128]));
		fin.read((char*)&(pMS3DMaterials[i].alphamap), sizeof(char[128]));
	}

	float fAnimationFPS; // 4 bytes
	float fCurrentTime; // 4 bytes
	int iTotalFrames; // 4 bytes
	unsigned short nNumJoints; // 2 bytes

	fin.read((char*)&(fAnimationFPS), sizeof(float));
	fin.read((char*)&(fCurrentTime), sizeof(float));
	fin.read((char*)&(iTotalFrames), sizeof(int));
	fin.read((char*)&(nNumJoints), sizeof(unsigned short));


	MS3DKeyframeJoint* pMS3DJoints = 0;

	if ( nNumJoints > 0 )
		pMS3DJoints = new MS3DKeyframeJoint[nNumJoints];

	for ( i = 0; i < nNumJoints; i++ )
	{
		fin.read((char*)&(pMS3DJoints[i].flags), sizeof(unsigned char));
		fin.read((char*)&(pMS3DJoints[i].name), sizeof(char[32]));
		fin.read((char*)&(pMS3DJoints[i].parentName), sizeof(char[32]));
		fin.read((char*)&(pMS3DJoints[i].rotation[0]), 3 * sizeof(float));
		fin.read((char*)&(pMS3DJoints[i].position[0]), 3 * sizeof(float));
		fin.read((char*)&(pMS3DJoints[i].numKeyFramesRot), sizeof(unsigned short));
		fin.read((char*)&(pMS3DJoints[i].numKeyFramesTrans), sizeof(unsigned short));

		pMS3DJoints[i].keyFramesRot = new MS3DKeyframeRotation[pMS3DJoints[i].numKeyFramesRot];
		pMS3DJoints[i].keyFramesTrans = new MS3DKeyframePosition[pMS3DJoints[i].numKeyFramesTrans];

		for ( int j = 0; j < pMS3DJoints[i].numKeyFramesRot; j++ )
		{
			fin.read((char*)&(pMS3DJoints[i].keyFramesRot[j].time), 1 * sizeof(float));
			fin.read((char*)&(pMS3DJoints[i].keyFramesRot[j].rotation), 3 * sizeof(float));
		}

		for ( int j = 0; j < pMS3DJoints[i].numKeyFramesTrans; j++ )
		{
			fin.read((char*)&(pMS3DJoints[i].keyFramesTrans[j].time), 1 * sizeof(float));
			fin.read((char*)&(pMS3DJoints[i].keyFramesTrans[j].position), 3 * sizeof(float));
		}

		//std::wstringstream s;
		//s << GlyphString::ToUnicode( std::string( pMS3DJoints[i].name ) ) << std::endl;
		//for ( int z = 0; z < pMS3DJoints[i].numKeyFramesRot; z++ )
		//	s << L"rotation: " << pMS3DJoints[i].keyFramesRot[z].time << L" " <<pMS3DJoints[i].keyFramesRot[z].rotation[0] << L" " << pMS3DJoints[i].keyFramesRot[z].rotation[1] << L" " << pMS3DJoints[i].keyFramesRot[z].rotation[2] << std::endl;

		//for ( int z = 0; z < pMS3DJoints[i].numKeyFramesTrans; z++ )
		//	s << L"position: " << pMS3DJoints[i].keyFramesTrans[z].time << L" " <<pMS3DJoints[i].keyFramesTrans[z].position[0] << L" " << pMS3DJoints[i].keyFramesTrans[z].position[1] << L" " << pMS3DJoints[i].keyFramesTrans[z].position[2] << std::endl;

		//Log::Get().Write( s.str() );
	}



	// Close the file (remaining file data unused)
	fin.close();


	// create the vertex element streams
	VertexElementDX11* pPositions = new VertexElementDX11( 3, usTriangleCount*3 );
	pPositions->m_SemanticName = VertexElementDX11::PositionSemantic;
	pPositions->m_uiSemanticIndex = 0;
	pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPositions->m_uiInputSlot = 0;
	pPositions->m_uiAlignedByteOffset = 0;
	pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPositions->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pBoneIDs = new VertexElementDX11( 1, usTriangleCount*3 );
	pBoneIDs->m_SemanticName = VertexElementDX11::BoneIDSemantic;
	pBoneIDs->m_uiSemanticIndex = 0;
	pBoneIDs->m_Format = DXGI_FORMAT_R32_SINT;
	pBoneIDs->m_uiInputSlot = 0;
	pBoneIDs->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pBoneIDs->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pBoneIDs->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pTexcoords = new VertexElementDX11( 2, usTriangleCount*3 );
	pTexcoords->m_SemanticName = VertexElementDX11::TexCoordSemantic;
	pTexcoords->m_uiSemanticIndex = 0;
	pTexcoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
	pTexcoords->m_uiInputSlot = 0;
	pTexcoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pTexcoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pTexcoords->m_uiInstanceDataStepRate = 0;

	VertexElementDX11* pNormals = new VertexElementDX11( 3, usTriangleCount*3 );
	pNormals->m_SemanticName = VertexElementDX11::NormalSemantic;
	pNormals->m_uiSemanticIndex = 0;
	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pNormals->m_uiInputSlot = 0;
	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pNormals->m_uiInstanceDataStepRate = 0;

	Vector3f* pPos = pPositions->Get3f( 0 );
	int* pIds = pBoneIDs->Get1i( 0 );
	Vector3f* pNrm = pNormals->Get3f( 0 );
	Vector2f* pTex = pTexcoords->Get2f( 0 );

	// Create the geometry object, and fill it with the data read from the file.

	GeometryDX11* pMesh = new GeometryDX11();

	TriangleIndices face;

	for ( int i = 0; i < usTriangleCount; i++ )
	{

		face.P1() = 3*i+0;
		face.P2() = 3*i+2;
		face.P3() = 3*i+1;

		pPos[3*i+0].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[0];
		pPos[3*i+0].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[1];
		pPos[3*i+0].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].vertex[2];
		pPos[3*i+1].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[0];
		pPos[3*i+1].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[1];
		pPos[3*i+1].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].vertex[2];
		pPos[3*i+2].x = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[0];
		pPos[3*i+2].y = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[1];
		pPos[3*i+2].z = -pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].vertex[2];

		pIds[3*i+0] = pMS3DVertices[pMS3DTriangles[i].vertexIndices[0]].boneId;
		pIds[3*i+1] = pMS3DVertices[pMS3DTriangles[i].vertexIndices[1]].boneId;
		pIds[3*i+2] = pMS3DVertices[pMS3DTriangles[i].vertexIndices[2]].boneId;

		pNrm[3*i+0].x = pMS3DTriangles[i].vertexNormals[0][0];
		pNrm[3*i+0].y = pMS3DTriangles[i].vertexNormals[0][1];
		pNrm[3*i+0].z = -pMS3DTriangles[i].vertexNormals[0][2];
		pNrm[3*i+1].x = pMS3DTriangles[i].vertexNormals[1][0];
		pNrm[3*i+1].y = pMS3DTriangles[i].vertexNormals[1][1];
		pNrm[3*i+1].z = -pMS3DTriangles[i].vertexNormals[1][2];
		pNrm[3*i+2].x = pMS3DTriangles[i].vertexNormals[2][0];
		pNrm[3*i+2].y = pMS3DTriangles[i].vertexNormals[2][1];
		pNrm[3*i+2].z = -pMS3DTriangles[i].vertexNormals[2][2];

		pTex[3*i+0].x = pMS3DTriangles[i].s[0];
		pTex[3*i+0].y = pMS3DTriangles[i].t[0];
		pTex[3*i+1].x = pMS3DTriangles[i].s[1];
		pTex[3*i+1].y = pMS3DTriangles[i].t[1];
		pTex[3*i+2].x = pMS3DTriangles[i].s[2];
		pTex[3*i+2].y = pMS3DTriangles[i].t[2];

		pMesh->AddFace( face );
	}

	for ( int i = 0; i < usVertexCount; i++ )
	{
		pNrm[i].Normalize();
	}

	pMesh->AddElement( pPositions );
	pMesh->AddElement( pBoneIDs );
	pMesh->AddElement( pTexcoords );
	pMesh->AddElement( pNormals );

	// Now set the geometry in the SkinnedActor, and create the bones
	// and add them to the SkinnedActor.

	if ( pActor )
	{
		// Set the geometry in the body of the actor
		pActor->GetBody()->SetGeometry( pMesh );

		// Create an array of nodes, one for each joint.
		std::map<std::string,Node3D*> JointNodes;

		for ( int i = 0; i < nNumJoints; i++ )
		{
			Node3D* pBone = new Node3D();

			Vector3f BindPosition = Vector3f( pMS3DJoints[i].position[0],
			 									pMS3DJoints[i].position[1],
												pMS3DJoints[i].position[2] );

			AnimationStream<Vector3f>* pPosFrames = new AnimationStream<Vector3f>();

			for ( int j = 0; j < pMS3DJoints[i].numKeyFramesTrans; j++ )
			{
				Vector3f p = Vector3f( pMS3DJoints[i].keyFramesTrans[j].position[0],
					pMS3DJoints[i].keyFramesTrans[j].position[1],
					pMS3DJoints[i].keyFramesTrans[j].position[2] );

				pPosFrames->AddState( AnimationState<Vector3f>( pMS3DJoints[i].keyFramesTrans[j].time, p ) ); 
			}

			AnimationStream<Vector3f>* pRotFrames = new AnimationStream<Vector3f>();
			
			Vector3f BindRotation = Vector3f( pMS3DJoints[i].rotation[0] + 6.28f, pMS3DJoints[i].rotation[1] + 6.28f, pMS3DJoints[i].rotation[2] + 6.28f );

			for ( int j = 0; j < pMS3DJoints[i].numKeyFramesRot; j++ )
			{
				Vector3f p = Vector3f( pMS3DJoints[i].keyFramesRot[j].rotation[0] + 6.28f,
					pMS3DJoints[i].keyFramesRot[j].rotation[1] + 6.28f,
					pMS3DJoints[i].keyFramesRot[j].rotation[2] + 6.28f );

				pRotFrames->AddState( AnimationState<Vector3f>( pMS3DJoints[i].keyFramesRot[j].time, p ) ); 
			}

			pActor->AddBoneNode( pBone, BindPosition, BindRotation, pPosFrames, pRotFrames );

			JointNodes[std::string(pMS3DJoints[i].name)] = pBone;
		}

		// Connect up the bones to form the skeleton.
		for ( int i = 0; i < nNumJoints; i++ )
		{
			Node3D* pParent = JointNodes[std::string(pMS3DJoints[i].parentName)];
			Node3D* pChild = JointNodes[std::string(pMS3DJoints[i].name)];

			// If the node has a parent, link them
			if ( pParent && pChild )
				pParent->AttachChild( pChild );

			// If the node has no parent, link it to the root of the skinned actor (for connection
			// to the scene graph).
			if ( !pParent && pChild )
				pActor->GetNode()->AttachChild( pChild );
		}
	}


	// Delete temporary joint information
	if ( pMS3DJoints )
	{
		for ( int i = 0; i < nNumJoints; i++ )
		{
			delete[] pMS3DJoints[i].keyFramesRot;
			delete[] pMS3DJoints[i].keyFramesTrans;
		}
		delete[] pMS3DJoints;
	}


	// Delete temporary materials
	if (pMS3DMaterials != NULL)
	{
		delete[] pMS3DMaterials;
		pMS3DMaterials = NULL;
	}

	// Delete temporary groups and their indices
	if (pMS3DGroups != NULL)
	{
		for (i = 0; i < usGroupCount; i++)
		{
			if (pMS3DGroups[i].triangleIndices != NULL)
			{
				delete[] pMS3DGroups[i].triangleIndices;
				pMS3DGroups[i].triangleIndices = NULL;
			}
		}
		delete[] pMS3DGroups;
		pMS3DGroups = NULL;
	}

	// Delete temporary triangles
	if (pMS3DTriangles != NULL)
	{
		delete[] pMS3DTriangles;
		pMS3DTriangles = NULL;
	}

	// Delete temporary vertices
	if (pMS3DVertices != NULL)
	{
        delete[] pMS3DVertices;
		pMS3DVertices = NULL;
	}

	//pMesh->GenerateVertexDeclaration();
	pMesh->LoadToBuffers();

	return( pMesh );
}
//--------------------------------------------------------------------------------
//GeometryDX11* GeometryLoaderDX11::loadMS3DFileWithAnimationAndWeights( std::wstring filename, SkinnedActor* pActor )
//{
//
//	msModel* pModel = new msModel();
//	bool bResult = pModel->Load( GlyphString::ToAscii( filename ).c_str() );
//
//	if ( !bResult )
//	{
//		Log::Get().Write( L"Failed to load *.ms3d model!" );
//		return( 0 );
//	}
//	
//
//	unsigned int usTriangleCount = pModel->GetNumTriangles();
//	unsigned int usVertexCount = pModel->GetNumVertices();
//	unsigned int usJointCount = pModel->GetNumJoints(); 
//
//	// create the vertex element streams
//	VertexElementDX11* pPositions = new VertexElementDX11( 3, usTriangleCount*3 );
//	pPositions->m_SemanticName = VertexElementDX11::PositionSemantic;
//	pPositions->m_uiSemanticIndex = 0;
//	pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	pPositions->m_uiInputSlot = 0;
//	pPositions->m_uiAlignedByteOffset = 0;
//	pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	pPositions->m_uiInstanceDataStepRate = 0;
//
//	VertexElementDX11* pBoneIDs = new VertexElementDX11( 4, usTriangleCount*3 );
//	pBoneIDs->m_SemanticName = VertexElementDX11::BoneIDSemantic;
//	pBoneIDs->m_uiSemanticIndex = 0;
//	pBoneIDs->m_Format = DXGI_FORMAT_R32G32B32A32_SINT;
//	pBoneIDs->m_uiInputSlot = 0;
//	pBoneIDs->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	pBoneIDs->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	pBoneIDs->m_uiInstanceDataStepRate = 0;
//
//	VertexElementDX11* pBoneWeights = new VertexElementDX11( 4, usTriangleCount*3 );
//	pBoneWeights->m_SemanticName = VertexElementDX11::BoneWeightSemantic;
//	pBoneWeights->m_uiSemanticIndex = 0;
//	pBoneWeights->m_Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	pBoneWeights->m_uiInputSlot = 0;
//	pBoneWeights->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	pBoneWeights->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	pBoneWeights->m_uiInstanceDataStepRate = 0;
//
//	VertexElementDX11* pTexcoords = new VertexElementDX11( 2, usTriangleCount*3 );
//	pTexcoords->m_SemanticName = VertexElementDX11::TexCoordSemantic;
//	pTexcoords->m_uiSemanticIndex = 0;
//	pTexcoords->m_Format = DXGI_FORMAT_R32G32_FLOAT;
//	pTexcoords->m_uiInputSlot = 0;
//	pTexcoords->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	pTexcoords->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	pTexcoords->m_uiInstanceDataStepRate = 0;
//
//	VertexElementDX11* pNormals = new VertexElementDX11( 3, usTriangleCount*3 );
//	pNormals->m_SemanticName = VertexElementDX11::NormalSemantic;
//	pNormals->m_uiSemanticIndex = 0;
//	pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	pNormals->m_uiInputSlot = 0;
//	pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	pNormals->m_uiInstanceDataStepRate = 0;
//
//	Vector3f* pPos = pPositions->Get3f( 0 );
//	int* pIds = pBoneIDs->Get1i( 0 );
//	Vector4f* pWghts = pBoneWeights->Get4f( 0 );
//	Vector3f* pNrm = pNormals->Get3f( 0 );
//	Vector2f* pTex = pTexcoords->Get2f( 0 );
//
//	// Create the geometry object, and fill it with the data read from the file.
//
//	GeometryDX11* pMesh = new GeometryDX11();
//
//	TriangleIndices face;
//
//	float fTotalWeight = 100.0f;
//
//
//	for ( int i = 0; i < usTriangleCount; i++ )
//	{
//		face.P1() = 3*i+0;
//		face.P2() = 3*i+2;
//		face.P3() = 3*i+1;
//
//		ms3d_triangle_t* pTriangle = pModel->GetTriangle( i );
//		unsigned int vIDs[3];
//		vIDs[0] = pTriangle->vertexIndices[0];
//		vIDs[1] = pTriangle->vertexIndices[1];
//		vIDs[2] = pTriangle->vertexIndices[2];
//
//
//		pPos[3*i+0].x =  pModel->GetVertex( vIDs[0] )->vertex[0];
//		pPos[3*i+0].y =  pModel->GetVertex( vIDs[0] )->vertex[1];
//		pPos[3*i+0].z = -pModel->GetVertex( vIDs[0] )->vertex[2];
//		pPos[3*i+1].x =  pModel->GetVertex( vIDs[1] )->vertex[0];
//		pPos[3*i+1].y =  pModel->GetVertex( vIDs[1] )->vertex[1];
//		pPos[3*i+1].z = -pModel->GetVertex( vIDs[1] )->vertex[2];
//		pPos[3*i+2].x =  pModel->GetVertex( vIDs[2] )->vertex[0];
//		pPos[3*i+2].y =  pModel->GetVertex( vIDs[2] )->vertex[1];
//		pPos[3*i+2].z = -pModel->GetVertex( vIDs[2] )->vertex[2];
//
//		pIds[12*i+0] = pModel->GetVertex( vIDs[0] )->boneId;
//		pIds[12*i+1] = pModel->GetVertex( vIDs[0] )->boneIds[0];
//		pIds[12*i+2] = pModel->GetVertex( vIDs[0] )->boneIds[1]; 
//		pIds[12*i+3] = pModel->GetVertex( vIDs[0] )->boneIds[2]; 
//
//		pIds[12*i+4] = pModel->GetVertex( vIDs[1] )->boneId; 
//		pIds[12*i+5] = pModel->GetVertex( vIDs[1] )->boneIds[0];
//		pIds[12*i+6] = pModel->GetVertex( vIDs[1] )->boneIds[1]; 
//		pIds[12*i+7] = pModel->GetVertex( vIDs[1] )->boneIds[2]; 
//
//		pIds[12*i+8] = pModel->GetVertex( vIDs[2] )->boneId;
//		pIds[12*i+9] = pModel->GetVertex( vIDs[2] )->boneIds[0]; 
//		pIds[12*i+10] = pModel->GetVertex( vIDs[2] )->boneIds[1];
//		pIds[12*i+11] = pModel->GetVertex( vIDs[2] )->boneIds[2];
//
//
//		float w1 = ((float)pModel->GetVertex( vIDs[0] )->weights[0] );
//		float w2 = ((float)pModel->GetVertex( vIDs[0] )->weights[1] );
//		float w3 = ((float)pModel->GetVertex( vIDs[0] )->weights[2] );
//		if ( w1 != 0.0f || w2 != 0.0f || w3 != 0.0f )
//		{
//			pWghts[3*i+0].x = w1 / fTotalWeight;
//			pWghts[3*i+0].y = w2 / fTotalWeight;
//			pWghts[3*i+0].z = w3 / fTotalWeight;
//			pWghts[3*i+0].w = 1.0f - w1 - w2 - w3;
//		}
//		else
//		{
//			pWghts[3*i+0].x = 1.0f;
//			pWghts[3*i+0].y = 0.0f;
//			pWghts[3*i+0].z = 0.0f;
//			pWghts[3*i+0].w = 0.0f;
//		}
//
//
//		//pWghts[3*i+0].x = ((float)pModel->GetVertex( vIDs[0] )->weights[0] ) / fTotalWeight;
//		//pWghts[3*i+0].y = ((float)pModel->GetVertex( vIDs[0] )->weights[1] ) / fTotalWeight;
//		//pWghts[3*i+0].z = ((float)pModel->GetVertex( vIDs[0] )->weights[2] ) / fTotalWeight;
//		//pWghts[3*i+0].w = 1.0f - pWghts[3*i+0].x - pWghts[3*i+0].y - pWghts[3*i+0].z;
//
//		w1 = ((float)pModel->GetVertex( vIDs[1] )->weights[0] );
//		w2 = ((float)pModel->GetVertex( vIDs[1] )->weights[1] );
//		w3 = ((float)pModel->GetVertex( vIDs[1] )->weights[2] );
//
//		if ( w1 != 0.0f || w2 != 0.0f || w3 != 0.0f )
//		{
//			pWghts[3*i+1].x = w1 / fTotalWeight;
//			pWghts[3*i+1].y = w2 / fTotalWeight;
//			pWghts[3*i+1].z = w3 / fTotalWeight;
//			pWghts[3*i+1].w = 1.0f - w1 - w2 - w3;
//		}
//		else
//		{
//			pWghts[3*i+1].x = 1.0f;
//			pWghts[3*i+1].y = 0.0f;
//			pWghts[3*i+1].z = 0.0f;
//			pWghts[3*i+1].w = 0.0f;
//		}
//
//		//pWghts[3*i+1].x = ((float)pModel->GetVertex( vIDs[1] )->weights[0] ) / fTotalWeight;
//		//pWghts[3*i+1].y = ((float)pModel->GetVertex( vIDs[1] )->weights[1] ) / fTotalWeight;
//		//pWghts[3*i+1].z = ((float)pModel->GetVertex( vIDs[1] )->weights[2] ) / fTotalWeight;
//		//pWghts[3*i+1].w = 1.0f - pWghts[3*i+1].x - pWghts[3*i+1].y - pWghts[3*i+1].z;
//
//		w1 = ((float)pModel->GetVertex( vIDs[2] )->weights[0] );
//		w2 = ((float)pModel->GetVertex( vIDs[2] )->weights[1] );
//		w3 = ((float)pModel->GetVertex( vIDs[2] )->weights[2] );
//
//		if ( w1 != 0.0f || w2 != 0.0f || w3 != 0.0f )
//		{
//			pWghts[3*i+2].x = w1 / fTotalWeight;
//			pWghts[3*i+2].y = w2 / fTotalWeight;
//			pWghts[3*i+2].z = w3 / fTotalWeight;
//			pWghts[3*i+2].w = 1.0f - w1 - w2 - w3;
//		}
//		else
//		{
//			pWghts[3*i+2].x = 1.0f;
//			pWghts[3*i+2].y = 0.0f;
//			pWghts[3*i+2].z = 0.0f;
//			pWghts[3*i+2].w = 0.0f;
//		}
//
//		//pWghts[3*i+2].x = ((float)pModel->GetVertex( vIDs[2] )->weights[0] ) / fTotalWeight;
//		//pWghts[3*i+2].y = ((float)pModel->GetVertex( vIDs[2] )->weights[1] ) / fTotalWeight;
//		//pWghts[3*i+2].z = ((float)pModel->GetVertex( vIDs[2] )->weights[2] ) / fTotalWeight;
//		//pWghts[3*i+2].w = 1.0f - pWghts[3*i+2].x - pWghts[3*i+2].y - pWghts[3*i+2].z;
//
//
//
//		if (pIds[12*i+0] == -1)
//		{
//			pIds[12*i+0] = 0;
//			pWghts[3*i+0].x = 0.0f; 
//		}
//
//		if (pIds[12*i+1] == -1)
//		{
//			pIds[12*i+1] = 0;
//			pWghts[3*i+0].y = 0.0f; 
//		}
//		if (pIds[12*i+2] == -1)
//		{
//			pIds[12*i+2] = 0;
//			pWghts[3*i+0].z = 0.0f; 
//		}
//		if (pIds[12*i+3] == -1)
//		{
//			pIds[12*i+3] = 0;
//			pWghts[3*i+0].w = 0.0f; 
//		}
//
//
//
//		if (pIds[12*i+4] == -1)
//		{
//			pIds[12*i+4] = 0;
//			pWghts[3*i+1].x = 0.0f; 
//		}
//		if (pIds[12*i+5] == -1)
//		{
//			pIds[12*i+5] = 0;
//			pWghts[3*i+1].y = 0.0f; 
//		}
//		if (pIds[12*i+6] == -1)
//		{
//			pIds[12*i+6] = 0;
//			pWghts[3*i+1].z = 0.0f; 
//		}
//		if (pIds[12*i+7] == -1)
//		{
//			pIds[12*i+7] = 0;
//			pWghts[3*i+1].w = 0.0f; 
//		}
//		if (pIds[12*i+8] == -1)
//		{
//			pIds[12*i+8] = 0;
//			pWghts[3*i+2].x = 0.0f; 
//		}
//		if (pIds[12*i+9] == -1)
//		{
//			pIds[12*i+9] = 0;
//			pWghts[3*i+2].y = 0.0f; 
//		}
//		if (pIds[12*i+10] == -1)
//		{
//			pIds[12*i+10] = 0;
//			pWghts[3*i+2].z = 0.0f; 
//		}
//		if (pIds[12*i+11] == -1)
//		{
//			pIds[12*i+11] = 0;
//			pWghts[3*i+2].w = 0.0f; 
//		}
//
//		pNrm[3*i+0].x = pTriangle->vertexNormals[0][0];
//		pNrm[3*i+0].y = pTriangle->vertexNormals[0][1];
//		pNrm[3*i+0].z = -pTriangle->vertexNormals[0][2];
//		pNrm[3*i+1].x = pTriangle->vertexNormals[1][0];
//		pNrm[3*i+1].y = pTriangle->vertexNormals[1][1];
//		pNrm[3*i+1].z = -pTriangle->vertexNormals[1][2];
//		pNrm[3*i+2].x = pTriangle->vertexNormals[2][0];
//		pNrm[3*i+2].y = pTriangle->vertexNormals[2][1];
//		pNrm[3*i+2].z = -pTriangle->vertexNormals[2][2];
//
//		pTex[3*i+0].x = pTriangle->s[0];
//		pTex[3*i+0].y = pTriangle->t[0];
//		pTex[3*i+1].x = pTriangle->s[1];
//		pTex[3*i+1].y = pTriangle->t[1];
//		pTex[3*i+2].x = pTriangle->s[2];
//		pTex[3*i+2].y = pTriangle->t[2];
//
//		pMesh->AddFace( face );
//	}
//
//	for ( int i = 0; i < usVertexCount; i++ )
//	{
//		pNrm[i].Normalize();
//	}
//
//	pMesh->AddElement( pPositions );
//	pMesh->AddElement( pBoneIDs );
//	pMesh->AddElement( pBoneWeights );
//	pMesh->AddElement( pTexcoords );
//	pMesh->AddElement( pNormals );
//
//	// Now set the geometry in the SkinnedActor, and create the bones
//	// and add them to the SkinnedActor.
//
//	if ( pActor )
//	{
//		// Set the geometry in the body of the actor
//		//pActor->GetBody()->SetGeometry( pMesh );
//
//		// Create an array of nodes, one for each joint.
//		std::map<std::string,Node3D*> JointNodes;
//
//		for ( int i = 0; i < usJointCount; i++ )
//		{
//			Node3D* pBone = new Node3D();
//			ms3d_joint_t* pJoint = pModel->GetJoint( i );
//
//			Vector3f BindPosition = Vector3f( pJoint->pos[0],
//			 								  pJoint->pos[1],
//											  -pJoint->pos[2] );
//
//			AnimationStream<Vector3f>* pPosFrames = new AnimationStream<Vector3f>();
//
//			for ( int j = 0; j < pJoint->positionKeys.size(); j++ )
//			{
//				Vector3f p = Vector3f( pJoint->positionKeys[j].key[0],
//					                   pJoint->positionKeys[j].key[1],
//					                   -pJoint->positionKeys[j].key[2] );
//
//				std::stringstream s;
//				s << "Position Frame " << j << " " << p.x << "," << p.y << "," << p.z;
//				Log::Get().Write( GlyphString::ToUnicode( s.str() ) );
//
//				pPosFrames->AddState( AnimationState<Vector3f>( pJoint->positionKeys[j].time, p ) ); 
//			}
//
//			AnimationStream<Vector3f>* pRotFrames = new AnimationStream<Vector3f>();
//			
//			Vector3f BindRotation = Vector3f( -pJoint->rot[0] + 6.28f,
//				                              -pJoint->rot[1] + 6.28f,
//											  pJoint->rot[2] + 6.28f );
//
//			for ( int j = 0; j < pJoint->rotationKeys.size(); j++ )
//			{
//
//				Vector3f p = Vector3f( -pJoint->rotationKeys[j].key[0] + 6.28f,
//					                   -pJoint->rotationKeys[j].key[1] + 6.28f,
//						               pJoint->rotationKeys[j].key[2] + 6.28f );
//
//				std::stringstream s;
//				s << "Rotation Frame " << j << " " << p.x << "," << p.y << "," << p.z;
//				Log::Get().Write( GlyphString::ToUnicode( s.str() ) );
//
//				pRotFrames->AddState( AnimationState<Vector3f>( pJoint->rotationKeys[j].time, p ) ); 
//			}
//
//			pActor->AddBoneNode( pBone, BindPosition, BindRotation, pPosFrames, pRotFrames );
//
//			std::stringstream s;
//			s << "Parent: " << pJoint->parentName << "\t Name:" << pJoint->name << "\t Bind Position:" << BindPosition.x << "," << BindPosition.y << "," << BindPosition.z << "\t Bind Rotation:" << BindRotation.x << "," << BindRotation.y << "," << BindRotation.z;
//
//			Log::Get().Write( GlyphString::ToUnicode( s.str() ) );
//			JointNodes[std::string(pJoint->name)] = pBone;
//		}
//
//		// Connect up the bones to form the skeleton.
//		for ( int i = 0; i < usJointCount; i++ )
//		{
//			ms3d_joint_t* pJoint = pModel->GetJoint( i );
//
//			Node3D* pParent = JointNodes[std::string(pJoint->parentName)];
//			Node3D* pChild = JointNodes[std::string(pJoint->name)];
//
//			// If the node has a parent, link them
//			if ( pParent && pChild )
//			{
//				pParent->AttachChild( pChild );
//				SkinnedBoneController* pParentController = (SkinnedBoneController*)pParent->GetController( 0 );
//				SkinnedBoneController* pChildController = (SkinnedBoneController*)pChild->GetController( 0 );
//				pChildController->SetParentBone( pParentController );
//			}
//
//			// If the node has no parent, link it to the root of the skinned actor (for connection
//			// to the scene graph).
//			if ( !pParent && pChild )
//			{
//				pActor->GetNode()->AttachChild( pChild );
//
//				pActor->GetGeometryEntity()->SetGeometry( pMesh );
//				pActor->GetGeometryEntity()->SetMaterial( MaterialGeneratorDX11::GenerateSkinnedSolid( *RendererDX11::Get() ) );
//				pChild->AttachChild( pActor->GetGeometryEntity() );
//
//				SkinnedBoneController* pChildController = (SkinnedBoneController*)pChild->GetController( 0 );
//				//pChildController->SetBindPosition( Vector3f( 0.0f, 0.0f, 0.0f ) );
//				//pChildController->SetBindRotation( Vector3f( 0.0f, 0.0f, 0.0f ) );
//
//				
//				pChildController->SetBindRotation( Vector3f( 1.5f + 6.28f, 1.5f + 6.28f, 0.0f + 6.28f ) );
//			}
//		}
//	}
//
//
//	delete pModel;
//
//	//pMesh->GenerateVertexDeclaration();
//	pMesh->LoadToBuffers();
//
//	return( pMesh );
//}
//--------------------------------------------------------------------------------
//void CGeometryLoaderDX9::removeWhiteSpace( std::wstring& s )
//{
//	unsigned int i = 0;
//	while ( i < s.length() )
//	{
//		switch ( s[i] )
//		{
//			case '\t':
//			case '\n':
//			case '\f':
//			case '\r':
//				s = s.substr( 0, i ) + s.substr( i+1, s.length() );
//				break;
//			default:
//				i++;
//		}
//	}
//}
//--------------------------------------------------------------------------------
//CGeometryDX9* CGeometryLoader::loadXFile( std::wstring filename )
//{
//	CGeometryDX9* pTriMesh = NULL;
//
//	ID3DXMesh* pMesh = NULL;
//	ID3DXBuffer* pAdjacency = NULL;
//	ID3DXBuffer* pMaterials = NULL;
//	ID3DXBuffer* pEffects = NULL;
//
//	DWORD Options = 0;
//	Options |= D3DXMESH_32BIT;
//	Options |= D3DXMESH_VB_MANAGED;
//	Options |= D3DXMESH_IB_MANAGED;
//
//	DWORD dMaterials = 0;
//
//	if ( D3D_OK == D3DXLoadMeshFromX( 
//		filename.c_str(),
//		Options,
//		CRenderer::GetRenderer()->GetDevice(),
//		&pAdjacency,
//		&pMaterials,
//		&pEffects,
//		&dMaterials,
//		&pMesh ) )
//	{
//		IDirect3DVertexBuffer9* pVB = NULL;
//		IDirect3DIndexBuffer9* pIB = NULL;
//		D3DVERTEXELEMENT9 pDeclaration[MAX_FVF_DECL_SIZE];
//	
//		DWORD dVertices = pMesh->GetNumVertices();
//		DWORD dFaces = pMesh->GetNumFaces();
//		DWORD dSize = pMesh->GetNumBytesPerVertex(); 
//
//		pMesh->GetVertexBuffer( &pVB );
//		pMesh->GetIndexBuffer( &pIB );
//		pMesh->GetDeclaration( pDeclaration );
//
//		pTriMesh = new CTriMesh();
//
//		std::ostringstream out;
//
//		int i = 0;
//		while ( pDeclaration[i].Stream != 0xff )
//		{
//			int iElementSize = 0;
//			if ( pDeclaration[i].Type == D3DDECLTYPE_FLOAT1 )
//				iElementSize = 1;
//			else if ( pDeclaration[i].Type == D3DDECLTYPE_FLOAT2 )
//				iElementSize = 2;
//			else if ( pDeclaration[i].Type == D3DDECLTYPE_FLOAT3 )
//				iElementSize = 3;
//			else if ( pDeclaration[i].Type == D3DDECLTYPE_FLOAT4 )
//				iElementSize = 4;
//
//			CVertexElement* pElement = new CVertexElement( iElementSize, dVertices );
//			pElement->m_Name = CGeometryLoader::getElementName( pDeclaration[i].Usage, pDeclaration[i].UsageIndex );
//			pElement->m_Type = (Glyph::VertexElementType)pDeclaration[i].Type;
//			pElement->m_Method = (Glyph::VertexElementMethod)pDeclaration[i].Method;
//			pElement->m_Usage = (Glyph::VertexElementUsage)pDeclaration[i].Usage;
//			pElement->m_UsageIndex = pDeclaration[i].UsageIndex;
//
//			BYTE* pbVertices;
//			pVB->Lock(0,0,(void**)(&pbVertices),0);
//
//			BYTE* pbStartVertex = pbVertices + pDeclaration[i].Offset;
//			BYTE* pbCurrentVertex = pbStartVertex;
//
//			for ( unsigned int v = 0; v < dVertices; v++ )
//			{
//				memcpy( (void*)((*pElement)[v]), pbCurrentVertex, pElement->size() * sizeof(float));
//				pbCurrentVertex += dSize;
//			}
//
//			pVB->Unlock();
//
//			pTriMesh->addElement( pElement );
//			i++;
//		}
//
//		TriangleIndices face;
//
//		unsigned int* pIndices = NULL;
//		pIndices = new unsigned int[dFaces*3];
//
//	    void* pbIndices = NULL;
//	    pIB->Lock( 0, dFaces * 3 * sizeof(unsigned int), &pbIndices, 0 );
//		memcpy( pIndices, pbIndices, dFaces * 3 * sizeof(unsigned int) );
//		pIB->Unlock();
//
//		for ( unsigned int i = 0; i < dFaces; i++ )
//		{
//			face.P1() = pIndices[3*i+0];
//			face.P2() = pIndices[3*i+1];
//			face.P3() = pIndices[3*i+2];
//			pTriMesh->addFace( face );
//		}
//
//		delete [] pIndices;
//
//		// create vertex elements depending on the vertex declaration *
//		// for each element, lock it and copy from the vertex buffer *
//		// add each element to the CTriMesh *
//		// for each face, create a TriangleIndices and add it to CTriMesh *
//		// clean up and release all temporary objects
//
//		pVB->Release();
//		pIB->Release();
//		pMesh->Release();
//	}
//
//
//	return( pTriMesh );
//}
//--------------------------------------------------------------------------------
//std::wstring CGeometryLoaderDX9::getElementName( int usage, int index )
//{
//	std::wstring name; 
//
//	switch( usage )
//	{
//		case D3DDECLUSAGE_POSITION:
//			name = "POSITION";
//			break;
//		case D3DDECLUSAGE_BLENDWEIGHT:
//			name = "BLENDWEIGHT";
//			break;
//		case D3DDECLUSAGE_BLENDINDICES:
//			name = "BLENDINDICES";
//			break;
//		case D3DDECLUSAGE_NORMAL:
//			name = "NORMAL";
//			break;
//		case D3DDECLUSAGE_PSIZE:
//			name = "PSIZE";
//			break;
//		case D3DDECLUSAGE_TEXCOORD:
//			switch( index )
//			{
//			case 0:
//				name = "TEXCOORD0";
//				break;
//			case 1:
//				name = "TEXCOORD1";
//				break;
//			case 2:
//				name = "TEXCOORD2";
//				break;
//			case 3:
//				name = "TEXCOORD3";
//				break;
//			case 4:
//				name = "TEXCOORD4";
//				break;
//			case 5:
//				name = "TEXCOORD5";
//				break;
//			case 6:
//				name = "TEXCOORD6";
//				break;
//			case 7:
//				name = "TEXCOORD7";
//				break;
//			}
//			break;
//		case D3DDECLUSAGE_TANGENT:
//			name = "TANGENT";
//			break;
//		case D3DDECLUSAGE_BINORMAL:
//			name = "BINORMAL";
//			break;
//		case D3DDECLUSAGE_TESSFACTOR:
//			name = "TESSFACTOR";
//			break;
//		case D3DDECLUSAGE_POSITIONT:
//			name = "TPOSITION";
//			break;
//		case D3DDECLUSAGE_COLOR:
//			switch( index )
//			{
//			case 0:
//				name = "DIFFUSE";
//				break;
//			case 1:
//				name = "SPECULAR";
//				break;
//			}
//			break;
//		case D3DDECLUSAGE_FOG:
//			name = "FOG";
//			break;
//		case D3DDECLUSAGE_DEPTH:
//			name = "DEPTH";
//			break;
//		case D3DDECLUSAGE_SAMPLE:
//			name = "SAMPLE";
//			break;
//
//	}
//
//	return( name );
//}


GeometryDX11* GeometryLoaderDX11::loadStanfordPlyFile( std::wstring filename, bool withAdjacency )
{
	// Load the contents of the file
	std::ifstream fin;

	// Open the file and read the MS3D header data
	fin.open( filename.c_str(), std::ios::in );

	if(!fin.is_open())
	{
		// signal error - bad filename?
		throw new std::exception( "Could not open file" );
	}

	// Parse the input
	std::string txt;

	// Read in header
	std::getline(fin, txt);

	if( 0 != txt.compare( "ply" ) )
	{
		// signal error - not a PLY format file
		throw new std::exception( "File does not contain the correct header - 'PLY' expected." );
	}

	std::getline(fin, txt);

	if( 0 != txt.compare( "format ascii 1.0" ) )
	{
		// signal error - not a format of PLY that this code supports
		throw new std::exception( "File is not correct format - ASCII 1.0 expected." );
	}

	std::vector< PlyElementDesc > elements;

	// Read in the rest of the header
	while(fin.is_open() && !fin.eof())
	{
		// Grab the next line of the header
		std::getline(fin, txt);

		// If we're at the end then stop processing
		if(0 == txt.compare("end_header"))
		{
			break;
		}
		// If this line is a comment, skip to the next line
		else if(0 == txt.compare(0, 7, "comment"))
		{
			continue;
		}
		// If this line is an element, process it
		else if(0 == txt.compare(0, 7, "element"))
		{
			elements.push_back(ParsePLYElementHeader( txt, fin ));
		}
		// Otherwise, wtf?
		else
		{
			throw new std::exception("File header contains unexpected line beginning");
		}
	}

	// Read all the raw data
	for( std::vector< PlyElementDesc >::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		(*it).data = ReadPLYElementData(fin, *it);
	}

	// Create a resource to contain the geometry
	GeometryDX11* pMesh = new GeometryDX11();

	// Convert data to D3D11 format
	int elemIdx = -1;

	// Pull out all the vertex data
	if(-1 < (elemIdx = FindPlyElementIndex(elements, "vertex")))
	{
		PlyElementDesc d = elements.at( elemIdx );
		
		// Has positions?
		int xIdx = FindPlyElementPropertyIndex( d.dataFormat, "x" );
		int yIdx = FindPlyElementPropertyIndex( d.dataFormat, "y" );
		int zIdx = FindPlyElementPropertyIndex( d.dataFormat, "z" );

		if ((-1 != xIdx) && (-1 != yIdx) && (-1 != zIdx))
		{
			VertexElementDX11 *pPositions = new VertexElementDX11( 3, d.elementCount );
			pPositions->m_SemanticName = VertexElementDX11::PositionSemantic;
			pPositions->m_uiSemanticIndex = 0;
			pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
			pPositions->m_uiInputSlot = 0;
			pPositions->m_uiAlignedByteOffset = 0;
			pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			pPositions->m_uiInstanceDataStepRate = 0;

			Vector3f* pRawPos = pPositions->Get3f( 0 );

			for(int v = 0; v < d.elementCount; ++v)
			{
				void** raw = d.data.at(v);

				float x = *reinterpret_cast<float*>(raw[xIdx]);
				float y = *reinterpret_cast<float*>(raw[yIdx]);
				float z = *reinterpret_cast<float*>(raw[zIdx]);

				pRawPos[v] = Vector3f( x, y, z );
			}

			pMesh->AddElement( pPositions );
		}

		// Has normals?
		int nxIdx = FindPlyElementPropertyIndex( d.dataFormat, "nx" );
		int nyIdx = FindPlyElementPropertyIndex( d.dataFormat, "ny" );
		int nzIdx = FindPlyElementPropertyIndex( d.dataFormat, "nz" );

		if ((-1 != nxIdx) && (-1 != nyIdx) && (-1 != nzIdx))
		{
			VertexElementDX11 *pNormals = new VertexElementDX11( 3, d.elementCount );
			pNormals->m_SemanticName = VertexElementDX11::NormalSemantic;
			pNormals->m_uiSemanticIndex = 0;
			pNormals->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
			pNormals->m_uiInputSlot = 0;
			pNormals->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			pNormals->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			pNormals->m_uiInstanceDataStepRate = 0;

			Vector3f* pRawNorms = pNormals->Get3f( 0 );

			for(int v = 0; v < d.elementCount; ++v)
			{
				void** raw = d.data.at(v);

				float x = *reinterpret_cast<float*>(raw[nxIdx]);
				float y = *reinterpret_cast<float*>(raw[nyIdx]);
				float z = *reinterpret_cast<float*>(raw[nzIdx]);

				pRawNorms[v] = Vector3f( x, y, z );
			}

			pMesh->AddElement( pNormals );
		}
	}
	else
	{
		throw new std::exception("Expected a 'vertex' element, but not found");
	}

	// Pull out all the face index data
	if(-1 < (elemIdx = FindPlyElementIndex(elements, "face")))
	{
		PlyElementDesc d = elements.at( elemIdx );

		// Firstly, assert that the format is correct
		if((1 != d.dataFormat.size()) && d.dataFormat.at(0).isList && (0 == d.dataFormat.at(0).type.compare("uint")))
		{
			// Expect a single list of integers
			throw new std::exception("Expected 'face' to be a single list of integers per-face");
		}

		// Secondly, assert that each list is of the same dimension
		int faceSize = -1;
		for(int f = 0; f < d.elementCount; ++f)
		{
			void** raw = d.data.at(f);
			PlyDataArray<int>* idxs = reinterpret_cast<PlyDataArray<int>*>(raw[0]);
			
			if( -1 == faceSize)
				faceSize = idxs->length;
			else if(faceSize != idxs->length)
				throw new std::exception("Expected each face to have the same number of indexes");
		}

		if(withAdjacency)
		{
			pMesh->SetPrimitiveType( (D3D11_PRIMITIVE_TOPOLOGY)(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST + ((2*faceSize) - 1)) );

			// Grab all of the faces so we can search for adjacency
			int* pRaw = new int[d.elementCount * faceSize];

			int pRawIdx = 0;

			for(int f = 0; f < d.elementCount; ++f)
			{
				void** raw = d.data.at(f);
				PlyDataArray<int>* idxs = reinterpret_cast<PlyDataArray<int>*>(raw[0]);

				for(unsigned int fi = 0; fi < idxs->length; ++fi)
					pRaw[pRawIdx++] = idxs->data[fi];
			}

			// We can now go and add the actual indices
			for(int f = 0; f < (d.elementCount * faceSize); f+=3)
			{
				pMesh->AddIndex( pRaw[f + 0] );
				pMesh->AddIndex( pRaw[f + 1] );
				pMesh->AddIndex( pRaw[f + 2] );

				// We now need to find an adjacency for each
				// edge where possible
				int a0 = FindAdjacentIndex( pRaw[f + 0], pRaw[f + 1], pRaw[f + 2], pRaw, d.elementCount * faceSize );
				int a1 = FindAdjacentIndex( pRaw[f + 1], pRaw[f + 2], pRaw[f + 0], pRaw, d.elementCount * faceSize );
				int a2 = FindAdjacentIndex( pRaw[f + 2], pRaw[f + 0], pRaw[f + 1], pRaw, d.elementCount * faceSize );

				std::wstringstream out;
				out << "Actual indices <" << pRaw[f+0] << ", " << pRaw[f+1] << ", " << pRaw[f+2] << "> have adjacency <" << a0 << ", " << a1 << ", " << a2 << ">.";
				OutputDebugString( out.str().c_str() );
				OutputDebugString( L"\n" );

				pMesh->AddIndex( a0 );
				pMesh->AddIndex( a1 );
				pMesh->AddIndex( a2 );
			}

			delete[] pRaw;
		}
		else
		{
			// Thirdly, can now set the appropriate topology
			pMesh->SetPrimitiveType( (D3D11_PRIMITIVE_TOPOLOGY)(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST + (faceSize - 1)) );

			// Finally, extract this data
			for(int f = 0; f < d.elementCount; ++f)
			{
				void** raw = d.data.at(f);
				PlyDataArray<int>* idxs = reinterpret_cast<PlyDataArray<int>*>(raw[0]);

				for(unsigned int fi = 0; fi < idxs->length; ++fi)
					pMesh->AddIndex( idxs->data[fi] );
			}
		}
	}
	else
	{
		throw new std::exception("Expected a 'face' element, but not found");
	}

	// Push into renderable resource
	pMesh->LoadToBuffers( );

	// Release all intermediary memory
	for( std::vector< PlyElementDesc >::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		PlyElementDesc d = *it;
		for(int e = 0; e < d.elementCount; ++e)
		{
			void** raw = d.data.at(e);

			if(d.dataFormat.at(0).isList)
			{
				PlyDataArray<void*>* rawArray = reinterpret_cast<PlyDataArray<void*>*>(raw[0]);
				SAFE_DELETE_ARRAY( rawArray->data );
				SAFE_DELETE(raw[0]);
			}
			else
			{
				SAFE_DELETE(raw[0]);
			}
		}
	}

	// Return to caller
	return pMesh;
}

int GeometryLoaderDX11::FindAdjacentIndex( int edgeStart, int edgeEnd, int triV, int* pRaw, int rawLen)
{
	for(int f = 0; f < rawLen; f+=3)
	{
		int esIdx = -1;
		for( int i = 0; i < 3; ++i ) { if(pRaw[f+i]==edgeStart) esIdx = i; }

		int eeIdx = -1;
		for( int i = 0; i < 3; ++i ) { if(pRaw[f+i]==edgeEnd) eeIdx = i; }

		if((-1!=esIdx)&&(-1!=eeIdx))
		{
			int oIdx = -1;
			for(int i = 0; i < 3; ++i) { if((i!=esIdx) && (i!=eeIdx)) oIdx = i; }

			if(pRaw[f+oIdx]!=triV)
				return pRaw[f + oIdx];
		}
	}

	return edgeStart;
}

GeometryLoaderDX11::PlyElementDesc GeometryLoaderDX11::ParsePLYElementHeader(std::string headerLine, std::ifstream& input)
{
	GeometryLoaderDX11::PlyElementDesc desc;
	std::string txt;

	// Parse the header line
	// "element <name> <count>"
	int split = headerLine.find_first_of(' ', 8);
	desc.name = headerLine.substr(8, split - 8);
		
	split = headerLine.rfind( ' ' );
	std::istringstream elemCount(headerLine.substr(split, headerLine.length() - split));
	elemCount >> desc.elementCount;

	// Parse any attached properties
	while(input.is_open() && !input.eof())
	{
		std::getline( input, txt );

		if(0 == txt.compare(0, 13, "property list"))
		{
			// Parse this property list declaration
			desc.dataFormat.push_back(ParsePLYElementPropertyList(txt.substr(14, txt.length() - 14)));
		}
		else if(0 == txt.compare(0, 8, "property"))
		{
			// Parse this property declaration
			desc.dataFormat.push_back(ParsePLYElementProperty(txt.substr(9, txt.length() - 9)));
		}
		else
		{
			// At this point we'll also have read a line too far so
			// need to "unread" it to avoid breaking remaining parsing.
			input.putback('\n');
			for(int i = -1 + txt.length(); i >= 0; i--)
				input.putback(txt.at(i));
			// (there must be a better way, no?!?)
			break;
		}
	}

	return desc;
}

GeometryLoaderDX11::PlyElementPropertyDeclaration GeometryLoaderDX11::ParsePLYElementProperty(std::string desc)
{
	// <type> <name>
	GeometryLoaderDX11::PlyElementPropertyDeclaration decl;
	decl.isList = false;

	int split = desc.find(' ');

	decl.type = desc.substr(0, split);
	decl.name = desc.substr(split + 1, desc.length() - (split + 1));

	return decl;
}

GeometryLoaderDX11::PlyElementPropertyDeclaration GeometryLoaderDX11::ParsePLYElementPropertyList(std::string desc)
{
	// <length_type> <element_type> <name>
	GeometryLoaderDX11::PlyElementPropertyDeclaration decl;
	decl.isList = true;

	int split = desc.find(' ');
	decl.listLengthType = desc.substr(0, split);

	decl.type = desc.substr(split + 1, desc.rfind(' ') - (split + 1));

	split = desc.rfind(' ') + 1;
	decl.name = desc.substr(split, desc.length() - split);

	return decl;
}

std::vector<void**> GeometryLoaderDX11::ReadPLYElementData(std::ifstream& input, const GeometryLoaderDX11::PlyElementDesc& desc)
{
	std::vector<void**> raw;

	for(int i = 0; i < desc.elementCount; ++i)
	{
		std::string txt;
		std::getline(input, txt);

		raw.push_back(ParsePLYElementData(txt, desc.dataFormat));
	}

	return raw;
}

void** GeometryLoaderDX11::ParsePLYElementData(std::string text, const std::vector<PlyElementPropertyDeclaration>& desc)
{
	void** parsed;

	parsed = new void*[desc.size()];

	std::vector<std::string> tokens;
	std::istringstream is (text);
	std::string tmps;
    while (is.good()) {
        is >> tmps;
		tokens.push_back(tmps);
    }


	unsigned int e = 0;
	for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if( e >= desc.size())
			break;

		if(desc[e].isList)
		{
			// Read this as length
			int arrLen = 0;

			arrLen = ExtractDataVal<int>(*it);

			// Size up the type
			if(0 == desc[e].type.compare("char"))
			{
				parsed[e] = ExtractDataPtrArray<char>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("uchar"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned char>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("short"))
			{
				parsed[e] = ExtractDataPtrArray<short>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("ushort"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned short>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("int"))
			{
				parsed[e] = ExtractDataPtrArray<int>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("uint"))
			{
				parsed[e] = ExtractDataPtrArray<unsigned int>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("float"))
			{
				parsed[e] = ExtractDataPtrArray<float>(arrLen, it);
			}
			else if(0 == desc[e].type.compare("double"))
			{
				parsed[e] = ExtractDataPtrArray<double>(arrLen, it);
			}
			else
			{
				// wtf?
			}
		}
		else
		{
			if(0 == desc[e].type.compare("char"))
			{
				parsed[e] = ExtractDataPtr<char>(*it);
			}
			else if(0 == desc[e].type.compare("uchar"))
			{
				parsed[e] = ExtractDataPtr<unsigned char>(*it);
			}
			else if(0 == desc[e].type.compare("short"))
			{
				parsed[e] = ExtractDataPtr<short>(*it);
			}
			else if(0 == desc[e].type.compare("ushort"))
			{
				parsed[e] = ExtractDataPtr<unsigned short>(*it);
			}
			else if(0 == desc[e].type.compare("int"))
			{
				parsed[e] = ExtractDataPtr<int>(*it);
			}
			else if(0 == desc[e].type.compare("uint"))
			{
				parsed[e] = ExtractDataPtr<unsigned int>(*it);
			}
			else if(0 == desc[e].type.compare("float"))
			{
				parsed[e] = ExtractDataPtr<float>(*it);
			}
			else if(0 == desc[e].type.compare("double"))
			{
				parsed[e] = ExtractDataPtr<double>(*it);
			}
			else
			{
				// wtf?
			}
		}

		++e;
	}

	return parsed;
}

template<typename T> T* GeometryLoaderDX11::ExtractDataPtr(std::string input)
{
	T* t = new T;

	std::istringstream iss(input);

	iss >> *t;

	return t;
}

template<typename T> T GeometryLoaderDX11::ExtractDataVal(std::string input)
{
	T t;

	std::istringstream iss(input);

	iss >> t;

	return t;
}

template<typename T> GeometryLoaderDX11::PlyDataArray<T>* GeometryLoaderDX11::ExtractDataPtrArray(int length, std::vector<std::string>::iterator iterator)
{
	PlyDataArray<T>* t = new PlyDataArray<T>;
	t->length = length;
	t->data = new T[length];

	for(int i = 0; i < length; ++i)
	{
		std::istringstream iss(*(++iterator));
		iss >> t->data[i];
	}

	return t;
}



int GeometryLoaderDX11::FindPlyElementIndex(std::vector<PlyElementDesc> elems, std::string name)
{
	for(unsigned int idx = 0; idx < elems.size(); ++idx)
		if(0 == elems.at(idx).name.compare(name))
			return idx;

	return -1;
}

int GeometryLoaderDX11::FindPlyElementPropertyIndex(std::vector<PlyElementPropertyDeclaration> elems, std::string name)
{
	for(unsigned int idx = 0; idx < elems.size(); ++idx)
		if(0 == elems.at(idx).name.compare(name))
			return idx;

	return -1;
}