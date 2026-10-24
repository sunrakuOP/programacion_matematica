// Preview de graficos -- adelanto de Fase 4 (ruta_codigo), NO es el
// contenido completo de esa fase, es solo para ver "el vector" en pantalla
// como pediste. Dibuja los ejes X/Y y un vector como lineas, sin camara,
// sin proyeccion 3D, sin GLM todavia -- coordenadas directas en NDC
// ([-1,1]), que es lo minimo necesario para que algo aparezca en pantalla
// con OpenGL moderno (core profile, todo por shaders, no hay pipeline fijo).
//
// El vector que se dibuja es el mismo (3,4) que ya verificaste a mano en
// Vector2D -- lo unico nuevo aca es COMO se ve, no los numeros.

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/Vector2D.hpp"

static const char* vertexShaderSrc = R"(
#version 410 core
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 410 core
uniform vec3 color;
out vec4 FragColor;
void main() {
    FragColor = vec4(color, 1.0);
}
)";

GLuint compilarShader(GLenum tipo, const char* fuente) {
    GLuint shader = glCreateShader(tipo);
    glShaderSource(shader, 1, &fuente, nullptr);
    glCompileShader(shader);

    int exito;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &exito);
    if (!exito) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Error compilando shader: " << log << std::endl;
    }
    return shader;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al iniciar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // obligatorio en Mac

    GLFWwindow* window = glfwCreateWindow(800, 800, "Vector2D preview", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error al crear la ventana\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Error al cargar GLAD\n";
        return -1;
    }

    // --- shaders ---
    GLuint vs = compilarShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compilarShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint programa = glCreateProgram();
    glAttachShader(programa, vs);
    glAttachShader(programa, fs);
    glLinkProgram(programa);
    glDeleteShader(vs);
    glDeleteShader(fs);
    GLint colorLoc = glGetUniformLocation(programa, "color");

    // --- datos: ejes + el vector, todo en NDC [-1,1] ---
    Vector2D v{3.0, 4.0};
    double escala = 0.15;  // para que (3,4) entre comodo en NDC
    float vx = (float)(v.x * escala);
    float vy = (float)(v.y * escala);

    float ejes[] = {
        -0.9f,  0.0f,   0.9f,  0.0f,   // eje X
         0.0f, -0.9f,   0.0f,  0.9f    // eje Y
    };
    float vectorLinea[] = {
        0.0f, 0.0f,
        vx,   vy
    };

    GLuint vaoEjes, vboEjes;
    glGenVertexArrays(1, &vaoEjes);
    glGenBuffers(1, &vboEjes);
    glBindVertexArray(vaoEjes);
    glBindBuffer(GL_ARRAY_BUFFER, vboEjes);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ejes), ejes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint vaoVector, vboVector;
    glGenVertexArrays(1, &vaoVector);
    glGenBuffers(1, &vboVector);
    glBindVertexArray(vaoVector);
    glBindBuffer(GL_ARRAY_BUFFER, vboVector);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vectorLinea), vectorLinea, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::cout << "Vector dibujado: " << v << ", magnitud = " << v.magnitud() << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programa);

        glUniform3f(colorLoc, 0.4f, 0.4f, 0.4f);  // ejes en gris
        glBindVertexArray(vaoEjes);
        glDrawArrays(GL_LINES, 0, 4);

        glUniform3f(colorLoc, 1.0f, 0.6f, 0.1f);  // vector en naranja
        glBindVertexArray(vaoVector);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
