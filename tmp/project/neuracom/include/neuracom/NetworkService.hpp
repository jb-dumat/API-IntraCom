//
// Created by Jean-Baptiste Dumat.
//

#pragma once

#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>

namespace net {
    class NetworkService : public boost::asio::io_service {
        using signalCallbackFn = std::function<void()>;

    public:
        NetworkService(const signalCallbackFn &fnCallback = nullptr)
                : boost::asio::io_service(), _signals(*this, SIGINT) {
            _signals.async_wait([&, fnCallback](const boost::system::error_code &, int) {
                if (fnCallback)
                    fnCallback();
                this->stop();
            });
        }

        ~NetworkService() = default;

        // Methods
    public:
        void run() { boost::asio::io_service::run(); }

        void stop() { boost::asio::io_service::stop(); }

        // Fields
    private:
        boost::asio::signal_set _signals;
    };
}