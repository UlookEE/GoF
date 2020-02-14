typedef int Topic;
const Topic NO__HELP_TOPIC = -1;
class HelpHandler {
public:
	HelpHandler(HelpHandler* = 0, Topic = NO__HELP_TOPIC);
	virtual bool HasHelp();
	virtual void SetHandler(HelpHandler* Topic);;
	virtual void HandleHelp();
private:
	HelpHandler* _successor;
	Topic _topic;
};

HelpHandler::HelpHandler(HelpHandler*h, Topic t) : _successor(h), _topic(t) {

}

bool HelpHandler::HasHelp() {
	return _topic != NO__HELP_TOPIC;
}

bool HelpHandler::HandleHelp() {
	if (_successor != 0) {
		_successor->HandleHelp();
	}
}

class Widget : public HelpHandler {
protected:
	Widget(Widget* parent, Topic t = NO__HELP_TOPIC);
private:
	Widget* _parent;
};

Widget::Widget(Widget*w, Topic t) : HelpHandler(w, t) {
	_parent = w;
}

class Button : public Widget {
public:
	Button(Widget*d, Topic t = NO__HELP_TOPIC);
	virtual void HandleHelp();
};

Button::Button(Widget* d, Topic t) :Widget(h, t) {

}

void Button::HandleHelp() {
	if (HasHelp()) {

	}
	else {
		HelpHandler::HandleHelp();
	}
}



class Dialog {
public:
	Dialog(HelpHandler*, Topic);
	virtual void HandleHelp();
};

Dialog::Dialog(HelpHandler*h, Topic t) : Widget(0) {
	SetHandler(h, t);
}

void Dialog::HandleHelp() {
	if (HasHelp()) {

	}
	else {
		HelpHandler::HandleHelp();
	}
}
class Application : public HelpHandler {
public:
	Application(Topic t) : HelpHandler(0, t) {

	}
	virtual void HandleHelp();
};

void Application::HandleHelp() {

}


const Topic PRINT_TOPIC = 1;
const Topic PAPER_ORIENTATION_TOPIC = 2;
const Topic APPLICATION_TOPIC = 3;

Application* application = new Application(APPLICATION_TOPIC);
Dialog* dialog = new Dialog(application, PRINT_TOPIC);
Button* button = new Button(dialog, PAPER_ORIENTATION_TOPIC);
