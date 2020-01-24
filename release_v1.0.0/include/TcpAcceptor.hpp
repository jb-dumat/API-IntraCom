#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <memory>

#include "NetworkService.hpp"
#include "TcpSocket.hpp"

namespace net {
    class TCPAcceptor {
        using acceptCallback_t = std::function<void(std::shared_ptr<ISocket>)>;

    public:
        explicit TCPAcceptor(NetworkService &netService);

        ~TCPAcceptor() noexcept = default;

        TCPAcceptor() = delete;

        TCPAcceptor(const TCPAcceptor &) = delete;

        TCPAcceptor(TCPAcceptor &&) = default;

        TCPAcceptor &operator=(const TCPAcceptor &) = delete;

        TCPAcceptor &operator=(TCPAcceptor &&) = delete;

        /*
         * Methods
         */
    public:
        template<typename T>
        T *accept(const acceptCallback_t &callback);

        bool bind(int);

        void close() { _acceptor.close(); }

        /*
         * Fields
         */
    private:
        NetworkService &_netService;
        boost::asio::ip::tcp::acceptor _acceptor;
    };

    template<>
    inline TCPSocket *TCPAcceptor::accept(const acceptCallback_t &callback) {
        auto client = std::make_shared<TCPSocket>(_netService);

        _acceptor.async_accept(client->get(),
                               [this, client, callback](const boost::system::error_code &error) {
                                   if (error) {
                                       return;
                                   }
                                   callback(client);
                                   accept<TCPSocket>(callback);
                               });
        return client.get();
    }
}