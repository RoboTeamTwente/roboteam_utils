//
// Created by john on 3/4/20.
//

#include <gtest/gtest.h>
#include "roboteam_utils/containers/state_machine.hpp"

#include <vector>

enum class TestEnum {
    Waiting,
    Success,
    Failure,
    Running
};

struct SkillInfo {};

class Base {
public:
    virtual TestEnum update(SkillInfo const& data) noexcept {
        return TestEnum::Success;
    }

    virtual void initialize() noexcept {}

    virtual void terminate() noexcept {}

    virtual uint8_t type_num() noexcept {
        return 0;
    }
};

class Derived : public Base {
public:
    TestEnum update(SkillInfo const& data) noexcept override {
        return TestEnum::Failure;
    }

    uint8_t type_num() noexcept override {
        return 1;
    }
};

TEST(StateMachineTest, test_construction) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };
    // compile means good :)
}

TEST(StateMachineTest, test_skip_n) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    ASSERT_EQ(machine.current_num(), 0);
    machine.skip_n(1);
    ASSERT_EQ(machine.current_num(), 1);
}

TEST(StateMachineTest, test_polymorphism) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    auto elem = machine.get_current();
    machine.skip_n(1);
    auto second = machine.get_current();

    ASSERT_EQ(elem->type_num(), 0);
    ASSERT_EQ(second->type_num(), 1);
}

TEST(StateMachineTest, test_finalize) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    ASSERT_EQ(machine.current_num(), 0);
    machine.terminate();
    ASSERT_EQ(machine.current_num(), 1);
}

TEST(StateMachineTest, test_update) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    ASSERT_EQ(machine.update(SkillInfo()), TestEnum::Success);
    machine.terminate();
    ASSERT_EQ(machine.update(SkillInfo()), TestEnum::Failure);
}

TEST(StateMachineTest, test_invocation_all) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    ASSERT_EQ(machine.update(SkillInfo()), TestEnum::Success);
    machine.terminate();
    ASSERT_EQ(machine.update(SkillInfo()), TestEnum::Failure);
    machine.terminate();

    ASSERT_TRUE(machine.finished());
}

TEST(StateMachineTest, test_for_loop) {
    rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    // no optimize -> volatile
    for (auto volatile& each : machine) {}
}

TEST(StateMachineTest, test_const_for_loop) {
    const rtt::collections::state_machine<Base, TestEnum, SkillInfo> machine{
            Base(),
            Derived(),
    };

    // no optimize -> volatile
    for (auto volatile const& each : machine) {}
}