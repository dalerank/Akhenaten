log_info("akhenaten: console_commands started")

[console_command=hello] // mission=name support
function mission0_console_command_hello(args) {
    log_info("Hello, " + (args[0] || "World") + "!");
}