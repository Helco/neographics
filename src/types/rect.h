#pragma once
#ifdef NGFX_IS_CORE
#include <stdint.h>
#else
#include <pebble.h>
#endif
#include "point.h"
#include "size.h"

/*-----------------------------------------------------------------------------.
|                                                                              |
|                                    Rect                                      |
|                                                                              |
`-----------------------------------------------------------------------------*/

/*! \addtogroup Types
 *  @{
 *  \addtogroup typerect Rect
 *  @{
 */

typedef struct n_GRect {
    n_GPoint origin;
    n_GSize size;
} n_GRect;

/*!
 * Convenience macro to quickly define a rectangle.
 */
#define n_GRect(x, y, w, h) ((n_GRect) {{x, y}, {w, h}})

/*!
 * Convenience macro to standardize a rectangle.
 * \warning Differs from the Pebble OS implementation, which is in-place and
 * takes a pointer.
 */
#define n_grect_standardize(a) \
    ((a).size.w >= 0 \
        ? (a).size.h >= 0 \
            /* normal */ \
            ? (n_GRect) { {  (a).origin.x,      (a).origin.y }, \
                          {  (a).size.w,        (a).size.h     }} \
            /* switch vertically */ \
            : (n_GRect) { {  (a).origin.x,      (a).origin.y + (a).size.h }, \
                          {  (a).size.w,       -(a).size.h }} \
        : (a).size.h >= 0 \
            /* switch horizontally */ \
            ? (n_GRect) { {  (a).origin.x + (a).size.w, (a).origin.y }, \
                          { -(a).size.w,    (a).size.h     }} \
            /* switch horizontally and vertically */ \
            : (n_GRect) { {  (a).origin.x + (a).size.w, (a).origin.y + (a).size.h }, \
                          { -(a).size.w,   -(a).size.h }})

/*!
 * Returns the point at the center of a GRect (will prefer top and/or left
 * at even sizes)
 */
n_GPoint n_grect_center_point(n_GRect *rect);

/*! @}
 *  @}
 */
