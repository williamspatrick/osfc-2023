
#include <com/meta/Poke/aserver.hpp>
#include <com/meta/Poke/error.hpp>

class Poke : public sdbusplus::aserver::com::meta::Poke<Poke>
{
  public:
    Poke(sdbusplus::async::context& ctx, const char* path) :
        sdbusplus::aserver::com::meta::Poke<Poke>(ctx, path)
    {}

    auto method_call(poke_t, auto source)
        -> sdbusplus::async::task<poke_t::return_type>
    {
        last_poke_ = source;
        co_return poke_counts[source]++;
    }

    bool set_property(last_poke_t, auto source)
    {
        if (source == "root")
        {
            std::swap(last_poke_, source);
            return last_poke_ != source;
        }
        throw sdbusplus::com::meta::Poke::Error::PermissionDenied();
    }

  private:
    std::map<last_poke_t::value_type, poke_t::return_type> poke_counts{};
};

/*
 *
 */

int main(int, char**)
{
    sdbusplus::async::context ctx{};
    sdbusplus::server::manager_t manager{ctx, "/"};

    Poke p{ctx, "/com/meta/poke"};

    ctx.spawn([](sdbusplus::async::context& ctx) -> sdbusplus::async::task<> {
        ctx.get_bus().request_name("com.meta.Poke");
        co_return;
    }(ctx));

    ctx.run();

    return 0;
}
