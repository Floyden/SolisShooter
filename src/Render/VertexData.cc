#include "VertexData.hh"


void VertexData::SetBuffer(uint32_t index, SPtr<VertexBuffer> buffer)
{
    mVertexBuffers[index] = buffer;
}

SPtr<VertexBuffer> VertexData::GetBuffer(uint32_t index) const
{
    auto it = mVertexBuffers.find(index);
    if(it != mVertexBuffers.end())
        return it->second;

    return nullptr;
}

uint32_t VertexData::GetBufferCount() const
{
    return mVertexBuffers.size();   
}