/********************************************************************************
 * ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
 * Copyright (c) 2010-2024 Daniel Chappuis                                       *
 *********************************************************************************
 *                                                                               *
 * This software is provided 'as-is', without any express or implied warranty.   *
 * In no event will the authors be held liable for any damages arising from the  *
 * use of this software.                                                         *
 *                                                                               *
 * Permission is granted to anyone to use this software for any purpose,         *
 * including commercial applications, and to alter it and redistribute it        *
 * freely, subject to the following restrictions:                                *
 *                                                                               *
 * 1. The origin of this software must not be misrepresented; you must not claim *
 *    that you wrote the original software. If you use this software in a        *
 *    product, an acknowledgment in the product documentation would be           *
 *    appreciated but is not required.                                           *
 *                                                                               *
 * 2. Altered source versions must be plainly marked as such, and must not be    *
 *    misrepresented as being the original software.                             *
 *                                                                               *
 * 3. This notice may not be removed or altered from any source distribution.    *
 *                                                                               *
 ********************************************************************************/

#ifndef REACTPHYSICS3D_OVERLAPPING_PAIR_H
#define REACTPHYSICS3D_OVERLAPPING_PAIR_H

// Libraries
#include <cstddef>
#include <reactphysics3d/collision/Collider.h>
#include <reactphysics3d/components/BodyComponents.h>
#include <reactphysics3d/components/ColliderComponents.h>
#include <reactphysics3d/components/RigidBodyComponents.h>
#include <reactphysics3d/containers/Map.h>
#include <reactphysics3d/containers/Pair.h>
#include <reactphysics3d/containers/Set.h>
#include <reactphysics3d/containers/containers_common.h>
#include <reactphysics3d/utils/Profiler.h>

/// ReactPhysics3D namespace
namespace reactphysics3d {

// Declarations
struct NarrowPhaseInfoBatch;
enum class NarrowPhaseAlgorithmType;
class CollisionShape;
class CollisionDispatch;

// Structure LastFrameCollisionInfo
/**
 * This structure contains collision info about the last frame.
 * This is used for temporal coherence between frames.
 */
struct LastFrameCollisionInfo {

    // TODO OPTI : Use bit flags instead of bools here

    /// True if we have information about the previous frame
    bool isValid;

    /// True if the frame info is obsolete (the collision shape are not overlapping in middle phase)
    bool isObsolete;

    /// True if the two shapes were colliding in the previous frame
    bool wasColliding;

    /// True if we were using GJK algorithm to check for collision in the previous frame
    bool wasUsingGJK;

    /// True if we were using SAT algorithm to check for collision in the previous frame
    bool wasUsingSAT;

    // ----- GJK Algorithm -----

    /// Previous separating axis
    Vector3 gjkSeparatingAxis;

    // SAT Algorithm
    bool satIsAxisFacePolyhedron1;
    bool satIsAxisFacePolyhedron2;
    uint8 satMinAxisFaceIndex;
    uint8 satMinEdge1Index;
    uint8 satMinEdge2Index;

    /// Constructor
    LastFrameCollisionInfo()
        : isValid(false)
        , isObsolete(false)
        , wasColliding(false)
        , wasUsingGJK(false)
        , wasUsingSAT(false)
        , gjkSeparatingAxis(Vector3(0, 1, 0))
        , satIsAxisFacePolyhedron1(false)
        , satIsAxisFacePolyhedron2(false)
        , satMinAxisFaceIndex(0)
        , satMinEdge1Index(0)
        , satMinEdge2Index(0)
    {
    }
};

// Class OverlappingPairs
/**
 * This class contains pairs of two colliders that are overlapping
 * during the broad-phase collision detection. A pair is created when
 * the two colliders start to overlap and is destroyed when they do not
 * overlap anymore. Each contains a contact manifold that
 * store all the contact points between the two bodies.
 *
 * Once the two bodies of an overlapping pair are disabled (sleeping or static),
 * we put the overlapping pair to the array of disabled pairs. We keep it so that
 * we can awake the other body if one body is destroyed and we can also correclty
 * track the lost contacts between bodies even after they go to sleep.
 */
class OverlappingPairs {

public:
    // Struct OverlappingPair
    /**
     * A base overlapping pair
     */
    struct OverlappingPair {

        /// Ids of the convex vs convex pairs
        uint64 pairID;

        /// Broad-phase Id of the first shape
        // TODO OPTI : Is this used ?
        int32 broadPhaseId1;

        /// Broad-phase Id of the second shape
        // TODO OPTI : Is this used ?
        int32 broadPhaseId2;

        /// Entity of the first collider of the convex vs convex pairs
        Entity collider1;

        /// Entity of the second collider of the convex vs convex pairs
        Entity collider2;

        /// True if we need to test if the convex vs convex overlapping pairs of shapes still overlap
        bool needToTestOverlap;

        /// Pointer to the narrow-phase algorithm
        NarrowPhaseAlgorithmType narrowPhaseAlgorithmType;

        /// True if the colliders of the overlapping pair were colliding in the previous frame
        bool collidingInPreviousFrame;

        /// True if the colliders of the overlapping pair are colliding in the current frame
        bool collidingInCurrentFrame;

        ///  True if at least one body of the pair is awake or not static
        bool isEnabled;

        /// Constructor
        OverlappingPair(uint64 pairId, int32 broadPhaseId1, int32 broadPhaseId2, Entity collider1, Entity collider2,
            NarrowPhaseAlgorithmType narrowPhaseAlgorithmType, bool isEnabled)
            : pairID(pairId)
            , broadPhaseId1(broadPhaseId1)
            , broadPhaseId2(broadPhaseId2)
            , collider1(collider1)
            , collider2(collider2)
            , needToTestOverlap(false)
            , narrowPhaseAlgorithmType(narrowPhaseAlgorithmType)
            , collidingInPreviousFrame(false)
            , collidingInCurrentFrame(false)
            , isEnabled(isEnabled)
        {
        }

        /// Destructor
        virtual ~OverlappingPair() = default;
    };

    // Struct ConvexOverlappingPair
    /**
     * An overlapping pair between two convex colliders
     */
    struct ConvexOverlappingPair : public OverlappingPair {

        /// Temporal coherence collision data for each overlapping collision shapes of this pair.
        /// Temporal coherence data store collision information about the last frame.
        /// If two convex shapes overlap, we have a single collision data but if one shape is concave,
        /// we might have collision data for several overlapping triangles.
        LastFrameCollisionInfo lastFrameCollisionInfo;

        /// Constructor
        ConvexOverlappingPair(uint64 pairId, int32 broadPhaseId1, int32 broadPhaseId2, Entity collider1, Entity collider2,
            NarrowPhaseAlgorithmType narrowPhaseAlgorithmType, bool isEnabled)
            : OverlappingPair(pairId, broadPhaseId1, broadPhaseId2, collider1, collider2, narrowPhaseAlgorithmType, isEnabled)
        {
        }
    };

    // Struct ConvexOverlappingPair
    /**
     * An overlapping pair between a convex collider and a concave collider
     */
    struct ConcaveOverlappingPair : public OverlappingPair {

    private:
        MemoryAllocator* mPoolAllocator;

    public:
        /// True if the first shape of the pair is convex
        bool isShape1Convex;

        /// Temporal coherence collision data for each overlapping collision shapes of this pair.
        /// Temporal coherence data store collision information about the last frame.
        /// If two convex shapes overlap, we have a single collision data but if one shape is concave,
        /// we might have collision data for several overlapping triangles. The key in the map is the
        /// shape Ids of the two collision shapes.
        Map<uint64, LastFrameCollisionInfo*> lastFrameCollisionInfos;

        /// Constructor
        ConcaveOverlappingPair(uint64 pairId, int32 broadPhaseId1, int32 broadPhaseId2, Entity collider1, Entity collider2,
            NarrowPhaseAlgorithmType narrowPhaseAlgorithmType,
            bool isShape1Convex, MemoryAllocator& poolAllocator, MemoryAllocator& heapAllocator, bool isEnabled,
            bool allocateLastFrameCollisionInfos = true)
            : OverlappingPair(pairId, broadPhaseId1, broadPhaseId2, collider1, collider2, narrowPhaseAlgorithmType, isEnabled)
            , mPoolAllocator(&poolAllocator)
            , isShape1Convex(isShape1Convex)
            , lastFrameCollisionInfos(heapAllocator, allocateLastFrameCollisionInfos ? 16 : 0)
        {
        }

        // Destroy all the LastFrameCollisionInfo objects
        void destroyLastFrameCollisionInfos()
        {

            for (auto it = lastFrameCollisionInfos.begin(); it != lastFrameCollisionInfos.end(); ++it) {

                // Call the destructor
                it->second->LastFrameCollisionInfo::~LastFrameCollisionInfo();

                // Release memory
                mPoolAllocator->release(it->second, sizeof(LastFrameCollisionInfo));
            }

            lastFrameCollisionInfos.clear();
        }

        // Add a new last frame collision info if it does not exist for the given shapes already
        LastFrameCollisionInfo* addLastFrameInfoIfNecessary(uint32 shapeId1, uint32 shapeId2)
        {

            uint32 maxShapeId = shapeId1;
            uint32 minShapeId = shapeId2;
            if (shapeId1 < shapeId2) {
                maxShapeId = shapeId2;
                minShapeId = shapeId1;
            }

            // Try to get the corresponding last frame collision info
            const uint64 shapesId = pairNumbers(maxShapeId, minShapeId);

            // If there is no collision info for those two shapes already
            auto it = lastFrameCollisionInfos.find(shapesId);
            if (it == lastFrameCollisionInfos.end()) {

                // Make sure capacity is an integral multiple of alignment
                const size_t allocatedMemory = std::ceil(sizeof(LastFrameCollisionInfo) / float(GLOBAL_ALIGNMENT)) * GLOBAL_ALIGNMENT;

                LastFrameCollisionInfo* lastFrameInfo = new (mPoolAllocator->allocate(allocatedMemory)) LastFrameCollisionInfo();

                // Add it into the map of collision infos
                lastFrameCollisionInfos.add(Pair<uint64, LastFrameCollisionInfo*>(shapesId, lastFrameInfo));

                return lastFrameInfo;
            } else {

                // The existing collision info is not obsolete
                it->second->isObsolete = false;

                return it->second;
            }
        }

        /// Clear the obsolete LastFrameCollisionInfo objects
        void clearObsoleteLastFrameInfos()
        {

            // For each last frame collision info
            for (auto it = lastFrameCollisionInfos.begin(); it != lastFrameCollisionInfos.end();) {

                // If the collision info is obsolete
                if (it->second->isObsolete) {

                    // Call the destructor
                    it->second->LastFrameCollisionInfo::~LastFrameCollisionInfo();

                    // Make sure capacity is an integral multiple of alignment
                    const size_t allocatedMemory = std::ceil(sizeof(LastFrameCollisionInfo) / float(GLOBAL_ALIGNMENT)) * GLOBAL_ALIGNMENT;

                    // Release memory
                    mPoolAllocator->release(it->second, allocatedMemory);

                    it = lastFrameCollisionInfos.remove(it);
                } else { // If the collision info is not obsolete

                    // Do not delete it but mark it as obsolete
                    it->second->isObsolete = true;

                    ++it;
                }
            }
        }
    };

private:
    // -------------------- Attributes -------------------- //

    /// Pool memory allocator
    MemoryAllocator& mPoolAllocator;

    /// Heap memory allocator
    MemoryAllocator& mHeapAllocator;

    /// Array of convex vs convex overlapping pairs
    Array<ConvexOverlappingPair> mConvexPairs;

    /// Array of convex vs concave overlapping pairs
    Array<ConcaveOverlappingPair> mConcavePairs;

    ///  Array of disabled convex overlapping pairs (pairs with both bodies disabled)
    Array<ConvexOverlappingPair> mDisabledConvexPairs;

    /// Array of disabled concave overlapping pairs (pairs with both bodies disabled)
    Array<ConcaveOverlappingPair> mDisabledConcavePairs;

    /// Map a convex pair id to the internal array index
    Map<uint64, uint64> mMapConvexPairIdToPairIndex;

    /// Map a concave pair id to the internal array index
    Map<uint64, uint64> mMapConcavePairIdToPairIndex;

    /// Map a disabled convex pair id to the internal array index
    Map<uint64, uint64> mMapDisabledConvexPairIdToPairIndex;

    /// Map a disable concave pair id to the internal array index
    Map<uint64, uint64> mMapDisabledConcavePairIdToPairIndex;

    /// Reference to the colliders components
    ColliderComponents& mColliderComponents;

    /// Reference to the body components
    BodyComponents& mBodyComponents;

    /// Reference to the rigid bodies components
    RigidBodyComponents& mRigidBodyComponents;

    /// Reference to the set of bodies that cannot collide with each others
    Set<bodypair>& mNoCollisionPairs;

    /// Reference to the collision dispatch
    CollisionDispatch& mCollisionDispatch;

#ifdef IS_RP3D_PROFILING_ENABLED

    /// Pointer to the profiler
    Profiler* mProfiler;

#endif

    // -------------------- Methods -------------------- //

    // Move a pair from a source to a destination index in the pairs array
    void movePairToIndex(uint64 srcIndex, uint64 destIndex);

    /// Swap two pairs in the array
    void swapPairs(uint64 index1, uint64 index2);

    /// Remove a disabled convex overlapping pair
    void removeDisabledConvexPairWithIndex(uint64 pairIndex, bool removeFromColliders);

    /// Remove a disabled concave overlapping pair
    void removeDisabledConcavePairWithIndex(uint64 pairIndex, bool removeFromColliders);

public:
    // -------------------- Methods -------------------- //

    /// Constructor
    OverlappingPairs(MemoryManager& memoryManager, ColliderComponents& colliderComponents,
        BodyComponents& bodyComponents,
        RigidBodyComponents& rigidBodyComponents, Set<bodypair>& noCollisionPairs,
        CollisionDispatch& collisionDispatch);

    /// Destructor
    ~OverlappingPairs();

    /// Deleted copy-constructor
    OverlappingPairs(const OverlappingPairs& pair) = delete;

    /// Deleted assignment operator
    OverlappingPairs& operator=(const OverlappingPairs& pair) = delete;

    /// Enable an overlapping pair (because at least one body of the pair is awaken or not static anymore)
    void enablePair(uint64 pairId);

    /// Disable an overlapping pair (because both bodies of the pair are disabled)
    void disablePair(uint64 pairId);

    /// Enable a convex overlapping pair
    void enableConvexPairWithIndex(uint64 pairIndex);

    /// Disable a convex overlapping pair (because both bodies of the pair are disabled)
    void disableConvexPairWithIndex(uint64 pairIndex);

    /// Enable a concave overlapping pair
    void enableConcavePairWithIndex(uint64 pairIndex);

    /// Disable a concave overlapping pair (because both bodies of the pair are disabled)
    void disableConcavePairWithIndex(uint64 pairIndex);

    /// Return true if a given pair is disabled (both bodies of the pair are disabled)
    bool isPairDisabled(uint64 pairId) const;

    /// Add an overlapping pair
    uint64 addPair(uint32 collider1Index, uint32 collider2Index, bool isConvexVsConvex);

    /// Remove an overlapping pair
    void removePair(uint64 pairId);

    /// Remove a convex pair at a given index
    void removeConvexPairWithIndex(uint64 pairIndex, bool removeFromColliders = true);

    // Remove a concave pair at a given index
    void removeConcavePairWithIndex(uint64 pairIndex, bool removeFromColliders = true);

    /// Delete all the obsolete last frame collision info
    void clearObsoleteLastFrameCollisionInfos();

    /// Set the collidingInPreviousFrame value with the collidinginCurrentFrame value for each pair
    void updateCollidingInPreviousFrame();

    /// Return the pair of bodies index of the pair
    static bodypair computeBodiesIndexPair(Entity body1Entity, Entity body2Entity);

    /// Set if we need to test a given pair for overlap
    void setNeedToTestOverlap(uint64 pairId, bool needToTestOverlap);

    /// Return a reference to an overlapping pair
    OverlappingPair* getOverlappingPair(uint64 pairId);

#ifdef IS_RP3D_PROFILING_ENABLED

    /// Set the profiler
    void setProfiler(Profiler* profiler);

#endif

    // -------------------- Friendship -------------------- //

    friend class PhysicsWorld;
    friend class CollisionDetectionSystem;
};

// Return the pair of bodies index
RP3D_FORCE_INLINE bodypair OverlappingPairs::computeBodiesIndexPair(Entity body1Entity, Entity body2Entity)
{

    // Construct the pair of body index
    bodypair indexPair = body1Entity.id < body2Entity.id ? bodypair(body1Entity, body2Entity) : bodypair(body2Entity, body1Entity);
    assert(indexPair.first != indexPair.second);
    return indexPair;
}

// Set if we need to test a given pair for overlap
RP3D_FORCE_INLINE void OverlappingPairs::setNeedToTestOverlap(uint64 pairId, bool needToTestOverlap)
{

    assert(mMapConvexPairIdToPairIndex.containsKey(pairId) || mMapConcavePairIdToPairIndex.containsKey(pairId));

    auto it = mMapConvexPairIdToPairIndex.find(pairId);
    if (it != mMapConvexPairIdToPairIndex.end()) {
        mConvexPairs[static_cast<uint32>(it->second)].needToTestOverlap = needToTestOverlap;
    } else {
        mConcavePairs[static_cast<uint32>(mMapConcavePairIdToPairIndex[pairId])].needToTestOverlap = needToTestOverlap;
    }
}

// Return a reference to an overlapping pair
RP3D_FORCE_INLINE OverlappingPairs::OverlappingPair* OverlappingPairs::getOverlappingPair(uint64 pairId)
{

    auto it = mMapConvexPairIdToPairIndex.find(pairId);
    if (it != mMapConvexPairIdToPairIndex.end()) {
        return &(mConvexPairs[static_cast<uint32>(it->second)]);
    }
    it = mMapConcavePairIdToPairIndex.find(pairId);
    if (it != mMapConcavePairIdToPairIndex.end()) {
        return &(mConcavePairs[static_cast<uint32>(it->second)]);
    }
    it = mMapDisabledConvexPairIdToPairIndex.find(pairId);
    if (it != mMapDisabledConvexPairIdToPairIndex.end()) {
        return &(mDisabledConvexPairs[static_cast<uint32>(it->second)]);
    }
    it = mMapDisabledConcavePairIdToPairIndex.find(pairId);
    if (it != mMapDisabledConcavePairIdToPairIndex.end()) {
        return &(mDisabledConcavePairs[static_cast<uint32>(it->second)]);
    }

    return nullptr;
}

// Return true if a given pair is disabled (both bodies of the pair are disabled)
RP3D_FORCE_INLINE bool OverlappingPairs::isPairDisabled(uint64 pairId) const
{
    return mMapDisabledConvexPairIdToPairIndex.containsKey(pairId) || mMapDisabledConcavePairIdToPairIndex.containsKey(pairId);
}

#ifdef IS_RP3D_PROFILING_ENABLED

// Set the profiler
RP3D_FORCE_INLINE void OverlappingPairs::setProfiler(Profiler* profiler)
{
    mProfiler = profiler;
}

#endif
}

#endif
