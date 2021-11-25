import QtQuick 2.5
import QtTest 1.0

ExampleStackPage {
    id: mainpage
    width: 100
    height: 100

    TestCase {
        name: "KeyClick"
        when: windowShown

        function test_key_click() {
            mouseClick( mainpage, 10 , 10 );
            verify(tst_mouseArea.wasClicked, "MouseArea was not clicked!");
        }
    }
}
