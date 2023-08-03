#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML/Graphics.hpp>

struct Matrix
{
	float **value;
	int x, y;

	Matrix(int input_x, int input_y);
	~Matrix();

	void identity();
	void display();

	void multiplyMatrix(Matrix &matrix);
	void multiplyConst(float& constant);

	void addMatrix(Matrix& matrix);
	void addConst(float& constant);
};

Matrix::Matrix(int input_x, int input_y) : x(input_x), y(input_y)
{
	value = new float* [x];

	for (int i = 0; i < x; i++)
	{
		value[i] = new float[y];
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			value[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
	delete[] value;
}

void Matrix::identity()
{
	if (x == y)
	{
		for (int i = 0; i < x; i++)
		{
			value[i][i] = 1;
		}
	}
}

void Matrix::display()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			std::cout << value[i][j] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void Matrix::multiplyMatrix(Matrix& matrix)
{
	if (y == matrix.x)
	{
		float** oldValue;

		oldValue = new float* [x];

		for (int i = 0; i < x; i++)
		{
			oldValue[i] = new float[y];
		}

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				oldValue[i][j] = value[i][j];
			}
		}

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < matrix.y; j++)
			{
				value[i][j] = 0;

				for (int k = 0; k < matrix.y; k++)
				{
					value[i][j] += oldValue[i][k] * matrix.value[k][j];
				}
			}
		}

	   delete[] oldValue;

	   y = matrix.y;
	}
	else
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				value[i][j] = -1;
			}
		}
	}
}

void Matrix::multiplyConst(float& constant)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			value[i][j] *= constant;
		}
	}
}

void Matrix::addMatrix(Matrix& matrix)
{
	if (x == matrix.x and y == matrix.y)
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				value[i][j] += matrix.value[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				value[i][j] = -1;
			}
		}
	}
}

void Matrix::addConst(float& constant)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			value[i][j] += constant;
		}
	}
}

void intersection(Matrix& line01, Matrix& line02)
{
	float a1 = line01.value[0][1] - line01.value[1][1];
	float b1 = line01.value[1][0] - line01.value[0][0];
	float c1 = line01.value[0][0] * line01.value[1][1] - line01.value[1][0] * line01.value[0][1];

	float a2 = line02.value[0][1] - line02.value[1][1];
	float b2 = line02.value[1][0] - line02.value[0][0];
	float c2 = line02.value[0][0] * line02.value[1][1] - line02.value[1][0] * line02.value[0][1];

	if ((a1 / a2) == (b1 / b2))
	{
		std::cout << "Lines don't intersect";
	}
	else
	{
		float temp = a1 * b2 - a2 * b1;
		float x = (b1 * c2 - b2 * c1) / temp;
		float y = (a2 * c1 - a1 * c2) / temp;

		std::cout << "Intersection point: (" << x << ", " << y << ")";
	}

	std::cout << std::endl;
}

int main()
{
	// Input
	float coordinate, angle;

	Matrix line01(2, 2);
	Matrix line02(2, 2);

	std::cout << "First line" << std::endl;

	std::cout << "   Enter coordinates of first point" << std::endl;
	std::cout << "	  x: ";
		 std::cin >> coordinate;
		 line01.value[0][0] = coordinate;
	std::cout << "	  y: ";
		 std::cin >> coordinate;
		 line01.value[0][1] = coordinate;

	std::cout << std::endl;

	std::cout << "   Enter coordinates of second point" << std::endl;
	std::cout << "	  x: ";
		 std::cin >> coordinate;
		 line01.value[1][0] = coordinate;
	std::cout << "	  y: ";
		 std::cin >> coordinate;
		 line01.value[1][1] = coordinate;

	std::cout << std::endl;

	std::cout << "Second line" << std::endl;

	std::cout << "   Enter coordinates of first point" << std::endl;
	std::cout << "	  x: ";
		 std::cin >> coordinate;
		 line02.value[0][0] = coordinate;
	std::cout << "	  y: ";
		 std::cin >> coordinate;
		 line02.value[0][1] = coordinate;

	std::cout << std::endl;

	std::cout << "   Enter coordinates of second point" << std::endl;
	std::cout << "	  x: ";
		 std::cin >> coordinate;
		 line02.value[1][0] = coordinate;
	std::cout << "	  y: ";
		 std::cin >> coordinate;
		 line02.value[1][1] = coordinate;

	std::cout << std::endl;

	// Intersection
	intersection(line01, line02);

	std::cout << "Enter angle in degrees: ";
	std::cin >> angle;

	std::cout << std::endl;

	// Rotation
	angle = -angle;

	Matrix rotation(2, 2);
	rotation.value[0][0] = cos(angle * M_PI / 180.);
	rotation.value[0][1] = sin(angle * M_PI / 180.);
	rotation.value[1][0] = -sin(angle * M_PI / 180.);
	rotation.value[1][1] = cos(angle * M_PI / 180.);

	line01.multiplyMatrix(rotation);
	line02.multiplyMatrix(rotation);

	// Intersection
	intersection(line01, line02);

	// Drawing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Matrix", sf::Style::Default, settings);
	window.setFramerateLimit(1);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(15, 15, 15));

		// Axis
		sf::Vertex axisX[] =
		{
			sf::Vertex(sf::Vector2f(0, 720 / 2), sf::Color(128, 128, 128)),
			sf::Vertex(sf::Vector2f(1280, 720 / 2), sf::Color(128, 128, 128))
		};

		window.draw(axisX, 2, sf::Lines);

		sf::Vertex axisY[] =
		{
			sf::Vertex(sf::Vector2f(1280 / 2, 0), sf::Color(128, 128, 128)),
			sf::Vertex(sf::Vector2f(1280 / 2, 720), sf::Color(128, 128, 128))
		};

		window.draw(axisY, 2, sf::Lines);

		// Lines
		sf::Vertex drawLine03[] =
		{
			sf::Vertex(sf::Vector2f(line01.value[0][0] + 1280 / 2, -line01.value[0][1] + 720 / 2), sf::Color(255, 0, 0)),
			sf::Vertex(sf::Vector2f(line01.value[1][0] + 1280 / 2, -line01.value[1][1] + 720 / 2), sf::Color(255, 0, 0))
		};

		window.draw(drawLine03, 5, sf::Lines);

		sf::Vertex drawLine04[] =
		{
			sf::Vertex(sf::Vector2f(line02.value[0][0] + 1280 / 2, -line02.value[0][1] + 720 / 2), sf::Color(255, 0, 0)),
			sf::Vertex(sf::Vector2f(line02.value[1][0] + 1280 / 2, -line02.value[1][1] + 720 / 2), sf::Color(255, 0, 0))
		};

		window.draw(drawLine04, 5, sf::Lines);

		window.display();
	}
}