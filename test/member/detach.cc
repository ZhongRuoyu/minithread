//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: no-threads

// <thread>

// class thread

// void detach();

#include <thread.h>

#include <atomic>
#include <cassert>
#include <system_error>

std::atomic_bool done(false);

class G {
    int alive_;
    bool done_;

   public:
    static int n_alive;
    static bool op_run;

    G() : alive_(1), done_(false) { ++n_alive; }

    G(const G &g) : alive_(g.alive_), done_(false) { ++n_alive; }
    ~G() {
        alive_ = 0;
        --n_alive;
        if (done_) done = true;
    }

    void operator()() {
        assert(alive_ == 1);
        assert(n_alive >= 1);
        op_run = true;
        done_ = true;
    }
};

int G::n_alive = 0;
bool G::op_run = false;

void foo() { done = true; }

int main(int, char **) {
    {
        G g;
        minithread::Thread t0(g);
        assert(t0.joinable());
        t0.detach();
        assert(!t0.joinable());
        while (!done) {
        }
        assert(G::op_run);
        assert(G::n_alive == 1);
    }
    assert(G::n_alive == 0);
    done = false;

    {
        minithread::Thread t0(foo);
        assert(t0.joinable());
        t0.detach();
        assert(!t0.joinable());
        try {
            t0.detach();
        } catch (std::system_error const &) {
        }
        // Wait to make sure that the detached thread has started up.
        // Without this, we could exit main and start destructing global
        // resources that are needed when the thread starts up, while the
        // detached thread would start up only later.
        while (!done) {
        }
    }

    return 0;
}
