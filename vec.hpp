#ifndef VEC_HPP
#define VEC_HPP

#include <iostream>
#include <cmath>
#include <iomanip>

// Zero tolerance, that is any number less than this considered to be 0
const float zero_tolerance = 1e-6;

//
// Two-dimensional real vector
//
struct vec2 {
    float x;
    float y;

    // Constructors
    vec2();
    vec2(float s);
    vec2(const float a, const float b);
    vec2(const vec2 & v);

    // Vector normalization to a given value
    void normalize(const float r);

    //
    // Operator overloading
    //

    // Inverse
    vec2 operator - () const;

    // Vector sum and difference
    friend vec2 operator + (const vec2& u, const vec2& v);
    friend vec2 operator - (const vec2& u, const vec2& v);

    // Multiplication by a scalar
    vec2 operator * (const float c) const;
    vec2 operator / (const float c) const;
    friend vec2 operator * (const float c, const vec2& v);

    // Compound assignment
    vec2& operator += (const vec2& v);
    vec2& operator -= (const vec2& v);
    vec2& operator *= (const float c);
    vec2& operator /= (const float c);

    // Indexing operators
    float& operator [] (const unsigned int i);
    const float operator [] (const unsigned int i) const;

    // Input and output
    friend std::ostream& operator << (std::ostream& os, const vec2& v);
    friend std::istream& operator >> (std::istream& is, vec2& v);
};

// Standard inner product
float dot(const vec2& u, const vec2& v);

// Length of a vector
float length(const vec2& v);

// Normalized vector
vec2 normalize(const vec2& v);


//
// Three-dimensional real vector
//
struct vec3 {
    float x;
    float y;
    float z;

    // Constructors
    vec3();
    vec3(float s);
    vec3(const float a, const float b, const float c);
    vec3(const vec3& v);
    vec3(const vec2& v, const float s);


    // Vector normalization
    void normalize();
    void normalize(const float r);

    //
    // Operator overloading
    //

    // Inverse
    vec3 operator - () const;

    // Vector sum and difference
    friend vec3 operator + (const vec3& u, const vec3& v);
    friend vec3 operator - (const vec3& u, const vec3& v);

    // Multiplication by a scalar
    vec3 operator * (const float c) const;
    vec3 operator / (const float c) const;
    friend vec3 operator * (const float c, const vec3& v);

    // Compound assignment
    vec3& operator += (const vec3& v);
    vec3& operator -= (const vec3& v);
    vec3& operator *= (const float c);
    vec3& operator /= (const float c);

    // Indexing operators
    float& operator [] (const unsigned int i);
    const float operator [] (const unsigned int i) const;

    // Cross product
    friend vec3 operator * (const vec3& u, const vec3& v);

    // Input and output
    friend std::ostream& operator << (std::ostream& os, const vec3& v);
    friend std::istream& operator >> (std::istream& is, vec3& v);
};

// Standard inner product
float dot(const vec3& u, const vec3& v);

// Length of a vector
float length(const vec3& v);

// Normalized vector
vec3 normalize(const vec3& v);


//
// Four-dimensional vector for homogeneous coordinates
//
struct vec4 {
    float x;
    float y;
    float z;
    float w;

    // Constructors
    vec4();
    vec4(const float s);
    vec4(const float a, const float b, const float c, const float d);
    vec4(const vec4 & v);
    vec4(const vec3 & v, const float s);

    //
    // Operator overloading
    //

    // Indexing operators
    float& operator [] (const unsigned int i);
    const float operator [] (const unsigned int i) const;

    // Extraction operator
    friend std::ostream& operator << (std::ostream& os, const vec4& v);
    friend std::istream& operator >> (std::istream& is, vec4& v);
};


//
// Some geometrical functions involving vectors
//

// Check if point belong to a given segment
bool belongs_to_segment(const vec2 & point, const vec2 & end_0,
    const vec2 & end_1, const double precision);

#endif
