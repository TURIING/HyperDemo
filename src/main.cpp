/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2025/3/8 00:15
* @version: 1.0
* @description: 
********************************************************************************/

#include "app/Application.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	Application app;

	a.exec();
}