/******************************************************************************
* Copyright (c) 2016, Howard Butler (howard@hobu.co)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/
#pragma once

#include <pdal/Log.hpp>
#include <pdal/PointRef.hpp>
#include <pdal/SpatialReference.hpp>
#include <pdal/util/Bounds.hpp>
#include <pdal/Geometry.hpp>

#include <geos_c.h>

namespace pdal
{

namespace geos { class ErrorHandler; }

class PDAL_DLL Polygon : public Geometry
{
public:
    Polygon();
    Polygon(const std::string& wkt_or_json,
           SpatialReference ref = SpatialReference());
    Polygon(const Polygon&);
    Polygon(const BOX2D&);
    Polygon(const BOX3D&);
    Polygon(GEOSGeometry* g, const SpatialReference& srs);
    Polygon(OGRGeometryH g, const SpatialReference& srs);
    Polygon& operator=(const Polygon&);

    OGRGeometryH getOGRHandle();

    ~Polygon();

    Polygon simplify(double distance_tolerance, double area_tolerance) const;
    Polygon transform(const SpatialReference& ref) const;
    double area() const;

    bool covers(const PointRef& ref) const;
    bool equal(const Polygon& p) const;
    bool covers(const Polygon& p) const;
    bool overlaps(const Polygon& p) const;
    bool contains(const Polygon& p) const;
    bool touches(const Polygon& p) const;
    bool within(const Polygon& p) const;
    bool crosses(const Polygon& p) const;

private:
    void initializeFromBounds(const BOX3D& b);


};

//
// PDAL_DLL std::ostream& operator<<(std::ostream& ostr,
//     const Polygon& p);
// PDAL_DLL std::istream& operator>>(std::istream& istr, Polygon& p);

} // namespace pdal
