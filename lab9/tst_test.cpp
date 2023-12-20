#include <..\objects\objects.h>
#include <QtTest>
class TestTest : public QObject
{
    Q_OBJECT

public:
    TestTest();
    ~TestTest();

private slots:
    void testCase1();
    void test_suv();
    void test_sedan();
    void test_bus();
    void test_route();
    void test_bicycle();

};
TestTest::TestTest()
{

}

TestTest::~TestTest()
{

}

void TestTest::testCase1()
{

}
void TestTest::test_suv()
{
Suv suv;
QCOMPARE(suv.getFuelLevel(),80);
QVERIFY(suv.drive(100));
QCOMPARE(suv.getFuelLevel(),55);
suv.refuel();
QCOMPARE(suv.getFuelLevel(),80);
QVERIFY(suv.drive(100));
QCOMPARE(suv.getMilage(),200);
QCOMPARE(suv.getFuelLevel(),55);
QVERIFY(!suv.drive(500));
QCOMPARE(suv.getMilage(),200);
QCOMPARE(suv.getFuelLevel(),55);
suv.refuel();

}
void TestTest::test_sedan()
{
Sedan sedan;
QCOMPARE(sedan.getFuelLevel(),60);
QVERIFY(sedan.drive(100));
QCOMPARE(sedan.getFuelLevel(),50);
sedan.refuel();
QCOMPARE(sedan.getFuelLevel(),60);
QVERIFY(sedan.drive(100));
QCOMPARE(sedan.getMilage(),200);
QCOMPARE(sedan.getFuelLevel(),50);
QVERIFY(sedan.drive(500));
QCOMPARE(sedan.getMilage(),700);
QCOMPARE(sedan.getFuelLevel(),0);
sedan.refuel();

}
void TestTest::test_bus()
{
Bus bus;
QCOMPARE(bus.getFuelLevel(),100);
QVERIFY(bus.drive(100));
QCOMPARE(bus.getFuelLevel(),66);
bus.refuel();
QCOMPARE(bus.getFuelLevel(),100);
QVERIFY(bus.drive(100));
QCOMPARE(bus.getMilage(),200);
QCOMPARE(bus.getFuelLevel(),66);
QVERIFY(!bus.drive(200));
QCOMPARE(bus.getMilage(),200);
QCOMPARE(bus.getFuelLevel(),66);
bus.refuel();
}

void TestTest::test_bicycle()
{
    Bicycle bicycle;
    QVERIFY(bicycle.drive(100));
    QVERIFY(bicycle.drive(100));
    QCOMPARE(bicycle.getMilage(),200);
    QVERIFY(bicycle.drive(500));
    QCOMPARE(bicycle.getMilage(),700);
    QVERIFY(bicycle.drive(500));
    QCOMPARE(bicycle.getMilage(),1200);
}
void TestTest::test_route()
{
Route route;
IVehicle* vehicles[1] = {new Bicycle};
IVehicle* vehicle = vehicles[0];
route.addPoint(RoutePoint(100,0,"point1"));
route.addPoint(RoutePoint(0,200,"point2"));
route.addPoint(RoutePoint(300,400,"point3"));
route.run(vehicle);
QCOMPARE(vehicle->getMilage(),583);
}


QTEST_APPLESS_MAIN(TestTest)

#include "tst_test.moc"
