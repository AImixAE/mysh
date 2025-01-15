add_rules("mode.release", "mode.debug")
add_includedirs("includes")

local utils = {}
for _, file in ipairs(os.files("src/utils/*.c")) do
    local name = file:match("src/utils/(.*)%.c")
    utils[name] = file
end

local tools = {}
for _, file in ipairs(os.files("src/tools/*.c")) do
    local name = file:match("src/tools/(.*)%.c")
    tools[name] = file
end

for name, file in pairs(utils) do
    target("shared_" .. name)
        set_kind("shared")
        add_files(file)

    target("static_" .. name)
        set_kind("static")
        add_files(file)
end

target("shared_main")
    set_kind("binary")
    add_files("src/main.c")

    for name, _ in pairs(utils) do
        add_deps("shared_" .. name)
    end

target("static_main")
    set_kind("binary")
    add_files("src/main.c")

    add_ldflags("-static")
    for name, _ in pairs(utils) do
        add_deps("static_" .. name)
    end

for name, file in pairs(tools) do
    target("binary_" .. name)
        set_kind("binary")
        add_files(file)

    target("static_binary_" .. name)
        set_kind("binary")
        add_ldflags("-static")
        add_files(file)
end