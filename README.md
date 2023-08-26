## How to Build
1. Update git submodule, it depends on spdlog, tomlplusplus and catch2
3. Build framework library to link in your own project

## How to Use
1. Define the config file
```toml
# test_log.toml

[[logger]]
name = "module_1"
level = "info"

[[logger]]
name = "module_2"
level = "debug"
```
2. Init and Use in cpp
```c++
int main()
{
    frame::Log::Init("test");
    LOG_ERROR(module_1, "test {}", 1);
    LOG_INFO(module_2, "Pi: {}", 3.14);
    return 0;
}

```

3. Please refer the unit test case, For more, Checking https://github.com/gabime/spdlog