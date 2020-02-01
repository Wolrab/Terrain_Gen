#ifndef __MATH_H
#define __MATH_H

struct Vector3f {
    float x, y, z;

    Vector3f() {}

    Vector3f(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f& operator+=(Vector3f &o) {
        x += o.x;
        y += o.y;
        z += o.z;

        return *this;
    }
};

struct Matrix4f {
    
}

#endif /* __MATH_H */