#include <iostream>
#include <cstring>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/*****************************************************/
/*
 * Исходные классы: Connection и MyBestSiteEverCreated
 */
/*****************************************************/

class Connection {
public:
    virtual bool login(string& username, string& password) { return false; }
    virtual bool logout(string& username) { return true;}
};

class MyBestSiteEverCreated{
public:
    explicit MyBestSiteEverCreated(Connection* connection) : connection_(connection) {}

    int Init(string& username, string& password) {
        if (!connection_->login(username, password)) {
            cout << "Login Failed\n";
            return -1;
        }
        return 1;
    }
private:
    Connection* connection_;
};

/*****************************************************/
/*
 * TESTING
 */
/*****************************************************/

class MockConnection : public Connection{
public:
    MockConnection() : Connection() {
        // дефолтное значение, сам метод вообще не реализован
        ON_CALL(*this, login(admin_, admin_)).WillByDefault(testing::Return(true));
    }

    MOCK_METHOD(bool, login, (string& username, string& password), (override));
private:
    string admin_ = "admin";
};


class Site : public ::testing::Test {
};


TEST(Site, LoginTest) {
    std::shared_ptr<MockConnection> mck (new MockConnection);

    // создаем сайт, но от заглушки, а не настоящего Connection
    MyBestSiteEverCreated site(&*mck);

    string testing_username = "admin";
    string testing_password = "admin";

    int retValue = site.Init(testing_username, testing_password);
    // сравниваем значения
    EXPECT_EQ(retValue, 1);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
