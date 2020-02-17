class Application{

};

class Command{	
public:
	virtual ~Command();
	virtual void Excute() = 0;
protected:
	Command();
};

class OpenCommand : public Command{
public:
	OpenCommand(Application*);
	virtual void Execute();
protected:
	virtual const char* AskUser();
private:	
	Application* _application;
	char* _response;
};

OpenCommand::OpenCommand (Application* a){
	_application = a;
}

class Document{
	
};

void OpenCommand::Excute(){
	const char * name = AskUser();
	if(name != 0){
		Document* document = new Document(name);
		_application->Add(document);
		document->Open();
	}
}

class PasteCommand : public Command{
public:
	PasteCommand(Document*);
	virtual void Execute();
private:
	Document* _document;
};

PasteCommand::PasteCommand (Document* doc){
	_document = doc;
}

void PasteCommand::Execute(){
	_document->Paste();
}

template <class Receiver>
void SimpleCommand<Reciver>::Execute(){
	(_receiver->*_action)();
}

MyClass* receiver = new MyClass;

Command* aCommand = new SimpleCommand<MyClass>(receiver, &MyClass::Action);

aCommand->Execute();

class MacroCommand : public Command{
public:
	MacroCommand();
	virtual ~MacroCommand();
	virtual void Add(Command*);
	virtual void Remove(Command*);
	virtual void Execute();
private:
	List<Command*> _cmds;
};

void MacroCommand::Execute(){
	ListIterator<Command*> i(_cmds);
	for(i.first(); !i.IsDone(); i.Next())
		Command* c = i.CurrentItem();
		c->Execute();
}

void MacroCommand::Add(){
	_cmds->Append(c);
}

void MacroCommand::Remove(){
	_cmds->Remove(c);

}
