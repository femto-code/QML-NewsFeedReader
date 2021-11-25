#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <QtTest/QtTest>

class TestCase : public QObject
{
	Q_OBJECT

private slots:
	void testFunction() {
		QCOMPARE( "Test", "Test");
	}
	

	
};

#endif
