//
//  branch.h
//  LeapKingyo28
//
//  Created by 岩城勇磨 on 2015/02/01.
//
//

#ifndef __LeapKingyo28__branch__
#define __LeapKingyo28__branch__

#include <stdio.h>
#include "ofMain.h"

class Branch {
public:
    float segments, startAngle, theta, num, t_x, t_y;
    Branch();
    void branch(float len);
    void position_x();
};

#endif /* defined(__LeapKingyo28__branch__) */
