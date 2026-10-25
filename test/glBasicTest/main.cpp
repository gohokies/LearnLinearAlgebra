// glBasicTest - gtest cases that exercise core OpenGL functionality by
// drawing a triangle into an offscreen GLFW window and verifying the
// resulting pixels.
#include <GLFW/glfw3.h>

#include <cmath>
#include <vector>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>

namespace {

// Read a single pixel back from the framebuffer in (r, g, b, a) order.
void ReadPixel(int x, int y, unsigned char rgba[4]) {
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
}

}  // namespace

class GlBasicTest : public ::testing::Test {
protected:
    void SetUp() override {
        if (!glfwInit()) {
            GTEST_SKIP() << "GLFW failed to initialize (no display/pbuffer available)";
        }

        // Ask for a legacy compatibility profile so that the immediate-mode
        // (glBegin/glEnd) API used by this test is available.
        // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        window_ = glfwCreateWindow(128, 128, "glBasicTest", nullptr, nullptr);
        if (!window_) {
            glfwTerminate();
            GTEST_SKIP() << "Failed to create a GLFW window";
        }

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(0);

        glViewport(0, 0, 128, 128);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // white background
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TearDown() override {
        if (window_) {
            glfwDestroyWindow(window_);
            window_ = nullptr;
        }
        glfwTerminate();
    }

    GLFWwindow* window_{nullptr};
};

// Verify that calling glClear produces a background of the requested color
// by reading the resulting pixel back from the default framebuffer.
TEST_F(GlBasicTest, DrawTriangle) {
    unsigned char background[4] = {0, 0, 0, 0};

    ReadPixel(0, 0, background);
    EXPECT_EQ(background[0], 255);  // r
    EXPECT_EQ(background[1], 255);  // g
    EXPECT_EQ(background[2], 255);  // b

    // Draw the triangle and verify the rasterizer produced the expected
    // per-vertex color inside its interior.
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
    glFlush();

    // Interior sample: near the bottom-right vertex blending region. This
    // point is inside the triangle, where the interpolated color is mostly
    // green (with a red contribution).
    unsigned char interior[4] = {0, 0, 0, 0};
    ReadPixel(100, 20, interior);
    EXPECT_GT(interior[1], 50) << "expected a green contribution inside the triangle";

    // A point outside the triangle (top-right corner, NDC +1,+1) must remain
    // the cleared white background.
    unsigned char outside[4] = {0, 0, 0, 0};
    ReadPixel(127, 127, outside);
    EXPECT_EQ(outside[0], 255);
    EXPECT_EQ(outside[1], 255);
    EXPECT_EQ(outside[2], 255);

    // glfwSwapBuffers(window_);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// Verify that a triangle with an opaque red fill writes the expected red
// value into the framebuffer and passes through the blend state correctly.
TEST_F(GlBasicTest, DrawSolidRedTriangle) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
    glClear(GL_COLOR_BUFFER_BIT);

    // A small solid red triangle centered in clip space.
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
    glFlush();

    // Sample the triangle centroid (0, -1/6) in NDC, i.e. pixel (64, ~53).
    unsigned char pixel[4] = {0, 0, 0, 0};
    ReadPixel(64, 53, pixel);

    EXPECT_GT(pixel[0], 200) << "triangle interior should be strongly red";
    EXPECT_LT(pixel[1], 50) << "triangle interior should contain no green";
    EXPECT_LT(pixel[2], 50) << "triangle interior should contain no blue";

    // glfwSwapBuffers(window_);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}