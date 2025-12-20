

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