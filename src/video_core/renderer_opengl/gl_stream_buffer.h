// Copyright 2018 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <tuple>
#include <glad/glad.h>
#include "common/common_types.h"
#include "video_core/renderer_opengl/gl_resource_manager.h"

class OGLStreamBuffer : private NonCopyable {
public:
    explicit OGLStreamBuffer(GLenum target, GLsizeiptr size, bool coherent = false);
    ~OGLStreamBuffer();

    GLuint GetHandle() const;
    GLsizeiptr GetSize() const;

    /*
     * Allocates a linear chunk of memory in the GPU buffer with at least "size" bytes
     * and the optional alignment requirement.
     * If the buffer is full, the whole buffer is reallocated which invalidates old chunks.
     * The return values are the pointer to the new chunk, the offset within the buffer,
     * and the invalidation flag for previous chunks.
     * The actual used size must be specified on unmapping the chunk.
     */
    std::tuple<u8*, GLintptr, bool> Map(GLsizeiptr size, GLintptr alignment = 0);

    void Unmap(GLsizeiptr size);

private:
    OGLBuffer gl_buffer;
    GLenum gl_target;
    GLbitfield map_flags;

    GLintptr buffer_pos = 0;
    GLsizeiptr buffer_size = 0;
    GLintptr mapped_offset = 0;
    GLsizeiptr mapped_size = 0;
    u8* mapped_ptr = nullptr;
};
