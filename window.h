#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "info.h"
#include "input.h"
#include "plotter.h"
#include "statusbar.h"
#include "storage.h"
#include "kernel.h"

class Window : public QMainWindow {
    Q_OBJECT

public:

    Window (int argc, char * argv [], QWidget * parent = nullptr);
    ~Window ();

    void parse_command_line (int argc, char * argv []);

private:

    Info    * m_info;
    Input   * m_input;
    Kernel  * m_kernel;
    Plotter * m_plotter;
    Status  * m_statusbar;

    Storage m_storage;
};

#endif // WINDOW_H
