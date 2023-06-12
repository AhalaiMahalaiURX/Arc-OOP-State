// Laba3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Context;

class State {
public:
    virtual void Handle(Context& context) = 0;
    virtual ~State() {}
};

class StateRed : public State {
public:
    void Handle(Context& context) override;
};

class StateYellow : public State {
public:
    void Handle(Context& context) override;
};

class StateGreen : public State {
public:
    void Handle(Context& context) override;
};

class Context {
public:
    Context(State* state) : state_(state) {}

    void ChangeState(State* state) {
        delete state_;
        state_ = state;
    }

    void Handle() {
        state_->Handle(*this);
    }

private:
    State* state_;
};

void StateRed::Handle(Context& context) {
    cout << "Red light" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    context.ChangeState(new StateYellow);
}

void StateYellow::Handle(Context& context) {
    cout << "Yellow light" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    context.ChangeState(new StateGreen);
}

void StateGreen::Handle(Context& context) {
    cout << "Green light" << endl;
    this_thread::sleep_for(chrono::seconds(5));
    context.ChangeState(new StateRed);
}

int main() {
    Context context(new StateRed);

    while (true) {
        context.Handle();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
