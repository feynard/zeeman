#include "graphics.hpp"
#include "physics.hpp"

typedef vec2 point2;

point2 points[3];

// Angle
float theta = 0;

// Points of a system
vec2 o(-b, 0);
vec2 r(-radius * cos(theta), radius * sin(theta));
vec2 p(2.5, 0);

// Precision
const float z = 0.01;

// World transform
const float scale = 0.3;

GLuint VAO;
GLuint VBO;
GLuint Program;
GLuint Color;
GLuint World;
GLuint Local;

vec4 color;
mat4 world = Scale(scale);
mat4 local = Id4();

// Number of points of catastrophe curve
int n = 0;

void init(void)
{
    // Wheel (circle)
    point2 wheel[50];
    for (int i = 0; i < 50; i++)
        wheel[i] = radius * vec2(cos(i * 2 * pi / 50), sin(i * 2 * pi / 50));

    // Catastrophe curve
    point2 catastrophe[4000];

    for (float x = x_1; x < x_2; x += z)
        for (float y = 0; y < y_2; y += z)
            for (float phi = phi_1; phi < phi_2; phi += z)
                if (abs(F(x, y, phi)) <= z / 2 && abs(G(x, y, phi)) <= z / 2)
                    catastrophe[n++] = vec2(x, y);

    for (float x = x_2; x > x_1; x -= z)
        for (float y = 0; y > y_1; y -= z)
            for (float phi = phi_1; phi < phi_2; phi += z)
                if (abs(F(x, y, phi)) <= z / 2 && abs(G(x, y, phi)) <= z / 2)
                    catastrophe[n++] = vec2(x, y);

    point2 * curve = new vec2[n / 3 - 1];
    for (int i = 0; i < n - 3; i += 3) {
        curve[i / 3] =
            (catastrophe[i] + catastrophe[i + 1] + catastrophe[i + 2]) / 3;
    }

    n = n / 3 - 1;

    // Spring
    point2 spring[18];
    spring[0] = vec2(0, 0);
    spring[1] = vec2(0.1, 0);
    for (int i = 2; i < 16; i++)
        spring[i] = vec2(0.1 * i, 0.1 * pow(-1, i % 2));

    spring[16] = vec2(1.6, 0);
    spring[17] = vec2(1.7, 0);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    Program = ShaderInit(
        "shader.vert",
        "shader.frag");

    glUseProgram(Program);

    points[0] = p;
    points[1] = r;
    points[2] = o;

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(wheel) + n * sizeof(vec2) + sizeof(spring),
        NULL,
        GL_STATIC_DRAW
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(points),
        points
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        sizeof(points),
        sizeof(wheel),
        wheel
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(wheel),
        n * sizeof(vec2),
        curve
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        sizeof(points) + sizeof(wheel) + n * sizeof(vec2),
        sizeof(spring),
        spring
    );

    delete[] curve;

    GLuint loc = glGetAttribLocation(Program, "vertex_position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    Color = glGetUniformLocation(Program, "color");
    Local = glGetUniformLocation(Program, "local_transform");
    World = glGetUniformLocation(Program, "world_transform");

    glClearColor(40.0 / 255, 40.0 / 255, 40.0 / 255, 1.0);
}

float mod2pi(float phi)
{
    if (phi > pi)
        return phi - 2 * pi;
    if (phi < 0)
        return phi + 2 * pi;

    return phi;
}

float dt = 0.5;
float omega = 0, alpha = 0;
float friction = 0.2;
float t = 0;

bool sin_movement = false;
bool circle_movement = false;
vec2 center;

void idle()
{
    if (sin_movement) {
        t += 0.03;
        p.y = 0.5 * sin(t);
    } else if (circle_movement) {
        t += 0.03;
        p = center + 0.2 * vec2(cos(t), sin(t));
    }

    t = mod2pi(t);

    alpha = radius * F(p.x, p.y, theta);
    omega += alpha * dt;
    omega *= (1 - friction);
    theta -= omega * dt;

    theta = mod2pi(theta);

    r = radius * vec2(-cos(theta), sin(theta));

    glutPostRedisplay();
}

bool show_curve = false;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Wheel
    color = vec4(69 / 255.0, 133 / 255.0, 136 / 255.0, 1.0);
    glUniform4fv(Color, 1, (GLfloat*) & color);
    glDrawArrays(GL_LINE_LOOP, 3, 50);

    // Catastrophe curve
    if (show_curve) {
        color = vec4(250 / 255.0, 189 / 255.0, 47 / 255.0, 1.0);
        glUniform4fv(Color, 1, (GLfloat*) & color);
        glPointSize(1);
        glDrawArrays(GL_LINE_LOOP, 53, n);
    }

    // Elastics
    color = vec4(204 / 255.0, 36 / 255.0, 29 / 255.0, 1.0);
    glUniform4fv(Color, 1, (GLfloat*) & color);

    // First spring
    local =
        Translate(-b, 0.0, 0.0) *
        RotZ(asin(radius * sin(theta) / length(o - r))) *
        ScaleX(length(o - r) / 1.7);

    glUniformMatrix4fv(Local, 1, true, (GLfloat*) & local);
    glDrawArrays(GL_LINE_STRIP, 53 + n, 18);

    // Second spring
    if ((p - r).y > 0)
        local =
            Translate(r.x, r.y, 0.0) *
            RotZ(acos((p - r).x / length(p - r))) *
            ScaleX(length(p - r) / 1.7);
    else
        local =
            Translate(r.x, r.y, 0.0) *
            RotZ(-acos((p - r).x / length(p - r))) *
            ScaleX(length(p - r) / 1.7);

    glUniformMatrix4fv(Local, 1, true, (GLfloat*) & local);
    glDrawArrays(GL_LINE_STRIP, 53 + n, 18);

    // p, r, o points
    color = vec4(251 / 255.0, 73 / 255.0, 52 / 255.0, 1.0);
    glUniform4fv(Color, 1, (GLfloat*) & color);
    glPointSize(7);

    // p - vector
    local = Id4();
    glUniformMatrix4fv(Local, 1, true, (GLfloat*) & local);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec2), &p);
    glDrawArrays(GL_POINTS, 0, 1);

    // r - vector
    local = RotZ(-theta);
    glUniformMatrix4fv(Local, 1, true, (GLfloat*) & local);
    glDrawArrays(GL_POINTS, 1, 1);

    // o - vector
    local = Id4();
    glUniformMatrix4fv(Local, 1, true, (GLfloat*) & local);
    glDrawArrays(GL_POINTS, 2, 1);

    // Buffer swap
    glutSwapBuffers();
}

//
// GLUT part
//

// Window width and height
int w, h;

// Keyboard handler (exit only)
void keyboard(unsigned char key, int x, int y)
{
    if (key == 's')
        show_curve ? show_curve = false : show_curve = true;

    if (key == '1') {
        sin_movement ? sin_movement = false : sin_movement = true;
        if (sin_movement)
            circle_movement = false;
    }

    if (key == '2') {
        circle_movement ? circle_movement = false : circle_movement = true;
        if (circle_movement) {
            center = p;
            sin_movement = false;
        }
    }



    if (key == 033 || key == 'q')
        exit(EXIT_SUCCESS);
}

// Window coordinates before button was pressed
int x_prev, y_prev;
// Left mouse button is pressed
bool left_button;

// Mouse handling
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {

        // OpenGL coordinates:
        // x =   2 * x_screen / w - 1
        // y = - 2 * y_sxreen / h + 1

        x_prev = x;
        y_prev = y;

        if (abs(p.x * scale / 1.5 - (float) x / w * 2 + 1) <= 0.05 &&
            abs(p.y * scale + (float) y / h * 2 - 1) <= 0.05)
            left_button = true;
    } else
        left_button = false;
}

// Change poistion of p (i.e. finger position)
void mouse_motion(int x, int y)
{
    float delta_x = (float) 2 * (x_prev - x) / w * 1.5;
    float delta_y = (float) 2 * (y_prev - y) / h;

    x_prev = x;
    y_prev = y;

    if (left_button)
        p += vec2(-delta_x, delta_y) / scale;
}

// Viewport
void reshape(GLsizei w_new, GLsizei h_new)
{
    glUniformMatrix4fv(World, 1, true, (GLfloat*) & world);

    w = w_new;
    h = h_new;
}

// Glut initialization
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_3_2_CORE_PROFILE);

    // Initial picture size
    w = 1200; h = 800;
    world[0][0] /= (float) w / h;

    glutInitWindowSize(w, h);

    glutCreateWindow("Zeeman's Catastrophe Machine");

    init();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
