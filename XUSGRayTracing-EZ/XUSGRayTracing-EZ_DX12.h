//--------------------------------------------------------------------------------------
// Copyright (c) XU, Tianchen. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "XUSGRayTracing-EZ.h"

namespace XUSG
{
	namespace RayTracing
	{
		namespace EZ
		{
			class CommandList_DXR :
				virtual public CommandList,
				virtual public RayTracing::CommandList_DX12,
				virtual public Ultimate::EZ::CommandList_DX12
			{
			public:
				CommandList_DXR();
				CommandList_DXR(RayTracing::CommandList* pCommandList, uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize);
				virtual ~CommandList_DXR();

				bool Create(RayTracing::CommandList* pCommandList, uint32_t samplerHeapSize, uint32_t cbvSrvUavHeapSize);
				bool Create(const RayTracing::Device* pDevice, void* pHandle, uint32_t samplerHeapSize,
					uint32_t cbvSrvUavHeapSize, const wchar_t* name = nullptr);
				bool CreatePipelineLayouts(
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
					uint32_t maxTLASSrvs = 0, uint32_t spaceTLAS = 0,
					uint32_t slotExt = 0, uint32_t spaceExt = 0x7FFF0ADE);
				bool Reset(const CommandAllocator* pAllocator, const Pipeline& initialState);
				bool PrebuildBLAS(BottomLevelAS* pBLAS, uint32_t numGeometries, const GeometryBuffer& geometries,
					BuildFlag flags = BuildFlag::PREFER_FAST_TRACE);
				bool PrebuildTLAS(TopLevelAS* pTLAS, uint32_t numInstances,
					BuildFlag flags = BuildFlag::PREFER_FAST_TRACE);
				bool PrebuildOmmArray(OpacityMicromapArray* pOmmArray, uint32_t numOpacityMicromaps,
					const GeometryBuffer& ommArrayDescs, BuildFlag flags = BuildFlag::PREFER_FAST_TRACE);
				bool AllocateAccelerationStructure(AccelerationStructure* pAccelerationStructure, size_t byteWidth = 0);

				void SetTriangleGeometries(GeometryBuffer& geometries, uint32_t numGeometries, Format vertexFormat,
					XUSG::EZ::VertexBufferView* pVBs, XUSG::EZ::IndexBufferView* pIBs = nullptr,
					const GeometryFlag* pGeometryFlags = nullptr, const ResourceView* pTransforms = nullptr);
				void SetAABBGeometries(GeometryBuffer& geometries, uint32_t numGeometries,
					XUSG::EZ::VertexBufferView* pVBs, const GeometryFlag* pGeometryFlags = nullptr);
				void SetOMMGeometries(GeometryBuffer& geometries, uint32_t numGeometries,
					const GeometryBuffer& triGeometries, const BottomLevelAS::OMMLinkage* pOmmLinkages,
					const GeometryFlag* pGeometryFlags = nullptr);
				void SetOmmArray(GeometryBuffer& ommArrayDescs, uint32_t numOpacityMicromaps,
					const OpacityMicromapArray::Desc* pOmmArrayDescs);
				void SetBLASDestination(BottomLevelAS* pBLAS, const Buffer::sptr destBuffer,
					uintptr_t byteOffset, uint32_t uavIndex);
				void SetTLASDestination(TopLevelAS* pTLAS, const Buffer::sptr destBuffer,
					uintptr_t byteOffset, uint32_t uavIndex, uint32_t srvIndex);
				void SetOmmArrayDestination(OpacityMicromapArray* pOmmArray, const Buffer::sptr destBuffer, uintptr_t byteOffset);
				void BuildBLAS(BottomLevelAS* pBLAS, const BottomLevelAS* pSource = nullptr,
					uint8_t numPostbuildInfoDescs = 0, const PostbuildInfoType* pPostbuildInfoTypes = nullptr);
				void BuildTLAS(TopLevelAS* pTLAS, Resource* pInstanceDescs, const TopLevelAS* pSource = nullptr,
					uint8_t numPostbuildInfoDescs = 0, const PostbuildInfoType* pPostbuildInfoTypes = nullptr);
				void BuildOmmArray(OpacityMicromapArray* pOmmArray, const OpacityMicromapArray* pSource = nullptr,
					uint8_t numPostbuildInfoDescs = 0, const PostbuildInfoType* pPostbuildInfoTypes = nullptr);
				void CopyRaytracingAccelerationStructure(const AccelerationStructure* pDst,
					const AccelerationStructure* pSrc, CopyMode mode);
				void SetTopLevelAccelerationStructure(uint32_t index, const TopLevelAS* pTopLevelAS) const;
				void RTSetShaderLibrary(uint32_t index, const Blob& shaderLib,
					uint32_t numShaders = 0, const wchar_t** pShaderNames = nullptr);
				void RTSetShaderConfig(uint32_t maxPayloadSize, uint32_t maxAttributeSize = sizeof(float[2]));
				void RTSetHitGroup(uint32_t index, const wchar_t* hitGroupName, const wchar_t* closestHitShaderName,
					const wchar_t* anyHitShaderName = nullptr, const wchar_t* intersectionShaderName = nullptr,
					HitGroupType type = HitGroupType::TRIANGLES);
				void RTSetMaxRecursionDepth(uint32_t depth);
				void RTSetPipelineState(const Pipeline& pipelineState, RayTracing::State* pState = nullptr);
				void DispatchRays(uint32_t width, uint32_t height, uint32_t depth, const wchar_t* rayGenShaderName,
					const wchar_t* const* pMissShaderNames, uint32_t numMissShaders);
				void DispatchRaysIndirect(const CommandLayout* pCommandlayout,
					uint32_t maxCommandCount,
					const wchar_t* rayGenShaderName,
					const wchar_t* const* pMissShaderNames,
					uint32_t numMissShaders,
					Resource* pArgumentBuffer,
					uint64_t argumentBufferOffset = 0,
					Resource* pCountBuffer = nullptr,
					uint64_t countBufferOffset = 0);

				size_t GetDispatchRaysArgReservedOffset() const { return sizeof(DX12DispatchRaysDescHeader); }

				const Device* GetRTDevice() const { return RayTracing::CommandList_DX12::GetRTDevice(); }
				RayTracing::CommandList* AsRTCommandList() { return dynamic_cast<RayTracing::CommandList*>(this); }

			protected:
				//using ShaderTablePtr = ShaderTable*;
				using CShaderTablePtr = const ShaderTable*;

				struct DX12DispatchRaysDescHeader
				{
					D3D12_GPU_VIRTUAL_ADDRESS_RANGE RayGenerationShaderRecord;
					D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE MissShaderTable;
					D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE HitGroupTable;
					D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE CallableShaderTable;
				};

				struct ArgumentBufferVA
				{
					Resource* pBuffer;
					uint64_t Offset;
				};

				bool createComputePipelineLayouts(uint32_t maxSamplers, const uint32_t* pMaxCbvsEachSpace,
					const uint32_t* pMaxSrvsEachSpace, const uint32_t* pMaxUavsEachSpace,
					uint32_t maxCbvSpaces, uint32_t maxSrvSpaces, uint32_t maxUavSpaces,
					uint32_t max32BitConstants, uint32_t constantSlot, uint32_t constantSpace,
					uint32_t maxTLASSrvs, uint32_t spaceTLAS, uint32_t slotExt, uint32_t spaceExt);

				void predispatchRays(CShaderTablePtr& pRayGen, CShaderTablePtr& pHitGroup, CShaderTablePtr& pMiss,
					const wchar_t* rayGenShaderName, const wchar_t* const* pMissShaderNames, uint32_t numMissShaders);

				Resource* needScratch(size_t size);

				const ShaderTable* getShaderTable(const std::string& key,
					std::unordered_map<std::string, ShaderTable::uptr>& shaderTables,
					uint32_t numShaderIDs);

				RayTracing::PipelineLib::uptr m_rayTracingPipelineLib;

				size_t m_scratchSize;
				std::vector<Buffer::uptr> m_scratches;

				RayTracing::State::uptr m_rayTracingState;
				bool m_isRTStateDirty;

				std::vector<uint32_t> m_tlasBindingToParamIndexMap;

				std::vector<Buffer::uptr> m_uploaders;

				std::unordered_map<std::string, ShaderTable::uptr> m_rayGenTables;
				std::unordered_map<std::string, ShaderTable::uptr> m_hitGroupTables;
				std::unordered_map<std::string, ShaderTable::uptr> m_missTables;

				std::unordered_set<std::string> m_argumentBufferVAs;
			};
		}
	}
}
