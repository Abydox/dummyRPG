#pragma once

#include <vector>

#include "dummyrpg/dummy_types.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace Dummy {

const uint16_t MAX_LAYER_BORDER_SIZE = 2000;

///////////////////////////////////////////////////////////////////////////////

// Template class, must be fully defined in .hpp

///
/// \brief A Layer is a simple wrapper around a vector
///
template <typename T> class Layer
{
public:
    Layer() {}

    ///
    /// \brief Layer Constructor of layer, fill width default value
    /// \param width wanted width, must not exceed MAX_LAYER_BORDER_SIZE
    /// \param height wanted height, must not exceed MAX_LAYER_BORDER_SIZE
    /// \param defaultValue default value to fill all cells
    ///
    Layer(uint16_t width, uint16_t height, T defaultValue)
    {
        if (width > MAX_LAYER_BORDER_SIZE)
            width = MAX_LAYER_BORDER_SIZE;
        if (height > MAX_LAYER_BORDER_SIZE)
            height = MAX_LAYER_BORDER_SIZE;

        m_width   = width;
        m_height  = height;
        m_content = std::vector(width * height, defaultValue);
    }

    uint16_t width() const { return m_width; }
    uint16_t height() const { return m_height; }
    size_t size() const { return m_content.size(); }

    ///
    /// \brief at Get value at coordinates
    /// \param coords Coordinates where to read value. Must be valid.
    /// \return value read
    ///
    T at(tilecoords coords) const
    {
        uint32_t rowIdx = coords.second; // use uint32_t to avoid uint16 overflow
        return m_content[coords.first + rowIdx * m_width];
    }
    ///
    /// \brief set Set value at coordinates
    /// \param coords Coordinates where to write value. Must be valid.
    /// \param val Value to write.
    ///
    void set(tilecoords coords, T val)
    {
        uint32_t rowIdx                            = coords.second;
        m_content[coords.first + rowIdx * m_width] = val;
    }
    ///
    /// \brief areCoordValid check if coordinates are valid
    /// \param coords coords to check
    /// \return true if valid
    ///
    bool areCoordValid(tilecoords coords)
    {
        uint32_t rowIdx = coords.second;
        return (coords.first + rowIdx * m_width) < m_content.size();
    }

private:
    std::vector<T> m_content;
    uint16_t m_width  = 0;
    uint16_t m_height = 0;
};

///////////////////////////////////////////////////////////////////////////////

using GraphicLayer  = Layer<tileaspect>;
using BlockingLayer = Layer<bool>;

///////////////////////////////////////////////////////////////////////////////

} // namespace Dummy
