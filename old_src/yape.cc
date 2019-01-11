#include <QApplication>
#include "main_window_view.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  MainWindowView window;
  window.show();

  return app.exec();
}

