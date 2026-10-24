#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

const char* vertexShaderSrc = R"(
#version 410 core
layout(location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
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

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Error compilando shader: " << log << "\n";
    }
    return shader;
}

GLuint crearPrograma() {
    GLuint vs = compilarShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compilarShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint programa = glCreateProgram();
    glAttachShader(programa, vs);
    glAttachShader(programa, fs);
    glLinkProgram(programa);

    GLint ok;
    glGetProgramiv(programa, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(programa, 512, nullptr, log);
        std::cerr << "Error linkeando programa: " << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return programa;
}

GLuint crearVAO(const std::vector<float>& puntos) {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, puntos.size() * sizeof(float), puntos.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    return vao;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al iniciar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "y = sen(x)", nullptr, nullptr);
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

    GLuint programa = crearPrograma();

    // Curva: x en [-pi, pi] normalizado a [-1, 1], y = sen(x) escalado para dejar margen.
    std::vector<float> curva;
    const int N = 200;
    for (int i = 0; i <= N; i++) {
        float x = -M_PI + (2.0f * M_PI) * i / N;
        float xNdc = x / M_PI;
        float yNdc = std::sin(x) * 0.8f;
        curva.push_back(xNdc);
        curva.push_back(yNdc);
    }
    GLuint vaoCurva = crearVAO(curva);

    // Ejes de referencia: una línea horizontal y una vertical.
    std::vector<float> ejes = {
        -1.0f, 0.0f,  1.0f, 0.0f,   // eje X
         0.0f, -1.0f, 0.0f, 1.0f    // eje Y
    };
    GLuint vaoEjes = crearVAO(ejes);

    GLint colorLoc = glGetUniformLocation(programa, "color");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programa);

        glUniform3f(colorLoc, 0.4f, 0.4f, 0.4f);
        glBindVertexArray(vaoEjes);
        glDrawArrays(GL_LINES, 0, 4);

        glUniform3f(colorLoc, 0.3f, 0.8f, 1.0f);
        glBindVertexArray(vaoCurva);
        glDrawArrays(GL_LINE_STRIP, 0, N + 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
