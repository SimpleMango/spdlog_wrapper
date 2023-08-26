# Spdlog Wrapper
You want to use spdlog quickly and conveniently?  
1. Laying out the FileLog frame quickly  
2. Using conveniently with configure

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
3. Output log file content
```javascript
# log/test/module_1_2023-08-26_14:15:22.log
[23-08-26 14:15:22.146118][E][4465730][LogTest.cpp:13] test 1

# log/test/module_2_2023-08-26_14:15:22.log
[23-08-26 14:15:22.146151][I][4465730][LogTest.cpp:14] Pi: 3.14
```

4. Please refer the unit test case. For more, please checking https://github.com/gabime/spdlog