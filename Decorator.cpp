class VisualComponent {
public:
	VisualComponent();
	virtual void Draw();
	virtual void Resize();
};

class Decorator : public VisualComponent {
public:
	Decorator(VisualComponent*);
	virtual void Draw();
	virtual void Resize();

private:
	VisualComponent* _component;
};

void Decorator::Draw() {
	_component->Draw();
}

void Decorator::Resize() {
	_component->Resize();
}

class BorderDecorator : public Decorator {
public:
	BorderDecorator(VisualComponent*, int borderwidth);
	virtual void Draw();
private:
	void DrawBorder(int);
private:
	int _width;
};

void BorderDecorator::Draw() {
	Decorator::Draw();
	DrawBorder(_width);
}

window->SetContents(new BorderDecorator(new ScrollDecorator(textview), 1));
