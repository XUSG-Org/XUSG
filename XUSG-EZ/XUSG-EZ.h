//--------------------------------------------------------------------------------------
// Copyright (c) XU, Tianchen. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Core/XUSG.h"

namespace XUSG
{
	namespace EZ
	{
		struct ResourceView
		{
			Resource* pResource;
			Descriptor view;
			std::vector<uint32_t> subresources;
		};

		//--------------------------------------------------------------------------------------
		// Command list
		//--------------------------------------------------------------------------------------
		class DLL_INTERFACE CommandList :
			public virtual XUSG::CommandList
		{
		public:
			//CommandList();
			virtual ~CommandList() {}

			virtual bool Create(const Device* pDevice, XUSG::CommandList* pCommandList, uint32_t samplerPoolSize, uint32_t cbvSrvUavPoolSize,
				uint32_t maxSamplers = 16, const uint32_t* pMaxCbvsEachSpace = nullptr, const uint32_t* pMaxSrvsEachSpace = nullptr,
				const uint32_t* pMaxUavsEachSpace = nullptr, uint32_t maxCbvSpaces = 1, uint32_t maxSrvSpaces = 1, uint32_t maxUavSpaces = 1) = 0;
			virtual bool Close() const = 0;
			virtual bool Reset(const CommandAllocator* pAllocator, const Pipeline& initialState) const = 0;

			virtual void ClearState(const Pipeline& initialState) const = 0;
			virtual void Draw(
				uint32_t vertexCountPerInstance,
				uint32_t instanceCount,
				uint32_t startVertexLocation,
				uint32_t startInstanceLocation) = 0;
			virtual void DrawIndexed(
				uint32_t indexCountPerInstance,
				uint32_t instanceCount,
				uint32_t startIndexLocation,
				int32_t baseVertexLocation,
				uint32_t startInstanceLocation) = 0;
			virtual void Dispatch(
				uint32_t threadGroupCountX,
				uint32_t threadGroupCountY,
				uint32_t threadGroupCountZ) = 0;
			virtual void CopyBufferRegion(const Resource* pDstBuffer, uint64_t dstOffset,
				const Resource* pSrcBuffer, uint64_t srcOffset, uint64_t numBytes) const = 0;
			virtual void CopyTextureRegion(const TextureCopyLocation& dst,
				uint32_t dstX, uint32_t dstY, uint32_t dstZ,
				const TextureCopyLocation& src, const BoxRange* pSrcBox = nullptr) const = 0;
			virtual void CopyResource(const Resource* pDstResource, const Resource* pSrcResource) const = 0;
			virtual void CopyTiles(const Resource* pTiledResource, const TiledResourceCoord* pTileRegionStartCoord,
				const TileRegionSize* pTileRegionSize, const Resource* pBuffer, uint64_t bufferStartOffsetInBytes,
				TileCopyFlag flags) const = 0;
			virtual void ResolveSubresource(const Resource* pDstResource, uint32_t dstSubresource,
				const Resource* pSrcResource, uint32_t srcSubresource, Format format) const = 0;
			virtual void IASetPrimitiveTopology(PrimitiveTopology primitiveTopology) = 0;
			virtual void RSSetViewports(uint32_t numViewports, const Viewport* pViewports) const = 0;
			virtual void RSSetScissorRects(uint32_t numRects, const RectRange* pRects) const = 0;
			virtual void OMSetBlendFactor(const float blendFactor[4]) const = 0;
			virtual void OMSetStencilRef(uint32_t stencilRef) const = 0;
			virtual void SetPipelineState(const Pipeline& pipelineState) = 0;
			virtual void ExecuteBundle(const CommandList* pCommandList) const = 0;
			virtual void SetGraphicsSamplerStates(uint32_t startBinding, uint32_t numSamplers, const SamplerPreset* pSamplerStates) = 0;
			virtual void SetGraphicsResources(Shader::Stage stage, DescriptorType descriptorType, uint32_t startBinding,
				uint32_t numResources, const ResourceView* pResourceViews, uint32_t space = 0) = 0;
			virtual void SetComputeSamplerStates(uint32_t startBinding, uint32_t numSamplers, const SamplerPreset* pSamplerStates) = 0;
			virtual void SetComputeResources(DescriptorType descriptorType, uint32_t startBinding,
				uint32_t numResources, const ResourceView* pResourceViews, uint32_t space = 0) = 0;
			virtual void IASetIndexBuffer(const IndexBufferView& view) const = 0;
			virtual void IASetVertexBuffers(uint32_t startSlot, uint32_t numViews, const VertexBufferView* pViews) const = 0;
			virtual void SOSetTargets(uint32_t startSlot, uint32_t numViews, const StreamOutBufferView* pViews) const = 0;
			virtual void OMSetRenderTargets(
				uint32_t numRenderTargets,
				const ResourceView* pRenderTargetViews,
				const ResourceView* pDepthStencilView = nullptr) = 0;
			virtual void ClearDepthStencilView(const Descriptor& depthStencilView, ClearFlag clearFlags,
				float depth, uint8_t stencil = 0, uint32_t numRects = 0, const RectRange* pRects = nullptr) const = 0;
			virtual void ClearRenderTargetView(const Descriptor& renderTargetView, const float colorRGBA[4],
				uint32_t numRects = 0, const RectRange* pRects = nullptr) const = 0;
			virtual void DiscardResource(const Resource* pResource, uint32_t numRects, const RectRange* pRects,
				uint32_t firstSubresource, uint32_t numSubresources) const = 0;
			virtual void BeginQuery(const QueryPool& queryPool, QueryType type, uint32_t index) const = 0;
			virtual void EndQuery(const QueryPool& queryPool, QueryType type, uint32_t index) const = 0;
			virtual void ResolveQueryData(const QueryPool& queryPool, QueryType type, uint32_t startIndex,
				uint32_t numQueries, const Resource* pDstBuffer, uint64_t alignedDstBufferOffset) const = 0;
			virtual void SetPredication(const Resource* pBuffer, uint64_t alignedBufferOffset, bool opEqualZero)const = 0;
			virtual void SetMarker(uint32_t metaData, const void* pData, uint32_t size) const = 0;
			virtual void BeginEvent(uint32_t metaData, const void* pData, uint32_t size) const = 0;
			virtual void EndEvent() = 0;
			virtual void ExecuteIndirect(const CommandLayout* pCommandlayout, uint32_t maxCommandCount,
				const Resource* pArgumentBuffer, uint64_t argumentBufferOffset = 0,
				const Resource* pCountBuffer = nullptr, uint64_t countBufferOffset = 0) = 0;

			virtual void ResetDescriptorPool(DescriptorPoolType type) = 0;
			virtual void Resize() = 0;

			virtual void Create(const Device* pDevice, void* pHandle, uint32_t samplerPoolSize, uint32_t cbvSrvUavPoolSize,
				uint32_t maxSamplers = 16, const uint32_t* pMaxCbvsEachSpace = nullptr, const uint32_t* pMaxSrvsEachSpace = nullptr,
				const uint32_t* pMaxUavsEachSpace = nullptr, uint32_t maxCbvSpaces = 1, uint32_t maxSrvSpaces = 1, uint32_t maxUavSpaces = 1,
				const wchar_t* name = nullptr) = 0;

			virtual void* GetHandle() const = 0;

			using uptr = std::unique_ptr<CommandList>;
			using sptr = std::shared_ptr<CommandList>;

			static uptr MakeUnique(XUSG::API api = XUSG::API::DIRECTX_12);
			static sptr MakeShared(XUSG::API api = XUSG::API::DIRECTX_12);
			static uptr MakeUnique(const Device* pDevice, XUSG::CommandList* pCommandList, uint32_t samplerPoolSize, uint32_t cbvSrvUavPoolSize,
				uint32_t maxSamplers = 16, const uint32_t* pMaxCbvsEachSpace = nullptr, const uint32_t* pMaxSrvsEachSpace = nullptr,
				const uint32_t* pMaxUavsEachSpace = nullptr, uint32_t maxCbvSpaces = 1, uint32_t maxSrvSpaces = 1, uint32_t maxUavSpaces = 1,
				XUSG::API api = XUSG::API::DIRECTX_12);
			static sptr MakeShared(const Device* pDevice, XUSG::CommandList* pCommandList, uint32_t samplerPoolSize, uint32_t cbvSrvUavPoolSize,
				uint32_t maxSamplers = 16, const uint32_t* pMaxCbvsEachSpace = nullptr, const uint32_t* pMaxSrvsEachSpace = nullptr,
				const uint32_t* pMaxUavsEachSpace = nullptr, uint32_t maxCbvSpaces = 1, uint32_t maxSrvSpaces = 1, uint32_t maxUavSpaces = 1,
				XUSG::API api = XUSG::API::DIRECTX_12);
		};
	}
}
