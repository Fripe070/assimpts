#pragma once
#include "assimp/postprocess.h"
// I am so sorry. I wish C++ had reflection to use instead.

#define POST_PROCESS_FLAGS(X) \
    X(calcTangentSpace, aiProcess_CalcTangentSpace) \
    X(joinIdenticalVertices, aiProcess_JoinIdenticalVertices) \
    X(makeLeftHanded, aiProcess_MakeLeftHanded) \
    X(triangulate, aiProcess_Triangulate) \
    X(removeComponent, aiProcess_RemoveComponent) \
    X(genNormals, aiProcess_GenNormals) \
    X(genSmoothNormals, aiProcess_GenSmoothNormals) \
    X(splitLargeMeshes, aiProcess_SplitLargeMeshes) \
    X(preTransformVertices, aiProcess_PreTransformVertices) \
    X(limitBoneWeights, aiProcess_LimitBoneWeights) \
    X(validateDataStructure, aiProcess_ValidateDataStructure) \
    X(improveCacheLocality, aiProcess_ImproveCacheLocality) \
    X(removeRedundantMaterials, aiProcess_RemoveRedundantMaterials) \
    X(fixInfacingNormals, aiProcess_FixInfacingNormals) \
    X(populateArmatureData, aiProcess_PopulateArmatureData) \
    X(sortByPType, aiProcess_SortByPType) \
    X(findDegenerates, aiProcess_FindDegenerates) \
    X(findInvalidData, aiProcess_FindInvalidData) \
    X(genUVCoords, aiProcess_GenUVCoords) \
    X(transformUVCoords, aiProcess_TransformUVCoords) \
    X(findInstances, aiProcess_FindInstances) \
    X(optimizeMeshes, aiProcess_OptimizeMeshes) \
    X(optimizeGraph, aiProcess_OptimizeGraph) \
    X(flipUVs, aiProcess_FlipUVs) \
    X(flipWindingOrder, aiProcess_FlipWindingOrder) \
    X(splitByBoneCount, aiProcess_SplitByBoneCount) \
    X(debone, aiProcess_Debone) \
    X(globalScale, aiProcess_GlobalScale) \
    X(embedTextures, aiProcess_EmbedTextures) \
    X(forceGenNormals, aiProcess_ForceGenNormals) \
    X(dropNormals, aiProcess_DropNormals) \
    X(genBoundingBoxes, aiProcess_GenBoundingBoxes)

#define POST_PROCESS_PRESETS(X) \
    X(convertToLeftHanded, aiProcess_ConvertToLeftHanded)  \
    X(targetRealtime_Fast, aiProcessPreset_TargetRealtime_Fast) \
    X(targetRealtime_Quality, aiProcessPreset_TargetRealtime_Quality) \
    X(targetRealtime_MaxQuality, aiProcessPreset_TargetRealtime_MaxQuality)

enum class PostProcessFlags : unsigned int
{
#define X(name, value) name = value,
    POST_PROCESS_FLAGS(X)
    POST_PROCESS_PRESETS(X)
#undef X
};