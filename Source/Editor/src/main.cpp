#include <Editor/Editor.hpp>

int main(int, char**)
{
	Editor::Editor* editor{ new Editor::Editor() };
	editor->Run();
	delete editor;
}