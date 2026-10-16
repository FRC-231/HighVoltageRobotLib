#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "Debounce.h"

// Debounce and SmartPID are the WPILib-light parts of this library and the
// natural place to start building a suite out. Anything touching TalonFX needs
// a Phoenix6 simulation fixture, which is a bigger lift.

using namespace std::chrono_literals;

TEST(DebounceTest, holdsPreviousValueUntilTheDelayElapses)
{
    HighVoltage::Debounce debounce{50ms};

    debounce.setValue(true);
    EXPECT_FALSE(debounce.getValue());

    std::this_thread::sleep_for(80ms);
    EXPECT_TRUE(debounce.getValue());
}

TEST(DebounceTest, aGlitchShorterThanTheDelayIsRejected)
{
    HighVoltage::Debounce debounce{50ms};

    debounce.setValue(true);
    std::this_thread::sleep_for(10ms);
    debounce.setValue(false);
    std::this_thread::sleep_for(80ms);

    EXPECT_FALSE(debounce.getValue());
}

// ---------------------------------------------------------------------------
// DISABLED: each documents a real defect found while writing this suite.
// ---------------------------------------------------------------------------

// BUG: forceValue() sets last_input and clears is_debouncing, but never
// assigns `output`. So it does not force anything - getValue() keeps returning
// the stale previous output. Worse, the state it leaves behind is stuck: a
// later setValue() with the same value is a no-op because input == last_input,
// so output can never catch up.
// Fix: add `output = input;` to forceValue().
TEST(DebounceTest, DISABLED_forceValueBypassesTheDelay)
{
    HighVoltage::Debounce debounce{50ms};

    debounce.forceValue(true);

    EXPECT_TRUE(debounce.getValue());
}

// BUG: operator bool() returns `output` directly - it neither applies the
// elapsed-time check that getValue() performs, nor takes the mutex. So it can
// report a stale value, and reading it while another thread calls setValue()
// is a data race. The two accessors can disagree.
// Fix: have operator bool() call getValue() (which means dropping const, or
// making the state mutable and the mutex a member mutable).
TEST(DebounceTest, DISABLED_conversionOperatorAgreesWithGetValue)
{
    HighVoltage::Debounce debounce{10ms};

    debounce.setValue(true);
    std::this_thread::sleep_for(30ms);

    EXPECT_EQ(static_cast<bool>(debounce), true);
}
