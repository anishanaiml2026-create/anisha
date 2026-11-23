
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void notify(const string& message) = 0;

    virtual ~Observer() {}
};

// Email Notification Class
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email
             << ": " << message << endl;
    }
};

// SMS Notification Class
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber
             << ": " << message << endl;
    }
};

// Factory Pattern
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

// Singleton Event Manager
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    // Private constructor
    EventManager() {}

public:
    // Prevent copying
    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    // Get the single EventManager object
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    // Subscribe an observer
    void subscribe(shared_ptr<Observer> observer)
    {
        if (observer != nullptr)
        {
            observers.push_back(observer);
        }
    }

    // Notify all observers
    void triggerEvent(const string& message)
    {
        cout << "\nEvent Triggered: "
             << message << endl;

        cout << "Sending Notifications..." << endl;

        for (const auto& observer : observers)
        {
            observer->notify(message);
        }
    }
};

// Main Function
int main()
{
    // Access Singleton EventManager
    EventManager& manager = EventManager::getInstance();

    // Create notifications using Factory Pattern
    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification(
            "EMAIL",
            "student@gmail.com");

    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification(
            "SMS",
            "9876543210");

    // Subscribe observers
    manager.subscribe(emailUser);
    manager.subscribe(smsUser);

    // Trigger event
    manager.triggerEvent(
        "University examination starts tomorrow!");

    return 0;
}
