//--------------------------------------------------------------------------------------
// Copyright (c) XU, Tianchen. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "XUSGUltimate-EZ.h"

namespace XUSG
{
	namespace Ultimate
	{
		namespace EZ
		{
			class CommandList_DX12 :
				virtual public CommandList,
				virtual public Ultimate::CommandList_DX12,
				virtual public XUSG::EZ::CommandList_DX12
			{
			public:
				CommandList_DX12();
				CommandList_DX12(Ultimate::CommandList* pCommandList,
					uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize,
					const uint32_t maxSamplers[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxCbvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxSrvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxUavsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxCbvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxSrvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxUavSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t max32BitConstants[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSlots[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					uint32_t slotExt = 0, uint32_t spaceExt = 0x7FFF0ADE);
				virtual ~CommandList_DX12();

				bool Create(Ultimate::CommandList* pCommandList,
					uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize,
					const uint32_t maxSamplers[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxCbvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxSrvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxUavsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxCbvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxSrvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxUavSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t max32BitConstants[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSlots[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					uint32_t slotExt = 0, uint32_t spaceExt = 0x7FFF0ADE);
				bool Create(const Device* pDevice, void* pHandle,
					uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize,
					const uint32_t maxSamplers[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxCbvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxSrvsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t* pMaxUavsEachSpace[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxCbvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxSrvSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t maxUavSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t max32BitConstants[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSlots[Shader::Stage::NUM_STAGE] = nullptr,
					const uint32_t constantSpaces[Shader::Stage::NUM_STAGE] = nullptr,
					uint32_t slotExt = 0, uint32_t spaceExt = 0x7FFF0ADE,
					const wchar_t* name = nullptr);

				void SetSamplePositions(uint8_t numSamplesPerPixel, uint8_t numPixels, SamplePosition* pPositions) const
				{
					Ultimate::CommandList_DX12::SetSamplePositions(numSamplesPerPixel, numPixels, pPositions);
				}

				void ResolveSubresourceRegion(Resource* pDstResource, uint32_t dstSubresource,
					uint32_t dstX, uint32_t dstY, Resource* pSrcResource, uint32_t srcSubresource,
					const RectRange& srcRect, Format format, ResolveMode resolveMode);

				void RSSetShadingRate(ShadingRate baseShadingRate, const ShadingRateCombiner* pCombiners) const
				{
					Ultimate::CommandList_DX12::RSSetShadingRate(baseShadingRate, pCombiners);
				}

				void RSSetShadingRateImage(Resource* pShadingRateImage);

				using XUSG::EZ::CommandList_DX12::SetGraphicsPipelineState;
				void SetGraphicsPipelineState(const Pipeline& pipelineState, const State* pState = nullptr);
				void OMSetBlendState(const Graphics::Blend* pBlend, uint32_t sampleMask = UINT_MAX);
				void OMSetBlendState(Graphics::BlendPreset preset, uint8_t numColorRTs = 1, uint32_t sampleMask = UINT_MAX);
				void OMSetSample(uint8_t count, uint8_t quality = 0);
				void RSSetState(const Graphics::Rasterizer* pRasterizer);
				void RSSetState(Graphics::RasterizerPreset preset);
				void DSSetState(const Graphics::DepthStencil* pDepthStencil);
				void DSSetState(Graphics::DepthStencilPreset preset);
				void SetGraphicsShader(Shader::Stage stage, const Blob& shader);
				void SetMeshGraphicsShader(Shader::Stage stage, const Blob& shader);
				void SetMeshGraphics32BitConstant(Shader::Stage stage, uint32_t srcData, uint32_t destOffsetIn32BitValues = 0) const;
				void SetMeshGraphics32BitConstants(Shader::Stage stage, uint32_t num32BitValuesToSet, const void* pSrcData, uint32_t destOffsetIn32BitValues = 0) const;
				void SetGraphicsNodeMask(uint32_t nodeMask);
				void DispatchMesh(uint32_t ThreadGroupCountX, uint32_t ThreadGroupCountY, uint32_t ThreadGroupCountZ);
				void DispatchMeshIndirect(const CommandLayout* pCommandlayout,
					uint32_t maxCommandCount,
					Resource* pArgumentBuffer,
					uint64_t argumentBufferOffset = 0,
					Resource* pCountBuffer = nullptr,
					uint64_t countBufferOffset = 0);
				void OMSetRenderTargets(
					uint32_t numRenderTargets,
					const XUSG::EZ::ResourceView* pRenderTargetViews,
					const XUSG::EZ::ResourceView* pDepthStencilView = nullptr);

				const XUSG::PipelineLayout& GetMSPipelineLayout() const;

				uint32_t GetMSConstantParamIndex(Shader::Stage stage) const;

				Ultimate::CommandList* AsUltimateCommandList() { return dynamic_cast<Ultimate::CommandList*>(this); }

			protected:
				enum StageIndex : uint8_t
				{
					PS,
					MS,
					AS,

					NUM_STAGE
				};

				bool init(Ultimate::CommandList* pCommandList, uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize);
				bool createMeshShaderPipelineLayouts(
					const uint32_t maxSamplers[Shader::Stage::NUM_STAGE],
					const uint32_t* pMaxCbvsEachSpace[Shader::Stage::NUM_STAGE],
					const uint32_t* pMaxSrvsEachSpace[Shader::Stage::NUM_STAGE],
					const uint32_t* pMaxUavsEachSpace[Shader::Stage::NUM_STAGE],
					const uint32_t maxCbvSpaces[Shader::Stage::NUM_STAGE],
					const uint32_t maxSrvSpaces[Shader::Stage::NUM_STAGE],
					const uint32_t maxUavSpaces[Shader::Stage::NUM_STAGE],
					const uint32_t max32BitConstants[Shader::Stage::NUM_STAGE],
					const uint32_t constantSlots[Shader::Stage::NUM_STAGE],
					const uint32_t constantSpaces[Shader::Stage::NUM_STAGE],
					uint32_t slotExt, uint32_t spaceExt);

				void predispatchMesh();

				const Shader::Stage& getShaderStage(uint8_t index) const;
				StageIndex getShaderStageIndex(Shader::Stage stage) const;

				PipelineLib::uptr m_meshShaderPipelineLib;

				XUSG::PipelineLayout m_pipelineLayout;

				State::uptr m_meshShaderState;

				std::vector<uint32_t> m_meshShaderSpaceToParamIndexMap[NUM_STAGE][CbvSrvUavTypes];

				uint32_t m_meshShaderConstantParamIndices[NUM_STAGE];
			};
		}
	}
}
