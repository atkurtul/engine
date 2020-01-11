#include "animation.h"
#include "clock.h"

mat4 interpolate(const mat4& x, const mat4& y, float t)
{
    quat q0 = x, q1 = y;
    mat4 re = q0 * (1.f - t) + sign(dot(q0, q1)) * t * q1;
    re.col[3].xyz = x.col[3].xyz + (y.col[3].xyz - x.col[3].xyz) * t;
    return re;
}

mat4* frame::getPoseAt(float t) const
{
    mat4* re = 0;
    if (input.empty()) return re;
    for (uint i = 1; i < input.size(); ++i)
    {
        if (input[i] > t)
        {
            t = (t - input[i - 1]) / (input[i] - input[i - 1]);
            return re = new mat4(interpolate(output[i - 1], output[i], t));
        }
    }
}

void animation::update() const
{
    t += clock::dt;
    if (t >= len) t -= len;
}
