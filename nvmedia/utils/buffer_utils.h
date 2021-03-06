/* Copyright (c) 2014-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef __BUFFER_UTILS_H__
#define __BUFFER_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia.h"
#include "nvmedia_image.h"
#include "nvmedia_isp.h"
#include "thread_utils.h"

#define BUFFERS_POOL_MAX_CAPACITY  600
#define BUFFERS_POOL_HIST_BINS     256
#define BUFFERS_POOL_LAC_WINDOWS   (128 * 128)

typedef enum {
    IMAGE_BUFFER_POOL = 0,
    SIBLING_BUFFER_POOL = 1
} BufferPoolType;

typedef struct {
    NvQueue          *queue;           // Buffers pool queue
    NvU32             capacity;        // Buffer pool capacity
    NvU32             timeout;         // Timeout for buffer dequeue
    void             *config;          // Config
    BufferPoolType    type;
} BufferPool;

typedef struct {
    NvMediaImage     *image;
    NvMediaImage    **siblingImages;
    NvMutex          *mutex;
    NvU32             imagesCount;
    NvU32             refCount;
    NvU32             imageID;
    BufferPool       *bufferPool;
    NvU64             processingStartTime;
    NvU64             processingEndTime;
} ImageBuffer;

typedef struct {
    NvU32                       width;              // Image width
    NvU32                       height;             // Image height
    NvMediaSurfaceType          surfType;           // Image surface type
    NvU32                       surfAttributes;     // Image attributes (NvMediaImageAttributes)
    NvMediaImageAdvancedConfig  surfAdvConfig;      // Image advanced config
    NvMediaImageClass           imageClass;         // Image class
    NvU32                       imagesCount;        // Images count (for NVMEDIA_IMAGE_CLASS_SINGLE_IMAGE should be set with 1)
    NvMediaDevice              *device;             // Device
    NvMediaBool                 createSiblingsFlag; // Optional flag for aggregated image type: create siblings
    NvU32                       siblingAttributes;  // Sibling images creation attributes
} ImageBufferPoolConfig;

typedef struct {
    NvMediaImage   *parentImage; // parent aggregated image
    NvU32           imageIndex;  // image index in parent
    NvU32           attributes;  // attributes
} SiblingBufferPoolConfig;

//  BufferPool_Create
//
//    BufferPool_Create()  Initialize buffer pool and create buffers.
//       Initial value for each buffer processingStartTime is set to ULONG_MAX
//       Initial value for each buffer processingEndTime is set to 0
//
//  Arguments:
//
//   pool
//      (out) Pointer to pointer to buffer pool
//
//   capacity
//      (in) Buffer pool capacity. Must be larger than 0 and smaller
//         than BUFFERS_POOL_MAX_CAPACITY
//
//   timeout
//      (in) Timeout for dequeue operations and insertion of buffers to the pool
//         Use NV_TIMEOUT_INFINITE for infinite timeout or 0 for no timeout.
//
//   config
//      (in) Pointer to buffer pool configuration. Use:
//         - ImageBufferPoolConfig structure for IMAGE_BUFFER_POOL
//         - SiblingBufferPoolConfig structure for SIBLING_BUFFER_POOL

NvMediaStatus
BufferPool_Create (
    BufferPool **poolOut,
    NvU32 capacity,
    NvU32 timeout,
    BufferPoolType type,
    void *config);

//  BufferPool_Destroy
//
//    BufferPool_Destroy()  Destroy buffer pool and release buffers.
//
//  Arguments:
//
//   pool
//      (in) Pointer to buffer pool

NvMediaStatus
BufferPool_Destroy (
    BufferPool *pool);

//  BufferPool_AcquireBuffer
//
//    BufferPool_AcquireBuffer()  Acquire buffer from buffer pool. Will wait
//       for <timeout> milliseconds for buffer to become available.
//
//  Arguments:
//
//   pool
//      (in) Pointer to buffer pool
//
//   buffer
//      (out) Pointer to pointer to acquired buffer.
//         Will be set with NULL if no buffers available.

NvMediaStatus
BufferPool_AcquireBuffer (
    BufferPool *pool,
    void **buffer);

//  BufferPool_ReleaseBuffer
//
//    BufferPool_ReleaseBuffer()  Release buffer - put buffer back to buffer pool.
//
//  Arguments:
//
//   pool
//      (in) Pointer to buffer pool
//
//   buffer
//      (in) Pointer to released buffer

NvMediaStatus
BufferPool_ReleaseBuffer (
    BufferPool *pool,
    void *buffer);

//  BufferPool_DoActionOnAllBuffers
//
//    BufferPool_DoActionOnAllBuffers()  Do an action on each buffer.
//
//  Arguments:
//
//   pool
//      (in) Pointer to buffer pool
//
//   context
//      (in) Context for the callback
//
//   callbackFunc
//      (in) The function to callback

NvMediaStatus
BufferPool_DoActionOnAllBuffers (
    BufferPool *pool,
    void *context,
    NvMediaStatus (* callbackFunc)(void *context, void *buffer));

//  BufferPool_AddRefToBuffer
//
//    BufferPool_AddRefToBuffer()  Add ref to buffer.
//
//  Arguments:
//
//   buffer
//      (in) Pointer to buffer

NvMediaStatus
BufferPool_AddRefToBuffer (
    ImageBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif // __BUFFER_UTILS_H__
