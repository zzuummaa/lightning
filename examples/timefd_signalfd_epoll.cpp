// need linux kernel >= 5.9 and glibc >= 2.34
#include <linux/close_range.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    auto timer = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC);
    if (timer < 0) {
        std::perror("create timer fd failed.");
        std::exit(EXIT_FAILURE);
    }

    // init timer
    // std::timespec now{};
    //std::timespec period{5, 0};
    //if (::clock_gettime(CLOCK_REALTIME, &now) == -1) {
    //    std::perror("clock_gettime failed.");
    //    std::exit(EXIT_FAILURE);
    //}
    //
    //{
    //    auto ltm = std::localtime(&now.tv_sec);
    //    constexpr int time_buffer_length = 30;
    //    char mbstr[time_buffer_length] = {0x00};
    //    std::strftime(mbstr, time_buffer_length, "%Y-%m-%d %T", ltm);
    //    std::cout << mbstr << ", init timer" << '\n';
    //}

    /*
    It equals to this code when is not setting a TIMER_ABSTIME flag;
    std::timespec start{3, 0};
    ::timerfd_settime(timer, 0, &t, nullptr);
    */
    std::timespec start{3, 0};
    ::itimerspec t =
    {
        //.it_interval = period,
        .it_value = start
    };
    if (::timerfd_settime(timer, 0, &t, nullptr) != 0) {
        std::perror("set timer failed.");
        std::exit(EXIT_FAILURE);
    }

    ::sigset_t sig{};
    ::sigemptyset(&sig);
    ::sigaddset(&sig, SIGINT);
    ::sigaddset(&sig, SIGHUP);
    auto sigfd = ::signalfd(-1, &sig, SFD_NONBLOCK|SFD_CLOEXEC);
    if (sigfd < 0) {
        std::perror("create signalfd failed.");
        std::exit(EXIT_FAILURE);
    }
    if (::sigprocmask(SIG_SETMASK, &sig, nullptr) != 0) {
        std::perror("set signal mask failed.");
        std::exit(EXIT_FAILURE);
    }

    // init an epoll instance
    auto ep = ::epoll_create1(EPOLL_CLOEXEC);
    if (ep < 0) {
        std::perror("create epoll fd failed.");
        std::exit(EXIT_FAILURE);
    }

    ::epoll_event ev;
    ::memset(&ev, 0, sizeof(::epoll_event));
    ev.events = EPOLLIN|EPOLLET;
    ev.data.fd = timer;
    if (::epoll_ctl(ep, EPOLL_CTL_ADD, timer, &ev) != 0) {
        std::perror("add timer to epoll failed.");
        std::exit(EXIT_FAILURE);
    }
    ev.data.fd = sigfd;
    if (::epoll_ctl(ep, EPOLL_CTL_ADD, sigfd, &ev) != 0) {
        std::perror("add sigfd to epoll failed.");
        std::exit(EXIT_FAILURE);
    }

    while (true) {
        constexpr int max_events = 3;
        epoll_event ep_events[max_events];
        auto n = ::epoll_wait(ep, ep_events, max_events, -1);
        if (n < 0) {
            std::perror("epoll wait failed.");
            std::exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; ++i) {
            if ((ep_events[i].events & EPOLLIN) && ep_events[i].data.fd == timer) {
                uint64_t count{};
                auto length = ::read(timer, &count, sizeof(uint64_t));
                std::cout << "read " << length << " bytes\n";
                if (length == -1) {
                    std::perror("timer read failed.");
                    std::exit(EXIT_FAILURE);
                }
                if (length != sizeof(uint64_t)) {
                    std::perror("timer read failed.");
                    std::exit(EXIT_FAILURE);
                }
                auto tt = std::time(nullptr);
                auto ltm = std::localtime(&tt);
                constexpr int time_buffer_length = 30;
                char mbstr[time_buffer_length] = {0x00};
                std::strftime(mbstr, time_buffer_length, "%Y-%m-%d %T", ltm);
                std::cout << mbstr << ", timer fired: " << count << '\n';
            }
            if ((ep_events[i].events & EPOLLIN) && ep_events[i].data.fd == sigfd) {
                ::signalfd_siginfo sinfo{};
                while (true) {
                    auto length = ::read(sigfd, &sinfo, sizeof(::signalfd_siginfo));
                    if (length == -1 && errno == EAGAIN) {
                        break;
                    }
                    if (length != sizeof(::signalfd_siginfo)) {
                        std::perror("sigfd read failed.");
                        std::exit(EXIT_FAILURE);
                    }
                    std::cout << "got signal: " << ::strsignal(sinfo.ssi_signo) << '\n';
                    if (sinfo.ssi_signo == SIGINT) {
                        std::cout << "Received SIGINT, program will exit.\n";
                        ::close_range(3, ~0u, 0);
                        return 0;
                    }
                }
            }
        }
    }
}