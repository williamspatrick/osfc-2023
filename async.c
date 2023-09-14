#include <systemd/sd-bus.h>

struct foo_state_t;

void foo(sd_bus *bus, struct foo_state_t *f)
{
    printf("Doing something to %p...\n", f);

    sd_bus_call_method_async(
            bus, NULL,
            "org.freedesktop.systemd1",
            "/org/freedesktop/systemd1",
            "org.freedesktop.DBus.Properties",
            "Get",
            foo_next, f,
            "ss",
            "org.freedesktop.systemd1.Manager",
            "Architecture");
}

int foo_next(sd_bus_message *reply,
             struct foo_state_t *f,
             sd_bus_error *err)
{
    char *arch = NULL;

    sd_bus_message_enter_container(reply, 'v', &arch);
    printf("Architecture is %s\n", arch);

    f.arch = strdup(arch);

    return 1;
}





