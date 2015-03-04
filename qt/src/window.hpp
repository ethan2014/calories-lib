#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>
#include <QPushButton>

class Window : public QWidget {
public:
	explicit Window(QWidget *parent = 0);

private:
	QPushButton button;
};

#endif
