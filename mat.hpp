#ifndef MAT_HPP
#define MAT_HPP

#include "vec.hpp"

#include <iostream>
#include <cmath>

//
// Two by two real valued matrix
//
class mat2 {

    vec2 M_[2];

public:

    //
    // Constructors
    //

    mat2();

    // Two row vectors
    mat2(const vec2& a, const vec2& b);

    // Diagonal matrix
    mat2(const float s);

    // Explicit constructor
    mat2(
    float a00, float a01,
    float a10, float a11);

    // Copy constructor
    mat2(const mat2 & A);


    //
    // Operator overloading
    //

    // Indexing operator
    vec2& operator [] (const unsigned int i);
    const vec2& operator [] (const unsigned int i) const;

    // Sum inverse
    mat2 operator - () const;

    // Sum and difference
    friend mat2 operator + (const mat2& A, const mat2& B);
    friend mat2 operator - (const mat2& A, const mat2& B);

    // Multiplication by a scalar
    mat2 operator * (const float s) const;
    mat2 operator / (const float s) const;
    friend mat2 operator * (const float c, const mat2& A);

    // Matrix multiplication
    friend mat2 operator * (const mat2& A, const mat2& B);

    // Compound assignment
    mat2& operator += (const mat2& A);
    mat2& operator -= (const mat2& A);
    mat2& operator *= (const float s);
    mat2& operator /= (const float s);
    mat2& operator *= (const mat2& A);

    // Matrix-vector multiplication
    friend vec2 operator * (const mat2& A, const vec2& v);

    // Output
    friend std::ostream& operator << (std::ostream& os, const mat2& A);
};

// Matrix operations

mat2 transpose(const mat2& A);
float det(const mat2& A);

// Anticlockwise rotation about the origin
mat2 Rot(const float theta);

// Reflection with respect to the axis that makes
// angle theta with positive x direction
mat2 Ref(const float theta);

//
// Three by three real valued matrix
//

class mat3 {

    vec3 M_[3];

public:

    //
    // Constructors
    //

    mat3();

    // Three row vectors
    mat3(const vec3& u, const vec3& v, const vec3& w);

    // Diagonal matrix
    mat3(const float s);

    // Explicit constructor
    mat3(
    const float a00, const float a01, const float a02,
    const float a10, const float a11, const float a12,
    const float a20, const float a21, const float a22);

    // Copy constructor
    mat3(const mat3 & A);

    //
    // Operator overloading
    //

    // Indexing operator
    vec3& operator [] (const unsigned int i);
    const vec3& operator [] (const unsigned int i) const;

    // Sum inverse
    mat3 operator - () const;

    // Sum and difference
    friend mat3 operator + (const mat3& A, const mat3& B);
    friend mat3 operator - (const mat3& A, const mat3& B);

    // Multiplication by a scalar
    mat3 operator * (const float s) const;
    mat3 operator / (const float s) const;
    friend mat3 operator * (const float s, const mat3& A);

    // Matrix multiplication
    friend mat3 operator * (const mat3& A, const mat3& B);

    // Compound assignments
    mat3& operator += (const mat3& A);
    mat3& operator -= (const mat3& A);
    mat3& operator *= (const float s);
    mat3& operator /= (const float s);
    mat3& operator *= (const mat3& A);

    // Matrix-vector multiplication
    friend vec3 operator * (const mat3& A, const vec3& v);

    // Output
    friend std::ostream& operator << (std::ostream& os, const mat3& A);
};

// Matrix operations
mat3 transpose(const mat3& A);
float det(const mat3& A);

// Rotations
mat3 Rx(const float theta);
mat3 Ry(const float theta);
mat3 Rz(const float theta);
mat3 R(const vec3 & v);



//
// Homogeneous four by four matrix
//
struct mat4 {

    vec4 M_[4];

//public:

    //
    // Constructors
    //

    mat4();

    // Four row vectors
    mat4(const vec4 & a, const vec4 & b, const vec4 & c, const vec4 & d);

    // Diagonal matrix
    mat4(const float s);

    // Explicit constructor
    mat4(
    const float a00, const float a01, const float a02, const float a03,
    const float a10, const float a11, const float a12, const float a13,
    const float a20, const float a21, const float a22, const float a23,
    const float a30, const float a31, const float a32, const float a33);

    // Copy constructor
    mat4(const mat4 & A);

    //
    // Operator overloading
    //

    // Indexing operator
    vec4 & operator [] (const unsigned int i);
    const vec4 & operator [] (const unsigned int i) const;

    // Matrix multiplication
    friend mat4 operator * (const mat4 & A, const mat4 & B);

    // Matrix-vector multiplication
    friend vec4 operator * (const mat4& A, const vec4& v);
    friend vec3 operator * (const mat4& A, const vec3& v);

    // Output
    friend std::ostream& operator << (std::ostream& os, const mat4 & A);
};

// Identity
mat4 Id4();

// Rotation matrices generators
mat4 RotX(const float theta);
mat4 RotY(const float theta);
mat4 RotZ(const float theta);
mat4 Rotate(const vec3 & v);

mat4 SmallRotX(const float theta);
mat4 SmallRotY(const float theta);
mat4 SmallRotZ(const float theta);

// Scaling matrices
mat4 Scale(const float a);
mat4 ScaleX(const float a);
mat4 ScaleY(const float a);
mat4 ScaleZ(const float a);

mat4 Scale(const float a, const float b, const float c);
mat4 Scale(const vec3 & v);

// Uniform translation matrix
mat4 Translate(const float x, const float y, const float z);
mat4 Translate(const vec3 & v);
mat4 Translate(const vec4 & v);

#endif
