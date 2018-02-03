#include <cmath>

// Zero precision
const float d = 0.001;

//
// Parameters of a system
//

// Rigidities
const float k_1 = 1.0;
const float k_2 = 1.0;

// Elastic lengths
const float a_1 = 1.0;
const float a_2 = 1.0;

const float b = 3.0;    // Distance between the pin and the origin
const float radius = 1.0;    // Radius of a wheel

// Boundaries
const float x_1 = 2.0;
const float x_2 = 4.0;

const float y_1 = -1.0;
const float y_2 =  1.0;

const float phi_1 = -pi;
const float phi_2 =  pi;

// Force projection
float F(float x, float y, float phi)
{
    float c_1, c_2;

    c_1 = sqrt(b * b - 2 * b * radius * cos(phi) + radius * radius);
    c_2 = sqrt(x * x + y * y + 2 * radius * (x * cos(phi) - y * sin(phi)) +
        radius * radius);

    return
        k_1 * (1 - a_1 / c_1) * b * sin(phi) -
        k_2 * (1 - a_2 / c_2) * (x * sin(phi) + y * cos(phi));
}

float G(float x, float y, float phi)
{
    return (F(x, y, phi + d) - F(x, y, phi)) / d;
}
