#include "DrawFunctions.h"
#include <math.h>
#include <vector>

namespace jm
{
	float getRadian(const float & degree) // degree to radian
	{
		return degree / 180.0f * 3.141592f;
	}
	
	void drawLine(const RGB & color0, const vec2 & position0, const vec3 & color1, const vec2 & position1)
	{
		glBegin(GL_LINES);
		{
			glColor3fv(&color0[0]);
			glVertex2fv(&position0[0]);
			glColor3fv(&color1[0]);
			glVertex2fv(&position1[0]);
		}
		glEnd();
	}
	
	void beginTransformation()
	{
		glPushMatrix();
	}

	void endTransformation()
	{
		glPopMatrix();
	}
	
	void translate(const float & pos_x, const float & pos_y)
	{
		glTranslatef(pos_x, pos_y, 0.0);
	}

	void translate(const vec2 & dx)
	{
		glTranslatef(dx.x, dx.y, 0.0);
	}

	void rotate(const float & degree)
	{
		glRotatef(degree, 0.0, 0.0, 1.0);
	}

	void scale(const float & scale_x, const float & scale_y)
	{
		glScalef(scale_x, scale_y, 1.0);
	}

	void drawPoint(const RGB & color, const vec2 & position, const float & size)
	{
		glColor3fv(color.data);
		glPointSize(size);
		glBegin(GL_POINTS);
		glVertex2fv(position.data);
		glEnd();
	}

	void drawWiredTriangle(const RGB & color, const float & edge_length)
	{
		drawWiredRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 90.0f, 3);
	}

	void drawWiredTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2)
	{
		glColor3fv(color.data);
		glBegin(GL_LINE_LOOP);
		glVertex2fv(v0.data);
		glVertex2fv(v1.data);
		glVertex2fv(v2.data);
		glEnd();
	}

	void drawFilledTriangle(const RGB& color, const vec2& v0, const vec2& v1, const vec2& v2)
	{
		glColor3fv(color.data);
		glBegin(GL_TRIANGLES);
		glVertex2fv(v0.data);
		glVertex2fv(v1.data);
		glVertex2fv(v2.data);
		glEnd();
	}

	void drawWiredSquare(const RGB & color, const float & edge_length)
	{
		drawWiredRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 45.0f, 4);
	}

	void drawFilledSquare(const RGB & color, const float & edge_length)
	{
		drawFilledRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.f), 45.0f, 4);
	}
	
	void drawFilledBox(const RGB & color, const float & width, const float & height)
	{
		const vec2 left_bottom(-0.5f * width, -0.5f * height);

		glColor3fv(&color[0]);
		glBegin(GL_QUADS);
		{
			glVertex2f(left_bottom.x, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y + height);
			glVertex2f(left_bottom.x, left_bottom.y + height);
		}
		glEnd();
	}

	void drawWiredBox(const RGB & color, const float & width, const float & height)
	{
		const vec2 left_bottom(-0.5f * width, -0.5f * height);

		glColor3fv(&color[0]);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left_bottom.x, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y);
			glVertex2f(left_bottom.x + width, left_bottom.y + height);
			glVertex2f(left_bottom.x, left_bottom.y + height);
		}
		glEnd();
	}

	void drawFilledRegularConvexPolygon(const RGB & color, const float & radius, const float & theta_start, const int & num_segments)
	{
		const float d_theta = 3.141592f * 2.0f / static_cast<float>(num_segments);

		glColor3fv(&color[0]);

		glBegin(GL_TRIANGLE_FAN);
		{
			float theta = getRadian(theta_start);
			for (int i = 0; i < num_segments; ++i)
			{
				glVertex2f(radius * cosf(theta), radius * sinf(theta));

				theta += d_theta;
			}
		}
		glEnd();
	}

	void drawFilledCircle(const RGB & color, const float & radius)
	{
		drawFilledRegularConvexPolygon(color, radius - 1e-4f, 0.0f, 30);
		drawWiredRegularConvexPolygon(color, radius, 0.0f, 30); // draw smooth boundary
	}

	void drawFilledTriangle(const RGB & color, const float & edge_length)
	{
		drawFilledRegularConvexPolygon(color, edge_length * 0.5f * sqrtf(2.0f), 90.0f, 3);
	}

	void drawGrid(const RGB & color, const float & dx)
	{
		const float maxl = 2.0f;
		const float dy = dx;

		// vertical
		for (float x = 0.0f; x < maxl; x += dx)
			drawLine(color, vec2(x, -maxl), color, vec2(x, +maxl));

		for (float x = -dx; x > -maxl; x -= dx)
			drawLine(color, vec2(x, -maxl), color, vec2(x, +maxl));

		// horizontal
		for (float y = 0.0f; y < maxl; y += dy)
			drawLine(color, vec2(-maxl, y), color, vec2(maxl, y));

		for (float y = -dy; y > -maxl; y -= dy)
			drawLine(color, vec2(-maxl, y), color, vec2(maxl, y));

	}

	void setLineWidth(const int & width)
	{
		glLineWidth(static_cast<float>(width));
	}

	void drawWiredRegularConvexPolygon(const RGB & color, const float & radius, const float & start_theta, const int & num_segments)
	{
		const float d_theta = 3.141592f * 2.0f / (float)num_segments;

		glColor3fv(&color[0]);

		glBegin(GL_LINE_LOOP);
		{
			float theta = getRadian(start_theta);
			for (int i = 0; i < num_segments; ++i)
			{
				glVertex2f(radius * cosf(theta), radius * sinf(theta));

				theta += d_theta;
			}
		}
		glEnd();
	}

	void drawWiredCircle(const RGB & color, const float & radius)
	{
		drawWiredRegularConvexPolygon(color, radius, 0.0f, 30);
	}

	void drawWiredPentagon(const RGB & color, const float & radius)
	{
		drawWiredRegularConvexPolygon(color, radius, 90.0f, 5);
	}

	void drawFilledPentagon(const RGB & color, const float & radius)
	{
		drawFilledRegularConvexPolygon(color, radius, 90.0f, 5);
		drawWiredPentagon(color, radius);// draw smooth boundary
	}

	std::vector<vec2> makeRegularConvexPolygon(const float & radius, const float & theta_start, const int & num_segments)
	{
		std::vector<vec2> vertices;
		vertices.resize(num_segments);

		const float d_theta = 3.141592f * 2.0f / static_cast<float>(num_segments);

		float theta = getRadian(theta_start);
		for (int i = 0; i < num_segments; ++i)
		{
			vertices[i] = vec2{ radius * cos(theta), radius * sin(theta) };
			theta += d_theta;
		}

		return vertices;
	}

	void drawFilledStar(const RGB & color, const float & outer_radius, const float & inner_radius)
	{
		const int num_segments = 5;

		//Note: not optimized
		const auto outer_vertices = makeRegularConvexPolygon(outer_radius, 90.0f, num_segments);
		const auto inner_vertices = makeRegularConvexPolygon(inner_radius, 90.0f - 360.0f * 0.5f / num_segments, num_segments);

		glColor3fv(&color[0]);
		
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < num_segments; ++i)
		{
			glVertex2fv(outer_vertices[i].data);
			glVertex2fv(inner_vertices[i].data);
			glVertex2fv(inner_vertices[(i+1)%5].data);

			glVertex2f(0.0f, 0.0f);
			glVertex2fv(inner_vertices[i].data);
			glVertex2fv(inner_vertices[(i + 1) % 5].data);
		}

		glEnd();
	}
}
