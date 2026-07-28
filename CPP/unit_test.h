#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>

class TestCase {
public:
    TestCase(std::string name, std::function<bool()> func)
        : name_(std::move(name)), func_(std::move(func)) {}

    bool run() const {
        bool passed = func_();
        return passed;
    }

    const std::string& name() const { return name_; }

private:
    std::string name_;
    std::function<bool()> func_;
};

class TestSuite {
public:
    static TestSuite& instance() {
        static TestSuite inst;
        return inst;
    }

    void add_test(const std::string& name, std::function<bool()> func) {
        tests_.emplace_back(name, std::move(func));
    }

    int run_all() {
        int passed = 0;
        int failed = 0;
        for (auto& test : tests_) {
            bool ok = test.run();
            if (ok) {
                std::cout << "[PASS] " << test.name() << "\n";
                ++passed;
            } else {
                std::cout << "[FAIL] " << test.name() << "\n";
                ++failed;
            }
        }
        std::cout << "\nResults: " << passed << " passed, "
                  << failed << " failed, "
                  << tests_.size() << " total\n";
        return failed;
    }

    void clear() { tests_.clear(); }
    size_t count() const { return tests_.size(); }

private:
    TestSuite() = default;
    std::vector<TestCase> tests_;
};

#define ASSERT_TRUE(expr) do { if (!(expr)) { std::cerr << "FAIL at " << __FILE__ << ":" << __LINE__ << ": " #expr << "\n"; return false; } } while(0)
#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))
#define ASSERT_EQ(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_NE(a, b) ASSERT_TRUE((a) != (b))
#define ASSERT_LT(a, b) ASSERT_TRUE((a) < (b))
#define ASSERT_LE(a, b) ASSERT_TRUE((a) <= (b))
#define ASSERT_GT(a, b) ASSERT_TRUE((a) > (b))
#define ASSERT_GE(a, b) ASSERT_TRUE((a) >= (b))
#define ASSERT_THROW(expr, exc) do { bool threw = false; try { expr; } catch (const exc&) { threw = true; } catch (...) {} ASSERT_TRUE(threw); } while(0)

#define TEST(name) void test_##name(); struct Register_##name { Register_##name() { TestSuite::instance().add_test(#name, test_##name); } } reg_##name; void test_##name()

#define RUN_TESTS() return TestSuite::instance().run_all()

#endif
