#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#include <SDL3/SDL.h>

#include "../SDL3_Developement_Project/Include/Enums.h"

#include "../SDL3_Developement_Project/Include/DataStructures.h"

class File {
public:
	std::ifstream* file = nullptr;

	File() {
	}
	File(const std::string& filename) {
		file = new std::ifstream(filename, std::ios::binary);
		if (!file) throw std::runtime_error("Cannot open file");
	}
	bool isLoaded() const {
		return file ? true : false;
	}
};

class IMAGE :File {
public:
	int width = 0;
	int height = 0;
	Color** pixelMatrix = nullptr;
	IMAGE() {
	}
	IMAGE(const std::string& fileName) : File(fileName) {
	}

	bool isLoaded() const {
		return File::isLoaded();
	}

	Color** getData() {
		file->seekg(18);
		file->read(reinterpret_cast<char*>(&width), 4);
		file->read(reinterpret_cast<char*>(&height), 4);
		file->seekg(10);
		uint32_t pixelDataOffset = 0;
		file->read(reinterpret_cast<char*>(&pixelDataOffset), 4);
		file->seekg(pixelDataOffset);

		// Each row is padded to a multiple of 4 bytes
		int rowSize = ((24 * width + 31) / 32) * 4;

		std::vector<uint8_t> rowData(rowSize);

		pixelMatrix = (Color**)calloc(height, sizeof(Color*));
		if (!pixelMatrix) {
			printError("Color** Object 'pixelMatrix' allocation", "Failed to allocate 'pixelMatrix' via calloc");
			return nullptr;
		}
		int i;
		for (i = 0; i < height; i++) {
			if (pixelMatrix + i)
				pixelMatrix[i] = (Color*)calloc(width, sizeof(Color));
			else {
				printError("Color* Object 'pixelMatrix[i]' allocation", "Failed to allocate 'pixelMatrix[i]' via calloc");
				return nullptr;
			}
		}
		for (int y = height - 1; y >= 0; --y) {
			file->read(reinterpret_cast<char*>(rowData.data()), rowSize);
			for (int x = 0; x < width; ++x) {
				if (pixelMatrix[y])
					pixelMatrix[y][x] = Color(rowData[x * 3 + 0], rowData[x * 3 + 1], rowData[x * 3 + 2]);
				else {
					printError("Color Object 'pixelMatrix[y][x]' allocation", "Failed to allocate 'pixelMatrix[y][x]' via calloc");
					return nullptr;
				}
			}
		}
		return pixelMatrix;
	}

	~IMAGE() {
		free(file);
		for (int i = 0; i < height; i++)
			free(pixelMatrix[i]);
		free(pixelMatrix);
		width = 0;
		height = 0;
	}
};

class Renderer;

class Object {
protected:
	bool isRendering = true;
public:
	Vector2 position;
	Vector2 size;
	//Constructors
	Object() {
		position = Vector2(0, 0);
		size = Vector2(0, 0);
	}
	Object(Vector2 position, Vector2 size) {
		this->position = position;
		this->size = size;
	}
	//Show Status
	void Show() { isRendering = true; }
	void Hide() { isRendering = false; }
	bool isShown() const { return isRendering; }
	//Render
	virtual void Render(Renderer* renderer) { }
};

void renderRect(SDL_Renderer* renderer, Vector2 position, Vector2 size) {
	SDL_RenderRect(renderer, new SDL_FRect{ position.x, position.y, size.x, size.y });
}

class Renderer {
	SDL_Renderer* renderer = nullptr;
public:
	Renderer() = default;

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	SDL_Renderer* Instance() {
		return renderer;
	}

	SDL_Renderer** InstanceAddress() {
		return &renderer;
	}

	void Delay(int x) {
		SDL_Delay(x);
	}

	void Clear() {
		SDL_RenderClear(renderer);
	}

	void Render() {
		SDL_RenderPresent(renderer);
	}

	void setDrawColor(Color color, Opacity opacity = OPACITY::OPAQUE) {
		SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, opacity.alpha);
	}

	void setScale(float x) {
		SDL_SetRenderScale(renderer, x, x);
	}

	void RenderObject(Object* object) {
		object->Render(this);
	}

	void RenderPoint(Vector2 position, Color color = COLOR::BLACK) {
		setDrawColor(color);
		SDL_RenderPoint(renderer, position.x, position.y);
	}

	void RenderLine(Vector2 start, Vector2 end, Color color = COLOR::BLACK) {
		setDrawColor(color);
		SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
	}

	void RenderFillRect(Vector2 position, Vector2 size, Color color = COLOR::BLACK) {
		setDrawColor(color);
		SDL_FRect rect{ position.x, position.y, size.x, size.y };
		SDL_RenderFillRect(renderer, &rect);
	}

	void RenderCircle(float radius, Vector2 center, Color color = COLOR::BLACK) {
		setDrawColor(color);

		float x = radius;
		float y = 0;
		float err = 0;

		while (x >= y) {
			SDL_RenderPoint(renderer, center.x + x, center.y + y);
			SDL_RenderPoint(renderer, center.x + y, center.y + x);
			SDL_RenderPoint(renderer, center.x - y, center.y + x);
			SDL_RenderPoint(renderer, center.x - x, center.y + y);
			SDL_RenderPoint(renderer, center.x - x, center.y - y);
			SDL_RenderPoint(renderer, center.x - y, center.y - x);
			SDL_RenderPoint(renderer, center.x + y, center.y - x);
			SDL_RenderPoint(renderer, center.x + x, center.y - y);

			if (err <= 0) {
				y++;
				err += 2 * y + 1;
			}
			if (err > 0) {
				x--;
				err -= 2 * x + 1;
			}
		}
	}

	~Renderer() {
		SDL_DestroyRenderer(renderer);
	}
};

class Event {
public:
	EventType type;
	Keys key;
};

template<typename type>
class EventHandler {
	
};
/*
EventHandler - handles events of an Object


*/
class Window {
	SDL_Window* window = nullptr;
	Color backgroundcolor = COLOR::WHITE;

public:
	int Width = 500;
	int Height = 500;
	float Scale = 1;
	Uint32 Delay = 0;

	Renderer renderer;
	Vector<Object*> Objects; // uses memory-safe Vector

	Window() = default;

	Window(const char* title, int width, int height) {
		Create(title, width, height);
	}

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	void Create(const char* title, int width, int height) {
		if (window)
			SDL_DestroyWindow(window);
		Width = width;
		Height = height;
		SDL_CreateWindowAndRenderer(title, width, height, 0, &window, renderer.InstanceAddress());
	}

	void setBackgroundColor(Color color) {
		backgroundcolor = color;
	}

	void Resize(Vector2 size) {
		Resize(size.x, size.y);
	}

	void Resize(int x, int y) {
		Width = x;
		Height = y;
		SDL_SetWindowSize(window, Width, Height);
	}

	void setScale(float x) {
		Scale = x;
		renderer.setScale(Scale);
	}

	void setDelay(int x) {
		Delay = x;
	}

	void RenderObjects() {
		for (int i = 0; i < Objects.Length(); ) {
			if (Objects[i] && Objects[i]->isShown()) {
				renderer.RenderObject(Objects[i]);
				i++;
			}
			else {
				Objects.RemoveAt(i); // safely deletes the object
			}
		}
	}

	void Render() {
		renderer.setDrawColor(backgroundcolor);
		renderer.Clear();
		RenderObjects();
		renderer.Render();
		renderer.Delay(Delay);
	}

	~Window() {
		Objects.ClearPointers(); // deletes all remaining objects
		SDL_DestroyWindow(window);
	}
};

class Point : public Object{
public:
	Color color;
	Point() { }
	Point(Vector2 position, Color color = COLOR::BLACK) {
		this->position = position;
		this->color = color;
	}
	void Render(Renderer* renderer) override {
		renderer->RenderPoint(position, color);
	}
};

class Line : public Object {
public:
	Vector2 end;
	Color color;
	Line( ) {}
	Line(Vector2 position, Vector2 end, Color color = COLOR::BLACK) {
		this->position = position;
		this->end = end;
		this->color = color;
	}
	void Render(Renderer* renderer) override {
		renderer->RenderLine(position, end, color);
	}
};

class Rect : public Object {
public:
	Rect() { }
	Rect(Vector2 Origin, Vector2 Size) {
		position = Origin;
		size = Size;
	}
	void Render(Renderer* renderer) override {

	}
};

class ColorRect : public Object {
public:
	Color color;
	Opacity opacity = OPACITY::OPAQUE;
	ColorRect() {}
	ColorRect(Vector2 Origin, Vector2 Size) {
		position = Origin;
		size = Size;
	}
	ColorRect(Vector2 Origin, Vector2 Size, Color color) {
		position = Origin;
		size = Size;
		this->color = color;
	}
	ColorRect(Vector2 Origin, Vector2 Size, Color color, Opacity opacity) {
		position = Origin;
		size = Size;
		this->color = color;
		this->opacity = opacity;
	}
	void setColor(Color color) {
		this->color = color;
	}
	void setColor(Color color, Opacity opacity) {
		this->color = color;
		this->opacity = opacity;
	}
	void Render(Renderer* renderer) override {
		renderer->RenderFillRect(position, size, color);
	}
};

class Collider : public Rect {
protected:
	bool canCollide = true;
public:
	Collider() {}
	Collider(Vector2 position, Vector2 size) {
		this->position = position;
		this->size = size;
	}
	void Enable() {
		canCollide = true;
	}
	void Disable() {
		canCollide = false;
	}
	bool isColliding(const Collider& collider) const {
		if (canCollide && collider.canCollide)
			return !(position.x + size.x < collider.position.x ||
				position.x > collider.position.x + collider.size.x ||
				position.y + size.y < collider.position.y ||
				position.y > collider.position.y + collider.size.y);
		return false;
	}
};

class ColorCollider : public Collider {
public:
	Color color;
	ColorCollider() {}
	ColorCollider(Vector2 position, Vector2 size, Color color = COLOR::BLACK) {
		this->position = position;
		this->size = size;
		this->color = color;
	}
};

class Circle : public Object {
public:
	float diameter;
	Color color;
	Circle() = default;
	Circle(float diameter, Vector2 center, Color color) {
		position = center - Vector2(diameter);
		this->diameter = diameter;
	}
	Circle(Vector2 position, float diameter, Color color) {
		this->position = position;
		this->diameter = diameter;
	}
	Vector2 getCenter() {
		return position + Vector2(diameter);
	}
	void Render(Renderer* renderer) override {
		renderer->RenderCircle(diameter, getCenter(), color);
	}
};

/*
void RenderCicrle(float diameter, Vector2 center, Color color = COLOR::BLACK) {
		if (diameter < 1)
			return;
		if (diameter == 1) {
			RenderPoint(center, color);
			return;
		}
		setDrawColor(color);
		float x = 0;
		float y = diameter;

		RenderPoint(center, COLOR::BLUE);
		RenderPoint(center + Vector2(diameter), COLOR::GREEN);

		while (x <= 5) {
			Vector2 point(center.x + x, center.y - y);
			Console::Log(std::to_string(x) + ", " + std::to_string(y));
			if (Vector2(x, y).Distance() > + diameter + .5)
				y -= 1;
			else {
				RenderPoint(point, color);
				x++;
			}
		}

		while (Vector2(5., y--).Distance() < diameter + .5) {
			RenderPoint(Vector2(center.x + 5, center.y - y) , color);
		}

		RenderPoint(center + Vector2(0., diameter), COLOR::RED);
		RenderPoint(center - Vector2(0., diameter), COLOR::RED);
		RenderPoint(center + Vector2(diameter, 0.), COLOR::RED);
		RenderPoint(center - Vector2(diameter, 0.), COLOR::RED);
	}
}

*/
template<typename type1, typename type2 >
class Pair {
public:
	type1 first;
	type2 second;
	Pair() { }
	Pair(type1 x, type2 y) {
		first = x;
		second = y;
	}
};

class Graph : public Object {
public:
	LinkedList<LinkedList<Vector2>> values;
	Vector2 size;
	LinkedList<Color> colors;

	Graph() {
		position = Vector2();
	}
	Graph(LinkedList<Vector2> values, Color color = COLOR::BLACK) : Graph() {
		this->values.Add(values);
		this->colors.Add(color);
	}
	Graph(Vector2 position, LinkedList<Vector2>& values, Color color = COLOR::BLACK) : Graph(values, color) {
		this->position = position;
	}

	void Add(LinkedList<Vector2> values, Color color = COLOR::BLACK) {
		this->values.Add(values);
		this->colors.Add(color);
	}

	void FormatSize() {
		Vector2 max;
		for (int i = 0; i < values.Length(); i++) {
			for (int j = 0; j < values[i].Length(); j++) {
				if (values[i][j].x > max.x) max.x = values[i][j].x;
				if (values[i][j].y > max.y) max.y = values[i][j].y;
			}
		}
		size = max;
	}

	void Render(Renderer* renderer) override {

		// Render X-axis baseline at y=0
		renderer->RenderLine(
			Vector2(position.x, position.y + size.y),
			Vector2(position.x + size.x, position.y + size.y),
			COLOR::BLACK
		);
		Node<Color>* color = colors.getRoot();
		// Draw each graph (start from 0, not 1)
		for (int i = 0; i < values.Length(); i++) {

			if (values[i].Length() < 2)
				continue; // cannot draw a line

			Vector2 first = values[i][0];
			Vector2 prev = position + Vector2(first.x, size.y - first.y);
			
			for (int j = 1; j < values[i].Length(); j++) {

				Vector2 point = values[i][j];
				Vector2 next = position + Vector2(point.x, size.y - point.y);

				renderer->RenderLine(prev, next, color->value);
				prev = next;
			}
			color = color->next;
		}
	}
};
//standard function
class Function : public Static_Class {
public:
	static float Standard(float a, float x, float c) {
		return a * x + c;
	}
	static float Quadratic(float x) {
		return x * x;
	}
	static float Sin(float angle) {
		return sinf(angle * M_PI / 180);
	}
	static float Cos(float angle) {
		return cosf(angle * M_PI / 180);
	}
};

class Coordinate_System : public Object{
	float left;
	float right;
	float top;
	float bottom;
public:
	LinkedList<LinkedList<Vector2>> values;
	LinkedList<Color> colors;



	Vector2 getCenter() {
		return position + Vector2(left, top);
	}
	

	void Render(Renderer* renderer) override {
		// Render X-axis baseline at y=0
		renderer->RenderLine(
			Vector2(position.x, position.y + size.y),
			Vector2(position.x + size.x, position.y + size.y),
			COLOR::BLACK
		);
		Node<Color>* color = colors.getRoot();
		// Draw each graph (start from 0, not 1)
		for (int i = 0; i < values.Length(); i++) {

			if (values[i].Length() < 2)
				continue; // cannot draw a line

			Vector2 first = values[i][0];
			Vector2 prev = position + Vector2(first.x, size.y - first.y);
			
			for (int j = 1; j < values[i].Length(); j++) {

				Vector2 point = values[i][j];
				Vector2 next = position + Vector2(point.x, size.y - point.y);

				renderer->RenderLine(prev, next, color->value);
				prev = next;
			}
			color = color->next;
		}
	}
};