#include "window.hpp"

Window::Window(QWidget *parent) : QWidget(parent),
				  button("button", this) {
	setFixedSize(100, 50);

	button.setGeometry(10, 10, 80, 30);
}
