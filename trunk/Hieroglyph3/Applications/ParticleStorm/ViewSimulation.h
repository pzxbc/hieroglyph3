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
// ViewSimulation
//
//--------------------------------------------------------------------------------
#ifndef ViewSimulation_h
#define ViewSimulation_h
//--------------------------------------------------------------------------------
#include "IRenderView.h"
//--------------------------------------------------------------------------------
namespace Glyph3
{
	class Entity3D;

	struct Particle
	{
		Vector3f position;
		Vector3f direction;
		Vector4f status;
	};

	class ViewSimulation : public IRenderView
	{
	public:
		ViewSimulation( RendererDX11& Renderer, int SizeX );

		virtual void Update( float fTime );
		virtual void PreDraw( RendererDX11* pRenderer );
		virtual void Draw( PipelineManagerDX11* pPipelineManager, ParameterManagerDX11* pParamManager );

		virtual void SetRenderParams( ParameterManagerDX11* pParamManager );
		virtual void SetUsageParams( ParameterManagerDX11* pParamManager );


		virtual ~ViewSimulation();

	protected:

		int m_iParticleCount;
		ResourcePtr ParticleStateBuffers[2];
		RenderEffectDX11*	pParticleUpdate;
		bool bOneTimeInit;
	};
};
//--------------------------------------------------------------------------------
#endif // ViewSimulation_h