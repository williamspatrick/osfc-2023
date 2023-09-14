
#include <com/meta/Poke/client.hpp>

#include <iostream>
#include <string>
#include <vector>

auto multi_poke(sdbusplus::async::context& ctx,
                std::vector<std::string> sources) -> sdbusplus::async::task<>
{
    auto poke_server = sdbusplus::client::com::meta::Poke(ctx)
                           .service("com.meta.Poke")
                           .path("/com/meta/poke");

    for (auto& source : sources)
    {
        auto count = co_await poke_server.poke(source);
        std::cout << source << " has poked " << count << " times." << std::endl;
    }
}

/*
 *
 */

int main(int, char**)
{
    sdbusplus::async::context ctx{};

    ctx.spawn(multi_poke(ctx, {"tom", "jerry"}));
    ctx.spawn(
        sdbusplus::async::execution::just() |
        sdbusplus::async::execution::then([&ctx]() { ctx.request_stop(); }));
    ctx.run();

    return 0;
}
