

auto foo::foo(sdbusplus::async::context& ctx)
    -> sdbusplus::async::task<>
{
    std::cout << "Do something to " << (uint64_t)this << std::endl;

    constexpr auto systemd =
        sdbusplus::async::proxy()
            .service("org.freedesktop.systemd1")
            .path("/org/freedesktop/systemd1")
            .interface("org.freedesktop.systemd1.Manager");

    this->arch =
        co_await systemd.get_property<std::string>(ctx,
                                                   "Architecture");

    std::cout << "Architecture is " << this->arch << std::endl;

    co_return;
}


