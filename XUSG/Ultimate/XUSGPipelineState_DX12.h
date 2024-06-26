//--------------------------------------------------------------------------------------
// Copyright (c) XU, Tianchen. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "XUSGUltimate.h"
#include "Core/XUSGInputLayout_DX12.h"

namespace XUSG
{
	namespace Ultimate
	{
		struct PipelineDesc
		{
			PipelineLayout Layout;
			Blob Shaders[Shader::Stage::NUM_STAGE];
			const Graphics::Blend* pBlend;
			const Graphics::Rasterizer* pRasterizer;
			const Graphics::DepthStencil* pDepthStencil;
			const InputLayout* pInputLayout;
			Blob CachedPipeline;
			PrimitiveTopologyType PrimTopologyType;
			uint8_t	NumRenderTargets;
			Format RTVFormats[8];
			Format	DSVFormat;
			uint8_t	SampleCount;
			uint8_t SampleQuality;
			uint32_t SampleMask;
			uint8_t IBStripCutValue;
			uint32_t NodeMask;
			PipelineFlag Flags;
			uint8_t NumViewInstances;
			ViewInstance ViewInstances[4];
			ViewInstanceFlag ViewInstanceFlags;
		};

		class State_DX12 :
			public virtual State
		{
		public:
			State_DX12();
			virtual ~State_DX12();

			void SetPipelineLayout(const PipelineLayout& layout);
			void SetShader(Shader::Stage stage, const Blob& shader);
			void SetCachedPipeline(const Blob& cachedPipeline);
			void SetNodeMask(uint32_t nodeMask);
			void SetFlags(PipelineFlag flag);

			void OMSetBlendState(const Graphics::Blend* pBlend, uint32_t sampleMask = UINT_MAX);
			void RSSetState(const Graphics::Rasterizer* pRasterizer);
			void DSSetState(const Graphics::DepthStencil* pDepthStencil);

			void OMSetBlendState(Graphics::BlendPreset preset, PipelineLib* pPipelineLib,
				uint8_t numColorRTs = 1, uint32_t sampleMask = UINT_MAX);
			void RSSetState(Graphics::RasterizerPreset preset, PipelineLib* pPipelineLib);
			void DSSetState(Graphics::DepthStencilPreset preset, PipelineLib* pPipelineLib);

			void IASetInputLayout(const InputLayout* pLayout);
			void IASetPrimitiveTopologyType(PrimitiveTopologyType type);
			void IASetIndexBufferStripCutValue(IBStripCutValue ibStripCutValue);

			void OMSetNumRenderTargets(uint8_t n);
			void OMSetRTVFormat(uint8_t i, Format format);
			void OMSetRTVFormats(const Format* formats, uint8_t n);
			void OMSetDSVFormat(Format format);
			void OMSetSample(uint8_t count, uint8_t quality = 0);

			void SetNumViewInstances(uint8_t n, ViewInstanceFlag flags);
			void SetViewInstance(uint8_t i, const ViewInstance& viewInstance);
			void SetViewInstances(const ViewInstance* viewInstances, uint8_t n, ViewInstanceFlag flags);

			Pipeline CreatePipeline(PipelineLib* pPipelineLib, const wchar_t* name = nullptr) const;
			Pipeline GetPipeline(PipelineLib* pPipelineLib, const wchar_t* name = nullptr) const;

			PipelineLayout GetPipelineLayout() const;
			Blob GetShader(Shader::Stage stage) const;
			Blob GetCachedPipeline() const;
			uint32_t GetNodeMask() const;
			PipelineFlag GetFlags() const;

			uint32_t OMGetSampleMask() const;
			const Graphics::Blend* OMGetBlendState() const;
			const Graphics::Rasterizer* RSGetState() const;
			const Graphics::DepthStencil* DSGetState() const;

			const InputLayout* IAGetInputLayout() const;
			PrimitiveTopologyType IAGetPrimitiveTopologyType() const;
			IBStripCutValue IAGetIndexBufferStripCutValue() const;

			uint8_t OMGetNumRenderTargets() const;
			Format OMGetRTVFormat(uint8_t i) const;
			Format OMGetDSVFormat() const;
			uint8_t OMGetSampleCount() const;
			uint8_t OMGetSampleQuality() const;

			uint8_t GetNumViewInstances(uint8_t n, ViewInstanceFlag flags) const;
			ViewInstanceFlag GetViewInstanceFlags() const;
			const ViewInstance& GetViewInstance(uint8_t i) const;

			const std::string& GetKey() const;

		protected:
			PipelineDesc* m_pKey;
			std::string m_key;
		};

		class PipelineLib_DX12 :
			public virtual PipelineLib
		{
		public:
			PipelineLib_DX12();
			PipelineLib_DX12(const Device* pDevice);
			virtual ~PipelineLib_DX12();

			void SetDevice(const Device* pDevice);
			void SetPipeline(const State* pState, const Pipeline& pipeline);

			void SetInputLayout(uint32_t index, const InputElement* pElements, uint32_t numElements);
			const InputLayout* GetInputLayout(uint32_t index) const;
			const InputLayout* CreateInputLayout(const InputElement* pElements, uint32_t numElements);

			Pipeline CreatePipeline(const State* pState, const wchar_t* name = nullptr);
			Pipeline GetPipeline(const State* pState, const wchar_t* name = nullptr);

			const Graphics::Blend* GetBlend(Graphics::BlendPreset preset, uint8_t numColorRTs = 1);
			const Graphics::Rasterizer* GetRasterizer(Graphics::RasterizerPreset preset);
			const Graphics::DepthStencil* GetDepthStencil(Graphics::DepthStencilPreset preset);

		protected:
			Pipeline createPipeline(const std::string& key, const wchar_t* name);
			Pipeline getPipeline(const std::string& key, const wchar_t* name);

			static void getStream(CD3DX12_PIPELINE_STATE_STREAM2* pStream, void* pInputElements, const std::string& key);
			static void getStream(CD3DX12_PIPELINE_STATE_STREAM3* pStream, void* pInputElements, const std::string& key);
			static void getStream(CD3DX12_PIPELINE_STATE_STREAM4* pStream, void* pInputElements, const std::string& key);
			static void getStream(CD3DX12_PIPELINE_STATE_STREAM5* pStream, void* pInputElements, const std::string& key);

			com_ptr<ID3D12Device> m_device;

			InputLayoutLib_DX12 m_inputLayoutLib;

			std::unordered_map<std::string, com_ptr<ID3D12PipelineState>> m_pipelines;
			std::unique_ptr<Graphics::Blend>		m_blends[Graphics::NUM_BLEND_PRESET];
			std::unique_ptr<Graphics::Rasterizer>	m_rasterizers[Graphics::NUM_RS_PRESET];
			std::unique_ptr<Graphics::DepthStencil>	m_depthStencils[Graphics::NUM_DS_PRESET];

			std::function<Graphics::Blend(uint8_t)>	m_pfnBlends[Graphics::NUM_BLEND_PRESET];
			std::function<Graphics::Rasterizer()>	m_pfnRasterizers[Graphics::NUM_RS_PRESET];
			std::function<Graphics::DepthStencil()>	m_pfnDepthStencils[Graphics::NUM_DS_PRESET];
		};
	}
}
