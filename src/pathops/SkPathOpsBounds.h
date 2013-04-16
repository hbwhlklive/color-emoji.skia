/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathOpBounds_DEFINED
#define SkPathOpBounds_DEFINED

#include "SkPathOpsRect.h"
#include "SkRect.h"

// SkPathOpsBounds, unlike SkRect, does not consider a line to be empty.
struct SkPathOpsBounds : public SkRect {
    static bool Intersects(const SkPathOpsBounds& a, const SkPathOpsBounds& b) {
        return a.fLeft <= b.fRight && b.fLeft <= a.fRight &&
                a.fTop <= b.fBottom && b.fTop <= a.fBottom;
    }

    // FIXME: add() is generically useful and could be added directly to SkRect
    void add(SkScalar left, SkScalar top, SkScalar right, SkScalar bottom) {
        if (left < fLeft) fLeft = left;
        if (top < fTop) fTop = top;
        if (right > fRight) fRight = right;
        if (bottom > fBottom) fBottom = bottom;
    }

    void add(const SkPathOpsBounds& toAdd) {
        add(toAdd.fLeft, toAdd.fTop, toAdd.fRight, toAdd.fBottom);
    }

    void add(const SkPoint& pt) {
        if (pt.fX < fLeft) fLeft = pt.fX;
        if (pt.fY < fTop) fTop = pt.fY;
        if (pt.fX > fRight) fRight = pt.fX;
        if (pt.fY > fBottom) fBottom = pt.fY;
    }

    // unlike isEmpty(), this permits lines, but not points
    // FIXME: unused for now
    bool isReallyEmpty() const {
        // use !<= instead of > to detect NaN values
        return !(fLeft <= fRight) || !(fTop <= fBottom)
                || (fLeft == fRight && fTop == fBottom);
    }

    void setCubicBounds(const SkPoint a[4]);
    void setLineBounds(const SkPoint a[2]);
    void setQuadBounds(const SkPoint a[3]);

    void setPointBounds(const SkPoint& pt) {
        fLeft = fRight = pt.fX;
        fTop = fBottom = pt.fY;
    }

    typedef SkRect INHERITED;
};

extern void (SkPathOpsBounds::*SetCurveBounds[])(const SkPoint[]);

#endif