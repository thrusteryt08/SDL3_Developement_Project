class Window {
	SDL_Window* window = nullptr;
	Color backgroundcolor = ColorName::White;

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
	Point(Vector2 position, Color color = ColorName::Black) {
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
	Line(Vector2 position, Vector2 end, Color color = ColorName::Black) {
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
	Opacity opacity = OpacityLevel::Opaque;
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
	ColorCollider(Vector2 position, Vector2 size, Color color = ColorName::Black) {
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
	Graph(LinkedList<Vector2> values, Color color = ColorName::Black) : Graph() {
		this->values.Add(values);
		this->colors.Add(color);
	}
	Graph(Vector2 position, LinkedList<Vector2>& values, Color color = ColorName::Black) : Graph(values, color) {
		this->position = position;
	}

	void Add(LinkedList<Vector2> values, Color color = ColorName::Black) {
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
			ColorName::Black
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