# Discord Worm Simulator

Educational C++ project that models worm-like behavior against a stubbed Discord API. **This tool must only be used in isolated lab environments for research and teaching purposes.** No real Discord endpoints are contacted by default.

## Ethical Disclaimer
Running malware, even in simulated form, carries risk. Use this repository responsibly and only with systems you own or have explicit permission to test. The authors do not condone misuse.

## Build Instructions
### Requirements
- C++17 compiler
- CMake 3.14+
- Internet access for dependency fetch

### Build & Run
```bash
cmake -S . -B build
cmake --build build
```

Start the stub Discord API:
```bash
python3 stub_server/server.py
```

Run the simulator:
```bash
./build/simulator
```

Create a file named `killswitch` in the working directory to stop execution.

## Docker
```bash
docker build -t worm-sim .
docker run --rm -it -p 5000:5000 worm-sim
```
Use another shell inside the container to run the stub server with `python3 /stub_server/server.py`.

## Testing
```bash
ctest --test-dir build
```

## Security Review Notes
- Uses only standard C++ threading and avoids raw pointers.
- Network communication targets `http://localhost:5000` and should be monitored.
- The file-based kill switch is polled; race conditions are mitigated with atomic flags but should be reviewed.
- No privileged or unsafe system calls are used.

## Extending the Simulator
- **Jitter/Backoff**: modify `RateLimiter` or insert delays in `WormLogic`.
- **Custom Payloads**: adjust payload in `WormLogic::processToken`.
- **Additional Behaviors**: add new modules or extend existing ones following the current style and Doxygen comments.

## Example Tokens
`tokens.txt` contains placeholder tokens. Replace with test tokens as needed.

