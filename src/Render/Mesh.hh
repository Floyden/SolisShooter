#pragma once
#include "IndexBuffer.hh"
#include "VertexData.hh"
#include "VertexAttributes.hh"

class Mesh {
public:
    SPtr<IndexBuffer> mIndexBuffer;
    SPtr<VertexData> mVertexData;
    SPtr<VertexAttributes> mAttributes;
};